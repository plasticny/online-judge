#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main () {
  int n;
  double p;

  while (cin >> n >> p) {
    cout << pow(p, 1.0/n) << endl;
  }

  return 0;
}
