#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
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

    int numberOfCommas = 0;
    for (size_t i = 0; i < input.length(); i++) 
    {
        if (input[i] == ',') {
            numberOfCommas++;
        }
    }

    // declare and init array for inputs from file
    int* programInputs = new int[numberOfCommas + 1];


    istringstream ss(input);
    string token;

    for (int i = 0; getline(ss, token, ','); i++)
    {
        // convert string token to int 
        // and save the input number 
        istringstream strToInput(token);
        strToInput >> programInputs[i];
        // cout << programInputs[i] << endl;
    }

    // ---- Day 2 ----

    // Replace pos 1 with value 12
    // and pos 2 with value 2
    programInputs[1] = 12;
    programInputs[2] = 2;

    // hop 4 input: opCode (ex 1,0,0,3)
    // arithmetic operation             -> 1 <- ADD (+)
    // index where take first value     -> 0 <- programInputs[0] (a value)
    // index where take second value    -> 0 <- programInputs[0] (a value)
    // index where store the result     -> 3 <- programInputs[3] = (assign the result of ADD)
    
    for (int j = 0; j < numberOfCommas + 1; j += 4)
    {
        int param1 = programInputs[j + 1];
        int param2 = programInputs[j + 2];
        int param3 = programInputs[j + 3];
        if (programInputs[j] == 1)
        {
            programInputs[param3] = programInputs[param1] + programInputs[param2];
        }
        else if (programInputs[j] == 2)
        {
            programInputs[param3] = programInputs[param1] * programInputs[param2];
        }
        else if (programInputs[j] == 99)
        {
            break;
        }
    }
    
    cout << programInputs[0] << endl;
}