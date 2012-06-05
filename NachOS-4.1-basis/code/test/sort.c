/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */


/*
#define UNIX
#define UNIX_DEBUG
*/

#ifdef UNIX
#include <stdio.h>
#define Exit exit
#else
#include "syscall.h"
#include "string.h"
#endif /* UNIX */

#define SIZE (1024)

int A[SIZE];	/* size of physical memory; with code, we'll run out of space!*/

int
main()
{
    int i, j, tmp;

    /* first initialize the array, in reverse sorted order */
    for (i = 0; i < SIZE; i++) {
        A[i] = (SIZE-1) - i;
    }
    
    println(ConsoleOutput, "Sortiere Liste...");

    /* then sort! */
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < (SIZE-1); j++) {
	   if (A[j] > A[j + 1]) {	/* out of order -> need to swap ! */
	      tmp = A[j];
	      A[j] = A[j + 1];
	      A[j + 1] = tmp;
    	   }
        }
    }

    for (i=0; i<SIZE; i++) {
        if (A[i] != i) {
            Exit(1);
        }   
    }

    println(ConsoleOutput, "Liste richig sortiert!");
    Exit(0);
    
}
