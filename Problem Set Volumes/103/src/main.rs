use std::io;

fn get_input () -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn sort_compare (a: &Vec<usize>, b: &Vec<usize>) -> std::cmp::Ordering {
    let mut a_iter = a.iter();
    let mut b_iter = b.iter();

    for _ in 0..a.len() {
        let a_val = a_iter.next().unwrap();
        let b_val = b_iter.next().unwrap();
        if a_val < b_val {
            return std::cmp::Ordering::Less;
        }
        else if a_val > b_val {
            return std::cmp::Ordering::Greater;
        }
    }
    return std::cmp::Ordering::Equal;
}

fn is_inner (a: &Vec<usize>, b: &Vec<usize>) -> bool {
    for i in 0..a.len() {
        if a[i] >= b[i] {
            return false;
        }
    }
    return true;
}

fn main() {
    loop {
        let raw_kn = get_input();
        if raw_kn.len() == 0 {
            break;
        }

        let k_n: Vec<&str> = raw_kn.split_whitespace().collect();
        let k = k_n[0].parse::<usize>().unwrap();
        let n = k_n[1].parse::<usize>().unwrap();

        let mut seq_ls: Vec<(usize, Vec<usize>)> = Vec::new();
        // (next index, sequence length)
        let mut next_ls: Vec<(isize, isize)> = Vec::new();

        let mut max_len = 0;
        let mut max_idx = 0;

        // Get input
        for i in 0..k {
            let raw_seq = get_input();
            let mut seq: Vec<usize> = raw_seq.split_whitespace().map(|x| x.parse::<usize>().unwrap()).collect();
            seq.sort();
            seq_ls.push((i, seq));
            next_ls.push((-1, 1));
        }
        seq_ls.sort_by(|a, b| sort_compare(&a.1, &b.1));

        for i in (0..k).rev() {
            let idx_i = seq_ls[i].0;
            for j in (i+1)..k {
                let idx_j = seq_ls[j].0;
                if is_inner(&seq_ls[i].1, &seq_ls[j].1) {
                    if next_ls[idx_i].1 <= next_ls[idx_j].1 {
                        next_ls[idx_i].0 = idx_j as isize;
                        next_ls[idx_i].1 = next_ls[idx_j].1 + 1;
                    }
                }
            }
            if next_ls[idx_i].1 > max_len {
                max_len = next_ls[idx_i].1;
                max_idx = idx_i;
            }
        }

        println!("{}", max_len);
        let mut idx = max_idx as isize;
        while idx != -1 {
            print!("{} ", idx + 1);
            idx = next_ls[idx as usize].0;
        }
        println!();
    }
}
