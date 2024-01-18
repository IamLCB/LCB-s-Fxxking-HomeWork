#include <iostream>

class NQueenSolver
{
public:
    // Constructor: Initializes the board with the given size.
    NQueenSolver(int n) : size(n)
    {
        board = new int *[size];
        for (int i = 0; i < size; ++i)
        {
            board[i] = new int[size]{0}; // Initialize each row with 0s.
        }
    }

    ~NQueenSolver()
    {
        for (int i = 0; i < size; ++i)
        {
            delete[] board[i];
        }
        delete[] board;
    }

    void solve()
    {
        placeQueens(0);
    }

private:
    int size;    // Size of the board (number of queens).
    int **board; // 2D array representing the chess board.

    // Checks if a queen can be safely placed at the given position.
    bool isSafe(int row, int col)
    {
        for (int i = 0; i < row; ++i)
        {
            // Check column, and two diagonals.
            if (board[i][col] == 1)
                return false;
            if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1)
                return false;
            if (col + (row - i) < size && board[i][col + (row - i)] == 1)
                return false;
        }
        return true;
    }

    // Recursive function to place queens on the board.
    void placeQueens(int row)
    {
        if (row == size)
        {
            printSolution();
            return;
        }

        for (int col = 0; col < size; ++col)
        {
            if (isSafe(row, col))
            {
                board[row][col] = 1;  // Place queen.
                placeQueens(row + 1); // Recur to place the rest of the queens.
                board[row][col] = 0;  // Backtrack: remove queen and try next column.
            }
        }
    }

    // Prints one of the solutions to the console.
    void printSolution()
    {
        static int count = 1;
        std::cout << "Solution " << count++ << ":\n";
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                std::cout << (board[i][j] ? "Q" : "_");
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};

int main()
{
    int n;
    std::cout << "Enter the number of queens: ";
    std::cin >> n;
    if (std::cin.fail() || n < 4)
    {
        std::cout << "Invalid input.\n";
        system("pause");
        return 1;
    }
    else if (n > 20)
    {
        std::cout << "Too many queens.\n";
        system("pause");
        return 1;
    }
    NQueenSolver solver(n);
    solver.solve(); // Start the solving process.

    system("pause");

    return 0;
}
