use std::{cmp::Ordering, collections::HashSet, fs::read_to_string};

fn main() {
  // store cases into case_ls
  let mut case_ls : Vec<Vec<(isize, String)>> = vec![Vec::new()];
  let mut case_cnt = 0;
  read_to_string("src/input.txt").unwrap().lines().for_each(|line| {
    line.split_whitespace().for_each(|raw_node| {
      if let Some((value, node_path)) = raw_node.split_once(',') {
        case_ls[case_cnt].push((
          value.get(1..).unwrap().parse::<isize>().unwrap(),
          node_path.get(..node_path.len()-1).unwrap().to_string()
        ));
      } else {
        case_ls.push(Vec::new());
        case_cnt += 1;
      }
    });
  });

  // handle cases
  for i in 0..case_cnt {
    // sort nodes by path
    case_ls[i].sort_by(|a, b| {
      let len_cmp = a.1.len().cmp(&b.1.len());
      if len_cmp == Ordering::Equal { a.1.cmp(&b.1) } else { len_cmp }
    });

    // check completed
    let mut path_set : HashSet<String> = HashSet::new();
    let mut completed = true;
    for j in 0..case_ls[i].len() {
      let node_path = case_ls[i][j].1.clone();
      if node_path.len() != 0 && !path_set.contains(node_path.get(0..node_path.len()-1).unwrap()) {
        // uncompleted tree
        completed = false;
        break;
      }
      path_set.insert(node_path);
    }

    // print result
    if completed {
      for j in 0..case_ls[i].len() {
        print!("{} ", case_ls[i][j].0);
      }
      println!();
    } else {
      println!("not complete");
    }    
  }
}
