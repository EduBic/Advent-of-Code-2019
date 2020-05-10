#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string readInput(int argc, char *argv[]) {
    if (argc != 2)
    {
        cerr << "Insert file name as input" << endl;
        exit(1);
    }

    ifstream inputList;
    inputList.open(argv[1]);

    if (!inputList)
    {
        cerr << "Unable to open file " << argv[1];
        exit(1);   // call system to stop
    }

    // read input from file
    // ex.: 3,4,5,30,0, ...
    string input;
    inputList >> input;

    return input;
}


int main(int argc, char* argv[])
{
    int wide = 25;
    int tall = 6;

    string input = readInput(argc, argv);

    int minNumZero = 15000;
    int minNumZeroLayer = -1;
    int minNumOneDigit = 15000;
    int minNumTwoDigit = 15000;

    int layer = 1;
    int currNumZeroDigit = 0;
    int currNumOneDigit = 0;
    int currNumTwoDigit = 0;

    for (int i = 0; i < input.length(); i++) 
    {
        int pixel = (input[i] - '0') % 48;

        if (pixel == 0) {
            currNumZeroDigit++;
        }
        else if (pixel == 1) 
        {
            currNumOneDigit++;
        }
        else if (pixel == 2)
        {
            currNumTwoDigit++;
        }


        if (i + 1 == wide * tall * layer)
        {
            if (currNumZeroDigit < minNumZero)
            {
                minNumZeroLayer = layer;
                minNumZero = currNumZeroDigit;
                minNumOneDigit = currNumOneDigit;
                minNumTwoDigit = currNumTwoDigit;
            }
            // next layer
            layer++;
            currNumZeroDigit = 0;
            currNumOneDigit = 0;
            currNumTwoDigit = 0;
        }
    }

    cout << "Final Result: " << minNumOneDigit * minNumTwoDigit << endl;

}