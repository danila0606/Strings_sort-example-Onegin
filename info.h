#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define VERSESIZE 2
#define RIFM 3

char* getstr (FILE *f);
void change (char* text, int *lines);
char** pointer_maker (char * text, int lines);
void ptr_copy (char** ptr1, char ** ptr2);
int compare (const void * str1, const void * str2);
void writer_text (FILE * file, char ** text, int verse_size);
int compare_end (const void * str1, const void * str2);

