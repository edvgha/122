/*
    1  2  3  4
    5  6  7  8
    9  10 11 12
    13 14 15 16

    1  2  3  4  5  
    6  7  8  9  10
    11 12 13 14 15

    1  2  3 
    4  5  6 
    7  8  9  
    10 11 12

    1  2  3  4  5 
    6  7  8  9  10 
    11 12 13 14 15
    16 17 18 19 20

    1  2  3 
    4  5  6 
    7  8  9  
    10 11 12
    13 14 15

*/

#include <iostream>
#include <vector>
#include <cmath>

void printFrame(std::vector<std::vector<int>>& matrix, int row1, int col1, int row2, int col2, bool t)
{
    //std::cout << std::endl << "param : " << row1 << " " << col1 << " " << row2 << " " << col2 << std::endl;
    if ((row1 == row2) && t) {
        for (int i = col2; i <= col1; ++i) {
            std::cout << matrix[row1][i] << ' ';
        }
    } else if ((col1 == col2) && t) {
        for (int i = row1 + 1; i <= row2; ++i) {
            std::cout << matrix[i][col1] << ' ';
        }
    } else {
        for (int i = col2; i <= col1; ++i) {
            std::cout << matrix[row1][i] << ' ';
        }
        for (int i = row1 + 1; i <= row2; ++i) {
            std::cout << matrix[i][col1] << ' ';
        }
        for (int i = col1 - 1 ; i >= col2; --i) {
            std::cout << matrix[row2][i] << ' ';
        }
        for (int i = row2 - 1; i >= row1 + 1; --i) {
            std::cout << matrix[i][col2] << ' ';
        }
    }
}

void spiralPrint(std::vector<std::vector<int>>& matrix)
{
    size_t row_size = matrix.size();
    size_t col_size = matrix[0].size();
    //std::cout << row_size << " " << col_size << std::endl;
    int row1 = 0;
    int col1 = col_size - 1;
    int row2 = row_size - 1;
    int col2 = 0;
    bool t = (1 == row_size % 2 && 1 == col_size % 2);

    int min = std::min(row_size, col_size);
    int cnt = (min / 2) + (min % 2);
    for (size_t i = 0; i < cnt; ++i) {
        printFrame(matrix, row1, col1, row2, col2, t);
        ++row1;
        --col1;
        --row2;
        ++col2;
    }
    std::cout << std::endl;
}

int main()
{
    {
        std::vector<std::vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
        spiralPrint(matrix);
    }
    {
        std::vector<std::vector<int>> matrix = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}};
        //spiralPrint(matrix);
    }
    {
        std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
        //spiralPrint(matrix);
    }
    {
        std::vector<std::vector<int>> matrix = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}};
        //spiralPrint(matrix);
    }
    {
        std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15}};
        //spiralPrint(matrix);
    }
}
