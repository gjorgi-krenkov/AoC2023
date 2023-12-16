#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#define cin infile
#define cout outfile

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

bool isMatchingCount(string row, vector<int> currArr)
{
    int hCount = 0;
    int index = 0;
    bool continueProcessing = true;
    for (auto r : row)
    {
        if (r == '#')
        {
            hCount++;
            if (index >= currArr.size() || hCount > currArr[index])
                return false;
        }
        if (r == '.' && hCount)
        {

            if (index >= currArr.size() || hCount != currArr[index])
                return false;
            index++;
            hCount = 0;
        }
        if (r == '?')
        {
            return continueProcessing;
        }
    }

    if (hCount)
    {
        if (index >= currArr.size() || hCount != currArr[index])
            return false;
        index++;
        hCount = 0;
    }

    return index == currArr.size();
}

bool hasNoQuotes(string row)
{
    for (auto r : row)
        if (r == '?')
            return false;
    return true;
}

long long countArrs(string row, vector<int> arrangement, set<string> &visited)
{
    // cout << row << endl;
    if (visited.count(row))
        return 0;
    if (!isMatchingCount(row, arrangement))
    {
        visited.insert(row);
        return 0;
    }
    if (hasNoQuotes(row))
    {
        if (visited.count(row))
            return 0;
        visited.insert(row);
        return 1;
    }
    long long subRes = 0;
    for (int q = 0; q < row.size(); q++)
    {
        if (row[q] == '?')
        {
            row[q] = '#';
            if (!visited.count(row))
                subRes += countArrs(row, arrangement, visited);
            visited.insert(row);

            row[q] = '.';
            if (!visited.count(row))
                subRes += countArrs(row, arrangement, visited);
            visited.insert(row);
        }
    }
    visited.insert(row);
    return subRes;
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    string input;
    long long res = 0;
    while (getline(cin, input))
    {
        string chars = "";
        bool charMode = true;
        bool numDetected = false;
        vector<int> desiredArrs;
        int number = 0;
        for (int it = 0; it < input.size(); it++)
        {
            if (input[it] == ' ')
                charMode = false;
            if (charMode)
                chars.push_back(input[it]);
            if (input[it] >= '0' && input[it] <= '9')
            {
                numDetected = true;
                number *= 10;
                number += input[it] - '0';
            }
            else if (numDetected)
            {
                desiredArrs.push_back(number);
                number = 0;
                numDetected = false;
            }
        }
        desiredArrs.push_back(number);
        set<string> visited;
        string c5 = chars + '?';
        string c5x = '?' + chars;
        string c6x = '?' + chars + '?';
        vector<int> dA5 = desiredArrs;

        long long p1 = countArrs(chars, desiredArrs, visited);
        visited.clear();
        long long p2 = countArrs(c5, dA5, visited);
        visited.clear();
        long long p3 = countArrs(c5x, dA5, visited);
        visited.clear();
        long long p4 = countArrs(c6x, dA5, visited);

        long long hs = max({
            p1 * p2 * p2 * p2 * p2,
            p1 * p3 * p3 * p3 * p3,
            p1 * p1 * p1 * p4 * p4,
            p4 * p1 * p2 * p2 * p1,
            p4 * p1 * p3 * p3 * p1,
        });
        res += chars[chars.size() - 1] == '#' || chars[0] == '#' ? p1 : hs;
    }
    cout << res << endl;
    return 0;
}
