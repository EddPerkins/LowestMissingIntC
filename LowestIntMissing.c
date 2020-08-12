/* LowestIntMissing.c Main File
 * Created by Edward Perkins on 27/07/2020
 * Examines a given unsorted array of integers and will display the lowest
 * missing value
 * Planned to add: a user input that makes use of malloc/realloc/free
 * 05/08/2020   Completed integer check, completing the exercise.
 * 09/08/2020   Added a bubblesort as an exercise to replace qsort
 * 12/08/2020   made bubblesort function more self contained*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void testArrarys(void);
//void variableArrays(void); //for the next part of the exercise
void bubbleSortArray(int*, int); //exercise for bubblesort in C

int lowestIntMissing(int*, int);
int removeDuplicates(int*, int);
int missingInts(int*, int);
void showArray(int*, int);

//following declared functions are no longer in use, but have been kept.
void sortArray(int*, int);
int comparetor (const void *, const void *);

main(){
    testArrarys();

    return 0;
}

void testArrarys(void){
    //test cases for the function
    int arrayLength;
    int lowestInt;

    // test duplicated numbers
    printf("\ntesting with duplicated numbers\n");
    int iArray[] = {1, 4, 2, 1};
    arrayLength = sizeof(iArray)/sizeof(int);
    showArray(iArray, arrayLength);
    lowestInt = lowestIntMissing(iArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    // testing nothing but duplicates
    printf("\ntesting with all duplicated numbers\n");
    int jArray[] = {1, 1, 1, 1};
    arrayLength = sizeof(jArray)/sizeof(jArray[0]);
    showArray(jArray, arrayLength);
    lowestInt = lowestIntMissing(jArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    // testing consecutive, positive only
    printf("\ntesting consecutive positive integers\n");
    int pArray[] = {1, 2, 3};
    arrayLength = sizeof(pArray)/sizeof(pArray[0]);
    showArray(pArray, arrayLength);
    lowestInt = lowestIntMissing(pArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    // testing single element array
    printf("\ntesting single element array\n");
    int qArray[] = {1};
    arrayLength = sizeof(qArray)/sizeof(qArray[0]);
    showArray(qArray, arrayLength);
    lowestInt = lowestIntMissing(qArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    // testing consecutive negative only
    printf("\ntesting consecutive negative numbers\n");
    int rArray[] = {-1, -2, -3};
    arrayLength = sizeof(rArray)/sizeof(rArray[0]);
    showArray(rArray, arrayLength);
    lowestInt = lowestIntMissing(rArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    // testing consecutive mixed
    printf("\ntesting consecutive mixed positive and negative\n");
    int sArray[] = {-1, 0, 1};
    arrayLength = sizeof(sArray)/sizeof(sArray[0]);
    showArray(sArray, arrayLength);
    lowestInt = lowestIntMissing(sArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    // testing consecutive starting beyond 1
    printf("\ntesting numbers starting beyond 1\n");
    int tArray[] = {2, 3, 4};
    arrayLength = sizeof(tArray)/sizeof(tArray[0]);
    showArray(tArray, arrayLength);
    lowestInt = lowestIntMissing(tArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    // testing missing below 0
    printf("\ntesting missing number below 0\n");
    int uArray[] = {-2, -3, -4};
    arrayLength = sizeof(uArray)/sizeof(uArray[0]);
    showArray(uArray, arrayLength);
    lowestInt = lowestIntMissing(uArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    // testing multiple missing numbers
    printf("\ntesting multiple missing numbers\n");
    int vArray[] = {1, 3, 5};
    arrayLength = sizeof(vArray)/sizeof(vArray[0]);
    showArray(vArray, arrayLength);
    lowestInt = lowestIntMissing(vArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    // testing missing multiple numbers
    printf("\ntesting missing multiple numbers\n");
    int wArray[] = {1, 2, 5};
    arrayLength = sizeof(wArray)/sizeof(wArray[0]);
    showArray(wArray, arrayLength);
    lowestInt = lowestIntMissing(wArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);
}

int lowestIntMissing(int* intArray, int size){
    /*  Takes an array of ints and returns lowest missing int
     *  feeds the array into various functions before checking conditions
    */
    int lowestMissing = 0;

    // sortArray(intArray, size); //for when I don't want to use bubblesort

    // using my bubblesort to sort the array
    if (size > 1) bubbleSortArray(intArray, size); // skip if array is size 1

    int max = *(intArray + size - 1); // get maximum value of the sorted array
    size = removeDuplicates(intArray, size); // update sized based on removed ints

    if (max < 1) lowestMissing = 1; //if less than 1, return 1
    else if (size == 1){ //check for a single element
        if (intArray[0] == 1) lowestMissing = 2; //is 1
        else lowestMissing = 1;
    }
    else{
        lowestMissing = missingInts(intArray, size);
    }
    // following will check if array is consecutive and starting at 1 or below
    if (lowestMissing == 0) lowestMissing = max + 1;
    return lowestMissing;
}

int comparetor (const void * a, const void * b){
    return ( *(int*)a - *(int*)b );
}

void bubbleSortArray(int *iArray, int arrayLength){
    /* Uses bubble sort to sort an array
    */
    int swapCount;
    int numA; // third variable for swapping values in array around

    while (swapCount != 0){ // loop to check if array has finished sorting
        swapCount = 0; // if this remains at 0 at end of loop, exit the loop
        for (int i = 1; i < arrayLength; ++i){ // loop for sorting
            if (*(iArray + i - 1) > *(iArray + i)){ // swap logic
                numA = *(iArray + i);
                iArray[i] = *(iArray + i - 1);
                iArray[i - 1] = numA;
                ++swapCount; //increment swap counter if a swap has taken place
            }
        }
    }
}

void sortArray(int *iArray, int arrayLength){
    /* uses comparator to sort the array in order of size
     * requires an array and the length of the array to be passed
     * returns nothing, as it works with pointers */
    qsort (iArray, arrayLength, sizeof(int), comparetor );
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

int missingInts(int* intArray, int arrayLength){
    /*
     * takes a sorted array of ints and returns the lowest one missing*/

    int out = 0;
    int diferenceFound = 0; // token that is flipped to one when a difference is found

    if (*intArray > 1) out = 1;
    else{
        for (int i = 1; i < arrayLength && diferenceFound == 0; ++i){
            int previous = *(intArray + i - 1);
            int current = *(intArray + i);
            if (current - previous > 1){
                out = previous + 1;
                diferenceFound = 1;
            }
        }
    }
    return out;
}

void showArray(int* array, int size){
    /* Shows prints out the contents and length of an array to the console
     * takes an array of integers and the size of the array
     * used for debugging
    */
    printf("The contents of the array are: ");
    for (int i = 0; i < size; ++i) printf("%d,", *(array + i));
    printf("\n");

    printf("The array is size %d\n", size);
}

int getArrayLength(int* intArray){
    /* gets the length of a non-character array
     * This is not possible in the C language.
     * when an array is passed to a function, it decays to a pointer
     * it is best to get the length of the array whilst it is in scope
     * This function is only here as a curiosity*/
    int *p;
    int count = 0;

    for (p=intArray; p<&intArray+1; ++p){ //this cannot work without a terminator value
        ++count;
    }
    printf("array length (func) = %d\n", count);
    return count;
}
