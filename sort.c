#include "sort.h"

void swap (uint8_t *a, uint8_t *b) {
	*b ^= (*a ^= *b);
	*a ^= *b;
}

void bubble_sort (uint8_t* array, size_t size) {
    uint8_t i = 0;
    uint8_t j = 0;
    
    for (i = 0; i < size-1; ++i) {
        for (j = 0; j < size -i -1; ++j) {
            if (array[j] > array[j+1]) {
                swap(array+j, array+j+1);
            }
        }
    }
}

void insert_sort (uint8_t *array, size_t size) {
	uint8_t* min = array;
	uint8_t i = 0;
	uint8_t j = 0;

	for (; i < size; ++i) {
		min = array + i;
		for (j = i; j < size; ++j) {
			if (array[j] < *min) min = array+j; 
		}
		swap(array+i, min);
	}
}
