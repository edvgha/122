static void place(void* bp, size_t asize)
{
    size_t size = GET_SIZE(HDRP(bp)) - asize; 
    if (size >= 2 * DSIZE) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        PUT(HDRP(NEXT_BLKP(bp)), PACK(size, 0);
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0);
    } else {
        PUT(HDRP(bp), PACK(GET_SIZE(HDRP(bp), 1));
        PUT(FTRP(bp), PACK(GET_SIZE(HDRP(bp), 1));
    }
}
