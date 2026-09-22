void q_sort            (void*, size_t, size_t, bool (*)(const void*, const void*));
void quick_sort        (void*, size_t, size_t, bool (*)(const void*, const void*), size_t);
size_t partition       (void*, size_t, size_t, bool (*)(const void*, const void*), size_t);
void* get_shift        (void*, size_t, size_t);
void swap              (void*, void*, size_t);


void q_sort(void* arr, size_t size, size_t size_of_element, bool (*compare)(const void*, const void*)) {
    assert(arr);

    quick_sort(arr, 0, size, compare, size_of_element);
}


void quick_sort(void* arr, size_t left, size_t right, bool (*compare)(const void*, const void*), size_t size_of_element) {
    assert(arr);

    if (left + 1 < right){
        size_t main_element = partition(arr, left, right, compare, size_of_element);

        quick_sort(arr, left, main_element, compare, size_of_element);
        quick_sort(arr, main_element, right, compare, size_of_element);
    }

}

size_t partition(void* arr, size_t left, size_t right, bool (*compare)(const void*, const void*), size_t size_of_element) {
    assert(arr);

    size_t index_for_min = left;
    size_t pivot = right - 1;

    for (size_t index = left; index < right; index++) {
        if (compare(get_shift(arr, size_of_element, index), get_shift(arr, size_of_element, pivot))) {
            swap(get_shift(arr, size_of_element, index), get_shift(arr, size_of_element, index_for_min), size_of_element);

            index_for_min++;
        }
    }

    return index_for_min - 1;
}

void* get_shift(void* a, size_t size, size_t index) {
    assert(a);

    return (void*)((char*)(a) + size*index);
}

void swap(void* a, void* b, size_t size_of_element) {
    assert(a);
    assert(b);

    void* temp_arr = calloc(size_of_element, 1);
    memcpy(temp_arr, a, size_of_element);
    memcpy(a, b, size_of_element);
    memcpy(b, temp_arr, size_of_element);
}
