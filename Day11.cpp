#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <string>
#include <vector>
#include <string.h>
#include <utility>
#include <queue>
#include <map>

#define cin infile
#define cout outfile

using namespace std;
bool partTwo = true;
int main()
{
  ifstream infile("input.txt");
  ofstream outfile("output.txt");

  int times = partTwo ? 999999 : 1;
  vector<string> graph;
  string input;
  vector<pair<int, int>> galaxies;

  int rowIdx = -1;
  int colIdx = -1;

  int row = 0;
  vector<int> emptyR, emptyC;
  while (getline(cin, input))
  {
    graph.push_back(input);
    int cnt = 0;
    for (int i = 0; i < input.size(); i++)
      if (input[i] == '#')
        cnt++;
    if (!cnt)
      emptyR.push_back(row);

    row++;
  }

  for (int i = 0; i < graph[0].size(); i++)
  {
    int cnt = 0;
    for (int j = 0; j < graph.size(); j++)
      if (graph[j][i] == '#')
        cnt++;
    if (cnt == 0)
    {
      emptyC.push_back(i);
    }
  }
  for (int i = 0; i < graph.size(); i++)
  {
    for (int j = 0; j < graph[0].size(); j++)
    {
      if (graph[i][j] == '#')
      {
        galaxies.push_back(make_pair(i, j));
      }
    }
  }

  long long res = 0;
  auto between = [emptyR, emptyC](int y2, int y1, int x2, int x1) {
    int cols = 0;
    int rows = 0;

    if(y1 > y2) swap(y1,y2);
    if(x1 > x2) swap(x1, x2);

    for(auto rr : emptyR) 
      if(rr>x1 && rr<x2) rows++;
    for (auto cc : emptyC)
      if (cc > y1 && cc < y2)
        cols++;
    return rows+cols;
  };
  for (int i = 0; i < galaxies.size(); i++)
  {
    for (int j = 0; j < i; j++)
    {
      int subRes = abs(galaxies[i].second - galaxies[j].second) + abs(galaxies[i].first - galaxies[j].first) + between(galaxies[i].second, galaxies[j].second, galaxies[i].first, galaxies[j].first)*times;
      res += subRes;
    }
  }
  cout << res << endl;
}