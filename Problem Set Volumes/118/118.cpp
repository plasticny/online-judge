#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <set>

using namespace std;

const char DIRECTION_LS[4] = {'N', 'E', 'S', 'W'};
const pair<int, int> MOVE_LS[4] = {{0,1}, {1,0}, {0,-1}, {-1,0}};

int dir_to_int (char c_dir) {
  for (int i = 0; i < 4; i++) {
    if (c_dir == DIRECTION_LS[i]) return i;
  }
  throw "unkown direction";
}

int turn (int dir, bool is_left) {
  if (is_left) {
    return dir == 0 ? 3 : dir - 1;
  }
  return  dir == 3 ? 0 : dir + 1;
}

void forward (int *x, int *y, int dir) {
  pair<int, int> move = MOVE_LS[dir];
  *x += move.first;
  *y += move.second;
}

int main () {
  ifstream ifs("input.txt");
  
  string line;
  int width, height, x, y, t_x, t_y, dir;
  char c_dir;
  bool is_lost;
  set<tuple<int, int, int>> danger_move; // {x, y, dir}

  getline(ifs, line);
  istringstream(line) >> width >> height;

  while (!ifs.eof()) {
    getline(ifs, line);
    istringstream(line) >> x >> y >> c_dir;

    t_x = x;
    t_y = y;
    dir = dir_to_int(c_dir);
    is_lost = false;

    getline(ifs, line);
    for (char action : line) {
      if (action != 'F') {
        dir = turn(dir, action == 'L');
        continue;
      }

      if (danger_move.count({x, y, dir}) != 0) {
        continue;
      }

      forward(&t_x, &t_y, dir);
      if (t_x < 0 || t_x > width || t_y < 0 || t_y > height) {
        is_lost = true;
        danger_move.insert({x, y, dir});
        break;
      }
      x = t_x;
      y = t_y;
    }

    printf("%d %d %c", x, y, DIRECTION_LS[dir]);
    printf(is_lost ? " LOST\n": "\n");
  }

  return 0;
}
