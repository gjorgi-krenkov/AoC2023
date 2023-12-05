#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>

#include <vector>
#include <string>

#define cin infile
#define cout outfile

using namespace std;

int main()
{
  ifstream infile("input.txt");
  ofstream outfile("output.txt");

  vector<long long> seeds;
  string input;
  getline(cin, input);
  bool semiColonPass = false;
  bool numDetected = false;
  long long number = 0;
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
      numDetected = false;
      seeds.push_back(number);
      number = 0;
    }
  }
  seeds.push_back(number);
  number = 0;
  numDetected = false;
  vector<long long> cpy_seeds(seeds);

  while (getline(cin, input))
  {
    if (!(input[0] >= '0' && input[0] <= '9'))
    {
      seeds = cpy_seeds;
      continue;
    }
    vector<long long> conversions;
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
    for (int i = 0; i < seeds.size(); i++)
    {
      long long seed = seeds[i];
      if (seed >= src && seed < src + range)
        cpy_seeds[i] = dest + seed - src;
    }
    conversions.clear();
  }
  seeds = cpy_seeds;
  long long minimum = 100000000000;
  for (auto &seed : seeds)
    minimum = min(seed, minimum);
  cout << minimum;

  return 0;
}
