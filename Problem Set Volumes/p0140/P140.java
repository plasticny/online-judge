import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Collections;

import org.apache.commons.math3.distribution.EnumeratedDistribution;
import org.apache.commons.math3.util.Pair;

/* Practice Genetic Algorithms */

class ConnectMap extends HashMap<Character, HashSet<Character>> {}

class P140 {
  public static void read_line (String line, ConnectMap connect_mp) {
    String[] record_ls = line.split(";");
    for (String record : record_ls) {
      char from = record.charAt(0);
      if (!connect_mp.containsKey(from)) {
        connect_mp.put(from, new HashSet<>());
      }
      HashSet<Character> connect_set = connect_mp.get(from);

      for (int i = 2; i < record.length(); i++) {
        char to = record.charAt(i);
        if (!connect_mp.containsKey(to)) {
          connect_mp.put(to, new HashSet<>());
        }
        connect_set.add(to);
        connect_mp.get(to).add(from);
      }
    }
  }

  public static int est (ArrayList<Character> ordering, ConnectMap connect_mp) {
    int max_d = 0;
    for (int i = 0; i < ordering.size() - 1; i++) {
      HashSet<Character> connect_set = connect_mp.get(ordering.get(i));
      for (int j = i + max_d + 1; j < ordering.size(); j++) {
        if (connect_set.contains(ordering.get(j))) {
          max_d = Math.max(max_d, j - i);
        }
      }
    }
    return max_d;
  }

  public static void copy_array (ArrayList<Character> src, ArrayList<Character> dst) {
    for (int i = 0; i < src.size(); i++) {
      dst.set(i, src.get(i));
    }
  }

  public static void swap (ArrayList<Character> ls, int i, int j) {
    char tmp = ls.get(i);
    ls.set(i, ls.get(j));
    ls.set(j, tmp);
  }

  public static void selection (ArrayList<ArrayList<Character>> population, ArrayList<Character> node_ls, ConnectMap connect_mp) {
    ArrayList<Double> weight_ls = new ArrayList<>();
    double total = 0.0;
    for (ArrayList<Character> m : population) {
      double weight = (double)(node_ls.size() - est(m, connect_mp));
      weight_ls.add(weight);
      total += weight;
    }

    ArrayList<Pair<ArrayList<Character>, Double>> pmf = new ArrayList<>();
    for (int i = 0; i < population.size(); i++) {
      pmf.add(new Pair<>(population.get(i), weight_ls.get(i) / total * 100));
    }

    EnumeratedDistribution<ArrayList<Character>> ed = new EnumeratedDistribution<>(pmf);
    for (int i = 0; i < population.size(); i++) {
      population.set(i, ed.sample());
    }
  }

  public static void crossover (ArrayList<Character> ls1, ArrayList<Character> ls2, ConnectMap connect_mp) {
    int cross_idx = (int)Math.round(1 + Math.random() * (ls1.size() - 2));
    int idx1 = 0, idx2 = 0;
    HashSet<Character> set1 = new HashSet<>(), set2 = new HashSet<>();
    ArrayList<Character> res1 = new ArrayList<>(), res2 = new ArrayList<>();

    for (int i = 0; i < ls1.size(); i++) {
      char c1, c2;
      if (i < cross_idx) {
        c1 = ls1.get(i);
        c2 = ls2.get(i);
      } else {
        while (set1.contains(ls2.get(idx2))) idx2++;
        while (set2.contains(ls1.get(idx1))) idx1++;
        c1 = ls2.get(idx2);
        c2 = ls1.get(idx1);
      }
      set1.add(c1);
      set2.add(c2);
      res1.add(c1);
      res2.add(c2);
    }

    if (est(res1, connect_mp) < est(ls1, connect_mp)) {
      copy_array(res1, ls1);
    }
    if (est(res2, connect_mp) < est(ls2, connect_mp)) {
      copy_array(res2, ls2);
    }
  }

  public static void mutation (ArrayList<Character> ls, ConnectMap connect_mp) {
    int v1 = est(ls, connect_mp);

    int i, j;
    i = (int)Math.round(Math.random() * (ls.size() - 1));
    do {
      j = (int)Math.round(Math.random() * (ls.size() - 1));
    } while (i == j);

    swap(ls, i, j);
    if (est(ls, connect_mp) > v1) {
      swap(ls, i, j);
    }
  }

  public static int find_min (ArrayList<ArrayList<Character>> population, ArrayList<Character> node_ls, ConnectMap connect_mp) {
    int res_idx = 0;
    double min_v = est(population.get(0), connect_mp);
    for (int i = 1; i < population.size(); i++) {
      double v = est(population.get(i), connect_mp);
      if (v < min_v) {
        min_v = v;
        res_idx = i;
      }
    }
    return res_idx;
  }

  public static int genetic (ConnectMap connect_mp, ArrayList<Character> min_ordering) {
    final int POPULATION_SIZE = 8;
    final int ROUND = 32;

    ArrayList<ArrayList<Character>> population = new ArrayList<>(POPULATION_SIZE);
    ArrayList<Character> node_ls = new ArrayList<>(connect_mp.keySet());
    int min_idx = 0;

    for (int i = 0; i < POPULATION_SIZE; i++) {
      Collections.shuffle(node_ls);
      ArrayList<Character> m = new ArrayList<>();
      for (char c : node_ls) {
        m.add(c);
      }
      population.add(m);
    }

    for (int r = 0; r < ROUND; r++) {
      selection(population, node_ls, connect_mp);
      for (int i = 0; i < POPULATION_SIZE; i += 2) {
        crossover(population.get(i), population.get(i + 1), connect_mp);
        mutation(population.get(i), connect_mp);
        mutation(population.get(i + 1), connect_mp);
      }
      min_idx = find_min(population, node_ls, connect_mp);
    }

    copy_array(population.get(min_idx), min_ordering);
    return est(min_ordering, connect_mp);
  }

  public static void solve (String line) {
    ConnectMap connect_mp = new ConnectMap();
    read_line(line, connect_mp);

    ArrayList<Character> min_ordering = new ArrayList<>();
    for (int i = 0; i < connect_mp.keySet().size(); i++) {
      min_ordering.add('a');
    }

    int min_bandwidth = genetic(connect_mp, min_ordering);

    // print result
    for (char node : min_ordering) {
      System.out.printf("%c ", node);
    }
    System.out.printf("-> %d\n", min_bandwidth);
  }

  public static void main (String[] args) {
    try {
      Scanner s = new Scanner(new File("input.txt"));
      while (s.hasNextLine()) {
        String line = s.nextLine();
        if (line.equals("#")) {
          break;
        }
        solve(line);
      }
      s.close();
    } catch (Exception e) {
      System.out.println(e);
    }
  }
}
