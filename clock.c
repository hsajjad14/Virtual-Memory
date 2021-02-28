#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

static int clock_hand;

int clock_evict() {
	// start at the 0th frame in coremap
	// loop through coremap
	// apply clock, approximating lru
	// http://pages.cs.wisc.edu/~remzi/OSTEP/vm-beyondphys-policy.pdf
	while(1){
		pgtbl_entry_t *page = coremap[clock_hand % memsize].pte;

		// check if page is referenced
		if(page->frame & PG_REF){
			// unreference page
			page->frame = page->frame & ~PG_REF;
		}else{
			// page is unreferenced
			return clock_hand % memsize;
		}

		// move to next clock hand (+1)
		clock_hand++;
	}


	// can't ever reach here
	return clock_hand % memsize;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {

	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm.
 */
void clock_init() {
	clock_hand = 0;
}
