#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;
static int index;

/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
static int index;
int fifo_evict() {
	// Starts from 0 since FIFO.

	int frame_num = index % memsize;


    index = index + 1;
	return frame_num;
	//I THINK I AM DONE
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {

	return;
}

/* Initialize any data structures needed for this
 * replacement algorithm
 */
void fifo_init() {
	index = 0;
}
