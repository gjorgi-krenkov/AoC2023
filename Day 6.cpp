#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <string>
#include <vector>
#include <math.h>

#define cin infile
#define cout outfile

using namespace std;

const bool partTwo = true;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    string input;

    bool semiColonPass = false;
    bool numDetected = false;
    long double number = 0;
    bool isDistance = false;
    vector<long double> time, dist;
    time.reserve(8);
    dist.reserve(8);

    while (getline(cin, input))
    {
        for (int it = 0; it < input.size(); it++)
        {
            if (input[it] == ':')
            {
                semiColonPass = true;
                continue;
            }
            if (!semiColonPass)
                continue;
            if (input[it] >= '0' && input[it] <= '9')
            {
                numDetected = true;
                number *= 10;
                number += input[it] - '0';
            } else if (!partTwo && numDetected) {
                if (isDistance)
                    dist.push_back(number);
                else
                    time.push_back(number);
                number = 0;
                numDetected = false;
            }
        }
        if (isDistance)
            dist.push_back(number);
        else
            time.push_back(number);
        isDistance = true;
        number = 0;
        numDetected = false;
    }

    long double numOfWays = 0;
    for (int i = 0; i < time.size(); i++)
    {
        long double x1, x2;

        long double b = -time[i];
        long double c = dist[i];
        long double discriminant = (b * b) - 4 * c;
        long double two = 2;
        if (discriminant <= 0)
            continue;

        x1 = (-b + sqrtl(discriminant)) / two;
        x2 = (-b - sqrtl(discriminant)) / two;

        if(x2 == (long long) x2) {
            x1--;
            x2++;
        }
        
        if(numOfWays == 0)
            numOfWays = floor(x1) - ceil(x2) + 1;
        else 
            numOfWays *= floor(x1) - ceil(x2) + 1;
    }
    cout << fixed << numOfWays;
    return 0;
}
