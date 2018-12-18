//-----------------------------------------------------------------------------
// ass3.c
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
#include <string.h>


//char verify_config(char);
char store(char);
char verify_config(char**);



int main(int argc, char const *argv[])
{
  int num = 0;
  int index = 0;
  FILE *file;
  char line[64];
  char **buffer;
  file=fopen(argv[1],"r");

  while(fgets(line, sizeof(line), file))
  {
    num++;
  }
  rewind(file);

  buffer = (char**)malloc(sizeof(line)*sizeof(char));


  for(int mem = 0;mem<num;mem++)
  {
    buffer[mem] = (char*)malloc(sizeof(line)*sizeof(char));
  }

  while(fgets(line, sizeof(line), file))
    {
      strcpy(buffer[index], line);
      index++;
    }
  
  for(int x = 0;x<index;x++) printf("%s", buffer[x]);

verify_config(buffer);


  free(buffer);
  fclose(file);

  return 0;
}



char verify_config(char** buffer){
int index = 0;
int x=0;
while((int)buffer[index] != EOF)
{
  while(buffer[index][x] != '\n')
  {
    if (buffer[index][x] >= "a" && buffer[index][x] <= "z")
    {
    printf("error");
    }
    x++;
  }
  index++;
} 

}