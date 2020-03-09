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
    // 1 => Thermal Environment Supervision Terminal (TEST) (day 5 part 1)
    // 5 => ID for the ship's thermal radiator controller   (day 5 part 2)
    
    // j is our program counter/instruction pointer
    for (int j = 0; j < numberOfCommas + 1;)
    {
        // PRINT MEMORY
        // for (int k = 0; k < numberOfCommas + 1; k++) {
        //     cout << memory[k] << " ";
        // }
        // cout << endl;

        int instruction = memory[j];  // => ex. 1002 -> 02 op, 0 param1 mode, 1 param2 mode, 0 param3 mode  

        int op;
        // 0 == position mode
        // 1 == immediate mode
        // N.B. Parameters that an instruction writes to will never be in immediate mode.
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
            cout << "Output: " << memory[i1] << endl;
            
            j += 2;
        }
        else if (op == 5)
        {
            int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
            int i2 = param2Mode == 0 ? memory[j + 2] : j + 2;

            int param1 = memory[i1];
            int param2 = memory[i2];
            if (param1 != 0)
            {
                j = param2;
            }
            else {
                j += 3;
            }
        }
        else if (op == 6)   // jump if false
        {
            int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
            int i2 = param2Mode == 0 ? memory[j + 2] : j + 2;

            int param1 = memory[i1];
            int param2 = memory[i2];
            if (param1 == 0)
            {
                j = param2;
            }
            else {
                j += 3;
            }
        }
        else if (op == 7)   // less to
        {
            int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
            int i2 = param2Mode == 0 ? memory[j + 2] : j + 2;
            int i3 = param3Mode == 0 ? memory[j + 3] : j + 3;

            int param1 = memory[i1];
            int param2 = memory[i2];
            int param3 = i3;    // TODO
            if(param1 < param2)
            {
                memory[param3] = 1;
            }
            else
            {
                memory[param3] = 0;
            }
            j += 4;
        }
        else if (op == 8)   // equal to
        {
            int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
            int i2 = param2Mode == 0 ? memory[j + 2] : j + 2;
            int i3 = param3Mode == 0 ? memory[j + 3] : j + 3;

            int param1 = memory[i1];
            int param2 = memory[i2];
            int param3 = i3;    // TODO
            if(param1 == param2)
            {
                memory[param3] = 1;
            }
            else
            {
                memory[param3] = 0;
            }
            j += 4;
        }
        else if (op == 99)
        {
            break;
        }
    }

    cout << endl << "End" << endl;
}