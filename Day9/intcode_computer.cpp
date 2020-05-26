#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// TODO: relative mode instead of ternary operator

string readInputFile(int argc, char *argv[]) {
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

int commasCounter(const std::string& input) {
    int numberOfCommas = 0;
    for (std::size_t i = 0; i < input.length(); i++) 
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
    // ex. A B C DE => 2 1 2 02
    // 3param 2param 1param Op
    // Cases (XY > 0)
    // 0-0000 0-0100 0-0200 0-1000 0-1100 0-1200 0-2000 0-2100 0-2200 
    // 2-0000 2-0100 2-0200 2-1000 2-1100 2-1200 2-2000 2-2100 2-2200
    paramMode1 = 0;
    paramMode2 = 0;
    paramMode3 = 0;

    // cout << " - Read instruction: " << instruction << endl;
    if (instruction > 22200 && instruction < 22300)
    {
        op = instruction % 22200;
        paramMode1 = 2;
        paramMode2 = 2;
        paramMode3 = 2;
    }
    else if (instruction > 22100 && instruction < 22200)
    {
        op = instruction % 22100;
        paramMode1 = 1;
        paramMode2 = 2;
        paramMode3 = 2;
    }
    else if (instruction > 22000 && instruction < 22100)
    {
        op = instruction % 22000;
        paramMode2 = 2;
        paramMode3 = 2;
    }
    else if (instruction > 21200 && instruction < 21300)
    {
        op = instruction % 21200;
        paramMode1 = 2;
        paramMode2 = 1;
        paramMode3 = 2;
    }
    else if (instruction > 21100 && instruction < 21200)
    {
        op = instruction % 21100;
        paramMode1 = 1;
        paramMode2 = 1;
        paramMode3 = 2;
    }
    else if (instruction > 21000 && instruction < 21100)
    {
        op = instruction % 21000;
        paramMode2 = 1;
        paramMode3 = 2;
    }
    else if (instruction > 20200 && instruction < 20300)
    {
        op = instruction % 20200;
        paramMode1 = 2;
        paramMode3 = 2;
    }
    else if (instruction > 20100 && instruction < 20200)
    {
        op = instruction % 20100;
        paramMode1 = 1;
        paramMode3 = 2;
    }
    else if (instruction > 20000 && instruction < 20100)
    {
        op = instruction % 20000;
        paramMode3 = 2;
    }
    else if (instruction > 2200 && instruction < 2300)
    {
        op = instruction % 2200;
        paramMode1 = 2;
        paramMode2 = 2;
    }
    else if (instruction > 2100 && instruction < 2200)
    {
        op = instruction % 2100;
        paramMode1 = 1;
        paramMode2 = 2;
    }
    else if (instruction > 2000 && instruction < 2100)
    {
        op = instruction % 2000;
        paramMode2 = 2;
    }
    else if (instruction > 1200 && instruction < 1300)
    {
        op = instruction % 1200;
        paramMode1 = 2;
        paramMode2 = 1;
    }
    else if (instruction > 1100 && instruction < 1200)
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
    else if(instruction > 200 && instruction < 300)
    {
        op = instruction % 200;
        paramMode1 = 2;
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


int execute(int argc, char *argv[], int setting, int input) 
{
    // read input from file
    // ex.: 3,4,5,30,0, ...
    const string input_program = readInputFile(argc, argv);
    const int numberOfCommas = commasCounter(input_program);

    // declare and init array for inputs from file
    int* memory = loadProgram(numberOfCommas, input_program);

    bool settingOn = false;
    int program_output;

    // ---- Day 5 ----
    
    // j is our program counter/instruction pointer
    for (int j = 0; j < numberOfCommas + 1;)
    {
        // PRINT MEMORY
        // for (int k = 0; k < numberOfCommas + 1; k++) {
        //     cout << memory[k] << " ";
        // }
        // cout << endl;

        // ex. 1002 -> 02 op, 0 param1 mode, 1 param2 mode, 0 param3 mode
        int instruction = memory[j];

        int op;
        // 0 == position mode
        // 1 == immediate mode
        // 2 == relative mode
        // N.B. Parameters that an instruction writes to will never be in immediate mode.
        int param1Mode;
        int param2Mode;
        int param3Mode;

        splitInstruction(instruction, op, param1Mode, param2Mode, param3Mode);

        if (op == 1)    // sum
        {
            int val1 = param1Mode == 0 ? memory[memory[j + 1]] : memory[j + 1];
            int val2 = param2Mode == 0 ? memory[memory[j + 2]] : memory[j + 2];
            int val3 = memory[j + 3];   // param3 mode is always 0 

            memory[val3] = val1 + val2;

            // cout << " - ADD " << val1 << " " << val2 << " -> memory[" << val3 << "]" << endl;

            j += 4;
        }
        else if (op == 2)   // multiply
        {
            int val1 = param1Mode == 0 ? memory[memory[j + 1]] : memory[j + 1];
            int val2 = param2Mode == 0 ? memory[memory[j + 2]] : memory[j + 2];
            int val3 = memory[j + 3];   // param3 mode is always 0
            
            memory[val3] = val1 * val2;
            
            j += 4;
        }
        else if (op == 3)    // get an input value
        {
            // ex. 3, 50
            int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
            // cout << "Insert input:" << endl;
            //cin >> memory[i1];
            if (settingOn)
            {
                memory[i1] = input;
            }
            else
            {
                memory[i1] = setting;
                settingOn = true;
            }
            
            j += 2;
        }
        else if (op == 4)    // print output value
        {
            // ex. 4,  50
            int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
            // cout << "Output: " << memory[i1] << endl;
            program_output = memory[i1];
            
            j += 2;
        }
        else if (op == 5)   // jump if true
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
        else if (op == 7)   // less than
        {
            int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
            int i2 = param2Mode == 0 ? memory[j + 2] : j + 2;
            int i3 = param3Mode == 0 ? memory[j + 3] : j + 3;

            int param1 = memory[i1];
            int param2 = memory[i2];
            int param3 = i3;
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
            int param3 = i3;
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
        else if (op == 99)  // exit program
        {
            return program_output;
            //break;
        }
    }

    cout << endl << "End" << endl;
    return -1;
}