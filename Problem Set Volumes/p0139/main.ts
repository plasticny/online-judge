import reader from './reader'

reader.load('input.txt')

interface CodeInfo {
  name: string
  price: number
}

class Node {
  public info : CodeInfo | undefined
  public next : Array<Node | undefined>

  constructor () {
    this.info = undefined
    this.next = Array(10).fill(undefined)
  }
}

function insert (root : Node, code : string, info : CodeInfo) {
  let node = root
  for (let i = 1; i < code.length; i++) {
    const num = code[i]
    if (node.next[num] === undefined) {
      node.next[num] = new Node()
    }
    node = node.next[num]
  }
  node.info = info
}

function find (root : Node, call_num : string) : {
  country : string,
  sub_num : string,
  cpm : number
} {
  // local
  if (call_num[0] !== '0') {
    return {
      country: 'Local',
      sub_num: call_num,
      cpm: 0
    }
  }

  let node = root
  let i = 1
  for (; i < call_num.length; i++) {
    node = node.next[parseInt(call_num[i])]
    if (node === undefined || node.info !== undefined) {
      break
    }
  }
  return {
    country: node ? node.info.name : 'Unknown',
    sub_num: node ? call_num.substring(++i) : '',
    cpm: node ? node.info.price : -1
  }
}

function main() {
  const root = new Node()

  // first part
  while (true) {
    const code = reader.next_str()
    if (code === '000000') {
      break
    }
    const [name, price] = reader.next_str().split('$')
    insert(root, code, {name: name, price: Number.parseInt(price) / 100})
  }

  // second part
  while (true) {
    const call_num = reader.next_str()
    if (call_num === '#') {
      break
    }
    const duration = parseInt(reader.next_str())

    const res = find(root, call_num)
    const cpm_str = res.cpm === -1 ? '' : res.cpm.toFixed(2).toString()
    const total = res.cpm === -1 ? -1 : Math.round(res.cpm * duration * 100) / 100

    let line = ''
    line += call_num.padEnd(16)
    line += res.country.padEnd(25)
    line += res.sub_num.padStart(9)
    line += duration.toString().padStart(5)
    line += cpm_str.padStart(6)
    line += total.toFixed(2).toString().padStart(7)
    console.log(line)
  }
}
main()
