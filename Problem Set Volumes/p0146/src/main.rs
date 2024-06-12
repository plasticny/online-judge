use std::fs::read_to_string;

fn char_to_idx (c : char) -> usize {
  (c as u8 - 'a' as u8) as usize
}

fn next_letter (cur : char, available : &Vec<bool>) -> char {
  for i in (char_to_idx(cur) + 1)..26 {
    if available[i] {
      return ('a' as u8 + i as u8) as char
    }
  }
  cur
}

fn get_letter_available (line : &String) -> Vec<bool> {
  let mut res : Vec<bool> = Vec::new();
  for _ in 0..26 {
    res.push(false);
  }
  for c in line.chars() {
    res[char_to_idx(c)] = true;
  }
  res
}

fn get_char (line : &String, idx : usize) -> char {
  line.chars().nth(idx).unwrap()
}

fn main () {
  let lines : Vec<String> = read_to_string("src/input.txt").unwrap().lines().map(|l| l.to_string()).collect();
  let end_line = "#".to_string();

  for line in lines {
    if line == end_line {
      break;
    }

    let line_len = line.len();
    let letter_available = get_letter_available(&line);

    // find change idx
    let mut letter_cnt : Vec<usize> = Vec::new();
    for _ in 0..26 {
      letter_cnt.push(0);
    }

    let mut change_idx: isize = -1;
    for i in (0..line_len).rev() {
      let cur =  get_char(&line, i);
      letter_cnt[char_to_idx(cur)] += 1;

      let next = next_letter(cur, &letter_available);
      if cur != next && letter_cnt[char_to_idx(next)] > 0 {
        change_idx = i as isize;
        break;
      }
    }

    if change_idx == -1 {
      println!("No Successor");
      continue;
    }

    // print successor
    // unchange letter
    for i in 0..(change_idx as usize) {
      print!("{}", get_char(&line, i));
    }

    // change letter
    let changed_letter = next_letter(get_char(&line, change_idx as usize), &letter_available);
    print!("{}", changed_letter);

    // remain letter
    letter_cnt[char_to_idx(changed_letter)] -= 1;
    for i in 0..letter_cnt.len() {
      if letter_cnt[i] == 0 {
        continue;
      }
      for _ in 0..letter_cnt[i] {
        print!("{}", ('a' as u8 + i as u8) as char);
      }
    }

    println!();
  }
}
