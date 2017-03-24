typedef struct ELE* tree_ptr;

struct ELE {
    long val;
    tree_ptr left;
    tree_ptr right;
};

long traverse(tree_ptr tp);

long traverse(tree_ptr tp)
{
    long  x = -9223372036854775808;
    if (tp == 0) 
        return x;
    long val = tp -> val;
    tp = tp -> left;
    long a = traverse(tp);
    tp = tp -> right;
    long b = traverse(tp);
    if (b <= a)
        b = a;
    if (val < b)
        val = b;

    return val;
}
