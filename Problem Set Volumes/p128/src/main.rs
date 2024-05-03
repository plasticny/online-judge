use std::{cmp::Ordering, fs::read_to_string};

fn main() {
  let g : u32 = 34943;

  let lines : Vec<String> = read_to_string("src/input.txt").unwrap().lines().map(|l| l.to_string()).collect();
  let end_line = "#".to_string();

  for line in lines {
    if line.cmp(&end_line) == Ordering::Equal {
      break;
    }

    let mut x : u32 = 0;
    for c in line.chars() {
      x += c as u32;
      x %= g;
      x <<= 8;
    }
    x <<= 8;

    let r = x % g;
    if r == 0 {
      println!("00 00");
    } else {
      x = g - r;
      let mut first_half = format!("{:04x}", x).to_string().to_uppercase();
      let second_half = first_half.split_off(2);
      println!("{} {}", first_half, second_half);
    }
  }
}
