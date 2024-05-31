import java.io.File;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Collections;

class Point {
  public static Point normalize (Point p, int n) {
    int nn;
    if (n % 2 == 0) {
      nn = n / 2;
      return new Point(p.x - nn + p.x / nn, nn - p.y - p.y / nn);
    } else {
      nn = (n - 1) / 2;
      return new Point(p.x - nn, nn - p.y);
    }
  }
  public static Point denormalize (Point p, int n) {
    int nn;
    if (n % 2 == 0) {
      nn = n / 2;
      return new Point(p.x + nn - (p.x > 0 ? 1 : 0), nn - p.y - (p.y < 0 ? 1 : 0));
    } else {
      nn = (n - 1) / 2;
      return new Point(p.x + nn, nn - p.y);
    }
  }

  public int x, y;
  public Point (int _x, int _y) {
    x = _x;
    y = _y;
  }
  public Point rotate (int degree, int n) {
    if (degree == 0) {
      return this;
    }

    Point pn = normalize(this, n);
    int x = pn.x;
    if (degree == 90) {
      pn.x = pn.y;
      pn.y = -x;
    } else if (degree == 180) {
      pn.x = -pn.x;
      pn.y = -pn.y;
    } else {
      pn.x = -pn.y;
      pn.y = x;
    }
    return denormalize(pn, n);
  }
  public boolean equal (Point p) {
    return x == p.x && y == p.y;
  }
}

class PointComparator implements Comparator<Point> {
  @Override
  public int compare (Point p1, Point p2) {
    return p1.x != p2.x ? p1.x - p2.x : p1.y - p2.y;
  }
}

class History {
  public final static int[] DEGREE_LS = {0, 90, 180, 270};

  public ArrayList<List<Point>> status_ls;

  public History (List<Point> pt_ls, int n) {
    status_ls = new ArrayList<>();
    status_ls.add(pt_ls);

    for (int i = 1; i < 4; i++) {
      int degree = DEGREE_LS[i];
      List<Point> status = new ArrayList<>();
      for (Point p : pt_ls) {
        status.add(p.rotate(degree, n));
      }
      status_ls.add(status);
    }
  }

  public boolean check (List<Point> pt_ls) {
    for (List<Point> appear : status_ls) {
      boolean same = true;
      for (int i = 0; i < appear.size(); i++) {
        if (!pt_ls.get(i).equal(appear.get(i))) {
          same = false;
          break;
        }
      }
      if (same) {
        return true;
      }
    }
    return false;
  }
}

public class P141 {
  public static boolean appeared (ArrayList<ArrayList<History>> history_ls, ArrayList<Point> status) {
    if (status.size() == 0 || status.size() > history_ls.size()) {
      return false;
    }
    for (History h : history_ls.get(status.size() - 1)) {
      if (h.check(status)) {
        return true;
      }
    }
    return false;
  }

  public static void solve (int n, Scanner s) {
    final String OP_ADD = "+";

    // 1st dim is number of spot
    ArrayList<ArrayList<History>> history_ls = new ArrayList<>();
    ArrayList<Point> prev_status = new ArrayList<>();
    boolean end = false;

    for (int round = 0; round < 2 * n; round++) {
      int x = s.nextInt() - 1;
      int y = s.nextInt() - 1;
      String op = s.next();
      
      if (end) {
        continue;
      }

      ArrayList<Point> status;
      if (op.equals(OP_ADD)) {
        status = new ArrayList<>(prev_status);
        status.add(new Point(x, y));
        Collections.sort(status, new PointComparator());
      } else {
        status = new ArrayList<>();
        for (Point p : prev_status) {
          if (p.x != x || p.y != y) {
            status.add(p);
          }
        }
      }
      prev_status = status;

      if (appeared(history_ls, status)) {
        System.out.printf("Player %d wins on move %d\n", round % 2 == 0 ? 2 : 1, round + 1);
        end = true;
        continue;
      }

      if (status.size() > history_ls.size()) {
        history_ls.add(new ArrayList<>());
      }
      if (status.size() > 0) {
        history_ls.get(status.size() - 1).add(new History(status, n));
      }
    }

    if (!end) {
      System.out.println("Draw");
    }
  }

  public static void main (String[] args) {
    try {
      Scanner s = new Scanner(new File("input.txt"));
      while (s.hasNextLine()) {
        int n = s.nextInt();
        if (n == 0) {
          break;
        }
        solve(n, s);
      }
      s.close();
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}
