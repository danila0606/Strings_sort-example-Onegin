#include "info.h"


/**
 * getstr определяет размер файла и выделяет динамическую память под весь текст
 *
 * @param[in] f Указатель на файл с исходным текстом
 * @return Указатель на массив с текстом
 */
char* getstr (FILE *f) {
    unsigned long long lenght = 0;

    fseek(f, 0, SEEK_END);
    lenght = ftell(f); /// количество байтов занимаемых текстом (1 байт =  1 char символ)

    char *text = (char *) calloc(lenght + 1, sizeof(char));
    if (text == 0)
        return 0;

    fseek(f, 0, SEEK_SET);

    unsigned long long len = fread (text, sizeof(char), lenght, f); ///len - количество прочитанных символов
    if (len != lenght) {  ///если размер текста не совпадет с прочитанным количеством символом, выдается предупреждение об ошибке считывания
        text = 0;
    }

    return text;
}

/**
 * change заменяет /r и /n на /0 для более удобной работы с текстом,
 * а также считает количество строк.
 *
 * @param text
 * @param lines
 */
void change (char* text, int *lines) {
    int inword= 0; /// переменная показывает находимся ли мы сейчас в новой строке или достигли ее конца

    for (int i = 0; text[i] != '\0'; i++) {
        text[i] = (char)tolower(text[i]);
        if (text[i] == '\r')
            text[i] = '\0';
        if (text[i] == '\0'  && inword == 1) {
            (*lines)++;
            inword = 0;
        }
        if ((text[i] != '\0') && (inword == 0) && (isalpha(text[i]))!= 0)
            inword = 1;
    }
    (*lines)++;
}

/**
 * pointer_maker Создает массив указателей на начала строк
 *
 * @param text
 * @param lines
 * @return
 */
char** pointer_maker (char * text, const int lines) {
    char **str_ptrs = (char **) calloc(lines, sizeof(char *));

    int inword = 1;
    int j = 0;

    for (int i = 0; j < lines; i++) {
        if ((text[i] != '\0') && (inword != 0) && (isalpha(text[i]) != 0)) {
            inword = 0;
            str_ptrs[j++] = &text[i];
        }
        if (text[i] == '\0') {
            inword = 1;
        }
    }
    return str_ptrs;
}

/**
 * ptr_copy копирует массив указателей на начала строк в другой массив указателей
 *
 * @param ptr_to
 * @param ptr_from
 */
void ptr_copy (char** ptr_to, char ** ptr_from) {
    for (int i = 0; ptr_from[i] != 0; i++) {
        ptr_to[i] = (char *) ptr_from[i];
    }
}

/**
 * compare - компаратор для qsort'а для сортировки по началу строк
 *
 * @param str1
 * @param str2
 * @return
 */
int compare (const void * str1, const void * str2) {
    int i = 0;
    int j = 0;
    char ** str_1 = (char**)str1;
    char ** str_2 = (char**)str2;
    unsigned long long str1_len = strlen(*str_1);
    unsigned long long str2_len = strlen(*str_2);

    while (((*str_1)[i] != '\0') && ((*str_2)[j] != '\0')) {
        for ( ; isalpha ((*str_1)[i]) == 0; ) { /// Пропуск символов отличных от букв
            if (++i >= str1_len)
                break;
        }
        for ( ; isalpha ((*str_2)[j]) == 0; ) {
            if (++j >= str2_len)
                break;
        }
        if ((*str_1)[i] > (*str_2)[j]) {
            return 1;
        }
        else if ((*str_1)[i] == (*str_2)[j]) {
            i++;
            j++;
        }
        else if ((*str_1)[i] < (*str_2)[j])
            return -1;
    }
    return 0;
}

/**
 * writer_text - выводит в файл текст
 *
 * @param file
 * @param text
 * @param verse_size
 */
void writer_text (FILE * file, char ** text, int verse_size) {

    for (int i = 0, j = 1; text[i] != 0; i++, j++) {
        fprintf(file,"%s\n", text[i]);
        if (verse_size != 1) {
            if (j % verse_size == 0) {
                fprintf(file, "\n");
                j = 0;
            }
        }
    }
}

/**
 *  compare_end - компаратор для qsort'а для сортировки по концу строки
 *
 * @param str1
 * @param str2
 * @return
 */
int compare_end (const void * str1, const void * str2) {
    int inrifm = 0;
    unsigned long long i = 0, j = 0;
    char ** str_1 = (char**)str1;
    char ** str_2 = (char**)str2;

    i = strlen(*str_1);
    j = strlen(*str_2);

    while ((i >= 0 ) && (j >= 0) && (inrifm <= RIFM)) {
        for ( ; isalpha((*str_1)[i]) == 0; ) {
            i--;
            if (i < 0)
                break;
        }
        for ( ; isalpha((*str_2)[j]) == 0; ) {
            j--;
            if (j < 0)
                break;
        }
        if ((*str_1)[i] > (*str_2)[j])
            return -1;
        if ((*str_1)[i] == (*str_2)[j]) {
            i--;
            j--;
            inrifm++;
            if ((i < 0) || (j < 0))
                break;
        }
        if ((*str_1)[i] < (*str_2)[j])
            return 1;
    }
    return 0;
}
