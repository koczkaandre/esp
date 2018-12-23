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
struct Card
{
  // Red == 1; Black == 2
  int color;
  // A,J,Q,K == 1,11,12,13
  int value;
  struct Card *next;
};

typedef struct Card Card;


int readInput(const char *fileName, Card **stack0, Card **stack1, Card **stack2, Card **stack3, Card **stack4);
int verifyConfig(char** config, int lines);
void removeSpaces(char* text);
void truncAllLines(char** config, int lines);
int containsCard(char* card, char** cards);
int buildStacks(char** config, int lines,  Card **stack0, Card **stack1, Card **stack2, Card **stack3, Card **stack4);
Card getCard(char* card, char** cards);
int addCardToStack(Card **stack, Card **card);
Card *allocCard(Card card);

//------------------------------------------------------------------------------
/// The main function, calls other functions
///
/// @return 0 if successful
//

int main(int argc, const char *argv[])
{
  Card *stack0;
  Card *stack1;
  Card *stack2;
  Card *stack3;
  Card *stack4;
  Card *stack5;
  Card *stack6;
  if(argc == 2)
  {
    readInput(argv[1], &stack0, &stack1, &stack2, &stack3, &stack4);
  }
  else
  {
    printf("[ERR] Usage: ./ass3 [file-name]\n");
    return 1;
  }
  printf("\n");
  printf("value%d\n", stack0);
  printf("value%d\n", stack0->next);
  do
  {
    printf("value%d\n", stack0->value);
    stack0 = stack0->next;
  }
  while(stack0->next!=stack0);
  return 0;
}

//-----------------------------------------------------------------------------
/// reads the input textfile with the cards 
///
/// @param fileName char pointer to the name of the input file from argv
//

int readInput(const char *fileName, Card **stack0, Card **stack1, Card **stack2, Card **stack3, Card **stack4)
{
  int num = 0;
  int index = 0;
  FILE *file;
  char line[255];
  char **buffer;
  file = fopen(fileName,"r");
  if(file == 0)
  {
      printf("[ERR] Invalid file!\n");
      return 3;
  }

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
  if(verifyConfig(buffer, num) == -1)
  {
      printf("[ERR] Invalid file!\n");
      free(buffer);
      return 3;
  }
  buildStacks(buffer, num, stack0, stack1, stack2, stack3, stack4);
  free(buffer);
  fclose(file);
  return 0;
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


//-----------------------------------------------------------------------------
/// Adds cards to the stack
///
/// @param Card stack double pointer
/// @param Card card double pointer 
//

int addCardToStack(Card **stack, Card **card)
{
  if(!(*stack))
  {
    (*card)->next = *(card);
    (*stack) = (*card);
    return 0;
  }
  do
    {
      if((*stack)->next == (*stack))
      {
        (*card)->next = (*card);
        (*stack)->next = (*card);
        return 0;
      }
      if((*stack)->next!=(*stack))
      {
        stack = &((*stack)->next);

      }
    }
  while((*stack)->next);

  return -1;
}

Card *allocCard(Card card)
{
  Card *helpCard;
  helpCard = (Card*)malloc(sizeof(Card));
  helpCard->color = card.color;
  helpCard->value = card.value;
  return helpCard;
}


//-----------------------------------------------------------------------------
/// Builds the card statcks 
///
/// @param char double pointer to the config file 
/// @param Card stack0 double pointer to stack 0
/// @param Card stack1 double pointer to stack 1
/// @param Card stack2 double pointer to stack 2
/// @param Card stack3 double pointer to stack 3
/// @param Card stack4 double pointer to stack 4
///
/// @return 0 if successful
//

int buildStacks(char** config, int lines,  Card **stack0, Card **stack1, Card **stack2, Card **stack3, Card **stack4)
{
  char* cards[26] = {"REDA", "RED2", "RED3", "RED4", "RED5", "RED6", "RED7", "RED8", "RED9",
                     "RED10", "REDJ", "REDQ", "REDK", "BLACKA", "BLACK2", "BLACK3", "BLACK4", "BLACK5",
                     "BLACK6", "BLACK7", "BLACK8", "BLACK9", "BLACK10", "BLACKJ", "BLACKQ", "BLACKK"};

  Card help;
  Card *pointhelp;
  int helpCount = 0;
  printf("\n");
  for(int i = 0; i < lines; i++)
  {
    if(containsCard(config[i], cards)==-2)
    {
      continue;
    }
    if(helpCount == 0)
    {
      help = getCard(config[i], cards);
      if(!(pointhelp = allocCard(help)))
      {
        printf("[ERR] Out of memory.\n");
      }
      addCardToStack(stack1, &pointhelp);
    }

    if((helpCount == 1)||(helpCount == 4))
    {
      help = getCard(config[i], cards);
      if(!(pointhelp = allocCard(help)))
      {
        printf("[ERR] Out of memory.\n");
      }
      addCardToStack(stack2, &pointhelp);
    }

    if((helpCount == 2)||(helpCount == 5)||(helpCount==7))
    {
      help = getCard(config[i], cards);
      if(!(pointhelp = allocCard(help)))
      {
        printf("[ERR] Out of memory.\n");
      }
      addCardToStack(stack3, &pointhelp);
    }


    if((helpCount == 3)||(helpCount == 6)||(helpCount==8)||(helpCount == 9))
    {
      help = getCard(config[i], cards);
      if(!(pointhelp = allocCard(help)))
      {
        printf("[ERR] Out of memory.\n");
      }
      addCardToStack(stack4, &pointhelp);
    }

    if(helpCount > 9)
    {
      printf("hallo");
      help = getCard(config[i], cards);
      if(!(pointhelp = allocCard(help)))
      {
        printf("[ERR] Out of memory.\n");
      }
      addCardToStack(stack0, &pointhelp);
    }
    helpCount++;
  }
  return 0;
}


//-----------------------------------------------------------------------------
/// Function to determine a given card
///
/// @param char cards double pointer to all of the cards
/// @param char card pointer 
///
/// @return ncard returns the card type
//


Card getCard(char* card, char** cards)
{
  Card ncard;
  switch (containsCard(card, cards))
  {
    case 0:
      ncard.color = 1;
      ncard.value = 1;
      break;
    case 1:
      ncard.color = 1;
      ncard.value = 2;
      break;
    case 2:
      ncard.color = 1;
      ncard.value = 3;
      break;
    case 3:
      ncard.color = 1;
      ncard.value = 4;
      break;
    case 4:
      ncard.color = 1;
      ncard.value = 5;
      break;
    case 5:
      ncard.color = 1;
      ncard.value = 6;
      break;
    case 6:
      ncard.color = 1;
      ncard.value = 7;
      break;
    case 7:
      ncard.color = 1;
      ncard.value = 8;
      break;
    case 8:
      ncard.color = 1;
      ncard.value = 9;
      break;
    case 9:
      ncard.color = 1;
      ncard.value = 10;
      break;
    case 10:
      ncard.color = 1;
      ncard.value = 11;
      break;
    case 11:
      ncard.color = 1;
      ncard.value = 12;
      break;
    case 12:
      ncard.color = 1;
      ncard.value = 13;
      break;
    case 13:
      ncard.color = 2;
      ncard.value = 1;
      break;
    case 14:
      ncard.color = 2;
      ncard.value = 2;
      break;
    case 15:
      ncard.color = 2;
      ncard.value = 3;
      break;
    case 16:
      ncard.color = 2;
      ncard.value = 4;
      break;
    case 17:
      ncard.color = 2;
      ncard.value = 5;
      break;
    case 18:
      ncard.color = 2;
      ncard.value = 6;
      break;
    case 19:
      ncard.color = 2;
      ncard.value = 7;
      break;
    case 20:
      ncard.color = 2;
      ncard.value = 8;
      break;
    case 21:
      ncard.color = 2;
      ncard.value = 9;
      break;
    case 22:
      ncard.color = 2;
      ncard.value = 10;
      break;
    case 23:
      ncard.color = 2;
      ncard.value = 11;
      break;
    case 24:
      ncard.color = 2;
      ncard.value = 12;
      break;
    case 25:
      ncard.color = 2;
      ncard.value = 13;
      break;
  }
  return ncard;
}

char convertCards(Card card)
{
  
  char* cards_converted[26] = {"RA", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9",
                     "R10", "RJ", "RQ", "RK", "BA", "B2", "B3", "B4", "B5",
                     "B6", "B7", "B8", "B9", "B10", "BJ", "BQ", "BK"};
  
  char* cardstring;
  switch (card.color)
  {
    case 1:
      
      switch (card.value)
      {
        case 1:
        cardstring = cards_converted[0];
        break;
        case 2:
        cardstring = cards_converted[1];
        break;
        case 3:
        cardstring = cards_converted[2];
        break;
        case 4:
        cardstring = cards_converted[3];
        break;
        case 5:
        cardstring = cards_converted[4];
        break;
        case 6:
        cardstring = cards_converted[5];
        break;
        case 7:
        cardstring = cards_converted[6];
        break;
        case 8:
        cardstring = cards_converted[7];
        break;       
        case 9:
        cardstring = cards_converted[8];
        break;
        case 10:
        cardstring = cards_converted[9];
        break;
        case 11:
        cardstring = cards_converted[10];
        break;
        case 12:
        cardstring = cards_converted[11];
        break;
        case 13:
        cardstring = cards_converted[12];
        break;
      }


      break;
    case 2:
    switch (card.value)
    {
        case 1:
        cardstring = cards_converted[13];
        break;
        case 2:
        cardstring = cards_converted[14];
        break;
        case 3:
        cardstring = cards_converted[15];
        break;
        case 4:
        cardstring = cards_converted[16];
        break;
        case 5:
        cardstring = cards_converted[17];
        break;
        case 6:
        cardstring = cards_converted[18];
        break;
        case 7:
        cardstring = cards_converted[19];
        break;
        case 8:
        cardstring = cards_converted[20];
        break;       
        case 9:
        cardstring = cards_converted[21];
        break;
        case 10:
        cardstring = cards_converted[22];
        break;
        case 11:
        cardstring = cards_converted[23];
        break;
        case 12:
        cardstring = cards_converted[24];
        break;
        case 13:
        cardstring = cards_converted[25];
        break;
    } 
    break;
  }
  return cardstring;



}