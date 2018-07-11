#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

struct vertex
{
    char data;
    enum Color { white, gray, black} color = white;
    std::vector<vertex*> edges;
    vertex(char c) : data(c) {}
};

std::vector<vertex*> build()
{
    vertex* r = new vertex('r');
    vertex* v = new vertex('v');
    vertex* s = new vertex('s');
    vertex* w = new vertex('w');
    vertex* t = new vertex('t');
    vertex* x = new vertex('x');
    vertex* y = new vertex('y');
    vertex* u = new vertex('u');

    r -> edges.push_back(s);
    r -> edges.push_back(v);

    s -> edges.push_back(r);
    s -> edges.push_back(w);

    v -> edges.push_back(r);

    w -> edges.push_back(s);
    w -> edges.push_back(t);
    w -> edges.push_back(x);

    t -> edges.push_back(w);
    t -> edges.push_back(u);
    t -> edges.push_back(x);

    x -> edges.push_back(t);
    x -> edges.push_back(w);
    x -> edges.push_back(y);

    y -> edges.push_back(x);
    y -> edges.push_back(u);

    u -> edges.push_back(t);
    u -> edges.push_back(y);
    return {r, v, s, w, t, u, x, y};
}

std::unordered_map<vertex*, int> d;
std::unordered_map<vertex*, vertex*> pi;

void print_path(vertex* s, vertex* v)
{
    if (v == s)
    {
        std::cout << s -> data;
    } 
    else
    {
        if (pi[v] == nullptr)
        {
            std::cout << "no path from " << s -> data << " to " << v -> data << std::endl;
        }
        else
        {
            print_path(s, pi[v]);
            std::cout << " -> " << v -> data;
        }
    }
}

void BFS(std::vector<vertex*> graph, vertex* v)
{
    for (size_t i = 0; i < graph.size(); ++i)
    {
        if (v -> data != graph[i] -> data && graph[i] -> color == vertex::white)
        {
            d[graph[i]] = -1;
            pi[graph[i]] = nullptr;
        }
    }
    std::queue<vertex*> queue;
    d[v] = 0;
    pi[v] = nullptr;
    v -> color = vertex::gray;
    queue.push(v);
    while (!queue.empty())
    {
        vertex* u = queue.front();

        for (size_t i = 0; i < u -> edges.size(); ++i)
        {
            if ((u -> edges)[i] -> color == vertex::white)
            {
                (u -> edges)[i] -> color = vertex::gray;
                d[(u -> edges)[i]] = d[u] + 1;
                pi[(u -> edges)[i]] = u;
                queue.push((u -> edges)[i]);
            }
        }
        u -> color = vertex::black;
        queue.pop();
    }
}

int main()
{
    std::vector<vertex*> g = build();
    BFS(g, g[2]);
    for (auto el : pi)
    {
        if (el.second)
            std::cout << el.second -> data << " -> ";
        else
            std::cout << "nullptr -> ";
        std::cout << el.first -> data << " " << d[el.first] << std::endl;
    }

    print_path(g[2], g[7]);
    std::cout << std::endl;
}
