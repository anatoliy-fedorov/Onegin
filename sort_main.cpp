#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#define IS_ERROR {if (errno != 0){printf("error in file %s line %d \n", __FILE__, __LINE__); perror("code error ");}}

#include "conf.h"
#include "read_or_print_file.cpp"
#include "qsort.cpp"

bool compare_up        (const void*, const void*);
bool compare_down      (const void*, const void*);
bool compare_address   (const void*, const void*);

int main() {

    FILE* file_output = fopen("output.txt", "w");
    const char name_of_file[] = "Onegin_text.txt";

    file_information information = {};
    __init__file_info(&information, name_of_file);
    //void* p = calloc(1000000000000, 8);
    //IS_ERROR

    //FI_print_struct(&information);

    q_sort(information.index, information.count_str, sizeof(information.index[0]), compare_up);
    print_strings(information.index, file_output, information.count_str);
    print_border(file_output);
    IS_ERROR

    q_sort(information.index, information.count_str, sizeof(information.index[0]), compare_down);
    print_strings(information.index, file_output, information.count_str);
    print_border(file_output);
    IS_ERROR

    //q_sort(information.index, information.count_str, sizeof(information.index[0]), compare_address);
    //print_strings(information.index, file_output, information.count_str);
    fprintf(file_output, "%s",information.buffer);
    free(information.index);
    free(information.buffer);
}

bool compare_up(const void* address_a, const void* address_b){
    assert(address_a);
    assert(address_b);

    char* line_one = (*(line_info const*)(address_a)).str;
    char* line_two = (*(line_info const*)(address_b)).str;

    size_t len_line_one = (*(line_info const*)(address_a)).len;
    size_t len_line_two = (*(line_info const*)(address_b)).len;

    size_t index_first_line = 0;
    size_t index_second_line = 0;

    while (index_first_line < len_line_one || index_second_line < len_line_two) {
        if (!isalpha(line_one[index_first_line]))
            index_first_line++;

        else if(!isalpha(line_two[index_second_line]))
            index_second_line++;

        else {
            int copy_first_symbol = tolower(line_one[index_first_line]);
            int copy_second_symbol = tolower(line_two[index_second_line]);

            if (copy_first_symbol != copy_second_symbol)
                return (copy_first_symbol < copy_second_symbol);
            index_first_line++;
            index_second_line++;
        }

    }

    return 1;
}

bool compare_down(const void* address_a, const void* address_b){
    assert(address_a);
    assert(address_b);

    char* line_one = (*(line_info const*)(address_a)).str;
    char* line_two = (*(line_info const*)(address_b)).str;

    int len_line_one = (int)(*(line_info const*)(address_a)).len;
    int len_line_two = (int)(*(line_info const*)(address_b)).len;

    int index_first_line = len_line_one - 1;
    int index_second_line = len_line_two - 1;

    while (index_first_line >= 0 && index_second_line >= 0) {
        if (!isalpha(line_one[index_first_line]))
            index_first_line--;

        else if(!isalpha(line_two[index_second_line]))
            index_second_line--;

        else {
            int copy_first_symbol = tolower(line_one[index_first_line]);
            int copy_second_symbol = tolower(line_two[index_second_line]);

            if (copy_first_symbol != copy_second_symbol)
                return (copy_first_symbol < copy_second_symbol);
            index_first_line--;
            index_second_line--;
        }

    }

    return index_first_line <= index_second_line;
}

bool compare_address(const void* address_a, const void* address_b) {
    assert(address_a);
    assert(address_b);

    char* line_one = *(char* const*)(address_a);
    char* line_two = *(char* const*)(address_b);

    return line_one <= line_two;
}
