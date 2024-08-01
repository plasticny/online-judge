import Reader from './reader'

class Date {
  public static year_days: Array<number> = [undefined, 31, undefined, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31]

  public static get_month_days (month: number, year: number): number {
    if (month == 2) {
      return year % 4 == 0 ? 29 : 28
    }
    return Date.year_days[month]
  }

  public constructor (public day: number, public month: number) {}

  public compare (other: Date): number {
    return this.month != other.month ? this.month - other.month : this.day - other.day
  }

  public get_remind_period (year: number): Map<number, Map<number, number>> {
    const res = new Map<number, Map<number, number>>()
    res.set(this.month, new Map())

    let m = this.month
    let d = this.day
    let month_day = Date.get_month_days(m, year)
    for (let day_between = 0; day_between <= 7; day_between++) {
      res.get(m).set(d, day_between)
      if (++d > month_day) {
        m += 1
        d = 1
        month_day = Date.get_month_days(m, year)
        res.set(m, new Map())
      }
    }

    return res
  }
}

class Anni extends Date {
  public constructor (
    day: number,
    month: number,
    public priority: number,
    public name: string,
    public seq: number
  ) {
    super(day, month)
  }

  public override compare (other: Anni): number {
    const date_cmp = super.compare(other)
    if (date_cmp != 0) {
      return date_cmp
    }
    if (this.priority != other.priority) {
      return this.priority - other.priority
    }
    return this.seq - other.seq
  }
}

interface AnniRemind {
  star: number
  anni: Anni
}

function solve (date_ls: Array<Date>, anni_ls: Array<Anni>, year: number): Array<Array<AnniRemind>> {
  // sort anni
  anni_ls.sort((a: Anni, b: Anni) => a.compare(b))

  // sort date for faster searching
  const date_idx_ls = Array.from(date_ls.keys())
  date_idx_ls.sort((a: number, b: number) => date_ls[a].compare(date_ls[b]))

  const res: Array<Array<AnniRemind>> = new Array(date_ls.length)
  let srt_search_idx = 0
  for (const date_idx of date_idx_ls) {
    const today = date_ls[date_idx]
    const remind_period = today.get_remind_period(year)

    // move the start search idx
    while (today.compare(anni_ls[srt_search_idx]) > 0) {
      srt_search_idx++
    }

    // search
    res[date_idx] = new Array()
    for (let i = srt_search_idx, anni = anni_ls[i]; i < anni_ls.length; anni = anni_ls[++i]) {
      const day_between_set = remind_period.get(anni.month)
      if (day_between_set === undefined || !day_between_set.has(anni.day)) {
        break
      }
  
      const day_between = day_between_set.get(anni.day)
      if (day_between == 0) {
        res[date_idx].push({star: 0, anni})
      }
      else if (day_between <= anni.priority) {
        res[date_idx].push({star: anni.priority - day_between + 1, anni})
      }
    }
  }

  return res
}

function main () {
  const reader = new Reader('input.txt')

  const year = reader.next_int()
  const anni_ls: Array<Anni> = []
  const date_ls: Array<Date> = []

  // read input
  while (true) {
    const event = reader.next_str()
    if (event === 'A') {
      const day = reader.next_int()
      const month = reader.next_int()
      const priority = reader.next_int()
      const name = reader.next_line()
      const seq = anni_ls.length
      const anni = new Anni(day, month, priority, name, seq)
      anni_ls.push(anni)

      if (anni.month == 1) {
        anni_ls.push(new Anni(day, month + 12, priority, name, seq))
      }
    }
    else if (event === 'D') {
      const day = reader.next_int()
      const month = reader.next_int()
      date_ls.push(new Date(day, month))
    }
    else {
      break
    }
  }
  const remind_ls = solve(date_ls, anni_ls, year)
  remind_ls.forEach((reminds, idx) => {
    if (idx > 0) {
      console.log()
    }

    const today = date_ls[idx]
    console.log(`Today is: ${today.day} ${today.month}`)
    for (const remind of reminds) {
      const star_str = remind.star == 0 ? '*TODAY*' : Array(remind.star).fill('*').join('').padEnd(7)
      const month = remind.anni.month == 13 ? 1 : remind.anni.month
      console.log(`${remind.anni.day.toString().padStart(3)}${month.toString().padStart(3)} ${star_str} ${remind.anni.name}`)
    }
  })
}
main()
