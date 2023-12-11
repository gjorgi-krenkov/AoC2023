#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <string>
#include <algorithm>
#include <vector>

#define cin infile
#define cout outfile

using namespace std;
bool partTwo = true;
int main()
{
  ifstream infile("input.txt");
  ofstream outfile("output.txt");

  string input;
  long long totalSum = 0;

  while (getline(cin, input))
  {
    vector<long long> nums;
    bool numDetected = false;
    bool minDetected = false;
    long long number = 0;
    for (int it = 0; it < input.size(); it++)
    {
      if (input[it] == '-')
      {
        minDetected = true;
        continue;
      }
      if (input[it] >= '0' && input[it] <= '9')
      {
        numDetected = true;
        number *= 10;
        number += input[it] - '0';
      }
      else if (numDetected)
      {
        if (minDetected)
          number *= -1;
        nums.push_back(number);
        number = 0;
        numDetected = false;
        minDetected = false;
      }
    }
    if(numDetected){
      if (minDetected)
        number *= -1;
      nums.push_back(number);
    }
    reverse(nums.begin(), nums.end());
    bool allZeros = false;
  
    while (!allZeros)
    {
      allZeros = true;
      totalSum += nums[nums.size()-1];
      for (int q = 0; q < nums.size() - 1; q++)
      {
        nums[q] = nums[q + 1] - nums[q];
        allZeros = allZeros && nums[q] == 0;
      }
      nums.pop_back();
    }
  }
  cout << totalSum << endl;
  return 0;
}
