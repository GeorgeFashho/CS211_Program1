/*  gfash2-proj1.c

	Written [5/18/2022] by [George Fashho] for CS 211, Summer 2022
	
	This program will read in a list of integers of undetermined
    length, store them in a dynamically allocated array, copy the array, sort the copy, and report how
    many values of the original list were already in their correctly sorted locations. The program will
    then read in another series of integers, and for each one will report whether the number was in the
    original list or not, and if so, if it was already in the correct location.
	
*/

#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------------------------
/* Function used to copy values from one array to another using a
    for loop and the size of the original array                */
void copyArray(int fromArray[], int toArray[], int size){

    for(int i = 0 ; i< size ; i++){
        toArray[i] = fromArray[i];
    }
}//end copyArray


//---------------------------------------------------------------------------
/* Using selection sort algorithm to sort the integers in the array,
   in ascending order                                           */
void selectionSort(int array[], int size){
    for(int i= 0 ; i < size +1 ; i++){  //initial for loop to go through the first
                                                //value in the array
        for(int j = i+ 1 ; j< size  ; j++){// second for loop to compare first value to the rest

            if(array[i]>array[j]){
                int temp = array[i];        //swapping values to put in order if a smaller value
                array[i] = array[j];       // than the first is found, then incrementing i
                array[j] = temp;
            }
        }
    }
}//end selectionSort


//---------------------------------------------------------------------------
/*Function to count the number of integers that were already in the correct
  index                                                                 */
void countMatches(int array[], int sortedArray[] , int size){
    int matches  = 0;

    for(int i =0 ; i< size ; i++) {
        if (array[i] == sortedArray[i]) {
            matches++;
        }
    }
            //calculating the percentage and outputting information
    double percentage =  ((double)matches/(double)size)*100;
    printf("\n\nNumbers already in sorted order = %i/%i =  %.1f%%\n",matches,size,percentage);
}//end countMatches()


//---------------------------------------------------------------------------
/*A function that checks to see if an integer inputted by the user is inside
 * the array then, counts the number of appearances in the array and finally,
 * checks to see if any integer was in the correct index before sorting.
 *                                                                          */
int findInList(int array[], int sortedArray[], int size, int target, int *nFound, int *index){

    int inOrder = -1, tempInOrder = 0 ;      //initializing conditional integers

    for(int i = 0 ; i < size ;  i++) {

        if (sortedArray[i] == target) {
            inOrder = 0;                //checking if the integer is inside the array
            *nFound += 1;

            if (sortedArray[i] == array[i]) {
                *index = i;                  //checking if integer was in correct
                tempInOrder = 1;            //index before sorting
            }
        }
    }

    if(tempInOrder == 1 ){
        inOrder = 1;
    }

    return inOrder; //returning condition
}//end findInList()


//---------------------------------------------------------------------------
int main( void ) {

    int val;
    int *dynamicArrayOfValues  = NULL;
    int allocatedMemory = 100;
    int mallocMemory = allocatedMemory*sizeof(int);

    dynamicArrayOfValues = (int*)malloc(mallocMemory);    // Creating a dynamically allocated array of ints
                                                              // with initial size 100

    printf( "Enter in a list of numbers to be stored in a dynamic array.\n" );
    printf( "End the list with the terminal value of -999\n" );         //prompting for user input

    scanf( "%d", &val );
    int index = 0;

    while( val != -999 ) {

        if(index +1 == allocatedMemory){ //checking if allocated memory is full, if so we double
                                        //the allocated memory for the dynamic array
            int *tempArr = dynamicArrayOfValues;
            mallocMemory = mallocMemory*2;
            dynamicArrayOfValues = (int*) malloc(mallocMemory);

            for(int i = 0 ; i<allocatedMemory;i++){     //copying values from array at old memory address
                dynamicArrayOfValues[i] = tempArr[i];  //and filling half of the array at the new memory address
            }

            free(tempArr);  //freeing space in memory
            tempArr = NULL;        //setting temp to NULL for safety
            allocatedMemory *=2;
        }

        dynamicArrayOfValues[index] = val;  //adding value to array
        index++;

        scanf( "%d", &val );
    }

    printf("Original List:  ");
    for(int i = 0 ; i < index; i++)                 //printing original array
        printf("%d ",dynamicArrayOfValues[i]);

    int *copyArr = NULL;
    copyArr = (int*) malloc((index+1)*sizeof (int));

    copyArray(dynamicArrayOfValues,copyArr,index);  //calling function to make copy array

    selectionSort(dynamicArrayOfValues,index);  //calling function to sort array in ascending order

    printf("\nSorted List:    ");
    for(int i = 0 ; i < index; i++)
        printf("%d ",dynamicArrayOfValues[i]); // printing sorted array

    countMatches(copyArr,dynamicArrayOfValues,index); //function to print matches

    printf( "Enter in a list of numbers to search for.  \n" );
    printf( "End the list with a terminal value of -999\n" );   //prompting input from user until -999
                                                                      //inputted
    scanf( "%d", &val );
    while( val != -999 ) {

        int numOfAppearances = 0;
        int indexUserVal =0;

        int conditionCheck = findInList(copyArr, dynamicArrayOfValues,index,val,&numOfAppearances,&indexUserVal);

        printf("Target: %d = ",val);

        switch(conditionCheck){ //printing conditions
            case -1:
                printf("Not even in the list!\n");
                break;
            case 0:
                printf("Present %d time(s) but not in order.\n",numOfAppearances);
                break;
            case 1:
                printf("Present %d time(s) and in order. First match at position %d.\n",numOfAppearances,indexUserVal+1);
                break;
        }
        scanf( "%d", &val );
    }
    printf( "Good bye\n" ); //final goodbye

    return 0;
}//end main()
