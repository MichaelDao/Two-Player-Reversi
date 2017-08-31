#include "utility.h"

/**
 * Function required when clearing the buffer. Simply reads
 * each char from the buffer until the buffer is empty again. 
 **/

void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}
