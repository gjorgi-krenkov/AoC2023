#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <vector>
#include <string>
#include <utility>
#include <set>
#include <map>

#define cin infile
#define cout outfile

using namespace std;

const bool partTwo = true;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    vector<string> graph;
    string line;
    while (getline(cin, line))
        graph.push_back(line);

    int graphWidth = graph[0].size();
    int graphHeight = graph.size();
    int currNumber = 0;
    long long result = 0;
    bool numberMode = false;
    bool isPartNumber = false;
    set<pair<int, int>> partPosForCurrNum{};
    map<pair<int, int>, vector<int>> partNumbers{};

    auto isCharNumber = [](char c)
    { return c >= '0' && c <= '9'; };
    auto isPartHelper = [isCharNumber](char h)
    { return partTwo ? h == '*' : !isCharNumber(h) && h != '.'; };
    auto areCoordsValid = [&graphWidth, &graphHeight](int rIdx, int cIdx)
    {
        return rIdx >= 0 && rIdx < graphWidth && cIdx >= 0 && cIdx < graphHeight;
    };
    auto checkNeighbors = [&graph, &graphWidth, &graphHeight, areCoordsValid, isPartHelper](int rowIdx, int colIdx)
    {
        const vector<pair<int, int>> directions{{-1, -1}, {-1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
        vector<pair<int, int>> gearCoords{};
        for (pair<int, int> dir : directions)
        {

            bool validCoords = areCoordsValid(rowIdx + dir.first, colIdx + dir.second);
            if (!validCoords)
                continue;
            bool satisfiesCondition = isPartHelper(graph[rowIdx + dir.first][colIdx + dir.second]);
            if (satisfiesCondition)
                gearCoords.push_back(make_pair(rowIdx + dir.first, colIdx + dir.second));
        }
        return gearCoords;
    };

    for (int rowIdx = 0; rowIdx < graphWidth; rowIdx++)
    {
        for (int colIdx = 0; colIdx < graphHeight; colIdx++)
        {
            char element = graph[rowIdx][colIdx];
            if (isCharNumber(element))
            {
                auto neighbors = checkNeighbors(rowIdx, colIdx);
                numberMode = true;
                currNumber *= 10;
                currNumber += element - '0';
                isPartNumber = isPartNumber || neighbors.size();
                for (auto neighbor : neighbors)
                    partPosForCurrNum.insert(neighbor);
            }
            if ((numberMode && !isCharNumber(element)) || colIdx == graphHeight - 1)
            {
                if (!partTwo && isPartNumber)
                    result += currNumber;
                else if (partTwo)
                {
                    for (auto pos : partPosForCurrNum)
                    {
                        for (auto visitedNumber : partNumbers[pos])
                        {
                            result += currNumber * visitedNumber;
                        }
                        partNumbers[pos].push_back(currNumber);
                    }
                }
                currNumber = 0;
                numberMode = false;
                isPartNumber = false;
                partPosForCurrNum.clear();
            }
        }
    }
    cout << result;
    return 0;
}
