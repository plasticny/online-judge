import java.util.Scanner;
import java.io.File;
import java.lang.Integer;
import java.util.Stack;

public class V116 {
  public static int get_min_prev_row (int[][] map, int row, int col) {
    int min = Integer.MAX_VALUE;
    int min_row = 0;
    for (int r = row-1; r <= row+1; r++) {
      int idx = (map.length + r) % map.length;
      int value = map[idx][col-1];
      if (min > value || (min == value && idx < min_row)) {
        min = value;
        min_row = idx;
      }
    }
    return min_row;
  }

  public static void a_case (Scanner s) {
    int m = s.nextInt(), n = s.nextInt();
    int[][] map = new int[m][n], prev = new int[m][n];
    
    for (int row = 0; row < m; row++) {
      for (int col = 0; col < n; col++) {
        map[row][col] = s.nextInt();
      }
    }
    
    for (int col = 1; col < n; col++) {
      for (int row = 0; row < m; row++) {
        int min_prev_row = get_min_prev_row(map, row, col);
        prev[row][col] = min_prev_row;
        map[row][col] += map[min_prev_row][col-1];
      }
    }

    // back tracing
    int res = map[0][n-1];
    int res_row = 0;
    Stack<Integer> stack = new Stack<>();
    for (int i = 1; i < m; i++) {
      if (res > map[i][n-1]) {
        res = map[i][n-1];
        res_row = i;
      }
    }
    for (int row = res_row, col = n-1; col >= 0; row = prev[row][col], col--) {
      stack.add(row+1);
    }

    // print result
    do {
      System.out.printf("%d ", stack.pop());
    } while(!stack.empty());
    System.out.printf("\n%d\n", res);
  }

  public static void main (String[] args) {
    try {
      Scanner s = new Scanner(new File("input.txt"));
      while (s.hasNextInt()) {
        a_case(s);
      }
      s.close();
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}
