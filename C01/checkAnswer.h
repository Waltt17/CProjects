#ifndef CHECKANSWER_H
#define CHECKANSWER_H
#include <inttypes.h>
#include <stdbool.h>

/*** DO NOT MODIFY THIS FILE IN ANY WAY! ***/

/**  Computes reference solution for given integers left and right, and
 *   compares it to the student solution.
 * 
 *   Pre:   stuSum has been obtained by calling the student's solution
 *             on the integers left and right
 *          pSum points to an int8_t variable in the calling code
 * 
 *   Post:  *pSum equals the reference solution
 * 
 *   Returns:  true iff stuSum matches reference solution
 */
bool checkAnswer(uint32_t left, uint32_t right, int8_t stuSum, int8_t* const pSum);

#endif
