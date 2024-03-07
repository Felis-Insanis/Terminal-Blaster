#include <stdio.h>
#include <stdlib.h>

void removeByIndex(int index, int *arrayPtr, int length) { // shifts elements
    int i;
    for (i = index; i < length; i++){
        arrayPtr[i] = arrayPtr[i+1];
    }
}

void removeFromEntityArrayByI(int index, int *arrayPtr, int length) { // shifts elements, then reallocates
    int *tmp;

    removeByIndex(index, arrayPtr, length);

    tmp = realloc(arrayPtr, (length-1) * sizeof(int));

    if (tmp == NULL) {
        exit(EXIT_FAILURE);
    }
    length--;
    arrayPtr = tmp;
}

int main() {
    int *ptr;
    int i, n, index;

    printf("How many elements should the list have?\n");
    scanf("%d", &n);
    printf("entered number of elements: %d\n", n);

    ptr = (int*)calloc(n, sizeof(int));

    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    } else {
        printf("Memory successfully allocated.\n");

        for (i = 0; i < n; i++) {
            ptr[i] = i+1;
        }

        printf("The elements of the list are:\n");
        for (i = 0; i < n; i ++) {
            printf("%d\n", ptr[i]);
        }
        printf("Length of the list: %d\n", n);

        printf("Which element do you want to erase?\n");
        scanf("%i", &index);
        printf("Index entered: %i\n", index);

        removeFromEntityArrayByI(index, ptr, n);

        printf("Length of the list: %d\n", n);
        n--;

        printf("The elements of the list are:\n");
        for (i = 0; i < n; i ++) {
            printf("%d\n", ptr[i]);
        }

    }
    
    free(ptr);
    return 0;
}