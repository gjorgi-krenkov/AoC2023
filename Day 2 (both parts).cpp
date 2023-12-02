#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <string>

#define cin infile
#define cout outfile

using namespace std;

int getColorVariantConstraint(string variant)
{
    if (((string) "red").compare(variant) == 0)
        return 12;
    if (((string) "green").compare(variant) == 0)
        return 13;
    if (((string) "blue").compare(variant) == 0)
        return 14;
    return 0;
}

void computeMaxForVariant(int &r, int &g, int &b, string variant, int newValue)
{
    if (((string) "red").compare(variant) == 0)
        r = max(r, newValue);
    if (((string) "green").compare(variant) == 0)
        g = max(g, newValue);
    if (((string) "blue").compare(variant) == 0)
        b = max(b, newValue);
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    bool partTwo = true;

    int res = 0;
    string inputLine;
    int gameId = 1;
    while (getline(cin, inputLine))
    {
        string colorVariant = "";
        int number = 0;
        bool passedSemi = false;
        bool numberMode = false;
        bool isValid = true;
        int maxR = 0, maxG = 0, maxB = 0;
        for (int it = 0; it < inputLine.size(); it++)
        {
            // cout << inputLine[it] << " ";

            if (inputLine[it] == ':')
            {
                // cout << "semi" <<endl;
                passedSemi = true;
                continue;
            }
            if (!passedSemi)
            {
                // cout << "Before semi" << endl;
                continue;
            }
            if (!numberMode && inputLine[it] == ' ')
            { // empty before number
                // cout << "before number" <<endl;
                numberMode = true;
                colorVariant = "";
                number = 0;
                continue;
            }
            if (!numberMode && (inputLine[it] == ',' || inputLine[it] == ';')) // end of definition
            {
                // cout << "computation" <<endl;
                if (partTwo)
                    computeMaxForVariant(maxR, maxG, maxB, colorVariant, number);
                else
                {
                    int cstr = getColorVariantConstraint(colorVariant);
                    // cout << number << " " << colorVariant << " " << cstr << endl;
                    if (number > cstr)
                    {
                        isValid = false;
                        break;
                    }
                }
            }
            if (!numberMode)
            {
                // cout << "colorVariant definition" <<endl;
                colorVariant.push_back(inputLine[it]);
            }
            if (numberMode)
            {
                if (inputLine[it] >= '0' && inputLine[it] <= '9')
                {
                    // cout << "Boosting number" << endl;
                    number *= 10;
                    number += inputLine[it] - '0';
                }
                if (inputLine[it] == ' ')
                {
                    // cout << "Switcihng from number to colorVariant" <<endl;
                    // cout << number <<endl;
                    numberMode = false;
                }
            }
        }
        if (isValid && !numberMode) // last case
        {
            if (partTwo)
                computeMaxForVariant(maxR, maxG, maxB, colorVariant, number);
            else
            {
                int cstr = getColorVariantConstraint(colorVariant);
                if (number > cstr)
                {
                    isValid = false;
                }
            }
        }

        if (!partTwo && isValid)
            res += gameId;
        else if (partTwo)
            res += maxR * maxG * maxB;

        gameId++;
    }
    cout << res;
    return 0;
}
