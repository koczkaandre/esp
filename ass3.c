//-----------------------------------------------------------------------------
// ass2.c
//
// Caesar enryppting program 
//
// Group: 4, study assistant Mathias Kahr
//
// Authors: Matthias Raber 01610242
//          Andre Koczka 11777088
// 
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  
FILE *f;
  char c;
  f=fopen(argv[1],"rt");

  while((c=fgetc(f))!=EOF)
  {
    printf("%c",c);
  }
  fclose(f);





  return 0;
}
