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
void readInput(*char);
//void verify_config(char*);


int main(int argc, char const *argv[])
{
 
 char argu= argv[1]

 readInput(*argu);

  return 0;
}


void readInput(char *argu ){

 int num = 0;
  int index = 0;
  FILE *file;
  char line[64];
  char **buffer;
  file=fopen(*argu,"r");

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
  

  //verify_config(&buffer);


  free(buffer);
  fclose(file);

}




// void verify_config(char *buffer){
// int index = 0;
// int x=0;
// while((int)buffer[index] != EOF)
// {
//   while(&buffer[x] != '\n')
//   {
//     if (&(buffer)[x] >= "a" && &(buffer)[x] <= "z")
//     {
//       if (buffer[index][x] >= "a" && buffer[index][x] <= "z")
//       {
//         printf("error");
//       }
//       x++;
//     }
//   index++;
//   }
// }
