#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

unsigned int frame;
int time;
int idx;
int base_val;

// typedef struct listnode {
//      unsigned int frame;
//      struct listnode *next;
// }



/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
        //gotta loop over to chekc time  at which each frame was accessed and remove the last used one.
	int min = base_val;
        idx = 0;
        for(int i = 0; i < memsize; i++) {
                if(min > coremap[i].last_time){
                        min = coremap[i].last_time;
                        idx = i;
                }
        }
        return idx;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
        if (p->frame & PG_VALID )
        {
                //printf("valid\n");
                frame = p->frame >> PAGE_SHIFT;
                // Checking if the page exists at the place
                if (coremap[frame].in_use)
                {	
			base_val = time;
                        coremap[frame].last_time = time;
                        time = time + 1;
                }
        base_val  = time;
        }
        return;
}


/* Initialize any data structures needed for this
 * replacement algorithm
 */
void lru_init() {
        // There are two ways to implement this algo either by creating a queue like array and managing all the
        // entries from there  or managing time whenever a page is accessed.
        idx = 0;
        time = 0;
        base_val = 0;
        frame = 0;

        //listnode *current  = NULL;

        // Initialising time field of cormap for each page to 0;
        while(idx < memsize) {
                coremap[idx].last_time = 0;
                idx = idx + 1;
        }

}
