void __init__file_info               (file_information*, const char*);
void FI_set_size_file                (file_information*);
void FI_set_real_size_file           (file_information*);
void FI_set_count_of_strings         (file_information*);
void FI_set_index_array              (file_information*);
void FI_print_struct                 (file_information*);
void print_strings                   (line_info*, FILE*, int);
void debug_print_strings             (line_info*, FILE*, int);
void print_border                    (FILE*);

void __init__file_info(file_information* information, const char* name_of_file) {
    assert(name_of_file);
    assert(information);

    information->name_file = name_of_file;
    FI_set_size_file(information);
    information->buffer = (char*)calloc(information->size_file + 1, sizeof(char));
    IS_ERROR
    FI_set_real_size_file(information);

    *(information->buffer + information->real_file_size) = '\0';

    FI_set_count_of_strings(information);
    FI_set_index_array(information);

}

void FI_set_size_file(file_information* information) {
    assert(information);

    struct stat inf_file = {};
    stat(information->name_file, &inf_file);
    information->size_file = inf_file.st_size;
}

void FI_set_real_size_file(file_information* information) {
    assert(information);

    int descriptor = open(information->name_file, O_RDONLY);

    information->real_file_size = read(descriptor, information->buffer, (unsigned int)information->size_file);
    close(descriptor);
}

void FI_set_count_of_strings(file_information* information) {
    assert(information);

    int temp_count = 0;
    char* temp_address = information->buffer;
    while ((temp_address = strchr(temp_address, '\n'))) {
        temp_count++;
        temp_address += 1;
    }

    information->count_str = temp_count;
}

void FI_set_index_array(file_information* information) {
    assert(information);

    information->index = (line_info*)calloc(information->count_str, sizeof(line_info));
    IS_ERROR;
    char* temp_address = (information->buffer);


    for (int i = 0; i < information->count_str; i++) {
        ((information->index)[i]).str = temp_address;
        ((information->index)[i]).len = strchr(temp_address, '\n') - temp_address;
        temp_address = strchr(temp_address, '\n') + 1;
    }
}

void FI_print_struct(file_information* information) {
    assert(information);

    printf("name = %s\n", information->name_file);
    printf("size = %llu\n", information->size_file);
    printf("change size = %llu\n", information->real_file_size);
    printf("count str = %d\n", information->count_str);

    for(int i = 0; i <  information->count_str; i++) {
        printf("%d <%s>\n",i, ((information->index)[i]).str);
    }

}

void print_strings(line_info* index, FILE* file, int count_of_strings) {
    assert(index);
    assert(file);

    for(int number_of_index = 0; number_of_index < count_of_strings; number_of_index++) {
        char* str = (index[number_of_index]).str;
        size_t len = (index[number_of_index]).len;

        fprintf(file, "%.*s\n", (int)len, str);
    }
}

void debug_print_strings(line_info* index, FILE* file, int count_of_strings) {
    assert(index);
    assert(file);

    for(int number_of_index = 0; number_of_index < count_of_strings; number_of_index++) {

        char* str = (index[number_of_index]).str;
        size_t len = (index[number_of_index]).len;
        fprintf(file, "len = %llu, address = %p, <%.*s>\n", len, str, (int)len, str);
    }
}

void print_border(FILE* file) {
    assert(file);

    fprintf(file, "\n\n\n");
    fprintf(file, "******************************************************");
    fprintf(file, "\n\n\n");
}


