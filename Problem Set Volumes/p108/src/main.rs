use std::{collections::VecDeque, io};

fn get_input () -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn main() {
    let n = get_input().parse::<usize>().unwrap();
    let mut rect : [[i8; 100]; 100] = [[0; 100]; 100];
    let mut sum_ls : [[i8; 100]; 101] = [[0; 100]; 101];
    let mut dp : [i8; 101] = [0; 101];

    let mut num_q : VecDeque<i8> = VecDeque::new();
    for i in 0..n {
        for j in 0..n {
            if num_q.len() == 0 {
                let line = get_input();
                for num in line.split_whitespace() {
                    num_q.push_back(num.parse::<i8>().unwrap());
                }
            }
            rect[i][j] = num_q.pop_front().unwrap();
        }
    }

    for i in 0..n {
        for j in 0..n {
            sum_ls[i][j+1] = sum_ls[i][j] + rect[i][j];
        }
    }

    let mut max = 0;
    for i in 0..n {
        for j in i..n {
            for k in 0..n {
                let row = sum_ls[k][j+1] - sum_ls[k][i];
                dp[k+1] = std::cmp::max(dp[k] + row, row);
                max = std::cmp::max(max, dp[k+1]);
            }
        }
    }

    println!("{}", max);
}
