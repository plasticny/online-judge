import reader from './reader'

type TGrid = Array<Array<TBumper|undefined>>
type TBumper = { value: number, cost: number }
type TDirection = 0|1|2|3

enum PosTypes {
  Empty, Bumper, Wall
}

function get_next_pos (x : number, y : number, dir : TDirection) : [number, number] {
  if (dir == 0) {
    return [x+1, y]
  }
  if (dir == 1) {
    return [x, y+1]
  }
  if (dir == 2) {
    return [x-1, y]
  }
  return [x, y-1]
}

function get_pos_type (x : number, y : number, gird : TGrid) : PosTypes {
  if (x == 0 || x == gird[0].length-1 || y == 0 || y == gird.length-1) {
    return PosTypes.Wall
  }
  if (gird[y][x] !== undefined) {
    return PosTypes.Bumper
  }
  return PosTypes.Empty
}

function turn (dir : TDirection) : TDirection {
  return dir == 0 ? 3 : (dir-1) as TDirection
}

function main () {
  reader.load('input.txt')

  const [grid_x, grid_y] = reader.next_line_int()
  const [wall_cost] = reader.next_line_int()
  const [bumper_num] = reader.next_line_int()

  const grid : TGrid =  new Array(grid_y).fill(new Array(grid_x).fill(undefined))

  for (let i = 0; i < bumper_num; i++) {
    const [x, y, value, cost] = reader.next_line_int()
    grid[y-1][x-1] = { value: value, cost: cost }
  }

  let total_pts = 0

  while (!reader.eof()) {
    let pt = 0
    let [x, y, dir_int, life] = reader.next_line_int()

    let dir = dir_int as TDirection
    x--, y--

    while (--life > 0) {
      const [next_x, next_y] = get_next_pos(x, y, dir)
      const next_pos_type = get_pos_type(next_x, next_y, grid)

      if (next_pos_type == PosTypes.Empty) {
        x = next_x
        y = next_y
        continue
      }

      if (next_pos_type == PosTypes.Wall) {
        life -= wall_cost
      }
      else {
        const { value, cost } = grid[next_y][next_x]
        life -= cost
        pt += value
      }
      dir = turn(dir);
    }

    console.log(pt)
    total_pts += pt
  }

  console.log(total_pts)
}
main()
