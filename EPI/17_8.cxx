#include <iostream>
#include <vector>
#include <stack>

bool is_new_pillar_or_reach_end(const std::vector<int>& heights, int curr_idx, int last_pillar_idx)
{
    return curr_idx < heights.size() ? 
    heights[curr_idx] <= heights[last_pillar_idx] :
    true;
}

int skyline(const std::vector<int>& heights)
{
    std::stack<int> pillar_ids;
    int max_area = 0;

    for (int i = 0; i < heights.size(); ++i)
    {
        while (!pillar_ids.empty() && is_new_pillar_or_reach_end(heights, i, pillar_ids.top()))
        {
            int height = heights[pillar_ids.top()];
            pillar_ids.pop();
            int width = pillar_ids.empty() ? i : i - pillar_ids.top() - 1;
            max_area = std::max(max_area, height * width);
        }
        pillar_ids.emplace(i);
    }
    return max_area;
}

int main()
{
    std::cout << skyline({1, 4, 2, 5, 6, 3, 2, 6, 6, 5, 2, 1, 3}) << std::endl;
}
