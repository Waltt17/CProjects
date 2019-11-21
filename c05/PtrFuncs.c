


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/**  Uses pointerbased logic to access a specified portion of a region of
*   memory and copy the corresponding bytes to a supplied array.
* 
*   Pre:   pDest points to an array of dimension nBytes + 1, or greater
*          baseAddrpoints to the first byte of the memory region
*          Offset is the location, relative to baseAddr, of the first
*             relevant byte of the memory region
*          nBytes is the number of bytes to be copied
*   Restrictions:
*      You must use only pointer syntax in accessing the datablock
*/
void getBytesAtOffset(uint8_t* const pDest, const uint8_t* const baseAddr, uint16_t Offset, uint8_t nBytes){
	
	//follows example in notes but altrered to fit problem
	// steps thru data and gets the bytes at the given offset
	uint8_t *y = (uint8_t*)baseAddr + Offset;
	uint32_t bytesRead = 0;
	
	while( bytesRead < nBytes ){
		pDest[bytesRead] = *y;
		++y;
		++bytesRead;
	}
	
	
}

/**  Uses pointer
-
based logic to search a specified portion of a region of
*   memory for occurrences of a specified one-byte value.
* 
*   Pre:  pOffsets points to an array of dimension at least 256
*         baseAddr points to the first byte of the memory region
*         Length is number of bytes in the memory region Byte is the value to be found
*   Post: The offsets of up to 256 occurrences of Byte have been stored
*            in pOffsets, in ascending order, starting at index 0.
*   Returns:  the number of occurrences of Byte found in the memory region(which may be less than the actual number of occurrences)
*   Restrictions:
*      You must use only pointer syntax in accessing the datablock.
*/
uint8_t findOccurrencesOfByte(uint16_t* const pOffsets, const uint8_t* const baseAddr, uint32_t Length, uint8_t Byte){
	
	// count is how many occurences there are
	// steps thru data to find number of occurences
	uint8_t count = 0;
	uint8_t *y = (uint8_t*)baseAddr;
	uint32_t bytesRead = 0;
	
	while( count < 256 && bytesRead < Length ){
		// if the byte at the location is eequal to the given byte it adds to array
		if(*y == Byte){
			pOffsets[count] = bytesRead;
			++count;
		}
		++y;
		++bytesRead;
	}
	
	
	return count;
}

/**  Uses pointer-based logic to compute the sum of two values taken from a region of memory, 
 * using pointer typecasts to control the number of bytes
*   that are summed, and the way those bytes are interpreted.
* 
*   Pre:   pDest points to a memory region large enough to hold the
*             requested value
*          baseAddr points to the first byte of the memory region
*          Offset1 is the location, relative to baseAddr, of the first
*             byte of the first operand
*          Offset2 is the location, relative to baseAddr, of the first
*             byte of the secondoperand
*          Sign indicates whether the bytes are to be interpreted as
*             representing signed or unsigned integers
*          nByte is the number of bytes to be considered (1, 2, 4, or 8 only)
*   Post:  *pDest holds the sum of the two specified values
*   Returns:  false if either of the requested values could not be obtained;
*             true otherwise
*   Restrictions:
*      You must use only pointer syntax in accessing the data.
*/

// enum for use in next function 
enum _Sign {SIGNED, UNSIGNED};
typedef enum _Sign Sign;

bool sumValuesAtOffsets(void* pDest, const uint8_t* const baseAddr, uint32_t Offset1, uint32_t Offset2, Sign Sgn, uint8_t nBytes){
	
	// if it is a signed operation or not
	if(Sgn == SIGNED){
		
		uint8_t *local1 = (uint8_t*)baseAddr + Offset1;
		uint8_t *local2 = (uint8_t*)baseAddr + Offset2;
		
		// one byte
		if(nBytes == 1){
			int8_t int1 = *(int8_t*)local1;
			int8_t int2 = *(int8_t*)local2;
			*(int8_t*)pDest = int1 + int2;
			
			return true;
		}
		// two byte
		else if(nBytes == 2){
			int16_t int1 = *(int16_t*)local1;
			int16_t int2 = *(int16_t*)local2;
			*(int16_t*)pDest = int1 + int2;
			
			return true;
		}
		// four byte
		else if(nBytes == 4){
			int32_t int1 = *(int32_t*)local1;
			int32_t int2 = *(int32_t*)local2;
			*(int32_t*)pDest = int1 + int2;
			
			return true;
			
		}
		// eight byte
		else if(nBytes == 8){
			int64_t int1 = *(int64_t*)local1;
			int64_t int2 = *(int64_t*)local2;
			*(int64_t*)pDest = int1 + int2;
			
			return true;
		}
		
	}
	// if it is an unsigned operation or not
	else if(Sgn == UNSIGNED){
		
		uint8_t *local1 = (uint8_t*)baseAddr + Offset1;
		uint8_t *local2 = (uint8_t*)baseAddr + Offset2;
		
		// one byte
		if(nBytes == 1){
			uint8_t int1 = *(uint8_t*)local1;
			uint8_t int2 = *(uint8_t*)local2;
			*(uint8_t*)pDest = int1 + int2;
			
			return true;
		}
		// two byte
		else if(nBytes == 2){
			uint16_t int1 = *(uint16_t*)local1;
			uint16_t int2 = *(uint16_t*)local2;
			*(uint16_t*)pDest = int1 + int2;
			
			return true;
		}
		// four byte
		else if(nBytes == 4){
			uint32_t int1 = *(uint32_t*)local1;
			uint32_t int2 = *(uint32_t*)local2;
			*(uint32_t*)pDest = int1 + int2;
			
			return true;
			
		}
		// eight byte
		else if(nBytes == 8){
			uint64_t int1 = *(uint64_t*)local1;
			uint64_t int2 = *(uint64_t*)local2;
			*(uint64_t*)pDest = int1 + int2;
			
			return true;
		}
	}
		
	return false;
}

