#include <stdio.h>

main() {
  char a[3][5]={"KOR","HUM","RES"};
  char b[3][5];
  char*pa[]={a[0],a[1],a[2]};
  int n=sizeof(pa)/sizeof(pa[0]);
  printf("%d\n", sizeof(pa));
  printf("%d\n", sizeof(pa[0]));
  for(int i=0; i<n;i++)
    printf("%c", pa[i][i]);
}


