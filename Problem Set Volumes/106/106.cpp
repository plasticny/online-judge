#include <iostream>
#include <math.h>
#include <vector>
#include <stack>

using namespace std;

vector<pair<int, int>> dp = { 1000000, make_pair(-1, -1) };

int mcd (int a, int b) {
  if (a%b == 0) {
    return b;
  }
  return mcd(b%a, a);
}

int main () {
  int n;
  while (cin >> n) {
    stack<int> s;
    for (int i = n-1; dp[i].first == -1; i--) {
      s.push(i+1);
    }

    // update dp
    while (!s.empty()) {
      int cur = s.top();
      s.pop();

      dp[cur-1].first = 0;
      if (cur == 1 || cur == 2) {
        continue;
      }

      int count = 0;
      for (int i = 1; i < cur; i++) {
        float y = sqrt(cur*cur - i*i);
        if (y == round(y)) {
          // update first appear
          if (dp[cur-1].second == -1) {
            dp[cur-1].second = cur;
          }
          if (dp[i-1].second == -1) {
            dp[i-1].second = cur;
          }
          if (dp[y-1].second == -1) {
            dp[y-1].second = cur;
          }

          // add count if relatively prime triple
          if (mcd(cur, i) == 1 && mcd(cur, y) == 1 && mcd(i, y) == 1) {
            count++;
          }
        }
      }
      dp[cur-1].first = count/2 + dp[cur-2].first;
    }

    // cout not appear
    int not_appear_cnt = 0;
    for (int i = 0; i < n; i++) {
      if (dp[i].second == -1 || dp[i].second > n) {
        not_appear_cnt++;
      }
    }
    cout << dp[n-1].first << " " << not_appear_cnt << endl;
  }
  return 0;
}