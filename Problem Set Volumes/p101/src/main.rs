use std::io;

fn get_input () -> String {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.trim().to_string()
}

fn main () {
    let s_move = String::from("move");
    let s_pile = String::from("pile");
    let s_onto = String::from("onto");
    let s_quit = String::from("quit");

    let box_num: usize = get_input().parse::<usize>().unwrap();

    let mut loc_ls : Vec<usize> = (0..box_num).map(|x| x).collect();
    let mut pile_ls : Vec<Vec<usize>> = (0..box_num).map(|x| vec![x]).collect();

    loop {
        let input = get_input();
        if input.eq(&s_quit) {
            break;
        }

        let input_ls: Vec<&str> = input.split_whitespace().collect();

        let command1 = input_ls[0];
        let command2 = input_ls[2];
        let box1_id = input_ls[1].parse::<usize>().unwrap();
        let box2_id = input_ls[3].parse::<usize>().unwrap();

        let box1_loc = loc_ls[box1_id];
        let box2_loc = loc_ls[box2_id];

        if command2.eq(&s_onto) {
            while pile_ls[box2_loc].last().unwrap() != &box2_id {
                let last_box = pile_ls[box2_loc].pop().unwrap();
                loc_ls[last_box] = last_box;
                pile_ls[last_box].push(last_box);
            }
        }

        if command1.eq(&s_move) {
            if pile_ls[box1_loc].last().unwrap() != &box1_id {
                panic!("Error: {} is not the top box in its pile", box1_id);
            }
            let box1 = pile_ls[box1_loc].pop().unwrap();
            loc_ls[box1] = box2_loc;
            pile_ls[box2_loc].push(box1);
        }
        else if command1.eq(&s_pile) {
            let mut pile = Vec::new();
            while pile_ls[box1_loc].last().unwrap() != &box1_id {
                pile.push(pile_ls[box1_loc].pop().unwrap());
            }
            pile.push(pile_ls[box1_loc].pop().unwrap());

            while !pile.is_empty() {
                let box1 = pile.pop().unwrap();
                loc_ls[box1] = box2_loc;
                pile_ls[box2_loc].push(box1);
            }
        }
    }

    for (i, pile) in pile_ls.iter().enumerate() {
        print!("{}:", i);
        for box_id in pile {
            print!(" {}", box_id);
        }
        println!();
    }
}