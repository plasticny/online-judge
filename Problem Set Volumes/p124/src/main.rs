use std::{collections::{HashMap, HashSet}, fs::read_to_string};

fn get_word_ls (s : &String) -> Vec<String> {
  s.split_whitespace().map(|str| str.to_string()).collect()
}

fn solve (prev : String, appeared_set : &mut HashSet<String>, letter_ls : &Vec<String>, constraint_mp : &HashMap<String, Vec<String>>, ) {
  for i in 0..letter_ls.len() {
    let letter = letter_ls.get(i).unwrap();

    // check if the letter not appeared
    if appeared_set.contains(letter) {
      continue;
    }

    // check fit constraint
    let mut do_fit = true;
    for l in constraint_mp.get(letter).unwrap() {
      if !appeared_set.contains(l) {
        do_fit = false;
        break;
      }
    }
    if !do_fit {
      continue;
    }

    let mut cur = prev.clone();
    cur.push_str(letter);

    // seq finish, print
    if cur.len() == letter_ls.len() {
      println!("{}", cur);
      continue;
    }

    appeared_set.insert(letter.clone());
    solve(cur, appeared_set, letter_ls, constraint_mp);
    appeared_set.remove(letter);
  }
}

fn main () {
  let lines : Vec<String> = read_to_string("src/input.txt").unwrap().lines().map(|l| l.to_string()).collect();
  for i in 0..lines.len()/2 {
    let letter_ls = get_word_ls(lines.get(i*2).unwrap());
    let mut constraint_mp : HashMap<String, Vec<String>> = HashMap::new();
    for j in 0..letter_ls.len() {
      constraint_mp.insert(letter_ls.get(j).unwrap().clone(), Vec::new());
    }

    let constraint_ls = get_word_ls(lines.get(i*2+1).unwrap());
    for j in 0..constraint_ls.len()/2 {
      let left = constraint_ls.get(j*2).unwrap();
      let right = constraint_ls.get(j*2+1).unwrap();
      constraint_mp.get_mut(right).unwrap().push(left.clone());
    }

    let mut appeared_set : HashSet<String> = HashSet::new();
    solve ("".to_string(), &mut appeared_set, &letter_ls, &constraint_mp);
    println!();
  }
}
