/*Zhuoming Huang 10/22/2019 xbits.h*/
/* header file for hw3 
 *
 *  functional prototypes for functions to study
 *  integer-hex conversions
 *
 *	modified by Ron Cheung sum'05
 */

/* function returns in hexstring the char sequence of hex digits
 * '0' ... 'F' used to represent int n. It is the caller's responsibility
 * to have allocated at least 1+2*sizeof(int) positions in bitstring.
 * itox must provide the concluding \0 in bitstring.
 */
void itox(char hexstring[], int n); /* source on right, target on left */



/* function returns in integer the decimal representation of
 * the hex characters in hexstring. The function needs to check if hexstring
 * contains only the characters '0' ... 'F'.
 */
int xtoi(char hexstring[]); /* return the converted integer */ 

