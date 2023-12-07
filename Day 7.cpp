#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

#define cin infile
#define cout outfile

using namespace std;

bool partTwo = true;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    string input;

    auto getHandType = [](string hand)
    {
        map<char, int> mp;
        int jokers = 0;
        for (int i = 0; i < 5; i++)
        {
            char card = hand[i];
            if(partTwo && card == 'J') {
                jokers++; 
                continue;
            }
            mp[card]++;
        }
        vector<int> values;
        for (auto y : mp)
            values.push_back(y.second);
        sort(values.begin(), values.end());
        reverse(values.begin(), values.end());
        if(jokers == 5)
            return 7;
        values[0] += jokers;
        if (values[0] == 5)
            return 7;
        if (values[0] == 4)
            return 6;
        if (values[0] == 3 && values[1] == 2)
            return 5;
        if (values[0] == 3 && values[1] == 1)
            return 4;
        if (values[0] == 2 && values[1] == 2)
            return 3;
        if (values[0] == 2 && values[1] == 1)
            return 2;
        return 1;
    };
    auto toNumCast = [](char c)
    {
        if (c >= '1' && c <= '9')
            return c - '0';
        if (c == 'T')
            return 10;
        if (c == 'J')
            return partTwo ? 1 : 11;
        if (c == 'Q')
            return 12;
        if (c == 'K')
            return 13;
        if (c == 'A')
            return 14;
        return 0;
    };
    auto isSecondHandBetter = [toNumCast](string hand1, string hand2)
    {
        for (int i = 0; i < 5; i++)
        {
            if (toNumCast(hand1[i]) > toNumCast(hand2[i]))
                return true;
            if (toNumCast(hand1[i]) < toNumCast(hand2[i]))
                return false;
        }
        return false;
    };

    vector<pair<string, int>> hands;

    while (getline(cin, input))
    {
        string hand = "";
        int val = 0;
        bool spacePassed = false;
        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] == ' ')
            {
                spacePassed = true;
                continue;
            }
            if (spacePassed)
            {
                val *= 10;
                val += input[i] - '0';
            }
            else
            {
                hand.push_back(input[i]);
            }
        }
        hands.push_back(make_pair(hand, val));
    }

    sort(hands.begin(), hands.end(), [isSecondHandBetter, getHandType](auto a, auto b)
         {
        if(getHandType(a.first) > getHandType(b.first)) return false;
        if (getHandType(a.first) < getHandType(b.first)) return true;
        return !isSecondHandBetter(a.first, b.first); });

    int sum = 0;
    for(int i = 0; i < hands.size(); i++)
    {
        sum += hands[i].second * (i+1);
    }
    cout << sum;
    return 0;
}
