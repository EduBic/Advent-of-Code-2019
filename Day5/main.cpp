#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

int commasCounter(const string& input) {
    int numberOfCommas = 0;
    for (size_t i = 0; i < input.length(); i++) 
    {
        if (input[i] == ',') {
            numberOfCommas++;
        }
    }
    return numberOfCommas;
}

int* loadProgram(const int numberOfCommas, const string& programInput) {
    // declare and init array for inputs from file
    int* programInputsMemory = new int[numberOfCommas + 1];

    istringstream ss(programInput);
    string token;

    for (int i = 0; getline(ss, token, ','); i++)
    {
        // convert string token to int 
        // and save the input number 
        istringstream strToInput(token);
        strToInput >> programInputsMemory[i];
        // cout << programInputs[i] << endl;
    }

    return programInputsMemory;
}

void splitInstruction(const int instruction, int& op, int& paramMode1, int& paramMode2, int& paramMode3) {
    // Cases (XY > 0)
    // 0 1 1 XY
    // 0 1 0 XY
    // 0 0 1 XY
    // 0 0 0 XY
    paramMode1 = 0;
    paramMode2 = 0;
    paramMode3 = 0;

    // cout << " - Read instruction: " << instruction << endl;

    if (instruction > 1100 && instruction < 1200)
    {
        op = instruction % 1100;
        paramMode1 = 1;
        paramMode2 = 1;
    }
    else if (instruction > 1000 && instruction < 1100)
    {
        op = instruction % 1000;
        paramMode2 = 1;
    }
    else if (instruction > 100 && instruction < 200)
    {
        op = instruction % 100;
        paramMode1 = 1;
    }
    else if (instruction > 0)
    {
        op = instruction;
    }
    else {
        cout << "ERROR READ INSTRUCTION " << instruction << endl;
    }
}


int main(int argc, char *argv[]) 
{
    // read input from file
    // ex.: 3,4,5,30,0, ...
    const string input = readInput(argc, argv);
    int numberOfCommas = commasCounter(input);

    // declare and init array for inputs from file
    int* memory = loadProgram(numberOfCommas, input);

    // ---- Day 5 ----
    
    // Documentation:
    // Give first input: 
    // 1 => Thermal Environment Supervision Terminal (TEST)
    // 5 => ID for the ship's thermal radiator controller
    
    // j is out program counter
    for (int j = 0; j < numberOfCommas + 1;)
    {
        int instruction = memory[j];  // => ex. 1002 -> 02 op, 0 param1 mode, 1 param2 mode, 0 param3 mode  

        int op;
        int param1Mode;
        int param2Mode;
        int param3Mode;

        splitInstruction(instruction, op, param1Mode, param2Mode, param3Mode);

        if (op == 1)
        {
            int val1 = param1Mode == 0 ? memory[memory[j + 1]] : memory[j + 1];
            int val2 = param2Mode == 0 ? memory[memory[j + 2]] : memory[j + 2];
            int val3 = memory[j + 3];   // param3 mode is always 0 

            memory[val3] = val1 + val2;

            // cout << " - ADD " << val1 << " " << val2 << " -> memory[" << val3 << "]" << endl;

            j += 4;
        }
        else if (op == 2)
        {
            int val1 = param1Mode == 0 ? memory[memory[j + 1]] : memory[j + 1];
            int val2 = param2Mode == 0 ? memory[memory[j + 2]] : memory[j + 2];
            int val3 = memory[j + 3];   // param3 mode is always 0
            
            memory[val3] = val1 * val2;
            
            j += 4;
        }
        else if(op == 3)
        {
            // ex. 3, 50
            int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
            cout << "Insert input:" << endl;
            cin >> memory[i1];

            j += 2;
        }
        else if(op == 4)
        {
            // ex. 4,  50
            int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
            cout << memory[i1];
            
            j += 2;
        }
        else if (op == 99)
        {
            break;
        }
    }

    cout << endl << "End" << endl;
}