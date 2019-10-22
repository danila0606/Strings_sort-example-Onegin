#include "info.h"

int main() {

    printf("|-------------------------------------------------------------|\n");
    printf("| This program sorts the rows in alphabetical order and rhyme |\n");
    printf("|                                                             |\n");
    printf("| Made by Danila Zubko                              22.10.2019|\n");
    printf("|                                                (C)for \"Ilab\"|\n");
    printf("|-------------------------------------------------------------|\n");

    char *text = 0;
    int lines = 0;

    FILE *f = fopen("text.txt", "rb");
    if (f == NULL) {
        printf("File not found. Check the file location");
        return 1;
    }
    text = getstr(f);
    if (!text) {
        printf ("an error occurred while reading the file\n");
        return 2;
    }
    fclose(f);

    change (text, &lines);

    char** str_ptrs = pointer_maker (text, lines);

    char** str_ptrs_copy = (char**) calloc (lines + 1, sizeof(char*));
    assert (str_ptrs_copy != 0);

    FILE *f_ch = fopen("CHANGE_TEXT.txt", "w");

    ptr_copy (str_ptrs_copy, str_ptrs);

    qsort (str_ptrs_copy, lines, sizeof(char **), compare);
    fprintf(f_ch,"AT_THE_BEGINNING_OF_THE_LINE_SORT\n");
    writer_text (f_ch, str_ptrs_copy, VERSESIZE);

    ptr_copy (str_ptrs_copy, str_ptrs);

    qsort (str_ptrs_copy, lines, sizeof(char **), compare_end);
    fprintf(f_ch,"AT_THE_END_OF_THE_LINE_SORT\n");
    writer_text (f_ch, str_ptrs_copy, VERSESIZE);

    fprintf(f_ch,"WITH_OUT_SORT\n");
    writer_text (f_ch, str_ptrs, VERSESIZE);

    free(text);
    free(str_ptrs);
    free(str_ptrs_copy);

    return 0;
}