import reader from './reader'
import { Queue } from 'typescript-collections'

reader.load('input.txt')

class Node {
  public to_ls : Array<number> = []
}

function solve_node (node_id : number, node_ls : Array<Node>, mat : Array<Array<number>>, branch_visited : Array<boolean>) {
  // cycle occur
  if (branch_visited[node_id] === true) {
    mark_cycle (node_id, node_ls, mat)
    return
  }

  // already solved, return
  if (mat[node_id] !== undefined) {
    return
  }

  mat[node_id] = new Array(mat.length).fill(0)
  branch_visited[node_id] = true

  // M(node) = M(x1) + M(x2) + ... + M(xn) + m(node)
  // where x is reachable nodes from node
  for (let idx of node_ls[node_id].to_ls) {
    // M(x)
    solve_node(idx, node_ls, mat, branch_visited)
    for (let i = 0; i < mat.length; i++) {
      if (mat[node_id][i] === -1) {
        continue
      }
      else if (mat[idx][i] === -1) {
        mat[node_id][i] = -1
      }
      else {
        mat[node_id][i] += mat[idx][i]
      }
    }

    // m(x)
    if (mat[node_id][idx] !== -1) {
      mat[node_id][idx]++
    }
  }

  branch_visited[node_id] = false
}

function mark_cycle (node_id : number, node_ls : Array<Node>, mat : Array<Array<number>>) {
  const q : Queue<number> = new Queue()
  q.enqueue(node_id)
  while (!q.isEmpty()) {
    const idx = q.dequeue()
    mat[node_id][idx] = -1
    for (let next of node_ls[idx].to_ls) {
      if (mat[node_id][next] !== -1) {
        q.enqueue(next)
      }
    }
  }
}

function main () {
  let city_cnt = 0
  while (!reader.eof()) {
    console.log(`matrix for city ${city_cnt++}`)
    const node_ls = new Array()

    // read links
    const link_cnt = reader.next_int()
    let col_cnt = 0
    for (let i = 0; i < link_cnt; i++) {
      const j = reader.next_int()
      const k = reader.next_int()

      col_cnt = Math.max(col_cnt, j, k)
      for (const i of [j, k]) {
        if (node_ls[i] === undefined) {
          node_ls[i] = new Node()
        }
      }
      node_ls[j].to_ls.push(k)
    }
    col_cnt++

    const mat : Array<Array<number>> = new Array(col_cnt)
    // loop nodes
    for (let i = 0; i < node_ls.length; i++) {
      if (node_ls[i] === undefined) {
        mat[i] = new Array(col_cnt).fill(0)
      }
      else {
        solve_node(i, node_ls, mat, new Array(col_cnt).fill(false))
      }
      console.log(mat[i].join(' '))
    }
  }
}
main()
