#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <numeric>

#define cin infile
#define cout outfile

using namespace std;

bool partTwo = false;

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    map<string, pair<string, string>> nodesMap;
    vector<string> ghostNodes;
    if (!partTwo)
        ghostNodes.push_back("AAA");

    string command;
    getline(cin, command);

    string input;
    getline(cin, input);
    while (getline(cin, input))
    {
        int it = 0;
        string nodeId = "";
        string left = "", right = "";
        while (input[it] != ' ')
        {
            nodeId.push_back(input[it]);
            it++;
        }
        if (partTwo && nodeId[nodeId.size() - 1] == 'A'){
            ghostNodes.push_back(nodeId);
        }
        while (input[it] != '(')
            it++;
        it++;
        while (input[it] != ',')
        {
            left.push_back(input[it]);
            it++;
        }
        it += 2;
        while (input[it] != ')')
        {
            right.push_back(input[it]);
            it++;
        }
        nodesMap[nodeId] = make_pair(left, right);
    }

    int opSize = command.size();
    if (!opSize)
        return 0;

    vector<long long> foundZ;

    for(auto &ghost : ghostNodes){
        long long i = 0;
        while(partTwo ? ghost[2] != 'Z' : ghost.compare("ZZZ")){
            ghost = command[i%command.size()] == 'L' ? nodesMap[ghost].first : nodesMap[ghost].second;
            i++; 
        }
        foundZ.push_back(i);
    }
    long long res = foundZ[0];
    for(int i = 1; i< foundZ.size(); i++)
    {
        res = res*foundZ[i] / gcd(res, foundZ[i]);
    }
    
    cout << res;
    return 0;
}
