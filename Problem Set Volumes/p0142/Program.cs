namespace P142 {
  using Icon = Tuple<int, int>; // x, y
  using Region = Tuple<int, int, int, int>; // lx, ly, rx, ry

  class P142 {
    static void Mouse_click (int x, int y, List<Icon> icon_ls, List<Region> region_ls) {
      // region
      for (int i = region_ls.Count - 1; i >= 0; i--) {
        var (lx, ly, rx, ry) = region_ls[i];
        if (x >= lx && x <= rx && y >= ly && y <= ry) {
          Console.WriteLine((char)('A' + i));
          return;
        }
      }

      // icon
      double min_d = double.MaxValue;
      List<int> neighbor_ls = [];
      for (int idx = 0; idx < icon_ls.Count; idx++) {
        var (ix, iy) = icon_ls[idx];
        double d = Math.Pow(x - ix, 2) + Math.Pow(y - iy, 2);
        if (d < min_d) {
          neighbor_ls = [idx + 1];
          min_d = d;
        } else if (d == min_d) {
          neighbor_ls.Add(idx + 1);
        }
      }
      foreach (int idx in neighbor_ls) {
        Console.Write(string.Format("{0}", idx).PadLeft(3));
      }
      Console.WriteLine();
    }

    static void Main () {
      using StreamReader reader = File.OpenText("input.txt");

      const string I = "I", R = "R", M = "M", end = "#";

      List<Icon> icon_ls = [];
      List<Region> region_ls = [];

      while (true) {
        string[] items = reader.ReadLine()!.Split(' ');
        switch (items[0]) {
          case end:
            return;
          case I:
            icon_ls.Add(
              new Icon(int.Parse(items[1]), int.Parse(items[2]))
            );
            break;
          case R:
            region_ls.Add(
              new Region(
                int.Parse(items[1]), int.Parse(items[2]),
                int.Parse(items[3]), int.Parse(items[4])
              )
            );
            break;
          case M:
            Mouse_click(
              int.Parse(items[1]), int.Parse(items[2]),
              icon_ls, region_ls
            );
            break;
        }
      }
    }
  }
}
