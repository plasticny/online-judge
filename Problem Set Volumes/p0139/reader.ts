import { readFileSync } from 'fs'

class Reader {
  str_ls : Array<string>

  public load (file_nm : string, splitter : string = ' ') {
    const file = readFileSync(file_nm)

    this.str_ls = new Array<string>()
    for (const line of file.toString().split('\r\n')) {
      for (const str of line.split(splitter)) {
        this.str_ls.push(str)
      }
    }
  }

  public eof () : boolean {
    return this.str_ls.length == 0
  }

  public next_str () : string {
    if (this.eof()) {
      throw 'Already reached end of the file'
    }
    return this.str_ls.shift()
  }

  public next_int () : number {
    return parseInt(this.next_str())
  }

  public next_float () : number {
    return parseFloat(this.next_str())
  }
}
export default new Reader()
