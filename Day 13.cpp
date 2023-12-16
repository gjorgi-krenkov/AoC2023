#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <vector>
#include <string>

#define cin infile
#define cout outfile

using namespace std;

bool partTwo = false;

bool areReflection(string rA, string rB)
{
    for (int i = 0; i < rA.size(); i++)
        if (rA[i] != rB[i])
            return false;
    return true;
}

bool isSmudge(string rA, string rB)
{
    if(!partTwo)
        return false;
    int cnt = 0;
    for (int i = 0; i < rA.size(); i++)
        if (rA[i] != rB[i])
            cnt++;
    
    return cnt == 1;
}

void transpose(vector<string> &graph)
{
    int width = graph[0].size();
    int height = graph.size();
    vector<string> helper;
    for(int i = 0; i < width; i++)
    {
        string q = "";
        for(int j = 0; j < height; j++)
            q += graph[j][width - 1 - i];

        helper.push_back(q);

    }
    graph = helper;
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    string input;

    vector<string> graph;
    long long res = 0;
    auto hasReflection = [&res, &cout](vector<string> graph, bool vertical = false)
    {
        int width = graph[0].size();
        int height = graph.size();
        int rIdx = 0;
        bool found = false;
        for (int i = 0; i < height - 1; i++)
        {
            bool smudgeActive = isSmudge(graph[i], graph[i+1]);
            if (areReflection(graph[i], graph[i + 1]) || smudgeActive)
            {
                found = true;
                for(int q = 1; i+q+1 < height && i-q >= 0; q++)
                {
                    found = areReflection(graph[i-q], graph[i+q+1]) || (partTwo && !smudgeActive && isSmudge(graph[i-q], graph[i+q+1]));
                    smudgeActive = smudgeActive || isSmudge(graph[i-q], graph[i+q+1]);
                    if (!found) {
                        break;
                    }
                }
                if(found && (!partTwo || smudgeActive)){
                    rIdx = vertical ? height - i - 2 : i;
                    break;
                } else found = false;
            }
        }
        if (found)
        {
            int multiple = vertical ? 1 : 100;
            res += (rIdx + 1) * multiple;
        }
        return found;
    };
    
    while (getline(cin, input))
    {
        if (input.size())
        {
            graph.push_back(input);
            continue;
        }
        // vertical search
        transpose(graph);
        if (hasReflection(graph, true))
        {
            graph.clear();
            continue;
        }

        transpose(graph);
        transpose(graph);
        transpose(graph);

        // horizontal search
        hasReflection(graph);

        graph.clear();
    }

    // vertical search
    transpose(graph);
    if(hasReflection(graph, true))
    {
        cout << res << endl;
        return 0;
    }

    transpose(graph);
    transpose(graph);
    transpose(graph);
    
    // horizontal search
    hasReflection(graph);
 
    cout << res <<endl;
    return 0;
}
