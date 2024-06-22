from io import TextIOWrapper

class WordDictItem:
  def __init__ (self, word : str):
    self.word = word
    self.letter_cnt = cnt_letter(word)
WordDict = list[WordDictItem]

def read_line (file : TextIOWrapper) -> str:
  line = file.readline()
  if line[-1] == '\n':
    return line[:-1]
  return line    

def cnt_letter (word : str) -> list[int]:
  res = [0] * 26
  for c in word:
    if c == ' ':
      continue
    res[ord(c) - ord('A')] += 1
  return res

def add_cnt_letter (word : str, letter_cnt : list[int]):
  for c in word:
    letter_cnt[ord(c) - ord('A')] += 1

def do_fit (dict_word : WordDictItem, sen_word_set : set[str], letter_cnt : list[int]) -> bool:
  if dict_word.word in sen_word_set:
    return False
  
  tmp = [0] * 26
  for c in dict_word.word:
    idx = ord(c) - ord('A')
    
    if letter_cnt[idx] == 0:
      # reverse
      for i, t in enumerate(tmp):
        letter_cnt[i] += t 
      return False
    
    tmp[idx] += 1
    letter_cnt[idx] -= 1
  return True

def find_anagram (
  anagram_ls : list[list[str]],
  cur_word_ls : list[str], word_dict : WordDict, sen_word_set : set[str],
  letter_cnt : list[int], dict_idx : int
):
  if all(map(lambda x : x == 0, letter_cnt)):
    anagram_ls.append(cur_word_ls.copy())
    return
  
  # check cur dict word fit
  dict_word = word_dict[dict_idx]
  fit = do_fit(dict_word, sen_word_set, letter_cnt)
  if fit:
    cur_word_ls.append(dict_word.word)
  elif len(cur_word_ls) == 0:
    return
  
  for i in range(dict_idx + 1, len(word_dict)):
    find_anagram(
      anagram_ls,
      cur_word_ls, word_dict, sen_word_set,
      letter_cnt, i
    )
  
  if fit:
    cur_word_ls.pop()
    add_cnt_letter(dict_word.word, letter_cnt)

def solve (line : str, word_dict : WordDict) -> None:
  letter_cnt : list[int] = cnt_letter(line)
  
  word_ls : list[str] = line.split(' ')
  word_set : set[str] = set(word_ls)

  anagram_ls : list[list[str]] = []
  for idx in range(0, len(word_dict)):
    find_anagram(
      anagram_ls,
      [], word_dict, word_set,
      letter_cnt, idx
    )
  
  appear_set = set()
  for anagram_word_ls in anagram_ls:
    s = " ".join(anagram_word_ls)
    if s in appear_set:
      continue
    appear_set.add(s)
    print(f'{line} = {s}')

if __name__ == "__main__":
  with open('input.txt', 'r') as file:
    word_dict : WordDict = []

    # read dictonary
    line = read_line(file)
    while line != '#':
      word_dict.append(WordDictItem(line))
      line = read_line(file)

    # find anagram
    line = read_line(file)
    while line != '#':
      solve(line, word_dict)
      line = read_line(file)
