// R. Jesse Chaney

#include <stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <math.h>
#ifndef __BEAVALLOC_H
# define __BEAVALLOC_H

#ifndef MAX
# define MAX(_a,_b) ((_a) > (_b) ? (_a) : (_b))
#endif // MAX

#ifndef MIN
# define MIN(_a,_b) ((_a) < (_b) ? (_a) : (_b))
#endif // MAX

#ifndef TRUE
# define TRUE 1
#endif // TRUE
#ifndef FALSE
# define FALSE 0
#endif // FALSE

// The basic memory allocator.
// If you pass NULL or 0, then NULL is returned.
// If, for some reason, the system cannot allocate the requested
//   memory, set errno to ENOMEM and return NULL.
// You must use sbrk() or brk() in requesting more memory for your
//   beavalloc() routine to manage.
// When calling sbrk() for more memory, always request 1024 bytes. It
//   is best if you use a macro for this value, in case it needs to change.
void *beavalloc(size_t size);

// A pointer returned from a previous call to beavalloc() must
//   be passed.
// If a pointer is passed to a block than is already free, 
//   simply return.
// If NULL is passed, just return.
// Blocks must be coalesced, where possible, as they are free'ed.
void beavfree(void *ptr);

// Completely reset your heap back to zero bytes allocated.
// You are going to like being able to do this.
// Implementation can be done in as few as 1 line, though
//   you will probably use more to reset the stats you keep
//   about heap.
// After you've called this function, everything you had in
//   the heap is just __GONE__!!!
// You should be able to call beavalloc() after calling beavalloc_reset()
//   to restart building the heap again.
void beavalloc_reset(void);

// Set the verbosity of your beavalloc() code (and related functions).
// This should modify a variable that is static to your C module.
void beavalloc_set_verbose(uint8_t);

void *beavcalloc(size_t nmemb, size_t size);
void *beavrealloc(void *ptr, size_t size);

void beavalloc_dump(uint leaks_only);
void check_and_split(void);
#endif // __BEAVALLOC_H

struct node{

	int size_of_block;
	void *mem_block;
	struct node *prev;
	int currently_in_use;
	int blk_no;
	struct node *next;	
};