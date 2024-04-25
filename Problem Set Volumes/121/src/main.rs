use std::fs::read_to_string;

fn skw (w : f32, h : f32) -> usize {
  let skw_w = (w - 0.5).floor();
  let skw_h = ((h - 1.0) / 0.75_f32.sqrt() + 1.0).floor();
  let half_skw_h = skw_h / 2.0;
  let res = w.floor() * half_skw_h.ceil() + skw_w * half_skw_h.floor();
  res as usize
}

fn main() {
  read_to_string("src/input.txt").unwrap().lines().for_each(|line| {
    let dim : Vec<f32> = line.split_whitespace()
      .map(|x| x.trim().parse::<f32>().unwrap())
      .collect();

    let grid = (dim[0].floor() * dim[1].floor()) as usize;
    let skw0 = skw(dim[0], dim[1]);
    let skw1 = if dim[0] != dim[1] { skw(dim[1], dim[0]) } else { 0 };

    if grid >= skw0 && grid >= skw1 {
      println!("{} grid", grid);
    }
    else {
      println!("{} skew", if skw0 > skw1 { skw0 } else { skw1 });
    }
  });
}
