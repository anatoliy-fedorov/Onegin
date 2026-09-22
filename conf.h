const char POISON_VAR = '/';

struct file_information {
    size_t size_file;
    char* name_file;
    int count_str;
    char* buffer;
    ssize_t real_file_size;
    char** index;
};

