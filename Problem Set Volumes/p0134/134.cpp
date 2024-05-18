#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

// word
#define EMPTY -1
#define A 0
#define MOD 1
#define BA 2
#define DA 3
#define LA 4
#define OTHER 5

using namespace std;

class LineReader {
  public:
    LineReader (ifstream &_ifs, string &_line);
    int get (int idx);

  private:
    bool end;
    vector<int> code_ls;
    string &line;
    ifstream &ifs;
    string::size_type line_idx;

    bool is_vowel (char c);
    int encode (string word);
    void read ();
};

LineReader::LineReader (ifstream &_ifs, string &_line) : ifs(_ifs), line(_line) {
  code_ls = vector<int>();
  end = false;
  line_idx = 0;
  read();
}

int LineReader::get (int idx) {
  if (code_ls.size() > idx) {
    return code_ls[idx];
  }

  while (!end && code_ls.size() - 1 != idx) {
    read();
  }
  if (code_ls.size() - 1 == idx) {
    return code_ls[idx];
  }
  return EMPTY;
}

bool LineReader::is_vowel (char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int LineReader::encode(string word) {
  int len = word.length();
  if (len == 1 && is_vowel(word[0])) {
    return A;
  }
  if (len == 2 && is_vowel(word[1])) {
    switch (word[0]) {
      case 'g': return MOD;
      case 'b': return BA;
      case 'd': return DA;
      case 'l': return LA;
      default: break;
    }
  }
  return OTHER;
}

void LineReader::read () {
  if (end) {
    throw "eof";
  }

  const string space = " ";
  string::size_type space_pos = line.find(space, line_idx);

  if (space_pos != string::npos) {
    code_ls.push_back(encode(line.substr(line_idx, space_pos - line_idx)));
    line_idx = space_pos + 1;
    return;
  }

  string word = line.substr(line_idx);
  if (word.back() == '.') {
    end = true;
    word = word.substr(0, word.length() - 1);
    line_idx = string::npos;
  } else {
    getline(ifs, line);
    line_idx = 0;
  }
  code_ls.push_back(encode(word));
}

bool phrase (int phrase, LineReader &reader, int &idx) {
  if (reader.get(idx) == phrase && reader.get(++idx) == OTHER) {
    while (reader.get(++idx) == OTHER) {}
    return true;
  }
  return false;
}

bool pn (LineReader &reader, int &idx) {
  if (reader.get(idx) == OTHER) {
    idx++;
    return true;
  }
  return phrase(LA, reader, idx);
}

bool a (LineReader &reader, int &idx) {
  if (reader.get(idx) != A) {
    return true;
  }

  if (phrase(A, reader, idx)) {
    while (phrase(A, reader, idx)) {}
    return true;
  }
  return false;
}

bool s (LineReader &reader) {
  int idx = 0;
  if (pn(reader, idx) && phrase(MOD, reader, idx)) {
    if (reader.get(idx) == LA && reader.get(idx) == OTHER) {
      pn(reader, idx);
    }
    return reader.get(idx) == EMPTY;
  }
  return false;
}

bool pc1 (LineReader &reader) {
  int idx = 0;
  return pn(reader, idx) && phrase(BA, reader, idx) && a(reader, idx) && reader.get(idx) == EMPTY;
}

bool pc2 (LineReader &reader) {
  int idx = 0;
  return phrase(DA, reader, idx) && a(reader, idx) && reader.get(idx) == EMPTY;
}

void solve (ifstream &ifs, string &line) {
  LineReader reader(ifs, line);

  bool valid = s(reader) || pc1(reader) || pc2(reader);
  cout << (valid ? "Good" : "Bad!") << endl;

  while(line.back() != '.') {
    getline(ifs, line);
  }
}

int main () {
  const string end = "#";
  ifstream ifs("input.txt");
  string line;

  while (true) {
    getline(ifs, line);
    if (line.compare(end) == 0) {
      break;
    }
    solve(ifs, line);
  }

  return 0;
}
