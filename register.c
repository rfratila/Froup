#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CONTENT_LENGTH getenv("CONTENT_LENGTH")
FILE *file;
int unique;
int userInterval = 0;
int checkUnique(char *name){//check if username is unique
   int length = strlen(name) +1;
   char line[300];
   fgets(line, 299, file);
   while(!feof(file)){
      //printf("line (%s)<br />",line);
      int i =0;
      while(line[i] != '\n'){
         i++;
      }
      line[i] = '\0';
      if(userInterval%4 == 0){//so it only compares when it needs to
         printf("line %d | ",userInterval);
         printf("comparison of Username (%s): %d with (%s)<br />",name, strcmp(name, line), line);
         if(strcmp(name, line) == 0){//a same username is found
            return 0;
         }
      }
      userInterval++;
      fgets(line, 299, file);
   }
   return 1;//it is unique
}

int profile(char *tok){
   char attribute[strlen(tok)];
   int i;
   if(tok[0] == '\n')printf("it is null");
   for (i=0; i < strlen(tok); i++){ 
      if(tok[i] != '='){
         attribute[i] = tok[i];
      }
      else break;
   }
   attribute[i] = '\0';
   i++;
   int j = 0;
   if(strcmp(attribute, "uName") == 0){//check username
      for(; tok[i] != '\0'; i++){
         attribute[j] = tok[i];
         j++;
      }
      attribute[j] = '\0';
     //printf("%s unique? %d<br />",attribute, checkUnique(attribute));
      if(checkUnique(attribute)){ 
           unique = 1;
           fputs(attribute, file);
           fputs("\n", file);
        }
      else unique = 0;
      return 0;
   }
   if(unique){
      if(strcmp(attribute, "pWord") == 0){//password
         for(; tok[i] != '\0'; i++){
            attribute[j] = tok[i];
            j++;
         }
         attribute[j] = '\0';
         fputs(attribute, file);
         fputs("\n", file);
         return 0;
      } 
      else if(strcmp(attribute, "fName") == 0){//full name
         for(; tok[i] != '\0'; i++){
            if(tok[i] == '+') attribute[j] = ' ';
            else attribute[j] = tok[i];
            j++;
         }
         attribute[j] = '\0';
         fputs(attribute, file);
         fputs("\n", file);
         return 0;
      }
      else if(strcmp(attribute, "uJob") == 0){//job description
         for(; tok[i] != '\0'; i++){
            if(tok[i] == '+') attribute[j] = ' ';
            else attribute[j] = tok[i];
            j++;
         }
         attribute[j] = '\0';
         fputs(attribute, file);
         fputs("\n", file);
         return 0;
      }
   }
}

int main(void){
   int n;
   file = fopen("users.txt", "a+");//so we can read and append to file
   char *token = NULL;
   char *inputString = NULL;
   printf("Content-Type:text/html\n\n");//to print to browser
   printf("<html>");
   printf("<body>");
   if(CONTENT_LENGTH != NULL){
      n = atoi(CONTENT_LENGTH);
      char manString[n];
      if((inputString = malloc(sizeof(char) * (n+1))) != NULL){
         if((fread(inputString, sizeof(char), n, stdin)) == n){
            strcpy(manString, inputString);
            printf("str length: %d and string is: %s.<br />",n, manString);
            token = strtok(manString, "&");
            while(token != NULL){
               profile(token);
               token = strtok(NULL, "&");
            }
         }
      }
   }
   printf("</body>");
   printf("</html>");
   fclose(file);
   return 0;
}
