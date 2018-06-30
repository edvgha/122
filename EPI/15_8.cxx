#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

struct tree_node
{
    int data;
    std::unique_ptr<tree_node> left;
    std::unique_ptr<tree_node> right;

    tree_node(int d) : data(d), left(nullptr), right(nullptr) {}
};

std::unique_ptr<tree_node> clone(std::unique_ptr<tree_node>& node)
{
    std::unique_ptr<tree_node> cnode = std::make_unique<tree_node>(node -> data);
    if (node -> left)
    {
        cnode -> left = clone(node -> left);
    }
    else 
    {
        cnode -> left = nullptr;
    }

    if (node -> right)
    {
        cnode -> right = clone(node -> right);
    }
    else 
    {
        cnode -> right = nullptr;
    }

    return cnode;
}

std::vector<std::unique_ptr<tree_node>> generate_binary(size_t nnodes)
{
    if (nnodes == 0)
    {
        return {};
    }

    std::vector<std::unique_ptr<tree_node>> result;

    for (size_t i = 0; i < nnodes; ++i)
    {
        //printf("%lu [%lu, %lu]\n", nnodes, i , nnodes - 1 - i);
        std::vector<std::unique_ptr<tree_node>> left_subtrees = generate_binary(i);
        std::vector<std::unique_ptr<tree_node>> right_subtrees = generate_binary(nnodes - 1 - i);
        if (left_subtrees.size() == 0 && right_subtrees.size() == 0)
        {
            std::unique_ptr<tree_node> root = std::make_unique<tree_node>(nnodes);
            result.emplace_back(std::move(root));
        } 
        else if (left_subtrees.size() != 0 && right_subtrees.size() != 0)
        {
            for (size_t l = 0; l < left_subtrees.size(); ++l)
            {
                for (size_t j = 0; j < right_subtrees.size(); ++j) 
                {
                    std::unique_ptr<tree_node> root = std::make_unique<tree_node>(nnodes);
                    root -> left = clone(left_subtrees[l]);
                    root -> right = clone(right_subtrees[j]);
                    result.emplace_back(std::move(root));
                }
            }
        }
        else if (left_subtrees.size() == 0 && right_subtrees.size() != 0)
        {
            for (size_t j = 0; j < right_subtrees.size(); ++j) 
            {
                std::unique_ptr<tree_node> root = std::make_unique<tree_node>(nnodes);
                root -> right = clone(right_subtrees[j]);
                result.emplace_back(std::move(root));
            }
        }
        else if (left_subtrees.size() != 0 && right_subtrees.size() == 0)
        {
            for (size_t l = 0; l < left_subtrees.size(); ++l)
            {
                std::unique_ptr<tree_node> root = std::make_unique<tree_node>(nnodes);
                root -> left = clone(left_subtrees[l]);
                result.emplace_back(std::move(root));
            }
        }
    }
    return result;
}

void display_tree(std::unique_ptr<tree_node>& t)
{
    if (t -> left)
    {
        printf(" %02x <-left ", t.get());
        display_tree(t -> left);
    }

    if (t -> right)
    {
        printf(" %02x right-> ", t.get()); 
        display_tree(t -> right);
    }

    if (! t -> left && ! t -> right)
    {
        printf(" %02x ", t.get());
    }
}

void display(std::vector<std::unique_ptr<tree_node>>& v)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        display_tree(v[i]);
        printf("\n\n");
    }
}

int main()
{
    auto trees = generate_binary(13);
    display(trees);
}
