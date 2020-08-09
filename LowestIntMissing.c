#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void testArrarys(void);
//void variableArrays(void); //for the next part of the exercise
int bubbleSortArray(int*, int); //exercise for bubblesort in C

int lowestIntMissing(int*, int);
void sortArray(int*, int);
int removeDuplicates(int*, int);
int missingInts(int*, int);
void showArray(int*, int);

int comparetor (const void *, const void *);

main(){
    testArrarys();

    return 0;
}

void testArrarys(void){
    //test cases for the function
    int arrayLength;
    int lowestInt;

    //test duplicated numbers
    printf("\ntesting with duplicated numbers\n");
    int iArray[] = {1, 4, 2, 1};
    arrayLength = sizeof(iArray)/sizeof(int);
    showArray(iArray, arrayLength);
    lowestInt = lowestIntMissing(iArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

        //testing nothing but duplicates
    printf("\ntesting with all duplicated numbers\n");
    int jArray[] = {1, 1, 1, 1};
    arrayLength = sizeof(jArray)/sizeof(jArray[0]);
    showArray(jArray, arrayLength);
    lowestInt = lowestIntMissing(jArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    //testing consecutive, positive only
    printf("\ntesting consecutive positive integers\n");
    int pArray[] = {1, 2, 3};
    arrayLength = sizeof(pArray)/sizeof(pArray[0]);
    showArray(pArray, arrayLength);
    lowestInt = lowestIntMissing(pArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    //testing single element array
    printf("\ntesting single element array\n");
    int qArray[] = {1};
    arrayLength = sizeof(qArray)/sizeof(qArray[0]);
    showArray(qArray, arrayLength);
    lowestInt = lowestIntMissing(qArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    //testing consecutive negative only
    printf("\ntesting consecutive negative numbers\n");
    int rArray[] = {-1, -2, -3};
    arrayLength = sizeof(rArray)/sizeof(rArray[0]);
    showArray(rArray, arrayLength);
    lowestInt = lowestIntMissing(rArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    //testing consecutive mixed
    printf("\ntesting consecutive mixed positive and negative\n");
    int sArray[] = {-1, 0, 1};
    arrayLength = sizeof(sArray)/sizeof(sArray[0]);
    showArray(sArray, arrayLength);
    lowestInt = lowestIntMissing(sArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    //testing consecutive starting beyond 1
    printf("\ntesting numbers starting beyond 1\n");
    int tArray[] = {2, 3, 4};
    arrayLength = sizeof(tArray)/sizeof(tArray[0]);
    showArray(tArray, arrayLength);
    lowestInt = lowestIntMissing(tArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    //testing missing below 0
    printf("\ntesting missing number below 0\n");
    int uArray[] = {-2, -3, -4};
    arrayLength = sizeof(uArray)/sizeof(uArray[0]);
    showArray(uArray, arrayLength);
    lowestInt = lowestIntMissing(uArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    //testing multiple missing numbers
    printf("\ntesting multiple missing numbers\n");
    int vArray[] = {1, 3, 5};
    arrayLength = sizeof(vArray)/sizeof(vArray[0]);
    showArray(vArray, arrayLength);
    lowestInt = lowestIntMissing(vArray, arrayLength);
    printf("lowest Missing Integer = %d\n", lowestInt);

    //testing missing multiple numbers
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
    int swapCount = 1;

    //sortArray(intArray, size); //for when I don't want to use bubblesort
    //using my bubblesort to sort the array
    while (swapCount > 0 && size > 1){ //won't run if the array is too small
        swapCount = bubbleSortArray(intArray, size);
    }

    int max = *(intArray + size - 1);
    int newSize = removeDuplicates(intArray, size);
    if (newSize < size) size = newSize;

    if (max < 1) lowestMissing = 1; //if less than 1, return 1
    else if (size == 1){ //check for a single element
        if (intArray[0] == 1) lowestMissing = 2;
        else lowestMissing = 1;
    }
    else{
        lowestMissing = missingInts(intArray, size);
    }
    if (lowestMissing == 0) lowestMissing = *(intArray + size - 1) + 1;
    return lowestMissing;
}

int comparetor (const void * a, const void * b){
    return ( *(int*)a - *(int*)b );
}

int bubbleSortArray(int *iArray, int arrayLength){
    /* Uses bubble sort to sort an array
    */
    //int max = INT_MAX;
    //int min = INT_MIN;
    int swapCount = 0;
    int numA;
    for (int i = 1; i < arrayLength; ++i){
        if (*(iArray + i - 1) > *(iArray + i)){
            numA = *(iArray + i);
            iArray[i] = *(iArray + i - 1);
            iArray[i - 1] = numA;
            ++swapCount;
        }
    }
    return swapCount;
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
     * takes a sorted array of ints and prints out any that are missing*/

    int out = 0;
    int diferenceFound = 0;
    //preform checks here
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
