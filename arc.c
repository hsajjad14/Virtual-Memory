#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

// double linkedlist
struct Node {
    pgtbl_entry_t *pde;
    struct Node* next; // Pointer to next node in DLL
    struct Node* prev; // Pointer to previous node in DLL
};

// make 4 linkedlists
static struct Node *t1;
static struct Node *t2;
static struct Node *b1;
static struct Node *b2;

// make 4 list counters
static int lt1;
static int lt2;
static int lb1;
static int lb2;

// p = the target
static int p;


/* Page to evict is chosen using the ARC algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int arc_evict() {

	return 0;
}

void deleteNode(struct Node** head_ref, struct Node* del)
{
    /* base case */
    if (*head_ref == NULL || del == NULL)
        return;

    /* If node to be deleted is head node */
    if (*head_ref == del)
        *head_ref = del->next;

    /* Change next only if node to be deleted is NOT
       the last node */
    if (del->next != NULL)
        del->next->prev = del->prev;

    /* Change prev only if node to be deleted is NOT
       the first node */
    if (del->prev != NULL)
        del->prev->next = del->next;

    /* Finally, free the memory occupied by del*/
    free(del);
}

/* This function is called on each access to a page to update any information
 * needed by the ARC algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void arc_ref(pgtbl_entry_t *p) {

	// check if its a hit in t1 or t2
	// check if in t1
	struct Node* dummy = t1;
	int foundt1 = 0;
	foundt1 = foundt1; // compiler
	p = p; // compiler
	while(dummy != NULL){
		if (dummy->pde == p){
			// hit in t1
			// make it the mru of t2
			struct Node* dummy2 = dummy;
			dummy2->next = t2;
			dummy2->prev = NULL;
			t2 = dummy2;

			// remove it from t1
			deleteNode(&t1, dummy);
			return;

		}
		dummy = dummy->next;
	}
	dummy = t2;

	// check for hit in t2
	while(dummy != NULL){
		if (dummy->pde == p){
			// hit in t1
			// make it the mru of t2
			pgtbl_entry_t pdedummy;
			struct Node* dummy2 = malloc(sizeof(struct Node));
			pdedummy = *dummy->pde;
			dummy2->pde = &pdedummy;
			deleteNode(&t2, dummy);
			dummy2->next = t2;
			dummy2->prev = NULL;
			t2 = dummy2;

			return;

		}
		dummy = dummy->next;
	}

	// not in t1 or t2 means its a miss
	// check if its b1
	dummy = b1;
	while(dummy != NULL){
		if (dummy->pde == p){

		}
		dummy = dummy->next;
	}

	return;
}

/* Initializes any data structures needed for this
 * replacement algorithm.
 */
void arc_init() {
	t1 = malloc(sizeof(struct Node));
	t2 = malloc(sizeof(struct Node));
	b1 = malloc(sizeof(struct Node));
	b2 = malloc(sizeof(struct Node));

	lt1 = 0;
	lt2 = 0;
	lb1 = 0;
	lb2 = 0;
	p = 0;

}
