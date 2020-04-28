#include "intcode_computer.cpp"

using namespace std;


int main(int argc, char * argv[]) {
    
    int amp_count = 5;

    // setting 0, 1, 2, 3, 4

    // A for 0, 1, 2, 3, 4                  A := setting_phase of amp A
    // B for 0, 1, 2, 3, 4 != A
    // C for 0, 1, 2, 3, 4 != A, B
    // D for 0, 1, 2, 3, 4 != A, B, C
    // E for 0, 1, 2, 3, 4 != A, B, C, D

    int count = 0;
    int max_out = 0;

    for (int a = 0; a < amp_count; a++) 
    {
        for (int b = 0; b < amp_count; b++) 
        {
            if (b != a) 
            {
                for (int c = 0; c < amp_count; c++) 
                {
                    if (c != a && c != b)
                    {
                        for (int d = 0; d < amp_count; d++) 
                        {
                            if (d != a && d != b && d != c)
                            {
                                for (int e = 0; e < amp_count; e++) 
                                {
                                    if (e != a && e != b && e != c && e != d)
                                    {
                                        count++;
                                        int amp_output_a = execute(argc, argv, a, 0);
                                        int amp_output_b = execute(argc, argv, b, amp_output_a);
                                        int amp_output_c = execute(argc, argv, c, amp_output_b);
                                        int amp_output_d = execute(argc, argv, d, amp_output_c);
                                        int amp_output_e = execute(argc, argv, e, amp_output_d);

                                        // signal_input = amp_output;
                                        cout << a << "," << b << "," << c << "," << d << "," << e 
                                             << "\t=>\t"
                                             << "Signal Output: " << amp_output_e << endl;

                                        if (amp_output_e > max_out) {
                                            max_out = amp_output_e; 
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "Total comb: " << count << endl << "Max output: " << max_out << endl << "End" << endl;
}