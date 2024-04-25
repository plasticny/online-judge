import java.io.File;
import java.lang.Integer;
import java.lang.Math;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

class V120 {
  public static void flip (ArrayList<Integer> s, int right) {
    double end = Math.ceil(right / 2.0);
    for (int i = 0, j = right - i; i < end; i++, j--) {
      Collections.swap(s, i, j);
    }
    System.out.printf("%d ", s.size() - right);
  }

  public static void a_case (String line) {
    Scanner sc = new Scanner(line); 
    ArrayList<Integer> s = new ArrayList<>();

    while (sc.hasNextInt()) {
      Integer num = sc.nextInt();
      s.add(num);
      System.out.printf("%d ", num);
    }
    System.out.println();

    for (int i = 0, right = s.size() - 1; i < s.size(); i++, right--) {
      // find largest idx
      int largest_idx = 0;
      for (int j = 1; j <= right; j++) {
        if (s.get(largest_idx) < s.get(j)) {
          largest_idx = j;
        }
      }

      // no need to swap
      if (largest_idx == right) {
        continue;
      }

      if (largest_idx != 0) {
        // swap largest num to top
        flip(s, largest_idx);
      }
      // swap largest num to its correct position
      flip(s, right);
    }
    System.out.println(0);

    sc.close();
  }

  public static void main(String a[]) {
    try {
      Scanner s = new Scanner(new File("input.txt"));
      while (s.hasNextLine()) {
        a_case(s.nextLine());
      }
      s.close();
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}
