import reader from "./reader"

reader.load('input.txt')

while (!reader.eof()) {
  const person_cnt = reader.next_int()
  const name_ls = new Array<string>()
  const name_net_map = new Map<string, number>()

  for (let i = 0; i < person_cnt; i++) {
    const name = reader.next_str()
    name_ls.push(name)
    name_net_map.set(name, 0)
  }

  for (let i = 0; i < person_cnt; i++) {
    const cur_preson = reader.next_str()
    const budget = reader.next_int()
    const give_cnt = reader.next_int()

    const pre_person = give_cnt == 0 ? 0 : Math.floor(budget / give_cnt)

    name_net_map.set(cur_preson, name_net_map.get(cur_preson) - pre_person * give_cnt)
    for (let j = 0; j < give_cnt; j++) {
      const got_person = reader.next_str()
      name_net_map.set(got_person, name_net_map.get(got_person) + pre_person)
    }
  }

  for (const name of name_ls) {
    console.log(`${name} ${name_net_map.get(name)}`)
  }

  if (!reader.eof()) {
    console.log()
  }
}
