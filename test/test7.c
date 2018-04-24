#include <string.h>
#ifdef CTRL
# include <stdlib.h>
#else
# include "malloc.h"
#endif

int		main()
{
    memcpy(malloc(256), "hello\n\xff\x1\x0", 8);
#ifndef CTRL
    show_alloc_mem_ex();
#endif
	return (0);
}
