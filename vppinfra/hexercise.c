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




int 
main(int argc, char **argv)
{	
	my_main_init();
	
	test_ui(&my_main);
		
	return 0;
}
