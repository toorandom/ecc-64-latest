#include "lightmp.h"
#define DOUBLE_WORD_INVERT(x) ((x<<32) | (x>>32))
int main(void) {
char a[] = "\x41\x42\x43\x44\x45\x46\x47\x48\xaa\xbb\xcc\xdd\xf1\xf2\xf3\xf4";
_ulong *b = (_ulong *)&a;
int *c;
b[0] = INVERT64(b[0]);
b[1] = INVERT64(b[1]);

b[0] = DOUBLE_WORD_INVERT(b[0]);
b[1] = DOUBLE_WORD_INVERT(b[1]);

printf("%016lx\n",b[0]);
printf("%016lx\n",b[1]);

c = (int *)b;

printf("%08x\n",c[0]);
printf("%08x\n",c[1]);
printf("%08x\n",c[2]);
printf("%08x\n",c[3]);





}
