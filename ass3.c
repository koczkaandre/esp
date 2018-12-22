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
int verifyConfig(const char** config, int lines);
void removeSpaces(char* text)
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

  verifyConfig(buffer, lines);


  free(buffer);
  fclose(file);

}

int verifyConfig(const char** config, int lines)
{
  int   i;
  char* line;
  for (int i = 0; i<=lines; i++)
  {
    line = config[i];
    removeSpaces(line);
    
  }


}

void removeSpaces(char* text)
{
    char* currChar = text;
    char* nextChar = text;
    while(*nextChar != 0)
    {
        *currChar = *nextChar++;
        if(*currChar != ' ')
            currChar++;
    }
    *currChar = 0;
}