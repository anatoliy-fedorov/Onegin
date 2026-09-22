struct file_information {
    size_t size_file;
    const char* name_file;
    int count_str;
    char* buffer;
    ssize_t real_file_size;
    char** index;
    size_t* array_of_lens_str;
};

