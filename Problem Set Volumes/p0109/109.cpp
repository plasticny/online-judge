#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

struct Point {
  int x, y;
  Point () {}
  Point (int _x, int _y) : x(_x), y(_y) {}
  bool operator < (const Point &p) const {
    return x < p.x || (x == p.x && y < p.y);
  }
};

bool ccw (const Point &a, const Point &b, const Point &c) {
  return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x) > 0;
}

vector<Point> convex_hull_monotone (vector<Point> &point_ls) {
  int n = point_ls.size(), k = 0;
  Point tmp[101];

  for (int i = 0; i < n; i++) {
    while (k >= 2 && !ccw(tmp[k-2], tmp[k-1], point_ls[i])) {
      k--;
    }
    tmp[k++] = point_ls[i];
  }

  for (int i = n-2, t = k; i > 0; i--) {
    while (k > t && !ccw(tmp[k-2], tmp[k-1], point_ls[i])) {
      k--;
    }
    tmp[k++] = point_ls[i];
  }

  return vector<Point>(tmp, tmp+k);
}

bool pip (const Point &p, const vector<Point> &polygon) {
  int n = polygon.size();
  bool res = 0;
  for (int i = 0, j = n-1; i < n; j = i++) {
    Point pi = polygon[i], pj = polygon[j];
    if (pi.y <= p.y < pj.y || pj.y <= p.y < pi.y) {
      if (p.x < (pj.x-pi.x)*(p.y-pi.y)*1.0/(pj.y-pi.y)+pi.x) {
        res ^= 1;
      }
    }
  }
  return res;
}

float signed_area (vector<Point> &polygon) {
  int n = polygon.size();
  float res = 0.0;
  for (int i = 1; i < n; i++) {
    res += polygon[i-1].x*polygon[i].y - polygon[i].x*polygon[i-1].y;
  }
  return abs(res*1.0/2);
}

int main () {
  int n, x, y, kingdom_cnt;
  float total_dead_area;
  Point missile;
  vector<vector<Point>> kingdom_ls;
  vector<Point> kingdom;
  vector<bool> alive;

  // add kingdoms
  while (scanf("%d", &n) && n != -1) {
    kingdom.clear();
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &x, &y);
      kingdom.push_back(Point(x, y));
    }

    kingdom_ls.push_back(convex_hull_monotone(kingdom));
  }
  kingdom_cnt = kingdom_ls.size();
  alive = vector<bool>(kingdom_ls.size(), true);

  // missile attack
  while (true) {
    scanf("%d %d", &x, &y);
    if (x == -1) {
      break;
    }

    missile = Point(x, y);
    for (int i = 0; i < kingdom_cnt; i++) {
      if (!alive[i]) {
        continue;
      }
      if (pip(missile, kingdom_ls[i])) {
        alive[i] = false;
        break;
      }
    }
  }

  // count total alive area
  total_dead_area = 0.0;
  for (int i = 0; i < kingdom_cnt; i++) {
    if (!alive[i]) {
      total_dead_area += signed_area(kingdom_ls[i]);
    }
  }

  printf("%.2f\n", total_dead_area);
}
