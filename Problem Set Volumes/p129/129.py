from math import floor
from typing import Union

def get_invalid (seq : list[int], left : int, right : int) -> Union[int, None]:
  while right < -1 and seq[left] == seq[right]:
    left += 1
    right += 1
  return seq[left] if right == -1 else None

def solve (n : int, l : int) -> list[int]:
  seq : list[int] = []
  mat : list[list[bool]] = [] # mark valid letters
  re_search : bool = False
  k : int = 0 # store the number of hard seq found

  while k < n:
    idx = len(seq) - 1
    
    if not re_search:
      mat.append([False] * l)
      seq.append(0)
      idx += 1
      
      invalid_set : set[int] = set()
      for j in range(floor(len(seq) / 2)):
        right = -1 * (j + 1)
        invalid : Union[int, None] = get_invalid(seq, 2 * right, right)
        if invalid is None:
          continue
        mat[idx][invalid] = True

        invalid_set.add(invalid)
        if len(invalid_set) == l:
          break

    while seq[idx] < l:
      if mat[idx][seq[idx]] == False:
        mat[idx][seq[idx]] = True
        break
      seq[idx] += 1

    if seq[idx] < l:
      k += 1
      re_search = False
    else:
      mat.pop()
      seq.pop()
      re_search = True
      
  return seq

if __name__ == '__main__':
  f = open('input.txt', 'r')

  while True:
    [n, l] = map(int, f.readline().split(' '))
    if n == 0 and l == 0:
      break
    
    seq : list[int] = solve(n, l)
    
    # print seq
    for idx, v in enumerate(seq):
      end = ''
      if idx == len(seq) - 1 or idx % 64 == 63:
        end = '\n'
      elif idx % 4 == 3:
        end = ' '
      print(chr(65 + v), end = end)
    print(len(seq))
        
  f.close()
  