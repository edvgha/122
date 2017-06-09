// First fit search
static void* find_fit(size_t asize)
{
    char* bp = NEXT_BLKP(heap_listp);

    while (!(GET_SIZE(HDRP(bp)) == 0 && GET_ALLOC(HDRP(bp)) == 1)) {
        if (GET_ALLOC(HDRP(bp)) == 0 && GET_SIZE(HDRP(bp)) >= asize) {
            return bp;
        }
        bp = NEXT_BLKP(bp);
    }
    return NULL;
}
