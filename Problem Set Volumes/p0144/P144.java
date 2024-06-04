import java.io.File;
import java.util.Scanner;
import java.util.Queue;
import java.util.LinkedList;

class P144 {
  public static void solve (int n, int k) {
    int store = 1, next_store = 2;
    int[] granted_ls = new int[n];
    Queue<Integer> q = new LinkedList<>();

    for (int i = 0; i < n; i++) {
      q.offer(i);
      granted_ls[i] = 0;
    }

    while (!q.isEmpty()) {
      int idx = q.poll();
      granted_ls[idx] += store;
      if (granted_ls[idx] < 40) {
        q.offer(idx);
      } else {
        System.out.format("%3d", idx + 1);
      }

      if (granted_ls[idx] > 40) {
        store = granted_ls[idx] - 40;
      } else {
        store = next_store;
        next_store = next_store == k ? 1 : next_store + 1;
      }
    }
    System.out.println();
  }

  public static void main (String[] args) {
    try {
      Scanner s = new Scanner(new File("input.txt"));
      while (s.hasNextLine()) {
        int n = s.nextInt();
        int k = s.nextInt();
        if (n == 0 && k == 0) {
          break;
        }
        solve(n, k);
      }
      s.close();
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}
