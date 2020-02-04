#include <string>
#include <iostream>

using namespace std;

struct Point {
    Point(): x(0), y(0) {}
    Point(int x, int y): x(x), y(y) {}
    int x;
    int y;
};

template <typename T> 
int sgn(T val) {
    return val < 0 ? -val : val;
}

void print(char** board, const int numRows, const int numColumns) {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numColumns; col++) {
            cout << board[row][col] << ' ';
        }
        cout << endl;
    }
}

void wireTracking(const Point& origin, const int sizeWire, 
    const string wire[], char** board, 
    Point intersections[100], int& intersectionCount, 
    char idCurrentWire, char idOtherWire)
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
            
            if (board[currentY][currentX] == idOtherWire)
            {
                board[currentY][currentX] = 'x';
                intersections[intersectionCount] = Point(currentX, currentY);
                intersectionCount++;
            }
            else 
            {
                board[currentY][currentX] = idCurrentWire;
            }
        }

        cout << "(" << currentX << "," << currentY << ")" << endl;

        cout << endl;
        //print<numRows, numColumns>(board);
    }
}

// Day 3
int main()
{
    // find the intersections
    // compute Manhattan distance
    //  https://xlinux.nist.gov/dads/HTML/manhattanDistance.html

    cout << "Init wires" << endl;
    int sizeWire1 = 4; //9
    string wire1[] = 
        {"R8","U5","L5","D3"};
        // { "R75","D30","R83","U83","L12","D49","R71","U7","L72" };
        //{"R98","U47","R26","D63","R33","U87","L62","D20","R33","U53","R51"};

    int sizeWire2 = 4;
    string wire2[] = 
        {"U7","R6","D4","L4"};                                          // ex 0
        // { "U62","R66","U55","R34","D71","R55","D58","R83" };         // ex 1 => 8
        // {"U98","R91","D20","R16","D67","R40","U7","R15","U6","R7"};  // ex 2

    

    // Simple example
    // + X
    // o +
    // U1, R1
    // R1, U1
    //
    //  Table 400x400
    //        Punto O(200, 200)
    
    cout << "Init Board" << endl;
    const int numColumns = 10000;
    const int numRows = 10000;
    Point origin(numColumns / 2 - 1, numRows / 2 - 1);
    cout << "Origin (" << origin.x << ", " << origin.y << ")" << endl;

    // allocate board
    char** board = new char*[numRows];
    for (int indexRow = 0; indexRow < numRows; indexRow++) {
        board[indexRow] = new char[numColumns];
    }

     // board[numRows][numColumns];
    Point intersections[1000];
    int intersectionCount = 0;
    
    // init board
    cout << "Board creation" << endl;
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numColumns; col++) {
            board[row][col] = '.';
        }
    }

    board[origin.y][origin.x] = 'o';

    cout << "DEBUG: start tracking 1 wire" << endl;
    wireTracking(origin, sizeWire1, wire1, board, intersections, intersectionCount, 'A', 'B');
    cout << "DEBUG: start tracking 2 wire" << endl;
    wireTracking(origin, sizeWire2, wire2, board, intersections, intersectionCount, 'B', 'A');

    cout << "Origin (" << origin.x << ", " << origin.y << ")" << endl;
    cout << intersectionCount << " intersections found" << endl;
    for (int i = 0; i < intersectionCount; i++) {
        cout << "\t(" << intersections[i].x << ", " << intersections[i].y << ")" << endl;
    }

    // print(board, numRows, numColumns);

    int minDistance = INT_MAX;
    // Compute Manhattan distance
    for (int i = 0; i < intersectionCount; i++)
    {
        int distance = sgn(origin.x - intersections[i].x) + sgn(origin.y - intersections[i].y);
        cout << i << ") " << distance << endl;
        if (minDistance > distance)
        {
            minDistance = distance;
        }
    }
    cout << minDistance << " is the min distance" << endl;
}