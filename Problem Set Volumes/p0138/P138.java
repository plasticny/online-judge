class P138 {
  public static void main (String[] args) {
    int left = 1, house = 2, cnt = 0;
    while (cnt < 10) {
      int right = 0, end = house + 1;
      while (right < left) {
        right += end++;
      }

      if (right == left) {
        System.out.println(String.format("%d %d", house, end - 1));
        cnt++;
      }
      
      left += house++;
    }
  }
}
