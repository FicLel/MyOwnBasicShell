#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>
#include <pwd.h>
#include <ctype.h>
#include <stdlib.h>

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

void lsCommand(char const *);

void createDirectoryCommand(char *);

void clearCommand();

char *preproccessString(char *);

int main(){

  
  char cwd[PATH_MAX];
  char initialString[BUFFERSIZE];
  ourPath = getcwd(NULL,0);
  //char *token;
  //token = strtok(initialString," ");
  char *prompt = "[VEML] V 0.4.0:~";
  char *a = ">";
  while(1){
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("\n%s%s %s",prompt,ourPath,a);
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
    
  }
  else if(hasAPrefix(getOptions,"mkdir") == 0){
    getOptions = strtok(NULL," ");
    createDirectoryCommand(getOptions);
    
  }

  else if(hasAPrefix(getOptions,"ls") == 0){
    lsCommand(ourPath);
  }
  else if(hasAPrefix(getOptions,"clear") == 0){
    clearCommand();
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
    perror("FALLO EN INSTRUCCION INEXPERADO");
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

void lsCommand(char const *pathName){
  //We have to use a structure to get the folder files
  struct dirent* currentDirectory;
  struct stat myStat;
  struct tm lt;
  struct passwd *pwd; //USER
  
  DIR* directory = opendir(pathName);
 
  if(directory != NULL){
   while((currentDirectory = readdir(directory))){
    //puts(currentDirectory->d_name);
    //With ls 
    if (currentDirectory->d_name[0] != '.' && currentDirectory->d_name[strlen(currentDirectory->d_name)-1] != '~') {
      printf("%s ",currentDirectory->d_name);
    }
   }
  }
  else{
    perror("Error en la lectura");
  }
  
}
//Clear command
void clearCommand(){
  int i = 0;
  //In place to use \n to print blank space we use a Regex
  for(i=0;i<100;){
    printf("\e[1;1H\e[2J");
    i+=1;
  }
}
void createDirectoryCommand(char *directoryName){
   char tempPath[BUFFERSIZE];
   strcpy(tempPath, ourPath);
   struct stat st = {0};
   strcat(tempPath,directoryName);
  char *result = preproccessString(directoryName);
   if (stat(tempPath, &st) == -1) {
      
     mkdir(result, 0700);
     free(result);
    }else{
      perror("No se puede crear el directorio");
    }
}

char *preproccessString(char *str) {
    // Create a new string of the size of the input string, so this might be bigger than needed but should never be too small
      char *result = malloc(sizeof(str));
      // Array of allowed chars with a 0 on the end to know when the end of the array is reached, I don't know if there is a more elegant way to do this
      // Changed from array to string for sake of simplicity
      char *allowedCharsArray = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
      // Initalize two integers
      // i will be increased for every char in the string
      int i = 0;
      // j will be increased every time a new char is added to the result
      int j = 0;
      // Loop over the input string
      while (str[i] != '\0') {
        // l will be increased for every char in the allowed chars array
        int l = 0;
        // Loop over the chars in the allowed chars array
        while (allowedCharsArray[l] != '\0') {
          // If the char (From the input string) currently under consideration (index i) is present in the allowed chars array
            if (allowedCharsArray[l] == (str[i])) {
              // Set char at index j of result string of char currently under consideration
              result[j] = (str[i]);
              j++;
            }
            l++;
        }
        i++;
      }
    return result;
  }
