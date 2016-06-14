#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chat.h"
//Function Prototypes
void fatal(char *); //func for fatal errors
void *ec_malloc(unsigned int);  //error checked malloc() wrapper
void *ec_realloc(char *str, unsigned int);
char *rmtrails(char *buf);

char *input(){

  size_t size = 1;

  char *str = (char *) ec_malloc (size * sizeof(char));

  char c;
  int i = 0;
  
  while(1){
    c = getc(stdin);
    
    //realloc memory by +1 each time, we use less mem this way
    //hopefully this will cause a heapoverflow inb4 instead of a bufferoverflow

    if(i >= size){
      size++;
      str = (char *) ec_realloc(str, size*sizeof(char)); 
    }
    if(c == '\n' || c == EOF) {
      str[i] == '\0';
      break;
    }else{
       str[i] = c;
    }
  i++;

  }

  return str;
}


char *addchar(const char *msg, const char *b){
  size_t len = strlen(msg);
  char *ret = (char*)ec_malloc(len * sizeof(char));
  *ret = '\0';
  return strcat(strcat(ret,msg), b);
}

//An error-checked malloc() wrapper function
void *ec_malloc(unsigned int size){
  void *ptr;
  ptr = malloc(size);
  if(ptr == NULL)
    fatal("in ec_malloc() on memory allocation");
  return ptr;
}

void *ec_realloc(char* str, unsigned int size){
  void *ptr;
  ptr = realloc(str, size);
  if(ptr == NULL)
    fatal("in ec_realloc() on memory re-allocation");
  return ptr;
}

void fatal(char *message){
  char error_message[100];

  strcpy(error_message, "[!!] Fatal Error ");
  strncat(error_message, message, 83);
  perror(error_message);
  exit(-1);
}


