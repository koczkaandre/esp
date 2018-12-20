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
void readInput(const char *fileName);
//void verify_config(char*);


int main(int argc, const char *argv[])
{
  readInput(argv[1]);
  return 0;
}


void readInput(const char *fileName){

  int num = 0;
  int index = 0;
  FILE *file;
  char line[64];
  char **buffer;
  file = fopen(fileName,"r");

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

  for(int x = 0;x<num;x++)
  {
      printf("%s", buffer[x]);
  }


  free(buffer);
  fclose(file);

}

void verify_config(const char* config, int lines)
{

}

void countWords(const char* line)
{
    int count = 0;
    int i;
    int len = strlen(line);
    char prevChar;
    if(len > 0)
    {
        prevChar = line[0];
    }
    for(i = 0; i <= len; i++)
    {
        
    }
}
