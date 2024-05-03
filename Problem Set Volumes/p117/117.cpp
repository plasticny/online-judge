#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
  int idx;
  vector<pair<Node*, int>> connect;
  Node (int _idx) : idx(_idx) {}
};
typedef pair<Node*, int> Connection; // <node connecting, distance>
typedef pair<Node*, int> QNode; // <current node, total distance so far>

pair<int, int> find_odd_pair (vector<Node> node_ls) {
  vector<int> tmp;
  for (int i = 0; i < node_ls.size(); i++) {
    if (node_ls[i].connect.size() % 2 == 1) {
      tmp.push_back(i);
    }
  }
  
  if (tmp.size() == 0) {
    return {-1, -1};
  }
  if (tmp.size() == 2) {
    return {tmp[0], tmp[1]};
  }
  throw "tmp size 1";
}

int shortest_path_cost (Node *st, Node *dst) {
  struct cmp {
    bool operator() (const QNode a, const QNode b) const { return a.second > b.second; }
  };
  priority_queue<QNode, vector<QNode>, cmp> q;
  bool visited[26] = {};

  q.push({st, 0});
  while (!q.empty()) {
    QNode node = q.top();
    q.pop();

    if (visited[node.first->idx]) {
      continue;
    }
    visited[node.first->idx] = true;

    if (node.first == dst) {
      return node.second;
    }

    for(Connection c : node.first->connect) {
      if (!visited[c.first->idx]) {
        q.push({c.first, node.second+c.second});
      }
    }
  }
  throw "dst not found";
}

int main () {
  ifstream ifs("input.txt");
  string name;
  vector<Node> node_ls;
  int total;

  for (int i = 0; i < 26; i++) {
    node_ls.push_back(Node(i));
  }

  while (!ifs.eof()) {
    for (int i = 0; i < 26; i++) {
      node_ls[i].connect.clear();
    }
    total = 0;

    while (getline(ifs, name) && name.compare("deadend") != 0) {
      Node  *np = &node_ls[name[0] - 'a'], 
            *nq = &node_ls[name[name.length() - 1] - 'a'];
      np->connect.push_back({nq, name.length()});
      nq->connect.push_back({np, name.length()});
      total += name.length();
    }

    pair<int, int> odd_pair = find_odd_pair(node_ls);
    if (odd_pair.first != -1) {
      total += shortest_path_cost(&node_ls[odd_pair.first], &node_ls[odd_pair.second]);
    }
    cout << total << endl;
  }

  return 0;
}