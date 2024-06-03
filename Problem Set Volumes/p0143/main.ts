import reader from './reader'

reader.load('input.txt')

interface Point {
  x : number, y : number
}

class Line {
  public a : number | undefined
  public c : number | undefined
  public min_y : number
  public max_y : number
  public min_x : number
  public max_x : number

  constructor (p1 : Point, p2 : Point) {
    const nu = p1.y - p2.y
    const de = p1.x - p2.x
    if (nu === 0) {
      this.a = 0
      this.c = p1.y
    } else if (de === 0) {
      this.a = undefined
      this.c = undefined
    } else {
      this.a = nu / de
      this.c = p1.y - this.a * p1.x
    }

    this.min_y = Math.min(p1.y, p2.y)
    this.max_y = Math.max(p1.y, p2.y)
    this.min_x = Math.min(p1.x, p2.x)
    this.max_x = Math.max(p1.x, p2.x)
  }

  public is_horizon () : boolean {
    return this.a === 0
  }

  public is_vertical () : boolean {
    return this.a === undefined
  }

  public y_in_range (y : number) : boolean {
    return y >= this.min_y && y <= this.max_y
  }

  public cal_x (y : number) : number {
    if (this.a === undefined || this.c === undefined) {
      throw "a or c undefined"
    }
    return (y - this.c) / this.a
  }
}

function solve (p1 : Point, p2 : Point, p3 : Point) {
  const line_ls = [new Line(p1, p2), new Line(p1, p3), new Line(p2, p3),]
  const min_y = Math.ceil(Math.min(p1.y, p2.y, p3.y))
  const max_y = Math.floor(Math.max(p1.y, p2.y, p3.y))

  let res = 0
  for (let y = min_y; y <= max_y; y++) {
    const x_ls : Array<number> = []
    for (let i = 0; i < 3 && x_ls.length < 2; i++) {
      const line : Line = line_ls[i]
      if (!line.y_in_range(y)) {
        continue
      }

      if (line.is_horizon()) {
        x_ls.push(line.min_x)
        x_ls.push(line.max_x)
      } else if (line.is_vertical()) {
        x_ls.push(line.min_x)
      } else {
        x_ls.push(line.cal_x(y))
      }
    }
    res += Math.floor(Math.max(...x_ls)) - Math.ceil(Math.min(...x_ls)) + 1
  }
  console.log(res.toString().padStart(4))
}

function main () {
  while (true) {
    let end : boolean = true;
    const num_ls : Array<number> = []
    for (let i = 0; i < 6; i++) {
      const num : number = reader.next_float()
      num_ls.push(num);
      end = end && num === 0.0
    }

    if (end) {
      return
    }
    solve (
      { x: num_ls[0], y: num_ls[1] },
      { x: num_ls[2], y: num_ls[3] },
      { x: num_ls[4], y: num_ls[5] }
    )
  }
}
main()
