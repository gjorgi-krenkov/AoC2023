#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <vector>
#include <string>
#include <utility>

#define cin infile
#define cout outfile

using namespace std;

const bool partTwo = true;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    vector<pair<long long, long long>> seeds;
    seeds.reserve(100000);
    string input;
    getline(cin, input);
    bool semiColonPass = false;
    bool numDetected = false;
    long long number = 0;
    long long storedNumber;
    bool switchPair = false;
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
        }
        else if (numDetected)
        {
            if (partTwo && switchPair)
            {
                seeds.push_back(make_pair(storedNumber, number));
                switchPair = false;
            }
            else if(partTwo && !switchPair)
            {
                storedNumber = number;
                switchPair = true;
            } else if(!partTwo)
            {
                seeds.push_back(make_pair(number, 1));
            }
            number = 0;
            numDetected = false;
        }
    }
    if(partTwo)
        seeds.push_back(make_pair(storedNumber, number));
    else 
        seeds.push_back(make_pair(number, 1));
    number = 0;
    numDetected = false;
    vector<pair<long long, long long>> cpy_seeds(seeds);
    vector<long long> conversions;

    while (getline(cin, input))
    {
        if (!(input[0] >= '0' && input[0] <= '9'))
        {
            seeds = cpy_seeds;
            continue;
        }
        for (int it = 0; it < input.size(); it++)
        {
            if (input[it] >= '0' && input[it] <= '9')
            {
                numDetected = true;
                number *= 10;
                number += input[it] - '0';
            }
            else if (numDetected)
            {
                numDetected = false;
                conversions.push_back(number);
                number = 0;
            }
        }
        conversions.push_back(number);
        number = 0;
        numDetected = false;

        long long dest = conversions[0];
        long long src = conversions[1];
        long long range = conversions[2];
        long long rangeEnd = src + range;

        for (int i = 0; i < seeds.size(); i++)
        {
            pair<long long, long long> &visitingRange = seeds[i];
            long long visitStart = visitingRange.first;
            long long visitEnd = visitStart + visitingRange.second;
            bool disjointRanges = src >= visitEnd || rangeEnd <= visitStart;
            if (disjointRanges)
                continue;
            // Let's create new ranges for anything that's not intersected
            if (src > visitStart && src < visitEnd)
            {
                // [visitStart, src-visitStart) items shouldn't be changed
                // keep them on this index and spawn new range in both arrays;
                // newRange []
                pair<long long, long long> newRange = make_pair(visitingRange.first + src - visitStart, visitingRange.second - (src - visitStart));

                // Add the new range
                seeds.push_back(newRange);
                cpy_seeds.push_back(newRange);

                visitingRange.second = src - visitStart; // reduce size of current pair in original
                cpy_seeds[i].second = src - visitStart;  // reduce size of current pair in copy

                continue;
            }
            if (rangeEnd < visitEnd && rangeEnd >= visitStart)
            {
                // [rangeEnd, visitEnd) items shouldn't be changed
                // keep them on this index and spawn new range in both arrays;
                long long diff = visitEnd - rangeEnd;

                pair<long long, long long> newRange = make_pair(visitingRange.first, visitingRange.second - diff);

                // Add the new range
                seeds.push_back(newRange);
                cpy_seeds.push_back(newRange);

                visitingRange.first = rangeEnd;
                cpy_seeds[i].first = rangeEnd;
                visitingRange.second = diff; // reduce size of current pair in original
                cpy_seeds[i].second = diff;  // reduce size of current pair in copy
                continue;
            }
            // whole segment is contained in [src, src + range] => change the starting value in copy // [16, 2] [30, 5]
            cpy_seeds[i].first = cpy_seeds[i].first - src + dest;
        }
        conversions.clear();
    }
    seeds = cpy_seeds;
    long long minimum = 10000000000;
    for (auto &seed : seeds)
    {
        minimum = min(seed.first, minimum);
    }
    cout << minimum;

    return 0;
}
