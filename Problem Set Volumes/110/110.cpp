#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void list_variables (vector<char> variables) {
  int n = variables.size();
  for (int i = 0; i < n; i++) {
    printf("%c", variables[i]);
    if (i < n-1) {
      printf(",");
    }
  }
}

void print_tabs (int n) {
  for (int i = 0; i < n; i++) {
    printf("  ");
  }
}

void generate (vector<char> &variables, vector<char> tmp) {
  if (variables.size() == tmp.size()) {
    print_tabs(tmp.size());
    printf("writeln(");
    list_variables(tmp);
    printf(")\n");
    return;
  }

  vector<char> new_tmp = vector<char> (tmp);
  new_tmp.push_back(variables[new_tmp.size()]);

  for (int i = new_tmp.size()-1; i >= 0; i--) {
    print_tabs(tmp.size());
    if (i == new_tmp.size()-1) {
      printf("if");
    }
    else if (i > 0) {
      printf("else if");
    }
    else {
      printf("else\n");
    }

    if (i > 0) {
      printf(" %c < %c then\n", new_tmp[i-1], new_tmp[i]);
    }

    generate(variables, new_tmp);

    if (i > 0) {
      swap(new_tmp[i-1], new_tmp[i]);
    }
  }
}

int main () {
  int m, n;
  vector<char> variable_ls = {}, tmp;

  scanf("%d", &m);
  while (m-- > 0) {
    scanf("%d", &n);

    variable_ls.clear();
    for (int i = 0; i < n; i++) {
      variable_ls.push_back(char('a'+i));
    }

    printf("program sort(input,output);\n");
    
    printf("var\n");
    list_variables(variable_ls);
    printf(" : integer;\n");

    printf("begin\n");
    printf("  readln(");
    list_variables(variable_ls);
    printf(");\n");

    tmp = { variable_ls[0] };
    generate(variable_ls, tmp);

    printf("end.\n");
  }
}
