namespace Program {
  class A {
    static bool Case (StreamReader reader) {
      string line = reader.ReadLine()!;
      string[] first_split = line.Split(' ', 2);
      
      line = first_split[1];

      int target = int.Parse(first_split[0]), cur = 0, open_cnt = 0;
      bool found = false;
      string buffer = "";
      char prev = ' ';
      Stack<int> s = new Stack<int>();

      while (true) {
        foreach (char c in line) {
          if (c == ' ') {
            continue;
          }
          else if (c == '(') {
            open_cnt++;
          }
          else if (c == ')') {
            open_cnt--;
          }

          if (found) {
            continue;
          }

          if (buffer.Length > 0 && (c == '(' || c == ')')) {
            int num = int.Parse(buffer);
            cur += num;
            s.Push(num);
            buffer = "";
          }

          if (c == ')') {
            if (prev == '(') {
              s.Push(0);
              if (cur == target) {
                found = true;
              }
            }
            cur -= s.Pop();
          }
          else if (c != '('){
            buffer += c;
          }

          prev = c;
        }

        if (open_cnt > 0) {
          line = reader.ReadLine()!;
        }
        else {
          break;
        }
      };

      return found;
    }

    static void Main (string[] args) {
      using (StreamReader reader = File.OpenText("input.txt")) {
        while (!reader.EndOfStream) {
          bool res = Case(reader);
          Console.WriteLine(res ? "yes" : "no");
        }
      }
    }
  }
}
