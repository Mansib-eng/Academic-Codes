/// For the 5-Queen Problem, find all solutions and print them .

#include <iostream>
#include <vector>

using namespace std;

void printSolution(vector<vector<int>>& board, int n)
    {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i][j] ? "Q " : "* ");
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(vector<vector<int>>& board, int row, int col, int n)
    {
    // Check this row on the left
    for (int i = 0; i < col; i++)
        {
        if (board[row][i]) return false;
    }

    // Check upper diagonal on the left
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        {
        if (board[i][j]) return false;
    }

    // Check lower diagonal on the left
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
        {
        if (board[i][j]) return false;
    }

    return true;
}

bool solveNQueensUntil(vector<vector<int>>& board, int col, int n)
    {
    // If all queens are placed, return true
    if (col >= n)
        {
        printSolution(board, n);
        return true;
    }

    bool res = false;
    for (int i = 0; i < n; i++)
        {
        if (isSafe(board, i, col, n))
        {

            board[i][col] = 1;

            // Recur to place rest of the queens
            res = solveNQueensUntil(board, col + 1, n) || res;

            // Backtrack
            board[i][col] = 0;
        }
    }
    return res;
}

void solveNQueen(int n)
    {
    vector<vector<int>> board(n, vector<int>(n, 0));
    if (!solveNQueensUntil(board, 0, n))
        {
        cout << "No solution exists" << endl;
    }
}

int main() {
    int n;
    n = 5 ;
    cout << "All Possible Solutions of 5-Queen Problem =>" << endl ;
    cout << endl ;
    solveNQueen(n);
    return 0;
}
