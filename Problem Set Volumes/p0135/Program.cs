namespace P0315 {
  class Program {
    static void Solve (int k) {
      // https://www.cnblogs.com/devymex/archive/2010/08/20/1804917.html
      // first k lines
      for (int i = 0; i < k; i++) {
        Console.Write("1");

        int srt = 2 + i * (k - 1);
        int end = srt + (k - 1);
        for (int j = srt; j < end; j++) {
          Console.Write(string.Format(" {0}", j));
        }
        Console.WriteLine();
      }

      // remaining
      for (int i = 1; i < k; i++) {
        int offset = k + i - 2;

        for (int j = 1; j < k; j++) {
          Console.Write(i + 1);

          int cur = k + j;
          int upper = (k - 1) * 3 + 1;
          for (int p = 1; p < k; p++) {
            Console.Write(string.Format(" {0}", cur));
            cur += offset;
            if (cur > upper) {
              cur -= k - 1;
            }
            upper += k - 1;
          }
          Console.WriteLine();
        }
      }

      Console.WriteLine();
    }

    static void Main () {
      using StreamReader reader = File.OpenText("input.txt");
      while (!reader.EndOfStream) {
        Solve(int.Parse(reader.ReadLine()!));
      }
    }
  }
}
