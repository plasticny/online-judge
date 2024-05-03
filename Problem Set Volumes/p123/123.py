from __future__ import annotations
from functools import cmp_to_key
from io import TextIOWrapper

ignore_set : set[str] = set()
title_ls : list[list[str]] = []
kwic_ls : list[Kwic] = []

class Kwic:
  title_idx : int
  key_idx : int
  
  @property
  def keyword (self) -> str:
    return title_ls[self.title_idx][self.key_idx]
  
  def __init__(self, title_idx : int, key_idx : int) -> None:
    self.title_idx = title_idx
    self.key_idx = key_idx
  
  def show (self):
    title_word_ls = title_ls[self.title_idx]
    for idx, word in enumerate(title_word_ls):
      print(
        f'{word.upper() if idx == self.key_idx else word}',
        end = ' ' if idx < len(title_word_ls)-1 else ''
      )
    print()

def read_line (file : TextIOWrapper) -> str :
  return file.readline().strip().lower()

def kwic_ls_cmp (x : Kwic, y : Kwic) -> int:
  # return > 0 if x > y
  if x.keyword != y.keyword:
    return 1 if x.keyword > y.keyword else -1
  if x.title_idx != y.title_idx:
    return x.title_idx - y.title_idx
  return x.key_idx - y.key_idx

if __name__ == '__main__':
  with open('input.txt', 'r') as f:
    line = read_line(f)
    # read ignore
    while line != '::':
      ignore_set.add(line)
      line = read_line(f)
      
    # read title
    line = read_line(f)
    while line != '':
      title_idx = len(title_ls)
      word_ls = line.split(' ')
      
      title_ls.append(word_ls)
      
      for idx, word in enumerate(word_ls):
        if word in ignore_set:
          continue
        kwic_ls.append(Kwic(title_idx=title_idx, key_idx=idx))
      
      line = read_line(f)
  
  for item in kwic_ls.sort(key=cmp_to_key(kwic_ls_cmp)):
    item.show()
