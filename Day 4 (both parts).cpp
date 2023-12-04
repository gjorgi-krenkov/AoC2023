#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <string>
#include <set>
#include <vector>

#define cin infile
#define cout outfile

using namespace std;

const bool partTwo = true;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    string inputLine;
    int totalRes = 0;
    vector<int> dp(205, 0);

    int idx = 0;
    while (getline(cin, inputLine))
    {
        int number = 0;
        bool hasNumber = false;
        bool passedSemi = false;
        bool parsingWinningCards = true;
        set<int> winningCards{};
        int localRes = 0;

        for (int it = 0; it < inputLine.size(); it++)
        {
            if (inputLine[it] == ':')
            {
                passedSemi = true;
                continue;
            }
            if (!passedSemi)
            {
                continue;
            }
            if (inputLine[it] == '|')
            {
                parsingWinningCards = false;
                continue;
            }
            if (inputLine[it] >= '0' && inputLine[it] <= '9')
            {
                hasNumber = true;
                number *= 10;
                number += inputLine[it] - '0';
            }
            if (inputLine[it] == ' ')
            {
                if (hasNumber && parsingWinningCards)
                {
                    winningCards.insert(number);
                }
                else if (hasNumber && winningCards.count(number))
                {
                    if (!localRes)
                        localRes = 1;
                    else if (!partTwo)
                        localRes += localRes;
                    else
                        localRes++;
                }
                hasNumber = false;
                number = 0;
            }
        }
        if (winningCards.count(number))
        {
            if (!localRes)
                localRes = 1;
            else if (!partTwo)
                localRes += localRes;
            else
                localRes++;
        }
        if (partTwo)
        {
            dp[idx]++;
            for (int i = 1; i <= localRes; i++)
            {
                dp[idx + i] += dp[idx];
            }
        }
        else
            totalRes += localRes;
        winningCards.clear();
        parsingWinningCards = true;
        localRes = 0;
        number = 0;
        passedSemi = false;
        hasNumber = false;
        idx++;
    }
    if (partTwo)
        for (auto cnt : dp)
            totalRes += cnt;
    cout << totalRes;
    return 0;
}
