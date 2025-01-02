/* compile

 -lvppinfra -lpthread -lrt -lm
*/

#include "vppinfra/time.h"
#include "vppinfra/cache.h"
#include "vppinfra/error.h"

#include <vppinfra/bihash_8_8.h>
#include <vppinfra/bihash_template.h>

#include <vppinfra/bihash_template.c>


/* A session  */
typedef struct {
	uword session_key;
	u32 my_session_cookie;
	
	/* Hash table used to look up session */
	BVT(clib_bihash) session_by_session_key;

	/* command buffer */
	u8 * cmdbuf;
} my_main_t;

my_main_t my_main;

clib_error_t *
test_add (my_main_t * mm, uword key, u32 cookie)
{
	BVT(clib_bihash_kv) kv, kv_return;
	BVT(clib_bihash) * h;
	int rv;
	
	h = &mm->session_by_session_key;

	/* See if the item already exists */
	kv.key = key;
	rv = BV(clib_bihash_search) (h, &kv, &kv_return);
	
	/* Yes, it exists */
	if (rv == 0)
		{
		return clib_error_return (0, "Key %lld already exists", key);
		}
	
	/* Add it ... */
	kv.key = key;
	kv.value = cookie;
	rv = BV(clib_bihash_add_del) (h, &kv, 1 /* is_add */);

	if (rv > 0)
		return clib_error_return (1, "added !");
	
	return 0;
}

clib_error_t *
test_del (my_main_t * mm, uword key)
{
	BVT(clib_bihash_kv) kv, kv_return;
	BVT(clib_bihash) * h;
	int rv;
	
	h = &mm->session_by_session_key;
	kv.key = key;

	rv = BV(clib_bihash_add_del) (h, &kv, 0 /* is_add */);

	if (rv < 0)
		return clib_error_return (0, "del failed!");
	
	return 0;
}

clib_error_t *
test_find (my_main_t * mm, uword key)
{
	BVT(clib_bihash_kv) kv, kv_return;
	BVT(clib_bihash) * h;
	int rv;
	
	h = &mm->session_by_session_key;

	kv.key = key;
	rv = BV(clib_bihash_search) (h, &kv, &kv_return);
	
	/* Yes, it exists */
	if (rv == 0)
		{
		return clib_error_return (0, "Found Key %lld cookie %ld ",
					key, (u32) kv_return.value);
		}
	
	else
		return clib_error_return (0, "Key %lld not found", key);
}

void
test_ui (my_main_t * mm)
{
	unformat_input_t _i, * i = &_i;
	u32 cookie;	
	uword key;
	clib_error_t * e;
	int len;

	vec_validate (mm->cmdbuf, 4095);

	while (1)
		{
			fformat (stdout, "cmd: ");
			fflush (stdout);
			
			if (fgets ((char *)mm->cmdbuf, vec_len(mm->cmdbuf), stdin) == 0)
				break;
			len = strlen ((char *)mm->cmdbuf);
			unformat_init_string (i, (char *)mm-cmdbuf, len);
			
			e = 0;
			if (unformat (i, "add key %llu cookie %lu",
					&key, &cookie))
				{
					e = test_add (mm, key, cookie);
				}
			else if (unformat (i, "del key %llu", &key))
				{
					e = test_del (mm, key);
				}
			else if (unformat (i, "find key %llu", &key))
				{
					e = test_find (mm, key);
				}
			else if (unformat (i, "dump verbose"))
				{
					fformat (stdout, "%U", BV(format_bihash),
						&mm->session_by_session_key, 1 /* verbose */);
				}
			else if (unformat (i, "dump"))
				{
					fformat (stdout, "%U", BV(format_bihash),
						&mm->session_by_session_key, 0 /* verbose */);
				}
			else if (unformat (i, "quit") || unformat (i, "q"))
				{
					return;
				}
			else
				e = clib_error_return (0, "unknow input '%U'",
							format_unformat_error, i);
			if (e)
				clib_error_report(e);
		}

}

static clib_error_t *
my_main_init (void /* normally, vlib_main_t * vm */)
{
	my_main_t * mm = &my_main;
	BVT(clib_bihash) * h;

	/* set up clib heap, not needed in real data plane code */
	clib_mem_init (0, 128ULL<<20);

	h = &mm->session_by_session_key;
	BV(clib_bihash_init) (h, "test", 4 /* bucket */, 128ULL<<20);
	return 0;
}

int
main(int argc, char **argv)
{	
	my_main_init();
	
	test_ui(&my_main);
		
	return 0;
}
