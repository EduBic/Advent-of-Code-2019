
#include<iostream>

using std::cout;
using std::endl;


bool checkTriple(const int cm, const int dm, const int m, const int c, const int d, const int u) {
    //                   0  1  2  3  4  5
    const int num[] = { cm, dm, m, c, d, u };

    for (int i = 0; i < 4; i++)
    {
        if (num[i] == num[i + 1] && num[i + 1] == num[i + 2]) 
        {
            return true;
        }
    }

    return false;
}

int main()
{
    // range
    // int min = 231832; int max = 767346;
    int min = 138307; int max = 654504;
    int passwordsCounter = 0;

    for (int cm = 0; cm <= 9; cm++)
    {
        for (int dm = cm; dm <= 9; dm++)
        {
            for (int m = dm; m <= 9; m++)
            {
                for (int c = m; c <= 9; c++)
                {
                    for (int d = c; d <= 9; d++)
                    { 
                        for (int u = d; u <= 9; u++)
                        {
                            int counter = (cm * 100000) + (dm * 10000) + (m * 1000) 
                                        + (c * 100) + (d * 10) + u;
                            // cout << counter << ", ";
                            if ( (counter >= min && counter <= max) && 
                                (cm == dm || dm == m || m == c || c == d || d == u) &&
                                !checkTriple(cm, dm, m, c, d, u) )
                            {
                                cout << cm << dm << m << c << d << u << endl;
                                passwordsCounter++;
                            }
                            // TODO: checkTriple remove valid number, like 111122
                        }
                    }
                }
            }
        }
    }  

    cout << "Number of different password between: (" 
         << min << ", " << max << "): " 
         << passwordsCounter << endl; 
}