/* alloc.h: external specs for alloc/freef package */

/* call this once before any alloc()'s */
void initalloc(void);

/* allocate a block of n bytes of memory and return its address, guaranteed
 * to be a multiple of 4 ("4-byte-aligned") to make sure that the
 * provided address can be used as an int * pointer for 32-bit ints.
 */
char *alloc(int n);

/* free a previously alloc'd block */
void freef(char *p);

/* for debugging */
void dumpfree(void);
