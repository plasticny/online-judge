#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node{
  int id;
  float value;
  Node* parent;
  int depth;
  Node(int id, float value, Node* parent, int depth) 
    : id(id), value(value), parent(parent), depth(depth)
    {}
};

int main () {
  unsigned int n;
  while (cin >> n) {
    // input
    vector<vector<float>> exchange_table = {};
    for (int i = 0; i < n; i++) {
      vector<float> curr = {};
      for (int j = 0; j < n; j++) {
        if (j == i) {
          curr.push_back(1.0);
        }
        else {
          float exchange;
          cin >> exchange;
          curr.push_back(exchange);
        }
      }
      exchange_table.push_back(curr);
    }

    // search
    vector<Node*> node_ls = {};
    vector<vector<bool>> visited = { n, vector<bool>(n, false) };

    queue<Node*> search_q;
    Node *start = new Node(0, 1.0, nullptr, 0);
    search_q.push(start);
    node_ls.push_back(start);

    Node* result = nullptr;
    
    while (!search_q.empty()) {
      Node *curr = search_q.front();
      search_q.pop();

      if (result != nullptr && curr->depth > result->depth) {
        break;
      }
      
      for(int i = 0; i < n; i++) {
        if (i == curr->id) {
          continue;
        }
        if (i != 0 && visited[curr->id][i]) {
          continue;
        }
        visited[curr->id][i] = true;

        Node *next = new Node(i, curr->value * exchange_table[curr->id][i], curr, curr->depth + 1);
        node_ls.push_back(next);

        if (next->id == 0 && next->value > 1.01) {
          if (result == nullptr || result->value < next->value) {
            result = next;
          }
        }
        else {
          search_q.push(next);
        }
      }
    }

    // output
    if (result == nullptr) {
      cout << "no arbitrage sequence exists" << endl;
    }
    else {
      vector<int> path = {};
      Node* curr = result;
      while (curr != nullptr) {
        path.push_back(curr->id);
        curr = curr->parent;
      }
      for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i] + 1;
        if (i > 0) {
          cout << " ";
        }
      }
      cout << endl;
    }

    // free memory
    for (int i = 0; i < node_ls.size(); i++) {
      delete node_ls[i];
    }
  }
  return 0;
}
