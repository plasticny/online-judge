#include <iostream>
#include <tuple>
using namespace std;

int main () {
  int b1, b2, b3, g1, g2, g3, c1, c2, c3;
  cin >> b1 >> g1 >> c1 >> b2 >> g2 >> c2 >> b3 >> g3 >> c3;

  std::tuple<string, int> p[6];
  p[0] = make_tuple("BCG", b2 + b3 + c1 + c3 + g1 + g2);
  p[1] = make_tuple("BGC", b2 + b3 + g1 + g3 + c1 + c2);
  p[2] = make_tuple("CBG", c2 + c3 + b1 + b3 + g1 + g2);
  p[3] = make_tuple("CGB", c2 + c3 + g1 + g3 + b1 + b2);
  p[4] = make_tuple("GBC", g2 + g3 + b1 + b3 + c1 + c2);
  p[5] = make_tuple("GCB", g2 + g3 + c1 + c3 + b1 + b2);

  int min = std::get<1>(p[0]);
  int min_idx = 0;
  for (int i = 1; i < 6; i++) {
    int v = std::get<1>(p[i]);
    if (v < min) {
      min = v;
      min_idx = i;
    }
  }

  cout << std::get<0>(p[min_idx]) << " " << min << endl;  

  return 0;
}