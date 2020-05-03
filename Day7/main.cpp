#include "Amplificator.hpp"

using namespace std;


int main(int argc, char * argv[]) {
    
    int min_window_settings = 5;
    int max_window_settings = 9;

    // setting 0, 1, 2, 3, 4

    // A for 0, 1, 2, 3, 4                  A := setting_phase of amp A
    // B for 0, 1, 2, 3, 4 != A
    // C for 0, 1, 2, 3, 4 != A, B
    // D for 0, 1, 2, 3, 4 != A, B, C
    // E for 0, 1, 2, 3, 4 != A, B, C, D

    int count = 0;
    int max_out = 0;

    for (int a = min_window_settings; a <= max_window_settings; a++) 
    {
        for (int b = min_window_settings; b <= max_window_settings; b++) 
        {
            if (b != a) 
            {
                for (int c = min_window_settings; c <= max_window_settings; c++) 
                {
                    if (c != a && c != b)
                    {
                        for (int d = min_window_settings; d <= max_window_settings; d++) 
                        {
                            if (d != a && d != b && d != c)
                            {
                                for (int e = min_window_settings; e <= max_window_settings; e++) 
                                {
                                    if (e != a && e != b && e != c && e != d)
                                    {
                                        // combination: a b c d e <= settings for ampls
                                        count++;
                                        int amp_output = 0;
                                        Amplificator* amp_a = new Amplificator("A", a, argc, argv);
                                        Amplificator* amp_b = new Amplificator("B", b, argc, argv);
                                        Amplificator* amp_c = new Amplificator("C", c, argc, argv);
                                        Amplificator* amp_d = new Amplificator("D", d, argc, argv);
                                        Amplificator* amp_e = new Amplificator("E", e, argc, argv);

                                        while (!amp_a->is_halted() && 
                                                !amp_b->is_halted() && 
                                                !amp_c->is_halted() && 
                                                !amp_d->is_halted() && 
                                                !amp_e->is_halted()) 
                                        {
                                            amp_output = amp_a->execute(amp_output);
                                            amp_output = amp_b->execute(amp_output);
                                            amp_output = amp_c->execute(amp_output);
                                            amp_output = amp_d->execute(amp_output);
                                            amp_output = amp_e->execute(amp_output);
                                        }

                                        // signal_input = amp_output;
                                        cout << a << "," << b << "," << c << "," << d << "," << e 
                                            << "\t=>\t"
                                            << "Signal Output: " << amp_output << endl;

                                        if (amp_output > max_out) {
                                            max_out = amp_output; 
                                        }

                                        delete amp_a, amp_b, amp_c, amp_d, amp_e;
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