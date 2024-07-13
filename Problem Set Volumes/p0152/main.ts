import reader from './reader'

reader.load('input.txt')

interface Point {
  x: number,
  y: number,
  z: number
}

class Tree {
  public p: Point
  public o: number

  constructor (x: number, y: number, z: number) {
    this.p = {x: x, y: y, z: z}
    this.o = distance2(this.p, {x: 0, y: 0, z: 0})
  }
}

function distance2 (p1 : Point, p2 : Point) : number {
  return Math.pow(p1.x - p2.x, 2) + Math.pow(p1.y - p2.y, 2) + Math.pow(p1.z - p2.z, 2)
}

function solve (tree_ls: Array<Tree>) : Array<number> {
  const closest_ls = new Array<number>()
  for (let i = 0; i < tree_ls.length; i++) {
    closest_ls.push(10)
  }

  tree_ls.sort((a, b) => { return a.o - b.o })

  for (let t1_idx = 0; t1_idx < tree_ls.length; t1_idx++) {
    const t1 = tree_ls[t1_idx]
    let upper = Math.pow(closest_ls[t1_idx], 3)

    // search frontward
    for (let t2_idx = t1_idx - 1; t2_idx >= 0; t2_idx--) {
      const t2 = tree_ls[t2_idx]
      if (t1.o - t2.o > upper) {
        break
      }

      const d = Math.pow(distance2(t1.p, t2.p), 0.5)
      const range = Math.floor(d)
      if (range < closest_ls[t1_idx]) {
        closest_ls[t1_idx] = range
        upper = Math.pow(range, 3)
      }
    }

    // search backward
    for (let t2_idx = t1_idx + 1; t2_idx < tree_ls.length; t2_idx++) {
      const t2 = tree_ls[t2_idx]
      if (t2.o - t1.o > upper) {
        break
      }

      const d = Math.pow(distance2(t1.p, t2.p), 0.5)
      const range = Math.floor(d)
      if (range < closest_ls[t1_idx]) {
        closest_ls[t1_idx] = range
        upper = Math.pow(range, 3)
      }
      if (range < closest_ls[t2_idx]) {
        closest_ls[t2_idx] = range
      }
    }
  }

  // count range
  const res : Array<number> = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
  for (const range of closest_ls) {
    if (range < 10) {
      res[range]++
    }
  }
  return res
}

function main () {
  const tree_ls = new Array<Tree>()

  // reader trees
  while (true) {
    const x = reader.next_float()
    const y = reader.next_float()
    const z = reader.next_float()
    if (x == 0 && y == 0 && z == 0) {
      break
    }
    tree_ls.push(new Tree(x, y, z))
  }

  const h = solve(tree_ls)
  
  let res = ''
  for (const n of h) {
    res += n.toString().padStart(4)
  }
  console.log(res)
}
main()
