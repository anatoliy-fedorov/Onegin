#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "read_or_print_file.cpp"
#include "qsort.cpp"

bool compare_up        (const void*, const void*);
bool compare_down      (const void*, const void*);
bool compare_address   (const void*, const void*);

int main() {
    //FILE* file_debug = fopen("debug.txt", "w");
    FILE* file_output = fopen("output.txt", "w");
    char name_of_file[] = "Onegin_text.txt";

    file_information information = {};
    make_struct(&information, name_of_file);

    //print_struct(&information);

    q_sort(information.index, information.count_str, sizeof(information.index[0]), compare_up);
    print_strings(information.index, file_output, information.count_str);
    print_border(file_output);

    q_sort(information.index, information.count_str, sizeof(information.index[0]), compare_down);
    print_strings(information.index, file_output, information.count_str);
    print_border(file_output);

    q_sort(information.index, information.count_str, sizeof(information.index[0]), compare_address);
    print_strings(information.index, file_output, information.count_str);



}

bool compare_up(const void* address_a, const void* address_b){
    assert(address_a);
    assert(address_b);

    char* line_one = *(char**)(address_a);
    char* line_two = *(char**)(address_b);

    size_t len_line_one = strlen(line_one);
    size_t len_line_two = strlen(line_two);

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

    char* line_one = *(char**)(address_a);
    char* line_two = *(char**)(address_b);

    int len_line_one = (int)strlen(line_one);
    int len_line_two = (int)strlen(line_two);

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

    char* line_one = *(char**)(address_a);
    char* line_two = *(char**)(address_b);

    return line_one <= line_two;
}
