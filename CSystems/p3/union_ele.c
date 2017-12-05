union ele {
    struct {
        int* p;
        int y;
    } e1;
    struct {
        int x;
        union ele* next;
    } e2;
};

void proc(union ele* up)
{
    up -> e2.next -> e1.y = *(up -> e2.next -> e1.p) - up -> e2.x;
}
