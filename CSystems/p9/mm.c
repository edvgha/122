#include "mm.h"

/* DEFINES */

#define WSIZE       4  
#define DSIZE       8
#define CHUNKSIZE  (1 << 12)

#define MAX(x, y) ((x) > (y)? (x) : (y))

#define PACK(size, alloc)  ((size) | (alloc))

#define GET(p)       (*(unsigned int *)(p))
#define PUT(p, val)  (*(unsigned int *)(p) = (val))

#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/***********/

void* heap_listp;
#ifdef NEXT_FIT
void* next_heap_listp;
#endif

static size_t PREV_ALLOC(void* bp) 
{
    void* ptr;
    for (ptr = heap_listp; GET_SIZE(HDRP(ptr)) > 0; ptr = NEXT_BLKP(ptr)) {
        if ((unsigned int*)bp == ((unsigned int*)(NEXT_BLKP(ptr))))
            return (GET_ALLOC(HDRP(ptr)));
    }
    return 2;
}

static void* coalesce(void* bp)
{
    size_t prev_alloc = PREV_ALLOC(bp);
    if (prev_alloc == 2) {
        errno = EFAULT;
        fprintf(stderr, "ERROR: Failed to get previous block ...\n");
        return (void *)-1;
    }
    //size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {
        return bp;
    }

    else if (prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }

    else if (!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    else {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) +
        GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    return bp;
}

static void* extend_heap(size_t words)
{
    char* bp;
    size_t size;

    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    return coalesce(bp);
}

#ifdef NEXT_FIT
static void* find_next_fit(size_t asize) 
{
    void* bp;
    void* old_next_heap_listp = next_heap_listp;

    for (bp = next_heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (! GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            if (GET_SIZE(HDRP(NEXT_BLKP(bp))) == 0)
                next_heap_listp = heap_listp;
            else 
                next_heap_listp = NEXT_BLKP(bp);
            return bp;
        }
    }
    for (bp = heap_listp; (old_next_heap_listp != next_heap_listp && 
                           bp != next_heap_listp); bp = NEXT_BLKP(bp)) {
        if (! GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            if (GET_SIZE(HDRP(NEXT_BLKP(bp))) == 0)
                next_heap_listp = heap_listp;
            else 
                next_heap_listp = NEXT_BLKP(bp);
            return bp;
        }
    }
    return NULL;
}
#endif

static void* find_fit(size_t asize)
{
    void* bp;

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (! GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            return bp;
        }
    }
    return NULL;
}

static void place(void* bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));

    if ((csize - asize) >= (2 * DSIZE)) {
        PUT(HDRP(bp), PACK(asize, 1));
        //PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize - asize, 0));
        PUT(FTRP(bp), PACK(csize - asize, 0));
#ifdef NEXT_FIT
        next_heap_listp = bp;
#endif
    } else {
        PUT(HDRP(bp), PACK(csize, 1));
        //PUT(FTRP(bp), PACK(csize, 1));
    }
}

void display()
{
    void* bp;

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        printf("SIZE : %d ALLOC : %d\n", GET_SIZE(HDRP(bp)), GET_ALLOC(HDRP(bp)));
    }
}

int mm_init(void)
{
    if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
        return -1;
    PUT(heap_listp, 0);
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));
    heap_listp += (2 * WSIZE);

    if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
        return -1;
#ifdef NEXT_FIT
    next_heap_listp = heap_listp;
#endif
    return 0;
}

void mm_free(void* bp)
{
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

void* mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char* bp;

    if (size == 0) 
        return NULL;

    if (size <= WSIZE)
        asize = DSIZE;
    else 
        asize = DSIZE * ((size + (WSIZE) + (DSIZE - 1)) / DSIZE);

    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;
}