#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <map>
#include <algorithm>

using namespace std;

string next_str (string line, string::size_type &srt) {
  while (line[srt] == ' ') {
    srt++;
  }

  string::size_type space_pos = line.find(" ", srt);
  bool not_found = space_pos == string::npos;

  string res = line.substr(srt, not_found ? line.length() - 1 : space_pos - srt);
  srt = not_found ? 0 : space_pos + 1;
  return res;
}

bool find_leading_word (string horizon_word, string vertical_word, int& v_cross_idx, int& h_cross_idx) {
  map<char, int> v_letter_idx_mp = map<char, int>();
  for (int i = 0; i < vertical_word.length(); i++) {
    char letter = vertical_word[i];
    if (v_letter_idx_mp.count(letter) == 0) {
      v_letter_idx_mp[letter] = i;
    }
  }

  for (int i = 0; i < horizon_word.length(); i++) {
    char letter = horizon_word[i];
    if (v_letter_idx_mp.count(letter) != 0) {
      v_cross_idx = v_letter_idx_mp[letter];
      h_cross_idx = i;
      return true;
    }
  }
  return false;
}

void solve (vector<string> word_ls) {
  string h_word_1 = word_ls[0], v_word_1 = word_ls[1];
  string h_word_2 = word_ls[2], v_word_2 = word_ls[3];

  // find cross idx
  int v_cross_idx_1, h_cross_idx_1;
  int v_cross_idx_2, h_cross_idx_2;
  if (
    !find_leading_word(h_word_1, v_word_1, v_cross_idx_1, h_cross_idx_1) ||
    !find_leading_word(h_word_2, v_word_2, v_cross_idx_2, h_cross_idx_2)
  ) {
    cout << "Unable to make two crosses" << endl;
    return;
  }

  // print the cross word
  int v1_start = max(v_cross_idx_2 - v_cross_idx_1, 0);
  int v1_end = v1_start + v_word_1.length();
  int v2_start = max(v_cross_idx_1 - v_cross_idx_2, 0);
  int v2_end = v2_start + v_word_2.length();

  string h_pad_1(h_cross_idx_1, ' ');
  string h_pad_2(h_word_1.length() - h_cross_idx_1 + 2 + h_cross_idx_2, ' ');

  for (int v_idx = 0; v_idx < max(v1_end, v2_end); v_idx++) {
    if (v_idx - v1_start == v_cross_idx_1) {
      cout << h_word_1 << "   " << h_word_2 << endl;
    }
    else {
      char v1 = (v_idx >= v1_start && v_idx < v1_end) ? v_word_1[v_idx - v1_start] : ' ';
      char v2 = (v_idx >= v2_start && v_idx < v2_end) ? v_word_2[v_idx - v2_start] : ' ';
      cout << h_pad_1 << v1 << h_pad_2 << v2 << endl;
    }
  }
}

int main () {
  const string end = "#";
  ifstream ifs("input.txt");
  string line;
  bool is_first = true;

  while (true) {
    getline(ifs, line);
    if (line.compare(end) == 0) {
      break;
    }

    if (!is_first) {
      cout << endl;
    }
    is_first = false;

    string::size_type space_idx = 0;
    vector<string> word_ls = vector<string>();
    for (int i = 0; i < 4; i++) {
      word_ls.push_back(next_str(line, space_idx));
    }

    solve(word_ls);
  }

  return 0;
}
