#ifndef SUMMATCHES_H	
#define SUMMATCHES_H
#include <inttypes.h>
#include <stdbool.h>

/*** DO NOT MODIFY THIS FILE IN ANY WAY! ***/

/**  Determines which digits of left and right are equal, and occur
 *   at the same positions, and computes the sum of those digits.
 *   
 *   Pre:  left and right are initialized
 *   Returns: sum of matching digits; zero if none occur
 * 
 *   Examples:   left            right            result
 *               314513612       424514723            10
 *               363984358            4469             4
 *                 4824421          535358            -1
 *                 8265263       478266264            24
 * 
 *   Restrictions:
 *      - does not use global variables
 *      - does not read input or write output
 */
int8_t sumMatches(uint32_t left, uint32_t right);

#endif
