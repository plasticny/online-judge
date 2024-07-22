bool is_lower (char a) {
  return a >= 'a' && a <= 'z';
}

int compare_char (char a, char b) {
  bool is_a_lower = is_lower(a);
  bool is_b_lower = is_lower(b);
  if (is_a_lower != is_b_lower) {
    return is_a_lower ? 1 : -1;
  }
  return a.CompareTo(b);
}

int compare_string (string a, string b) {
  for (int i = 0; i < a.Length && i < b.Length; i++) {
    int cmp = compare_char(a[i], b[i]);
    if (cmp != 0) {
      return cmp;
    }
  }
  return a.Length.CompareTo(b.Length);
}

void Solve (List<string> word_ls) {
  Dictionary<string, bool> map = [];
  List<string> key_ls = [];

  word_ls.Sort(compare_string);
  foreach (string word in word_ls) {
    string key = string.Concat(word.ToLower().OrderBy(c => c));
    key_ls.Add(key);
    map[key] = map.ContainsKey(key);
  }

  for (int i = 0; i < word_ls.Count; i++) {
    if (map[key_ls[i]] == false) {
      Console.WriteLine(word_ls[i]);
    }
  }
}

void Main () {
  DateTime start = DateTime.Now;

  using StreamReader reader = File.OpenText("input.txt");

  List<string> word_ls = [];
  while (true) {
    string[] token_ls = reader.ReadLine()!.Split(' ');
    if (token_ls[0].Equals("#")) {
      break;
    }

    foreach (string token in token_ls) {
      if (token.Length == 0) {
        continue;
      }
      word_ls.Add(token);
    }
  }
  Solve(word_ls);

  DateTime end = DateTime.Now;
  Console.WriteLine(end - start);
}
Main();
