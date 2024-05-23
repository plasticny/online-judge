import reader from './reader'

reader.load('input.txt')

interface Point {
  x : number,
  y : number
}

function read_ploygon (n : number) : Array<Point> {
  const ploygon : Array<Point> = []
  for (let i = 0; i < n; i++) {
    ploygon.push({
      x: reader.next_int(),
      y: reader.next_int()
    })
  }
  return ploygon
}

function ploygon_area (ploygon : Array<Point>) : number {
  let res = 0
  for (let i = 0, j = ploygon.length - 1; i < ploygon.length; j = i++) {
    res += ploygon[j].x * ploygon[i].y - ploygon[i].x * ploygon[j].y
  }
  return Math.abs(res / 2)
}

function pip (p : Point, ploygon : Array<Point>) : boolean {
  let res = false
  for (let i = 0, j = ploygon.length - 1; i < ploygon.length; j = i++) {
    const pi = ploygon[i], pj = ploygon[j]
    if ((pi.y < p.y && p.y <= pj.y) || (pj.y < p.y && p.y <= pi.y)) {
      if (p.x < (pj.x - pi.x) * (p.y - pi.y) / (pj.y - pi.y) + pi.x) {
        res = !res
      }
    }
  }
  return res
}

function add_pip (inter : Array<Point>, pg1 : Array<Point>, pg2 : Array<Point>) {
  for (const p of pg1) {
    if (pip(p, pg2)) {
      inter.push(p)
    }
  }
}

function find_intersection (srt1 : Point, end1 : Point, srt2 : Point, end2 : Point) : Point | null {  
  const de = (end2.y - srt2.y) * (end1.x - srt1.x) - (end2.x - srt2.x) * (end1.y - srt1.y)
  // parallel lines
  if (de === 0) {
    return null
  }

  const ua = ((end2.x - srt2.x) * (srt1.y - srt2.y) - (end2.y - srt2.y) * (srt1.x - srt2.x)) / de
  const ub = ((end1.x - srt1.x) * (srt1.y - srt2.y) - (end1.y - srt1.y) * (srt1.x - srt2.x)) / de
  // is the intersection along the segments
  if (ua < 0 || ua > 1 || ub < 0 || ub > 1) {
    return null
  }

  return {
    x: srt1.x + ua * (end1.x - srt1.x),
    y: srt1.y + ua * (end1.y - srt1.y)
  }
}

function add_intersection (inter : Array<Point>, pg1 : Array<Point> , pg2 : Array<Point>) {
  for (let i1 = 0, j1 = pg1.length - 1; i1 < pg1.length; j1 = i1++) {
    for (let i2 = 0, j2 = pg2.length - 1; i2 < pg2.length; j2 = i2++) {
      const intersection : Point | null = find_intersection(
        pg1[j1], pg1[i1], pg2[j2], pg2[i2]
      )
      if (intersection !== null) {
        inter.push(intersection)
      }
    }
  }
}

function is_ccw (p1 : Point, p2 : Point, p3 : Point) : boolean {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x) > 0
}

function convex_hull (point_ls : Array<Point>) : Array<Point> {
  point_ls.sort((a, b) => {
    if (a.x !== b.x) {
      return a.x - b.x
    }
    return a.y - b.y
  })

  const n = point_ls.length
  const tmp_res : Array<Point> = []
  let k = 0

  for (let i = 0; i < n; i++) {
    while (k >= 2 && !is_ccw(tmp_res[k-2], tmp_res[k-1], point_ls[i])) k--;
    tmp_res[k++] = point_ls[i];
  }

  for (let i = n-2, tmp = k; i >= 0; i--) {
    while (k > tmp && !is_ccw(tmp_res[k-2], tmp_res[k-1], point_ls[i])) k--;
    tmp_res[k++] = point_ls[i];
  }

  const res : Array<Point> = []
  for (let i = 0; i < k - 1; i++) {
    res.push(tmp_res[i])
  }
  return res
}

function cal_inter_area (pg1 : Array<Point>, pg2 : Array<Point>) : number {
  const intersection : Array<Point> = []

  add_pip(intersection, pg1, pg2)
  add_pip(intersection, pg2, pg1)
  add_intersection(intersection, pg1, pg2)

  return ploygon_area(convex_hull(intersection))
}

function main () {
  let res : string = ''
  while (true) {
    const pg1n = reader.next_int()
    if (pg1n === 0) {
      break
    }

    const pg1 = read_ploygon(pg1n)
    const pg2 = read_ploygon(reader.next_int())

    const pg1_area = ploygon_area(pg1)
    const pg2_area = ploygon_area(pg2)
    const inter_area = cal_inter_area(pg1, pg2)
    
    const required_area = pg1_area + pg2_area - inter_area * 2
    res += (Math.round(required_area * 100) / 100).toString().padStart(8)
  }
  console.log(res)
}
main()
