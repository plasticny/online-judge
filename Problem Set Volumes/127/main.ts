import reader from './reader'

reader.load('input.txt')

class Node {
  public s : Array<string> = new Array()
  public prev? : Node
  public next? : Node

  public is_match (card : string) : boolean {
    const top = this.s[this.s.length - 1]
    return top[0] === card[0] || top[1] === card[1]
  }
}

function get_prev (node : Node) : Node | undefined {
  return node === undefined ? undefined : node.prev
}

function solve (head : Node) {
  let node = head
  while (node !== undefined) {
    const top = node.s.pop()
    const prev = get_prev(node)
    const prev3 = get_prev(get_prev(prev))

    let next : Node
    if (prev3 !== undefined && prev3.is_match(top)) {
      prev3.s.push(top)
      next = prev3
    }
    else if (prev !== undefined && prev.is_match(top)) {
      prev.s.push(top)
      next = prev
    }
    else {
      node.s.push(top)
      next = node.next
    }

    if (node.s.length == 0) {
      if (node.prev !== undefined) {
        node.prev.next = node.next
      }
      if (node.next !== undefined) {
        node.next.prev = node.prev
      }
      node = null
    }

    node = next
  }
}

function main () {
  while (true) {
    let head : Node | undefined
    let prev : Node | undefined
    for (let i = 0; i < 52 && !reader.eof(); i++) {
      const node = new Node()
      node.s.push(reader.next_str())

      if (head === undefined) {
        head = node
      }

      if (prev !== undefined) {
        prev.next = node
        node.prev = prev
      }
      prev = node
    }

    if (head.s[0] === '#') {
      break
    }

    solve(head)

    let pile_cnt = 0
    let num_str = ''
    for(let node = head; node !== undefined; node = node.next) {
      pile_cnt++
      num_str += node.s.length.toString()
      num_str += ' '
    }
    console.log(`${pile_cnt} pile${pile_cnt > 1 ? 's' : ''} remaining: ${num_str}`)
  }
}
main()
