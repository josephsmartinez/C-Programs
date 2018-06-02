/** *******************************************************************
 * Purpose/Description: Implement a recursive function that calculates the remainder of a 
 *                      non-negative number when dividing by three.
 * Author’s Panther ID: 3816842
 * Certification:
 * I hereby certify that this work is my own and none of it is the work of
 * any other person.
 ******************************************************************* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *  This function use recursion to find the remainder of MOD3
 *  The trick here is to use the value found by the recursive function
 *  and discover the remainder by the following expression:
 *  (sum - ((sum / 3) * 3 )) which will return the remainder from MOD3.
 *  @param n[]   an array of integers that represent a number
 *  @param size  the size of the array
 *  @return      integer value of the remainder
 */ 
 
int nMOD3(int n[], int size){
	
    if(size < 0)
	  return 0;
    int x = ((n[size]) + nMOD3(n, size - 1));
    return (x-((x / 3)*3));
}

//Test main method
main(void){
	//UNIT TEST CASES
	int size1 = 3;
	int number1[] = {2, 3, 5};       //MOD3 = 1 Expected
    
	int size2 = 4;
	int number2[] = {1, 2, 3, 4};   //MOD3 = 1 Expected

    int size3 = 3;
	int number3[] = {6, 5, 0};      //MOD3 = 2 Expected

    int size4 = 3;
	int number4[] = {3, 2, 1};      //MOD3 = 0 Expected

    int size5 = 3;
	int number5[] = {0, 0, 5};      //MOD3 = 2 Expected

	
    int results;

	results = nMOD3(number1, size1 - 1);
	printf("235 mod3 is: %d\n", results);
    
	results = nMOD3(number2, size2 - 1);
	printf("1234 mod3 is: %d\n", results);
	
    results = nMOD3(number3, size3 - 1);
	printf("650 mod3 is: %d\n", results);
    
    results = nMOD3(number4, size4 - 1);
	printf("321 mod3 is: %d\n", results);
    
    results = nMOD3(number5, size5 - 1);
	printf("005 mod3 is: %d\n", results);
    return EXIT_SUCCESS;
}