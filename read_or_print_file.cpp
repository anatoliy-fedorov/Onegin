void make_struct                     (file_information*, char*);
void make_size_file                  (file_information*);
void make_real_size_file             (file_information*);
void make_count_of_strings           (file_information*, char);
void make_index_array                (file_information*);
void replace_str                     (file_information*);
void print_struct                    (file_information*);
void print_strings                   (char**, FILE*, int);
void debug_print_strings             (char**, FILE*, int);
void print_border                    (FILE*);

void make_struct(file_information* information, char* name_of_file) {
    assert(name_of_file);

    information->name_file = name_of_file;
    make_size_file(information);
    information->buffer = (char*)calloc(information->size_file + 1, sizeof(char));
    IS_ERROR
    make_real_size_file(information);

    *(information->buffer + information->real_file_size) = '\0';

    make_count_of_strings(information, '\n');
    make_index_array(information);
    replace_str(information);

}

void make_size_file(file_information* information) {
    assert(information);

    struct stat inf_file = {};
    stat(information->name_file, &inf_file);
    information->size_file = inf_file.st_size;
}

void make_real_size_file(file_information* information) {
    assert(information);

    int descriptor = open(information->name_file, O_RDONLY);
    IS_ERROR
    information->real_file_size = read(descriptor, information->buffer, (unsigned int)information->size_file);
    close(descriptor);
}

void make_count_of_strings(file_information* information, char symbol) {
    assert(information);

    int temp_count = 0;
    char* temp_address = information->buffer;
    while ((temp_address = strchr(temp_address, symbol))) {
        temp_count++;
        temp_address += 1;
    }

    information->count_str = temp_count;
}

void make_index_array(file_information* information) {
    assert(information);

    information->index = (char**)calloc(information->count_str, sizeof(char*));
    IS_ERROR
    char* temp_address = (information->buffer);
    (information->index)[0] = temp_address;

    for (int i = 1; i < information->count_str; i++) {
        temp_address = strchr(temp_address, '\n');
        (information->index)[i] = temp_address + 1;
        temp_address += 1;
    }
}

void replace_str(file_information* information) {
    assert(information);

    char* temp_address = (information->buffer);
    while ((temp_address = strchr(temp_address, '\n'))) {
        *temp_address = '\0';
        temp_address += 1;
    }
}

void print_struct(file_information* information) {
    assert(information);

    printf("name = %s\n", information->name_file);
    printf("size = %llu\n", information->size_file);
    printf("change size = %llu\n", information->real_file_size);
    printf("count str = %d\n", information->count_str);

    for(int i = 0; i <  information->count_str; i++) {
        printf("%d <%s>\n",i, (information->index)[i]);
    }
}

void print_strings(char** index, FILE* file, int count_of_strings) {
    assert(index);
    assert(file);

    for(int number_of_index = 0; number_of_index < count_of_strings; number_of_index++) {
        char* str = index[number_of_index];
        fprintf(file, "%s\n", str);
    }
}

void debug_print_strings(char** index, FILE* file, int count_of_strings) {
    assert(index);
    assert(file);

    for(int number_of_index = 0; number_of_index < count_of_strings; number_of_index++) {
        char* str = index[number_of_index];
        fprintf(file, "len = %llu, address = %p, <%s>\n", strlen(str), str, str);
    }
}

void print_border(FILE* file) {
    assert(file);

    fprintf(file, "\n\n\n");
    fprintf(file, "******************************************************");
    fprintf(file, "\n\n\n");
}
