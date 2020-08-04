#include<stdio.h>
#include<stdlib.h>

int lowestIntMissing(int*, int);
void sortArray(int*, int);
int getArrayLength(int*);
int removeDuplicates(int*, int);

int comparetor (const void *, const void *);

main(){

    int lowestInt;
    // input array
    int iArray[] = {1, 4, 2, 1};
    // check size of array for checking function output
    int arrayLength = sizeof(iArray)/sizeof(iArray[0]);
    printf("array length = %d\n", arrayLength);
    lowestInt = lowestIntMissing(iArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    int pArray[] = {1, 2, 3};
    arrayLength = sizeof(pArray)/sizeof(pArray[0]);
    lowestInt = lowestIntMissing(pArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    int qArray[] = {2};
    arrayLength = sizeof(qArray)/sizeof(qArray[0]);
    lowestInt = lowestIntMissing(qArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);
    return 0;
}

int lowestIntMissing(int* intArray, int size){
    /*  Takes an array of ints and returns lowest missing int
     *  feeds the array into various functions before checking conditions
    */
    int lowestMissing = 0;
    // sort array
    sortArray(intArray, size);
    // get maximum value
    int max = *(intArray + size - 1);
    printf("highest value in the array = %d\n", max);

    // remove duplicates
    int newSize = removeDuplicates(intArray, size);
    // compare lengths
    if (newSize < size) size = newSize;
    printf("Current size of the array = %d\n", size);

    if (max < 1) lowestMissing = 1; //if less than 1, return 1
    else if (size = 1){ //check for a single element
        if (intArray[0] == 1) lowestMissing = 2;
        else {
            lowestMissing = 1;
        }
    }
    return lowestMissing;
}

int comparetor (const void * a, const void * b){
    return ( *(int*)a - *(int*)b );
}

void sortArray(int *iArray, int arrayLength){
    // uses comparator to sort the array in order of size
    // requires an array and the length of the array to be passed
    // returns nothing, as it works with pointers

    qsort (iArray, arrayLength, sizeof(int), comparetor );

    //for (int j = 0; j < arrayLength; ++j)\
        printf("element %d of array = %d\n", j, *(iArray+j)); //for debugging

}

int removeDuplicates(int* intArray, int arrayLength){
/* looks through the array for duplicates
 * compares each element of the array with all following elements
 * returns the new array length
 * NOTE - does not need array to be sorted*/

    /* loop for comparisons*/
    for (int i = 0; i < arrayLength; i++){
        for (int j = i + 1; j< arrayLength; ++j){ /*must be set to i+1, not 0*/
            if (*(intArray + i) == *(intArray + j)){/* check for identical values*/
                for(int k = j; k < arrayLength; ++k) //putting a "read next line" operator breaks the program
                    (intArray[k]) = (intArray [k + 1]); /* moves elements in array left 1*/
                --arrayLength; /*sets new sizes for array length and inner loop*/
                --j;
            }
        }
    }
    return arrayLength;
}

int getArrayLength(int* intArray){
    // gets the length of a non-character array
    // This is not possible.
    // when an array is passed to a function, it decays to a pointer
    // it is best to get the length of the array whilst it is in scope
    int *p;
    int count = 0;

    for (p=intArray; p<&intArray+1; ++p){ //this cannot work
        ++count;
    }
    printf("array length (func) = %d\n", count);
    return count;
}
