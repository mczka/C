/* compile

 -lvppinfra -lpthread -lrt -lm
*/

#include "vppinfra/clib.h"
#include "vppinfra/vec.h"
#include "vppinfra/format.h"


int 
main(int argc, char **argv)
{	
	u32 * foo = 0;
	int i;
	
	for (i=0; i < 10; i++)
		{
		vec_add1(foo, i);
		fformat(stdout, "[%d] foo is 0x%llx\n", i, foo);
		}
	
	fformat(stdout, "vec_len(foo) = %d\n", vec_len(foo));
	
	vec_delete(foo, 1 /*element*/, 0 /*starting at index */);
	
	fformat(stdout, "after deleting element 0 ...\n");
	
	fformat(stdout, "vec_len(foo) = %d\n", vec_len(foo));
	
	for (i=0; i < vec_len(foo); i++)
		fformat(stdout, "[%d] %d\n", i, foo[i]);
	
	fformat(stdout, "reset vector length\n");
	
	vec_reset_length(foo);
	
	fformat(stdout, "add a single element\n");
	
	vec_add1(foo, 1);
	
	for (i=0; i < vec_len(foo); i++)
		fformat(stdout, "[%d] %d\n", i, foo[i]);
	
	vec_free(foo);
	
	fformat(stdout, "after vec_free, foo is now 0x%llx\n", foo);
	
	return 0;
}
