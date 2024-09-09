#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void updateCell(const std::vector<std::vector<int>> &board, std::vector<std::vector<int>> &newBoard, int row, int col, int n)
{
    int liveNeighbors = 0;
    int rows = board.size();
    int cols = board[0].size();

    for (int i = row - 1; i <= row + 1; ++i)
    {
        for (int j = col - 1; j <= col + 1; ++j)
        {

            int r = (i + rows) % rows;
            int c = (j + cols) % cols;

            if (board[r][c] == 1 && !(r == row && c == col))
            {
                ++liveNeighbors;
            }
        }
    }

    if (liveNeighbors == n)
    {
        newBoard[row][col] = board[row][col];
    }
    else if (liveNeighbors == n + 1)
    {
        newBoard[row][col] = 1;
    }
    else
    {
        newBoard[row][col] = 0;
    }
}

void updateBoard(std::vector<std::vector<int>> &board, int n)
{
    int rows = board.size();
    int cols = board[0].size();

    std::vector<std::vector<int>> newBoard(rows, std::vector<int>(cols, 0)); 

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            updateCell(board, newBoard, i, j, n);
        }
    }

    board = newBoard;
}

void writeMatrixToFile(const std::vector<std::vector<int>> &matrix, const std::string &filename)
{
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        for (const auto &row : matrix)
        {
            for (int val : row)
            {
                file << val << ' ';
            }
            file << '\n';
        }
        file << '\n';
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main()
{

    int rows = 100;
    int cols = 100;
    int generations = 100;

    std::vector<std::vector<int>> board(rows, std::vector<int>(cols, 0));

    board[20][20] = 1;
    board[20][21] = 1;

    board[30][30] = 1;
    board[30][31] = 1;
    board[31][30] = 1;

    board[40][40] = 1;
    board[40][41] = 1;
    board[41][40] = 1;
    board[41][41] = 1;

    board[60][60] = 1;
    board[60][61] = 1;
    board[61][60] = 1;
    board[61][61] = 1;
    board[62][62] = 1;

    board[70][70] = 1;
    board[70][71] = 1;
    board[71][70] = 1;
    board[71][71] = 1;
    board[72][70] = 1;
    board[72][71] = 1;

    board[80][80] = 1;
    board[80][81] = 1;
    board[81][80] = 1;
    board[81][81] = 1;
    board[82][80] = 1;
    board[82][81] = 1;
    board[83][80] = 1;

    board[10][10] = 1;
    board[10][11] = 1;
    board[11][10] = 1;
    board[11][11] = 1;
    board[12][10] = 1;
    board[12][11] = 1;
    board[13][10] = 1;
    board[13][11] = 1;

    board[90][90] = 1;
    board[90][91] = 1;
    board[91][90] = 1;
    board[91][91] = 1;
    board[92][90] = 1;
    board[92][91] = 1;
    board[93][90] = 1;
    board[93][91] = 1;
    board[94][90] = 1;

    for (int n = 1; n <= 8; ++n)
    {
        std::string filename = "simulation_data_periodic_n" + std::to_string(n) + ".data"; 

        std::ofstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Unable to open file for writing!" << std::endl;
            return 1;
        }

        std::vector<std::vector<int>> currentBoard = board;
        for (int generation = 0; generation < generations; ++generation)
        {
            writeMatrixToFile(currentBoard, filename);

            updateBoard(currentBoard, n);
        }

        file.close();
    }

    return 0;
}
