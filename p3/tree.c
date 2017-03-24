typedef struct ELE* tree_ptr;

struct ELE {
    long val;
    tree_ptr left;
    tree_ptr right;
};

long trace(tree_ptr tp);

long trace(tree_ptr tp)
{
    long r = 0;
    while (tp != 0) {
        r = tp->val;
        tp = tp -> right;
    }
    return r;
}
