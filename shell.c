#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>

//This is the string lentgh we'll admit
#define BUFFERSIZE 200

//We'll use this function to know if we have a funcion in our string
int hasAPrefix(char const *, char const *);
//We will use this to store the conditions for each statement
void menu(char *);
//With this function we will make our cd command
void cdCommand(char const *);
//To make readable our, path we have to casth(?) our cwd
char *getcwd(char *buf, size_t size);

char *ourPath;

int main(){

  
  char cwd[PATH_MAX];
  char initialString[BUFFERSIZE];
  ourPath = getcwd(NULL,0);
  //char *token;
  //token = strtok(initialString," ");
  char *prompt = "[VEML] V 0.1.6:~";
  char *a = ">";
  while(1){
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("\n%s %s %s",prompt,ourPath,a);
  }
  //We send variable and to save, size and protocol?
   fgets(initialString,BUFFERSIZE,stdin);
   //token = strtok(initialString," ");
   //We send all the string to our menu function
   menu(initialString); 
   //token=strtok(NULL," ");
  // printf("\n%s",token);

  }
     
  return 0;
}

void menu(char *menu){
  //We will use this pointer to save our string and then divide split it
  char *getOptions;
  //We say each space it's a delimiter to split our string 
  getOptions = strtok(menu," ");
  //We compare each first element of our elements to know wich command we have to use
  if(hasAPrefix(getOptions,"pwd") == 0){
    printf("\n%s\n",getcwd(NULL,0));   
  }
  else if(hasAPrefix(getOptions,"cd") == 0){
    getOptions = strtok(NULL," ");
    cdCommand(getOptions);
    
    //printf("%s siguiente",getOptions);
  }
  else{
    puts("Instruccion no encontrada");
  }
}

int hasAPrefix(char const *p, char const *q)
{
    int i = 0;
    for(i = 0;q[i];i++)
    {
      if(p[i] != q[i])
        return -1;
    }
    return 0;
}

void cdCommand(char const *thisToken){
  //ourPath = "CAMBIAMOS PERROS";    
//  thisToken = strtok(NULL," ")
  if(thisToken == NULL){
    printf("hey man");
  }

  printf("%s",thisToken);
  char tempPath[BUFFERSIZE];
  strcpy(tempPath, ourPath); 
  int i = 0;
  int j = 0;
  char *p = strtok (tempPath, "/");
  char *array[BUFFERSIZE];
  char newPath[BUFFERSIZE];
  if(hasAPrefix(thisToken,"..") == 0){
    while (p != NULL){
     array[i++] = p;
     p = strtok (NULL, "/");
     j+=1;
    }
    strcpy(newPath,"/");
    for (i = 0; i < j-1;i++){
      if(array[i] != NULL){
        strcat(newPath,array[i]);
        if(i < j-2){
        strcat(newPath,"/");
        }
      }
    }
    strcpy(ourPath,newPath);
  }
  //To get direct from parent folder we have to identify if the user just use CD, there are two possible cases, NULL or empty
  else if(thisToken == NULL || *thisToken != '\0' ){
   // puts("IREMOS AL DIRECTORIO PADREEEEEE");
    strcpy(ourPath,"/");
  }
  else{
    puts("\nDirectorio no encontrado amiguito\n");
  }
  
}
