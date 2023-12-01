#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <string>
#include <vector>
#include <algorithm>

#define cin infile
#define cout outfile

using namespace std;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    const bool partTwo = true;

    const vector<string> cipherIds = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int sum = 0;
    string inputLine;
    while (getline(cin, inputLine))
    {
        string num;
        int index = 0;
        bool rtl = false;
        for (int it = 0; it < inputLine.size(); it++)
        {
            if (rtl)
                index = inputLine.size() - 1 - it;
            else
                index = it;

            if (inputLine[index] >= '0' && inputLine[index] <= '9')
            {
                num.push_back(inputLine[index]);
                if (rtl)
                    break;
                it = -1;
                rtl = true;
                continue;
            }
            // Part two
            for (char cipher = '0'; partTwo && cipher <= '9'; cipher++)
            {
                string cipherId = cipherIds[cipher - '0'];
                if (index <= inputLine.size() - cipherId.size())
                {

                    string sstr = inputLine.substr(index, cipherId.size());

                    if (cipherId.compare(sstr) == 0)
                    {
                        num.push_back(cipher);
                        if (rtl)
                            it = inputLine.size() + 1;
                        else
                            it = -1;

                        rtl = true;
                        break;
                    }
                }
            }
        }
        sum += (num[0] - '0') * 10 + (num[num.size() - 1] - '0');
    }

    cout << sum;

    return 0;
}
