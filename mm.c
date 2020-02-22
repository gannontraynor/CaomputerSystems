/*
 *Gannon Traynor
 * The allocator implemented here uses the size of a pointer to define the size of a 
 word (sizeof(void*)). This allows for the allocator to use the standard type uintptr_t
 to define unsigned integers that are the same size as the pointer. The initializer
 tries to allocate the initial heap area only if 0 is returned. Malloc uses the size of
 the memory to return the address of the allocated block. Free uses the address of the
 block in order to free it unless the block is null. Realloc also uses the address of
 the block reallocates the pointer to the bloack with at least the size bytes of payload
 unless the size is 0. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/* single word (4) or double word (8) alignment */
#define WSIZE 4
#define DSIZE 8
#define ALIGNMENT 8
#define CHUNKSIZE  (1 << 12)
#define HEAP_SIZE  24

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define PACK(size, alloc)  ((size) | (alloc))

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

/*  Read  a  word  at  address  p  */
#define  GET(p)	 (*(unsigned int *)(p))
#define PUT(p, val)  (*(uintptr_t *)(p) = (val))

/*  Read  the  size  field  from  address  p  */
#define  GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p)  (GET(p) & 0x1)

/*  Given  block  ptr  bp,  compute  address  of  its  header */
#define  HDRP(bp)	((char *)(bp) - WSIZE)
#define FTRP(bp)  ((void *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
#define NEXT_BLK(bp)  ((void *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLK(bp)  ((void *)(bp) - GET_SIZE((void *)(bp) - DSIZE))
#define GET_NEXT_PTR(bp)  (*(char **)(bp + WSIZE))
#define GET_PREV_PTR(bp)  (*(char **)(bp))
#define SET_NEXT_PTR(bp, qp) (GET_NEXT_PTR(bp) = qp)
#define SET_PREV_PTR(bp, qp) (GET_PREV_PTR(bp) = qp)
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

static char *heap_listp = 0; 
static char *free_lists = 0;
static void *coalesce(void *bp);
static void *extend_heap(size_t words);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);
static void insert_freel(void *bp); 
static void remove_freel(void *bp); 

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    if ((heap_listp = mem_sbrk(8*WSIZE)) == NULL) 
        return -1;

    PUT(heap_listp, 0);                            
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1)); 
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1)); 
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));   
    free_lists = heap_listp + 2*WSIZE; 

    if (extend_heap(4) == NULL) 
        return -1;
  
    return 0;
}

static void *extend_heap(size_t words) {
  char *bp;
  size_t size;

  size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;

  if (size < 16)
    size = 16;
    
  if ((int)(bp = mem_sbrk(size)) == -1)
    return NULL;

  PUT(HDRP(bp), PACK(size, 0));        
  PUT(FTRP(bp), PACK(size, 0));         
  PUT(HDRP(NEXT_BLK(bp)), PACK(0, 1));
  
  return coalesce(bp);
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    size_t asize;      
    size_t extendsize; 
    char *bp;      

    if (size <= 0)
        return NULL;

    if((ALIGN(size) + DSIZE) < HEAP_SIZE)
        asize = HEAP_SIZE;
    else
      asize = ALIGN(size) + DSIZE;

    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    extendsize = MAX(asize,CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;
}

/*
 * mm_free - Currently, freeing a block does nothing.
 * 	You must revise this function so that it frees the block.
 */
void mm_free(void *ptr)
{
    size_t size;
    
    if (ptr == NULL)
        return;
  
    size = GET_SIZE(HDRP(ptr));
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{   
    if((int)size < 0) 
        return NULL; 
    else if((int)size == 0){ 
        mm_free(ptr); 
        return NULL; 
    } 
    else if(size > 0){ 
        size_t oldsize = GET_SIZE(HDRP(ptr)); 
        size_t newsize = size + 2 * WSIZE;
        
        if(newsize <= oldsize) 
            return ptr;  
        else { 
          size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLK(ptr))); 
          size_t csize;
         
            if(!next_alloc && ((csize = oldsize + GET_SIZE(  HDRP(NEXT_BLK(ptr))  ))) >= newsize){ 
                remove_freel(NEXT_BLK(ptr)); 
                PUT(HDRP(ptr), PACK(csize, 1)); 
                PUT(FTRP(ptr), PACK(csize, 1)); 
                return ptr; 
            }
            else {  
                void *new_ptr = mm_malloc(newsize);  
                place(new_ptr, newsize);
                memcpy(new_ptr, ptr, newsize); 
                mm_free(ptr); 
                return new_ptr; 
            } 
        }
    }
    else 
        return NULL;
}

static void *coalesce(void *bp){

  size_t NEXT_ALLOC = GET_ALLOC(  HDRP(NEXT_BLK(bp))  );
  size_t PREV_ALLOC = GET_ALLOC(  FTRP(PREV_BLK(bp))  ) || PREV_BLK(bp) == bp;
  size_t size = GET_SIZE(HDRP(bp));
  
  if (PREV_ALLOC && !NEXT_ALLOC) {                  
    size += GET_SIZE( HDRP(NEXT_BLK(bp))  );
    remove_freel(NEXT_BLK(bp));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  }
  else if (!PREV_ALLOC && NEXT_ALLOC) {               
    size += GET_SIZE( HDRP(PREV_BLK(bp))  );
    bp = PREV_BLK(bp);
    remove_freel(bp);
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  }
  else if (!PREV_ALLOC && !NEXT_ALLOC) {                
    size += GET_SIZE( HDRP(PREV_BLK(bp))  ) + GET_SIZE( HDRP(NEXT_BLK(bp))  );
    remove_freel(PREV_BLK(bp));
    remove_freel(NEXT_BLK(bp));
    bp = PREV_BLK(bp);
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  }
    
  insert_freel(bp);
  return bp;
}

static void *find_fit(size_t asize){
  void *bp;
  static int last_malloced_size = 0;
  static int repeat_counter = 0;
    
  if( last_malloced_size == (int)asize){
      if(repeat_counter>30){  
          int extendsize = MAX(asize, 4 * WSIZE);
          bp = extend_heap(extendsize/4); 
          return bp;
      }
      else
          repeat_counter++;
  }
  else
    repeat_counter = 0;
    
  for (bp = free_lists; GET_ALLOC(HDRP(bp)) == 0; bp = GET_NEXT_PTR(bp) ){
    if (asize <= (size_t)GET_SIZE(HDRP(bp)) ) {
      last_malloced_size = asize;
      return bp;
    }
  }
  return NULL;
}

static void place(void *bp, size_t asize){
  size_t csize = GET_SIZE(HDRP(bp));

  if ((csize - asize) >= 4 * WSIZE) {
    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    remove_freel(bp);
    bp = NEXT_BLK(bp);
    PUT(HDRP(bp), PACK(csize-asize, 0));
    PUT(FTRP(bp), PACK(csize-asize, 0));
    coalesce(bp);
  }
  else {
    PUT(HDRP(bp), PACK(csize, 1));
    PUT(FTRP(bp), PACK(csize, 1));
    remove_freel(bp);
  }
}

static void insert_freel(void *bp){
  SET_NEXT_PTR(bp, free_lists); 
  SET_PREV_PTR(free_lists, bp); 
  SET_PREV_PTR(bp, NULL); 
  free_lists = bp; 
}

static void remove_freel(void *bp){
  if (GET_PREV_PTR(bp))
    SET_NEXT_PTR(GET_PREV_PTR(bp), GET_NEXT_PTR(bp));
  else
    free_lists = GET_NEXT_PTR(bp);
  SET_PREV_PTR(GET_NEXT_PTR(bp), GET_PREV_PTR(bp));
}













