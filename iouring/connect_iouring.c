#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <liburing.h>
#include <arpa/inet.h>

#define THROW_ERROR(fmt, ...)   do { \
    printf("\t\tERROR:" fmt " in func %s at line %d of file %s with errno %d: %s\n", \
    ##__VA_ARGS__, __func__, __LINE__, __FILE__, errno, strerror(errno)); \
    return -1; \
} while (0)

static int ENTRIES = 128;
static struct io_uring ring;
static int local_errno = 0;

static void sigint_handler();
static int get_completion_and_print(struct io_uring *ring);

static int init_test_server(struct sockaddr_in *serv_addr) {
    // Init server socker. Bind but don't listen.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        THROW_ERROR("server_routine, error creating socket");
    }

    serv_addr->sin_family = AF_INET;
    serv_addr->sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t servaddr_len = sizeof(struct sockaddr_in);
    if (bind(sockfd, (struct sockaddr *)serv_addr, servaddr_len) < 0) {
        THROW_ERROR("server_routine, error binding socket");
    }

    // Get the addresses the socket is bound to because the port is chosen by the network stack.
    if (getsockname(sockfd, (struct sockaddr *)serv_addr, &servaddr_len) < 0) {
        THROW_ERROR("getsockname() failed");
    }

    return 0;
}

// Return the client fd
static int init_test_client() {
    // Init client socket
    struct sockaddr_in client_addr = {};
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0) {
        THROW_ERROR("server_routine, error creating socket");
    }

    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t addr_len = sizeof(struct sockaddr_in);
    if (bind(clientfd, (struct sockaddr *)&client_addr, addr_len) < 0) {
        THROW_ERROR("server_routine, error binding socket");
    }

    // Get the addresses the socket is bound to because the port is chosen by the network stack.
    if (getsockname(clientfd, (struct sockaddr *)&client_addr, &addr_len) < 0) {
        THROW_ERROR("getsockname() failed");
    }

    return clientfd;
}

static int test_io_uring_connect(int clientfd, struct sockaddr_in *serv_addr) {
    struct io_uring_sqe *sqe;
    sqe = io_uring_get_sqe(&ring);

    io_uring_prep_connect(sqe, clientfd, (const struct sockaddr *)serv_addr,
                          sizeof(struct sockaddr_in));

    int sub_num = io_uring_submit_and_wait(&ring, 1);
    printf("submit number = %d\n", sub_num);

    int ret = get_completion_and_print(&ring);
    if (ret != 1 || local_errno != ECONNREFUSED) {
        THROW_ERROR("get completion and print error");
    }

    return 0;
}

int main() {
    struct io_uring_params params;
    int client_socket;

    if (geteuid()) {
        THROW_ERROR("You need root privileges to run this program.\n");
    }

    memset(&params, 0, sizeof(params));
    params.flags |= IORING_SETUP_SQPOLL;
    params.sq_thread_idle = 120000; // 2 minutes in ms

    int ret = io_uring_queue_init_params(ENTRIES, &ring, &params);
    if (ret < 0) {
        THROW_ERROR("iouring init failure");
    }

    signal(SIGINT, sigint_handler);

    struct sockaddr_in serv_addr = {};
    ret = init_test_server(&serv_addr);
    if (ret < 0) {
        THROW_ERROR("init test server failure");
    }

    int clientfd = init_test_client();
    if (clientfd < 0) {
        THROW_ERROR("prepare client failure");
    }

    // Try connect twice. Expect to get the ECONNREFUSED errno same as sync "connect()".
    ret = test_io_uring_connect(clientfd, &serv_addr);
    if (ret < 0) {
        THROW_ERROR("test connect failure");
    }

    printf("second try\n");

    ret = test_io_uring_connect(clientfd, &serv_addr);
    if (ret < 0) {
        THROW_ERROR("test connect failure");
    }

    printf("TEST PASSED!\n");
    return 0;
}

void sigint_handler() {
    printf("^C pressed. Shutting down.\n");
    io_uring_queue_exit(&ring);
    exit(0);
}


int get_completion_and_print(struct io_uring *ring) {
    struct io_uring_cqe *cqe;
    int ret = io_uring_wait_cqe(ring, &cqe);
    /* Mark this completion as seen */
    io_uring_cqe_seen(ring, cqe);

    if (ret < 0) {
        perror("io_uring_wait_cqe");
        return -1;
    }

    if (cqe->res < 0) {
        /* The system call invoked asynchonously failed */
        printf("io_uring_wait_cqe: %s\n", strerror(-cqe->res));
        local_errno = -cqe->res;
        return 1;
    }

    printf("connect request complete, ret = %d\n", cqe->res);
    return 0;
}
