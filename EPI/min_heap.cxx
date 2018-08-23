#include <iostream>

#define PQ_SIZE 100
using item_type = int;

struct priority_queue
{
    item_type q[PQ_SIZE + 1];
    int n;
};

int pq_parent(int n)
{
    if (n == 1) return -1;
    else return n / 2;
}

int pq_young_child(int n)
{
    return 2 * n;
}

void pq_swap(priority_queue* q, int p, int pp)
{
    int t = q -> q[p];
    q -> q[p] = q -> q[pp];
    q -> q[pp] = t;
}

void bubble_up(priority_queue* q, int p)
{
    if (pq_parent(p) == -1) return ;

    if (q -> q[pq_parent(p)] > q -> q[p])
    {
        pq_swap(q, p, pq_parent(p));
        bubble_up(q, pq_parent(p));
    }
}

void pq_insert(priority_queue* q, item_type x)
{
    if (q -> n >= PQ_SIZE)
        printf("Warning: priority queue overflow insert x=%d\n", x);
    else
    {
        q -> n = q -> n + 1;
        q -> q[ q -> n] = x;
        bubble_up(q, q -> n);
    }
}

void pq_init(priority_queue* q)
{
    q -> n = 0;
}

void make_heap(priority_queue* q, item_type s[], int n)
{
    pq_init(q);
    for (int i = 0; i < n; ++i)
    {
        pq_insert(q, s[i]);
    }
}

void bubble_down(priority_queue* q, int p)
{
    int c = pq_young_child(p);
    int min_index = p;

    for (int i = 0; i <= 1; ++i) 
    {
        if (c + i <= q -> n) 
        {
            if (q -> q[min_index] > q -> q[c + i])
                min_index = c + i;
        }
    }

    if (min_index != p)
    {
        pq_swap(q, p, min_index);
        bubble_down(q, min_index);
    }
}

item_type extract_min(priority_queue* q)
{
    int min = -1;

    if (q -> n <= 0) 
        printf("Warning: empty priority queue.\n");
    else
    {
        min = q -> q[1];
        q -> q[1] = q -> q[ q -> n ];
        q -> n = q -> n - 1;
        bubble_down(q, 1);
    }

    return min;
}

int main()
{
    priority_queue q;
    item_type s[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    make_heap(&q, s, 10); 

    for (int i = - 0; i < 10; ++i)
        std::cout << extract_min(&q) << std::endl;
}
