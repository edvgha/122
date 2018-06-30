#include <iostream>
#include <vector>

std::vector<std::pair<int, int>> get_neighbors(std::vector<std::vector<int>> grid, std::pair<int, int> id)
{
    std::vector<std::pair<int, int>> r;

    auto [x, y] = id;

    if (x != 0) 
    {
        r.push_back({x - 1, y});
    }
    if (x != grid.size() - 1)
    {
        r.push_back({x + 1, y});
    }
    if (y != 0) 
    {
        r.push_back({x, y - 1});
    }
    if (y != grid[0].size() - 1)
    {
        r.push_back({x, y + 1});
    }
    return r;
}

std::vector<std::pair<int, int>> find_elem_in(std::vector<std::vector<int>> grid, int elem)
{
    std::vector<std::pair<int, int>> r;
    for (size_t i = 0; i < grid.size(); ++i)
    {
        for (size_t j = 0; j < grid[0].size(); ++j)
        {
            if (grid[i][j] == elem)
                r.push_back({i, j});
        }
    }
    return r;
}

std::vector<std::pair<int, int>> find_patter_internal(std::vector<std::vector<int>> grid, std::vector<int> arr, size_t narr)
{
    if (narr == arr.size() - 1)
    {
        return find_elem_in(grid, arr[arr.size() - 1]);
    }

    std::vector<std::pair<int, int>> r = find_patter_internal(grid, arr, narr + 1);

    if (r.empty())
        return {};

    std::vector<std::pair<int, int>> result;
    for (size_t i = 0; i < r.size(); ++i)
    {
        std::vector<std::pair<int, int>> ne = get_neighbors(grid, r[i]);
        for (size_t j = 0; j < ne.size(); ++j) 
        {
            if (grid[ne[j].first][ne[j].second] == arr[narr])
            {
                result.push_back(ne[j]);
            }
        }
    }
    return result;
}

bool find_patter(std::vector<std::vector<int>> grid, std::vector<int> arr)
{
    std::vector<std::pair<int, int>> r = find_patter_internal(grid, arr, 0);
    return !r.empty();
}

int main()
{
    //std::cout << std::boolalpha << find_patter({{1, 2, 3}, {3, 4, 5}, {5, 6, 7}}, {1, 3, 4, 6}) << std::endl;
    std::cout << std::boolalpha << find_patter({{1, 2, 3}, {3, 4, 5}, {5, 6, 7}}, {1, 2, 3, 4}) << std::endl;
}
