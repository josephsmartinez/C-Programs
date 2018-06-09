#include <stdio.h>
#include <stdlib.h>
/**
* Different ways to initialize an array.
*/

#define MAX_SIZE 10

int main(int argc, char** argv) {

    //Most common way of initializing an array of elements
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr2[5] = {1, 2, 3, 4, 5};
    int arr3[3] = {0, 0, 0};

    //All other values are set to zero
    int arr4[500] = {100, 90, 90};
    //C99 designated initializers, where we can pick the index to initialize.
    float arr5[10] = {[1]= 400.10, [4]=89.99};

    double arr6[MAX_SIZE];

    return (EXIT_SUCCESS);
}
