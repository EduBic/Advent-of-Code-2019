#include <string>
#include <iostream>

#include "intcode_computer.cpp"

using namespace std;

class Amplificator
{

public:

    Amplificator(const string name, const int setting, int argc, char *argv[]) : 
        name(name), halted(false), setting(setting)
    {
        // read input from file
        // ex.: 3,4,5,30,0, ...
        const string input_program = readInput(argc, argv);
        this->numberOfCommas = commasCounter(input_program);

        // declare and init array for inputs from file
        this->memory =  loadProgram(this->numberOfCommas, input_program);
        this->j = 0;
        this->settingOn = false;
    }

    bool is_halted()
    {
        return this->halted;
    }


    int execute(int input) 
    {
        if (this->is_halted()) {
            cout << "Cannot execute, " << name << " is halt" << endl;
            return input;
        }
        
        // Documentation:
        // Give first input: 
        // 1 => Thermal Environment Supervision Terminal (TEST) (day 5 part 1)
        // 5 => ID for the ship's thermal radiator controller   (day 5 part 2)
        
        // j is our program counter/instruction pointer
        while (j < this->numberOfCommas + 1)
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
                    memory[i1] = this->setting;
                    this->settingOn = true;
                }
                
                j += 2;
            }
            else if (op == 4)    // print output value
            {
                // ex. 4,  50
                int i1 = param1Mode == 0 ? memory[j + 1] : j + 1;
                // cout << "Output: " << memory[i1] << endl;
                int program_output = memory[i1];
                
                j += 2;
                return program_output;
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
                halted = true;
                cout << this->name << " halt" << endl;
                return input;
                //break;
            }
        }

        cout << endl << this->name << "ERROR" << endl;
        return -1;
    }

private:
    const string name;
    bool halted;
    const int setting;

    int* memory;
    int numberOfCommas;
    int j;
    bool settingOn;

};