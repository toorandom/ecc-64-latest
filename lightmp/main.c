#include "lightmp.h"
int main(int argc, char **argv) {
/*
char a[] = "\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
char b[] = "\x01";
*/
bint *x,*y,*z,*w;
char *a,*b;

a = argv[1];
b = argv[2]; 
x = bint_alloc(100 ,POSITIVE);
y = bint_alloc(100,POSITIVE);
z = bint_alloc(100,POSITIVE);
w = bint_alloc(100,POSITIVE);
x=atobint((void *)a,(size_t)strlen(a), POSITIVE,x);
y=atobint((void *)b,(size_t)strlen(b), POSITIVE,y);
printf("obase=16\nibase=16\n");
bint_debug(x,"x");
bint_debug(y,"y");
bint_sub(x,y,z);
bint_mul(x,y,w);
printf("x-y\nx+y\nquit\n");
bint_debug(z,"x-y");
bint_debug(w,"x*y");
return 0;
}

