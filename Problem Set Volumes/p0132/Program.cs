namespace P132 {
  struct Point (int _idx, int _x, int _y) {
    public int idx = _idx;
    public float x = _x, y = _y;
  }

  class P132 {
    static List<Point> Read_vertex (StreamReader reader, string line) {
      List<Point> res = [];
      int idx = 0;
      while (true) {
        string[] num_ls = line.Split(' ');
        for (int i = 0; i < num_ls.Length; i += 2) {
          int x = int.Parse(num_ls[i]);
          int y = int.Parse(num_ls[i + 1]);

          if (x == 0 && y == 0) {
            return res;
          }
          res.Add(new Point(idx++, x, y));
        }
        line = reader.ReadLine()!;
      }
    }

    static float Ccw (Point p1, Point p2, Point p3) {
      return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x); 
    }

    static List<Point> Convex_hull (List<Point> point_ls) {
      point_ls.Sort(delegate (Point a, Point b) {
        if (a.x != b.x) {
          return (int)(a.x - b.x);
        }
        return (int)(a.y - b.y);
      });

      int n = point_ls.Count, k = 0;
      Point[] tmp_ls = new Point[100];

      for (int i = 0; i < n; i++) {
        while (k >= 2 && Ccw(tmp_ls[k - 2], tmp_ls[k - 1], point_ls[i]) < 0) {
          k--;
        }
        tmp_ls[k++] = point_ls[i];
      }

      for (int i = n - 2, tmp = k; i >= 0; i--) {
        while (k > tmp && Ccw(tmp_ls[k - 2], tmp_ls[k - 1], point_ls[i]) < 0) {
          k--;
        }
        tmp_ls[k++] = point_ls[i];
      }

      List<Point> res = [];
      for (int i = 0; i < k; i++) {
        res.Add(tmp_ls[i]);
      }
      return res;
    }

    static void Solve (string name, List<Point> vertex_ls) {
      int res = int.MaxValue;

      List<Point> monochain = Convex_hull(vertex_ls);
      int line_max = monochain[0].idx;
      for (int i = 1; i < monochain.Count; i++) {
        Point p = monochain[i];
        if (i == 1 || Ccw(monochain[i - 2], monochain[i - 1], p) == 0) {
          // is straight
          line_max = int.Max(line_max, p.idx);
        } else {
          res = int.Min(res, line_max);
          line_max = p.idx;
        }
      }

      Console.WriteLine(string.Format("{0,-20}{1:D}", name, res));
    }

    static void Main (string[] a) {
      const string end_line = "#";
      using StreamReader reader = File.OpenText("input.txt");

      while (true) {
        // read input
        string[] first_line = reader.ReadLine()!.Split(' ', 2);
        string name = first_line[0];

        if (name.Equals(end_line)) {
          break;
        }
        string line = first_line.Length > 1 ? first_line[1] : reader.ReadLine()!;
        List<Point> vertex_ls = Read_vertex(reader, line);

        Solve(name, vertex_ls);
      }
    }
  }
}
