// sumMatches.c
#include "sumMatches.h"

/**  Determines which digits of left and right are equal, and occur
 *   at the same positions, and computes the sum of those digits.
 *   
 *   Pre:  left and right are initialized
 *   Returns: sum of matching digits; zero if none occur
 */
 
 
 
int8_t sumMatches(uint32_t left, uint32_t right) {
	
	int8_t sum = 0;
	
	// IMPLEMENT THE LOGIC FOR YOUR SOLUTION HERE	
	
	// Checks if one of the numbers is zero and if it matches the 
	// first digit of the other number
	if( (left == 0 || right == 0) && left % 10 == right % 10 )
		return 0;
	
	// Boolean used to see if there is at least one matching digit	
	bool atLeastOne = false;
	
	// Checks each digit of each number and if they match add them
	while( left > 0 && right > 0 ){
		
		if( left % 10 == right % 10 ){
			sum = sum + (left % 10);
			atLeastOne = true;
		}
		left = left / 10;
		right = right / 10;	
	}
	
	// If there was at least one matching digit 
	if( atLeastOne == false )
		return -1;
	return sum;
	
}

