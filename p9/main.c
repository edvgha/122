#include "mm.h"

int main() 
{
    mem_init();
    mm_init();

    printf("initial\n");
    display();

    void* p1 = mm_malloc(10);
    void* p2 = mm_malloc(30);
    void* p3 = mm_malloc(50);
    void* p4 = mm_malloc(30);
    void* p5 = mm_malloc(70);
    void* p6 = mm_malloc(10);
    mm_free(p1);
    mm_free(p3);
    mm_free(p5);
    printf("step1\n");
    display();
}
