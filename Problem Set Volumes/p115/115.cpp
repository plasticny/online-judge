#include <queue>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#define IS_PARENT 1
#define IS_CHILD 0

using namespace std;

struct Node {
  int id;
  vector<pair<Node*, bool>> node_ls;
  Node () {}
  Node (int _id): id(_id) {}
};

int main () {
  const string no_child = "no.child";

  ifstream ifs("input.txt");
  string line, p, q;
  map<string, Node> m;
  Node *np, *nq;
  queue<Node*> qu;
  vector<Node*> prev_ls;
  vector<bool> is_prev_parent_ls;
  int p_cnt, c_cnt;

  // construct graph
  while (true) {
    getline(ifs, line);
    istringstream(line) >> p >> q;

    if (p.compare(no_child) == 0) {
      break;
    }

    if (m.count(p) == 0) {
      m.insert({p, Node(m.size())});
    }
    if (m.count(q) == 0) {
      m.insert({q, Node(m.size())});
    }

    m[p].node_ls.push_back({&m[q], IS_PARENT});
    m[q].node_ls.push_back({&m[p], IS_CHILD});
  }

  // cases
  while (getline(ifs, line)) {
    istringstream(line) >> p >> q;

    // init variables
    prev_ls = vector<Node*> (m.size(), nullptr);
    is_prev_parent_ls = vector<bool> (m.size());
    qu = queue<Node*>();
    p_cnt = 0, c_cnt = 0;

    if (m.count(p) == 0 || m.count(q) == 0) {
      goto end_find_path;
    }

    // cout << p << ", " << q << endl;
    np = &m[p];
    nq = &m[q];

    prev_ls[np->id] = np;
    is_prev_parent_ls[np->id] = IS_PARENT;
    qu.push(np);

    // find path
    for (Node *cur_node = qu.front(); !qu.empty(); qu.pop(), cur_node = qu.front()) {
      for (pair<Node*, bool> node : cur_node->node_ls) {
        int id = node.first->id;
        if (prev_ls[id] != nullptr) {
          continue;
        }

        qu.push(node.first);
        prev_ls[id] = cur_node;
        is_prev_parent_ls[id] = node.second;
        if (node.first == nq) {
          goto end_find_path;
        }
      }
    }
    end_find_path:

    // print relationship
    if (prev_ls[nq->id] == nullptr) {
      cout << "no relation" << endl;
      continue;
    }
  
    for (Node *cur_node = nq; cur_node != np; cur_node = prev_ls[cur_node->id]) {
      if (!is_prev_parent_ls[cur_node->id]) {
        p_cnt++;
      }
      else {
        c_cnt++;
      }
    }

    if (p_cnt == 0 || c_cnt == 0) {
      for (int i = max(p_cnt, c_cnt); i > 0; i--) {
        if (i == 1) {
          cout << (p_cnt == 0 ? "child" : "parent");
        }
        else if (i == 2) {
          cout << "grand ";
        }
        else {
          cout << "great ";
        }
      }
      cout << endl;
    }
    else if (p_cnt == 1 && c_cnt == 1) {
      cout << "sibling" << endl;
    }
    else {
      int n = p_cnt-1, m = c_cnt-1;
      cout << min(n, m) << " cousins removed " << abs(n - m) << " times" << endl;
    }
  }

  m.clear();
  return 0;
}
