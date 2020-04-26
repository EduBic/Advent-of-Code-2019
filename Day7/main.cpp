#include "intcode_computer.cpp"

using namespace std;


int main(int argc, char *argv[]) 
{
    int amp_count = 5;

    int setting = 0;        // 0, 1, 2, 3, 4
    int signal_input = 0;
    for (int e = 4; e < amp_count; e++)
    {
        for (int d = 3; d < amp_count; d++)
        {
            for (int c = 2; c < amp_count; c++)
            {
                for(int b = 1; b < amp_count; b++)
                {
                    for (int a = 0; a < amp_count; a++)
                    {
                        int amp_output = execute(argc, argv, setting, signal_input);
                        signal_input = amp_output;
                    }
                }
            }
        }
    }

    cout << endl << "End" << endl;
}