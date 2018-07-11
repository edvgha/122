#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

struct vertex
{
    char data;
    enum Color { white, gray, black} color = white;
    std::vector<vertex*> edges;
    vertex(char c) : data(c) {}
};

std::vector<vertex*> build()
{
    vertex* u = new vertex('u');
    vertex* v = new vertex('v');
    vertex* w = new vertex('w');
    vertex* x = new vertex('x');
    vertex* y = new vertex('y');
    vertex* z = new vertex('z');

    u -> edges.push_back(x);
    u -> edges.push_back(v);

    v -> edges.push_back(y);

    w -> edges.push_back(y);
    w -> edges.push_back(z);

    x -> edges.push_back(v);

    y -> edges.push_back(x);

    z -> edges.push_back(z);

    return {u, v, w, x, y, z};
}

int tt = 0;
std::unordered_map<vertex*, vertex*> pi;
std::unordered_map<vertex*, int> d;
std::unordered_map<vertex*, int> f;

void DFS_Visit(vertex* u)
{
    u -> color = vertex::gray;
    d[u] = ++tt;
    for (size_t i = 0; i < u -> edges.size(); ++i)
    {
        if ((u -> edges)[i] -> color == vertex::white)
        {
            pi[(u -> edges)[i]] = u;
            DFS_Visit((u -> edges)[i]);
        }
    }
    u -> color = vertex::black;
    f[u] = ++tt;
}

void DFS_Visit_iter(vertex* u)
{
    std::stack<vertex*> stack;
    stack.push(u);
    while (!stack.empty())
    {
        vertex* v = stack.top();
        if (v -> color == vertex::white)
        {
            v -> color = vertex::gray;
            d[v] = ++tt;
        }

        bool bypass = true;
        for (size_t i = 0; i < v -> edges.size(); ++i)
        {
            if ((v -> edges)[i] -> color == vertex::white)
            {
                pi[(v -> edges)[i]] = v;
                stack.push((v -> edges)[i]);
                bypass = false;
            }
        }

        if (bypass)
        {
            v = stack.top();
            if (v -> color == vertex::gray)
            {
                v -> color = vertex::black;
                f[v] = ++tt;
            }
            stack.pop();
        }
    }
}

void DFS(std::vector<vertex*>& g)
{
    for (size_t i = 0; i < g.size(); ++i)
    {
        if (g[i] -> color == vertex::white)
        {
            pi[g[i]] = nullptr;
        }
    }
    tt = 0;
    for (size_t i = 0; i < g.size(); ++i)
    {
        if (g[i] -> color == vertex::white)
        {
            //DFS_Visit(g[i]);
            DFS_Visit_iter(g[i]);
        }
    }
}

int main()
{
    std::vector<vertex*> g = build();
    DFS(g);
    for (auto el : pi)
    {
        if (el.second)
            std::cout << el.second -> data << " -> ";
        else
            std::cout << "nullptr -> ";
        std::cout << el.first -> data << " " << d[el.first] << ' ' << f[el.first] << std::endl;
    }
}
