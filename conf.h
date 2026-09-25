struct line_info {
    char* str;
    size_t len;
};

struct file_information {
    size_t size_file;
    const char* name_file;
    int count_str;
    char* buffer;
    ssize_t real_file_size;
    line_info* index;
};

