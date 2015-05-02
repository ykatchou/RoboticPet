#ifndef SHELL_H
#define SHELL_H

#include "Common.h"
#include "logger.h"
#include "string.h"

void shell_print(char* str){
  log(str);
}

void shell_println(char* str){
  logline(str);
}

char shell_read(){
  return Serial.read();
}

/**
 * Lis une chaîne de maximum 80 caractères. 
 * (retourne donc maxi 81 caractères car fini par \0)
 */
char* shell_readline(){
  char buffer[81];
  const char eol='\n';

  int idx=0;
  boolean again=true;
  while(again && idx<80){
    char tmp = Serial.read(); 
    buffer[idx]=tmp;

    if(tmp == eol){
      again=false;
    }
    idx++;
  }

  buffer[idx]='\0';
  return buffer;
}

/**
 * Configure le shell.
 */
void shell_configure(){
}

void shell_launch(){

}

#endif




