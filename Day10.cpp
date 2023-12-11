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

int main()
{
  ifstream infile("input.txt");
  ofstream outfile("output.txt");

  vector<string> graph;
  string input;

  int rowIdx = -1;
  int colIdx = -1;

  int row = 0;
  while (getline(cin, input))
  {
    graph.push_back(input);
    for (int i = 0; i < input.size(); i++)
      if (input[i] == 'S')
      {
        colIdx = i;
        rowIdx = row;
      }
    row++;
  }
  int colSize = graph.size();
  int rowSize = graph[0].size();
  int cnt_map[rowSize][colSize];
  bool visited[rowSize][colSize];
  for (int i = 0; i < rowSize; i++)
    for (int j = 0; j < colSize; j++)
    {
      cnt_map[i][j] = 0;
      visited[i][j] = false;
    }

  queue<pair<int, int>> q;

  q.push(make_pair(rowIdx, colIdx));

  auto isValid = [graph, colSize, rowSize](int nbrX, int nbrY, char checkDir)
  {
    if (nbrX >= rowSize || nbrX < 0 || nbrY >= colSize || nbrY < 0)
      return false;

    char pipeType = graph[nbrX][nbrY];

    if (checkDir == 's') // can accept something coming from south
    {
      return pipeType == '|' || pipeType == '7' || pipeType == 'F' || pipeType == 'S';
    }
    if (checkDir == 'n')
    {
      return pipeType == '|' || pipeType == 'L' || pipeType == 'J' || pipeType == 'S';
    }
    if (checkDir == 'e')
    {
      return pipeType == '-' || pipeType == 'L' || pipeType == 'F' || pipeType == 'S';
    }
    if (checkDir == 'w')
    {
      return pipeType == '-' || pipeType == 'J' || pipeType == '7' || pipeType == 'S';
    }
    return false;
  };

  auto canGo = [](char pipeType, char checkDir)
  {
    if (checkDir == 's')
    {
      return pipeType == '|' || pipeType == '7' || pipeType == 'F' || pipeType == 'S';
    }
    if (checkDir == 'n')
    {
      return pipeType == '|' || pipeType == 'L' || pipeType == 'J' || pipeType == 'S';
    }
    if (checkDir == 'e')
    {
      return pipeType == '-' || pipeType == 'L' || pipeType == 'F' || pipeType == 'S';
    }
    if (checkDir == 'w')
    {
      return pipeType == '-' || pipeType == 'J' || pipeType == '7' || pipeType == 'S';
    }
    return false;
  };

  while (!q.empty())
  {
    rowIdx = q.front().first;
    colIdx = q.front().second;
    q.pop();
    if (visited[rowIdx][colIdx])
      continue;
    visited[rowIdx][colIdx] = true;
    char cEl = graph[rowIdx][colIdx];

    bool canGoSouth = canGo(cEl, 's');
    bool canGoNorth = canGo(cEl, 'n');
    bool canGoEast = canGo(cEl, 'e');
    bool canGoWest = canGo(cEl, 'w');

    if (canGoEast && isValid(rowIdx, colIdx + 1, 'w') && !visited[rowIdx][colIdx + 1])
    {
      cnt_map[rowIdx][colIdx + 1] = max(cnt_map[rowIdx][colIdx + 1], cnt_map[rowIdx][colIdx] + 1);
      q.push(make_pair(rowIdx, colIdx + 1));
    }
    if (canGoWest && isValid(rowIdx, colIdx - 1, 'e') && !visited[rowIdx][colIdx - 1])
    {
      cnt_map[rowIdx][colIdx - 1] = max(cnt_map[rowIdx][colIdx - 1], cnt_map[rowIdx][colIdx] + 1);
      q.push(make_pair(rowIdx, colIdx - 1));
    }
    if (canGoNorth && isValid(rowIdx - 1, colIdx, 's') && !visited[rowIdx - 1][colIdx])
    {
      cnt_map[rowIdx - 1][colIdx] = max(cnt_map[rowIdx - 1][colIdx], cnt_map[rowIdx][colIdx] + 1);
      q.push(make_pair(rowIdx - 1, colIdx));
    }
    if (canGoSouth && isValid(rowIdx + 1, colIdx, 'n') && !visited[rowIdx + 1][colIdx])
    {
      cnt_map[rowIdx + 1][colIdx] = max(cnt_map[rowIdx + 1][colIdx], cnt_map[rowIdx][colIdx] + 1);
      q.push(make_pair(rowIdx + 1, colIdx));
    }
  }
  int mx = 0;

  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      cout << cnt_map[i][j] << " ";
      mx = max(mx, cnt_map[i][j]);
    }
    cout <<endl;
  }
  cout << mx << endl;
  return 0;
}
