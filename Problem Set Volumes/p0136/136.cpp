#include <iostream>
#include <set>
#include <queue>

using namespace std;

int main () {
  set<unsigned int> ugly_num = set<unsigned int>();
  ugly_num.insert(1);

  priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int>> q;
  q.push(1);
  
  unsigned int cur, cnt = 0;
  while (true) {
    cur = q.top();
    q.pop();

    if(++cnt == 1500) {
      break;
    }

    vector<unsigned int> next = {cur * 2, cur * 3, cur * 5};
    for (unsigned int c : next) {
      if (ugly_num.count(c) == 0) {
        ugly_num.insert(c);
        q.push(c);
      }
    }
  }

  cout << "The 1500'th ugly number is " << cur << ".";
  return 0;
}
