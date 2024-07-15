use std::fs::read_to_string;

fn char_to_idx (c : char) -> usize {
  (c as u8 - 'a' as u8) as usize
}

fn next_pt (pt: &mut usize, letter_cnt: &Vec<usize>) {
  while *pt < 25 && letter_cnt[*pt] == 0 {
    *pt += 1;
  }
}

fn factorial (n: usize) -> usize {
  let mut res = 1;
  for i in 2..(n+1) {
    res *= i
  }
  res
}

fn cal_prev (idx: usize, letter_cnt: &Vec<usize>) -> usize {
  let mut res = 0;
  for i in 0..idx {
    if letter_cnt[i] == 0 {
      continue;
    }

    let mut cnt = 0;
    let mut de = 0;
    for j in 0..26 {
      if letter_cnt[j] == 0 {
        continue;
      }

      let lc = letter_cnt[j] - if j == i {1} else {0};
      cnt += lc;
      if lc > 1 {
        de += factorial(lc);
      }
    }
    res += factorial(cnt) / if de == 0 {1} else {de};
  }
  res
}

fn solve (line: &String) -> usize {
  let mut letter_cnt: Vec<usize> = Vec::new();
  for _ in 0..26 {
    letter_cnt.push(0);
  }
  for c in line.chars() {
    letter_cnt[char_to_idx(c)] += 1;
  }

  let mut pt: usize = 0;
  next_pt(&mut pt, &letter_cnt);

  let mut res: usize = 0;
  for c in line.chars() {
    let c_idx = char_to_idx(c);
    if c_idx != pt {
      res += cal_prev(c_idx, &letter_cnt);
    }
    letter_cnt[c_idx] -= 1;
    next_pt(&mut pt, &letter_cnt);
  }

  res + 1
}

fn main () {
  let lines : Vec<String> = read_to_string("src/input.txt").unwrap().lines().map(|l| l.to_string()).collect();
  let end_line = "#".to_string();

  for line in lines {
    if line == end_line {
      break;
    }
    println!("{:10}", solve(&line));
  }
}
