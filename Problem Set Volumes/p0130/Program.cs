namespace P0130 {
  class P0130 {
    static int Cal_m (int n, int k) {
      int r = k % n;
      return r == 0 ? k - 1 : r - 1;
    }

    static int Constraint_pos (int p, int len) {
      return p >= len ? p % len : p;
    }

    static int Move (int p, int m, int[] mat, bool[] empty_mat_ls) {
      while (m > 0) {
        p += empty_mat_ls[p] ? mat[p] : 1;
        p = Constraint_pos(p, mat.Length);
        if (!empty_mat_ls[p]) {
          m--;
        }
      }
      return p;
    }

    static int Cal_move_mark (int p, int[] mat, bool[] empty_mat_ls) {
      int next = Constraint_pos(p+1, mat.Length);
      return empty_mat_ls[next] ? mat[next] + 1 : 1;
    }

    static void Solve (int n, int k) {
      int[] mat = new int[n];
      bool[] empty_mart_ls = new bool[n];
      for (int i = 0; i < n; i++) {
        mat[i] = i + 1;
        empty_mart_ls[i] = false;
      }

      int p = 0;
      for (int r = n; r > 1; r--) {
        // move distance
        int m = Cal_m(r, k);
        // victim
        p = Move(p, m, mat, empty_mart_ls);
        // person to bury the victim
        int b = Move(p, m + 1, mat, empty_mart_ls);

        mat[p] = mat[b];
        mat[b] = Cal_move_mark(b, mat, empty_mart_ls);
        empty_mart_ls[b] = true;

        p = Move(p, 1, mat, empty_mart_ls);
      }

      for (int i = 0; i < n; i++) {
        if (!empty_mart_ls[i]) {
          Console.WriteLine(mat[i]);
        }
      }
    }

    static void Main (string[] a) {
      using (StreamReader reader = File.OpenText("input.txt")) {
        while (true) {
          string[] line = reader.ReadLine()!.Split(' ', 2);

          int n = int.Parse(line[0]);
          int k = int.Parse(line[1]);

          if (n == 0 && k == 0) {
            break;
          }
          
          Solve(n, k);
        }
      }
    }
  }
}