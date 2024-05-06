#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

int main () {
  int l, h, r;
  vector<tuple<int, int, bool>> node_ls;
  while (scanf("%d %d %d", &l, &h, &r) != EOF) {
    if (l == -1) break;
    node_ls.push_back(make_tuple(l, h, false));
    node_ls.push_back(make_tuple(r, h, true));
  }

  sort(
    node_ls.begin(),
    node_ls.end(),
    [](tuple<int, int, bool> &a, tuple<int, int, bool> &b) {
      return get<0>(a) < get<0>(b);
    }
  );

  multiset<int> height_set;
  height_set.insert(0);
  int max_height = 0;
  for (int i = 0; i < node_ls.size(); i++) {
    tuple<int, int, bool> node = node_ls[i];
    int loc = get<0>(node);
    int height = get<1>(node);
    bool is_end = get<2>(node);

    if (is_end) {
      height_set.erase(height_set.find(height));
    } else {
      height_set.insert(height);
    }

    int cur_max_height = *height_set.rbegin();

    if (cur_max_height != max_height) {
      max_height = cur_max_height;
      cout << loc << " " << max_height << " ";
    }
  }
  cout << endl;
}