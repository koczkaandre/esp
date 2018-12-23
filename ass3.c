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


//------------------------------------------------------------------------------
/// Function prototypes
//

void readInput(const char *fileName);
int verifyConfig(char** config, int lines);
void removeSpaces(char* text);
void truncAllLines(char** config, int lines);
int containsCard(char* card, char** cards);

//------------------------------------------------------------------------------
/// The main function, calls other functions
///
/// @return 0 if successful
//

int main(int argc, const char *argv[])
{
  readInput(argv[1]);
  return 0;
}

//-----------------------------------------------------------------------------
/// reads the input textfile with the cards 
///
/// @param fileName char pointer to the name of the input file from argv
//

void readInput(const char *fileName)
{
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
  truncAllLines(buffer, num);
  verifyConfig(buffer, num);


  free(buffer);
  fclose(file);

}


//-----------------------------------------------------------------------------
/// Verifies the config file
///
/// @param config char double pointer to the single elements of the config file
/// @param lines integer for the sum of lines in the config file
/// @return -1 if config is invalid
/// @return 0 if the function ran sucessfully 
//

int verifyConfig(char** config, int lines)
{
  char* cards[26] = {"REDA", "RED2", "RED3", "RED4", "RED5", "RED6", "RED7", "RED8", "RED9",
  "RED10", "REDJ", "REDQ", "REDK", "BLACKA", "BLACK2", "BLACK3", "BLACK4", "BLACK5",
  "BLACK6", "BLACK7", "BLACK8", "BLACK9", "BLACK10", "BLACKJ", "BLACKQ", "BLACKK"};

  int containedcards[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < lines; i++)
    {
      if(containsCard(config[i], cards)==-1)
      {
        printf("ERROR");
        return -1;
      }
      if(containsCard(config[i], cards)!=-2)
      {
        containedcards[containsCard(config[i], cards)] += 1;
      }
    }

    for(int i = 0; i < 26; i++)
    {
            printf("%d", containedcards[i]);

    }

    for(int i = 0; i < 26; i++)
    {
        if(containedcards[i]!=1)
        {
            printf("ERROR");
            return -1;
        }
    }


  return 0;

}

//-----------------------------------------------------------------------------
/// Verifies if a given card is valid 
///
/// @param card char pointer to a given card
/// @param cards char double pointer for all of the cards
/// @return -2
/// @return i
/// @return -1
//

int containsCard(char* card, char** cards)
{
  if(strcmp(card, "")==0)
  {
    return -2;
  }
  for(int i = 0; i < 26; i++)
  {
    if(strcmp(card, cards[i])==0)
    {
      return i;
    }
  }
  return -1;
}


//-----------------------------------------------------------------------------
/// Calls removeSpaces function for every single line in the config file
///
/// @param lines integer to get the sum of lines in the config file
/// @param config char double pointer for all the elements in the config
// 


void truncAllLines(char** config, int lines)
{
    for(int i = 0; i < lines; i++)
    {
        removeSpaces(config[i]);
    }
}

//-----------------------------------------------------------------------------
/// Removes whitespaces from the lines in the config file
///
/// @param text char pointer to the text that needs the whitespaces 
//  to be removed
//

void removeSpaces(char* text)
{
    char* currChar = text;
    char* nextChar = text;
    while(*nextChar != 0)
    {
        *currChar = *nextChar++;
        if(*currChar != ' ')
        {
            if(*currChar == '\n')
            {
                *currChar = 0;
            }
            currChar++;
        }
    }
    *currChar = 0;
}
