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
void removeSpaces(char* text);
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
  char line[255];
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

  verifyConfig(buffer, num);


  free(buffer);
  fclose(file);

}

int verifyConfig(const char** config, int lines)
{
  char *cards[26] = {"REDA", "RED2", "RED3", "RED4", "RED5", "RED6", "RED7", "RED8", "RED9",
  "RED10", "REDJ", "REDQ", "REDK", "BLACKA", "BLACK2", "BLACK3", "BLACK4", "BLACK5",
  "BLACK6", "BLACK7", "BLACK8", "BLACK9", "BLACK10", "BLACKJ", "BLACKQ", "BLACKK"};
  
  char *verify = "1";
  char* line;
  for (int i = 0; i<=lines; i++)
  {
    line = config[i];
    removeSpaces(line); 
  }

  //test:
   if (config[0]==config[1]){
     printf("tru");
   }



  for (int i = 0; i<lines; i++)
  {
    for (int j = 0; j<26; j++)
    {
      if (config[i] == cards[j])
      { 
        strcpy(cards[j], verify);
        
      } 
      else if(config[i] != cards[j] &&  (int)config[i] != EOF)
      {
       
        printf("invalid");

         //printf("%s, %s", config[1], cards[7]);
        return -1;
        
      }
      else if((int)config[i] == EOF)
      {
        printf("valid");
        return -1;
      }   
        //realloc(cards[j],sizeof(verify)); 
        
      }   

    printf("Valid");
    return 1;

  }
  
  return 1;

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
