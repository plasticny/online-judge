#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int cal_m (int n, int k) {
  if (k < n) {
    return k - 1;
  }
  int r = k % n;
  return r == 0 ? n - 1 : r - 1;
}

int constraint_pos (int p, int n) {
  return p >= n ? p % n : (p < 0 ? n + p : p);
}

int move_p (int p, int m, bool clockwise, vector<pair<int, int>> mat) {
  while (m > 0) {
    if (mat[p].first != 0) {
      p += clockwise ? mat[p].first : mat[p].second;
    } else {
      p += clockwise ? -1 : 1;
    }

    p = constraint_pos(p, mat.size());
    if (mat[p].first == 0) {
      m--;
    }
  }
  return p;
}

pair<int, int> cal_move_mark (int p, vector<pair<int, int>> mat) {
  int next_c = constraint_pos(p - 1, mat.size());
  int next_cc = constraint_pos(p + 1, mat.size());
  return {
    mat[next_c].first == 0 ? -1 : mat[next_c].first - 1,
    mat[next_cc].second == 0 ? 1 : mat[next_cc].second + 1,
  };
}

void solve (int n, int k, int m) {
  vector<pair<int, int>> mat = vector<pair<int, int>>();
  for (int i = 0; i < n; i++) {
    mat.push_back({0, 0});
  }

  int cc = 0;
  int c = n - 1;
  int person_left = n;
  while (person_left) {
    // cal move distance
    int km = cal_m(person_left, k);
    int mm = cal_m(person_left, m);

    // victim
    cc = move_p(cc, km, false, mat);
    c = move_p(c, mm, true, mat);

    // remove
    mat[cc] = cal_move_mark(cc, mat);
    cout << setw(3) << cc + 1;
    person_left--;
    if (c != cc) {
      mat[c] = cal_move_mark(c, mat);
      cout << setw(3) << c + 1;
      person_left--;
    }

    // next
    if (person_left) {
      cout << ',';
      cc = move_p(cc, 1, false, mat);
      c = move_p(c, 1, true, mat);
    }
  }
  cout << endl;
}

int main () {
  ifstream ifs("input.txt");

  string line;
  int n, k, m;

  cout << right;
  while (true) {
    getline(ifs, line);
    istringstream(line) >> n >> k >> m;

    if (n == 0 && k == 0 & m == 0) {
      break;
    }
    solve(n, k, m);
  }

  return 0;
}
