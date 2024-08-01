import { readFileSync } from 'fs'

type TLine = Array<string>
type TDoc = Array<TLine>

export default class {
  private doc: TDoc

  public constructor (file_nm: string, public splitter: string = ' ') {
    this.doc = new Array<TLine>()
    for (const line of readFileSync(file_nm).toString().split('\r\n')) {
      const str_ls = new Array<string>()
      for (const str of line.split(splitter)) {
        str_ls.push(str)
      }
      this.doc.push(str_ls)
    }
  }

  public get eof (): boolean {
    return this.doc.length == 0
  }

  public assert_not_eof (): void {
    if (this.eof) {
      throw 'Already reached end of the file'
    }
  }

  public next_str (): string {
    this.assert_not_eof()
    const str = this.doc[0].shift().trim()
    if (this.doc[0].length == 0) {
      this.doc.shift()
    }
    return str
  }

  public next_int (): number {
    return parseInt(this.next_str())
  }

  public next_float (): number {
    return parseFloat(this.next_str())
  }

  /* read until end of current line and return a string */
  public next_line (): string {
    this.assert_not_eof()
    return this.doc.shift().join(this.splitter).trim()  
  }
}
