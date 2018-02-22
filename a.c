typedef long long _long;
int main(void) {
_long x,y,m=-1LL;
x = 0xf000000000000000LL;
y = 0x7000000000000000LL;
printf("%llx + %llx = %llx\n",x,y,(x+y));
return 0;
}
