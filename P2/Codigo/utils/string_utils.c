#include "string_utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bool.h"

bool isDigit(char *string){
  return isdigit(string[0]);
}

bool startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? FALSE : strncmp(pre, str, lenpre) == 0;
}

char * strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
    	if(*s != '\t' && *s != '\n') {
    		*p2++ = *s++;
    	} else {
    		++s;
    	}
    }
    *p2 = '\0';
    return p2;
}