#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Bin {
  char color;
  char waste;
  Bin(char _color, char _waste): color(_color), waste(_waste) {}
};

int distance (vector<Bin> a, vector<Bin> b) {
  int res = 0;
  for (int i = 0; i < 5; i++) {
    if (a[i].waste != b[i].waste) {
      res++;
    }
  }
  return res;
}

int solve (vector<string> line_ls) {
  vector<vector<Bin>> city_bin_ls = vector<vector<Bin>>();
  for (string line : line_ls) {
    vector<Bin> bin_ls = vector<Bin>();
    for (int i = 0; i < 5; i++) {
      int s = i * 4;
      bin_ls.push_back(Bin(line[s], line[s + 2]));
      sort(bin_ls.begin(), bin_ls.end(), [] (Bin a, Bin b) {
        return a.color < b.color;
      });
    }
    city_bin_ls.push_back(bin_ls);
  }

  int max_idx = 0;
  int max = INT_MAX;
  vector<int> dp = vector<int>(city_bin_ls.size(), 0);
  for (int i = 0; i < city_bin_ls.size(); i++) {
    int di = dp[i];
    for (int j = i + 1; j < city_bin_ls.size(); j++) {
      int dj = distance(city_bin_ls[i], city_bin_ls[j]);
      di += dj;
      dp[j] += dj;
    }

    if (di < max) {
      max = di;
      max_idx = i + 1;
    }
  }

  return max_idx;
}

int main () {
  const string end = "#";
  ifstream ifs("input.txt");
  string line;

  while (true) {
    getline(ifs, line);
    if (line.compare(end) == 0) {
      break;
    }

    vector<string> line_ls = vector<string>();
    while (line[0] != 'e') {
      line_ls.push_back(line);
      getline(ifs, line);
    }
    cout << solve(line_ls) << endl;
  }

  return 0;
}
