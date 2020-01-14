#include <string>
#include <iostream>

using namespace std;

struct Point {
    Point(int x, int y): x(x), y(y) {}
    int x;
    int y;
};

// Day 3
int main()
{
    // find the intersections
    // compute Manhattan distance

    // R75,D30,R83,U83,L12,D49,R71,U7,L72
    // U62,R66,U55,R34,D71,R55,D58,R83
    int sizeWire1 = 9;
    string wire1[] = { "R75","D30","R83","U83","L12","D49","R71","U7","L72" };
    int sizeWire2 = 8;
    string wire2[] = { "U62","R66","U55","R34","D71","R55","D58","R83" };

    // Simple example
    // + X
    // o +
    // U1, R1
    // R1, U1
    //
    //  Table 400x400
    //        Punto O(200, 200)
    //
    //   0          ...
    //              1
    //  ...   1  2  3  4  5 ...
    //             -1
    //             ...

    const int numColumns = 400;
    const int numRows = 400;
    Point origin(numColumns / 2, numRows / 2);

    char board[numColumns][numRows];

    board[origin.x][origin.y] = 'o';

    for (int i = 0; i < sizeWire1; i++)
    {
        // print value of wire1 at index i
        cout << wire1[i] << endl;
        char direction = wire1[i].at(0);
        int numSteps = stoi(wire1[i].substr(1, 2));
        if (direction == 'U') {
            board[x][y] = '|'
        }
        else if (direction == 'R') {

        }
        else if (direction == 'D') {

        }
        else if (direction == 'L') {

        }
    }

}