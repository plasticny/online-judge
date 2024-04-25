import { readFileSync } from 'fs'

class Reader {
  lines : Array<string>

  public load (file_nm : string) {
    const file = readFileSync(file_nm)
    this.lines = file.toString().split('\n')
  }

  public eof () : boolean {
    return this.lines.length == 0
  }

  public next_line () : string {
    if (this.eof()) {
      throw 'Already reached end of the file'
    }
    return this.lines.shift()
  }

  public next_line_str (spliter : string = ' ') : Array<string> {
    return this.next_line().split(spliter)
  }

  public next_line_int (spliter : string = ' ') : Array<number> {
    return this.next_line_str(spliter).map(str => parseInt(str))
  }
}
export default new Reader()
