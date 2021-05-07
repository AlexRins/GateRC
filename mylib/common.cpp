#include <stdlib.h>
#include <stdio.h>
#include "common.h"


// Convert Dec string to int
int StrDecToInt(char *str, int len){
    int cint;
    char arr[6];
    for (int i = 0;i < len;i++)
    {
        arr[i] = *str++;
    }
    arr[len] = '\0';
    cint  = (int)strtol(arr,0,10);
    return cint;
}


// Convert hex string to int
int StrHexToInt(char *str, int len) {
    int cint;
    char arr[6];
    for (int i =0;i<len;i++)
    {
        arr[i] = *str++;
    }
    arr[len] = '\0';
    cint  = (int)strtol(arr,0,16); 
    return cint;
    }