#include <string>
#include <iostream>

using namespace std;

struct Point {
    Point(int x, int y): x(x), y(y) {}
    int x;
    int y;
};

template <size_t numRows, size_t numColumns>
void print(char (&board)[numRows][numColumns]) {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numColumns; col++) {
            cout << board[row][col] << ' ';
        }
        cout << endl;
    }
}

template <size_t numRows, size_t numColumns>
void wireTracking(const Point& origin, const int sizeWire, const string wire[], char (&board)[numRows][numColumns])
{
    int currentX = origin.x;
    int currentY = origin.y;
    
    for (int i = 0; i < sizeWire; i++)
    {
        // print value of wire1 at index i
        cout << wire[i] << endl;
        char direction = wire[i].at(0);
        int steps = stoi(wire[i].substr(1, 2)); // get second char of instruction

        for (int k = 0; k < steps; k++)
        {
            if (direction == 'R')
            {
                currentX++;
            }
            else if (direction == 'U')
            {
                currentY--;
            }
            else if (direction == 'L')
            {
                currentX--;
            }
            else if (direction == 'D')
            {
                currentY++;
            }
            
            if (board[currentY][currentX] == '*')
            {
                board[currentY][currentX] = 'x';
            }
            else 
            {
                board[currentY][currentX] = '*';
            }
        }

        cout << "(" << currentX << "," << currentY << ")" << endl;

        cout << endl;
        print<numRows, numColumns>(board);
    }
}

// Day 3
int main()
{
    // find the intersections
    // compute Manhattan distance
    //  https://xlinux.nist.gov/dads/HTML/manhattanDistance.html

    // R75,D30,R83,U83,L12,D49,R71,U7,L72
    // U62,R66,U55,R34,D71,R55,D58,R83
    int sizeWire1 = 4; //9
    string wire1[] = {"R8", "U5", "L5", "D3"}; // { "R75","D30","R83","U83","L12","D49","R71","U7","L72" };
    int sizeWire2 = 4;
    string wire2[] = {"U7", "R6", "D4", "L4"}; //{ "U62","R66","U55","R34","D71","R55","D58","R83" };

    // Simple example
    // + X
    // o +
    // U1, R1
    // R1, U1
    //
    //  Table 400x400
    //        Punto O(200, 200)
    //

    const int numColumns = 10;
    const int numRows = 14;
    // Point origin(numColumns / 2, numRows / 2);
    Point origin(1, 12);

    char board[numRows][numColumns];

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numColumns; col++) {
            board[row][col] = '.';
        }
    }

    board[origin.y][origin.x] = 'o';

    wireTracking<numRows, numColumns>(origin, sizeWire1, wire1, board);
    wireTracking<numRows, numColumns>(origin, sizeWire2, wire2, board);

}