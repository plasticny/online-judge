from __future__ import annotations
from typing import Literal
from functools import cmp_to_key

class Term:
  def __init__(self, coeff : int = 0, x_exp : int = 0, y_exp : int = 0) -> None:
    self.coeff : int = coeff
    self.x_exp : int = x_exp
    self.y_exp : int = y_exp
  
  def times (self, other : Term) -> Term:
    return Term(
      coeff = self.coeff * other.coeff,
      x_exp = self.x_exp + other.x_exp,
      y_exp = self.y_exp + other.y_exp
    )
    
def is_sign (c : chr) -> bool:
  return c == '+' or c == '-'

def is_var (c : chr) -> bool:
  return c == 'x' or c == 'y'

def read_terms (line : str) -> list[Term]:
  term_ls : list[Term] = [Term()]
  
  r : Literal['+','-','x','y','e'] = '+' if line[0] != '-' else '-'
  start = 1 if is_sign(line[0]) else 0
  buffer = 0
  
  line += 'e'
  for c in line[start:]:
    if is_sign(c) or is_var(c) or c == 'e':
      buffer = max(buffer, 1)
      if is_sign(r):
        term_ls[-1].coeff = buffer
        term_ls[-1].coeff *= -1 if r == '-' else 1
      elif r == 'x':
        term_ls[-1].x_exp = buffer
      else:
        term_ls[-1].y_exp = buffer

      if is_sign(c):
        term_ls.append(Term())

      buffer = 0
      r = c
    else:
      buffer = buffer * 10 + int(c)
  
  return term_ls

def cmp_term (a : Term, b : Term) -> int:
  if a.x_exp != b.x_exp:
    return b.x_exp - a.x_exp
  if a.y_exp != b.y_exp:
    return a.y_exp - b.y_exp
  return a.coeff - b.coeff

def print_ploy (p : list[Term]):
  upper = ''
  lower = ''
  
  p.append(None)
  
  prev = p[0]
  for term in p[1:]:
    if term is not None and prev.x_exp == term.x_exp and prev.y_exp == term.y_exp:
      prev.coeff += term.coeff
    elif prev.coeff == 0:
      prev = term
    else:
      # sign
      if len(upper) == 0:
        if prev.coeff < 0:
          upper += ' '
          lower += '-'
      else:
        upper += '   '
        lower += ' + ' if prev.coeff > 0 else ' - '

      # coeff
      coeff = abs(prev.coeff)
      if coeff == 1 and prev.x_exp == 0 and prev.y_exp == 0:
        upper += ' '
        lower += '1'
      elif coeff != 1:
        upper += ' ' * len(str(coeff))
        lower += str(coeff)

      # x
      for (v, c) in [(prev.x_exp, 'x'),(prev.y_exp, 'y')]:
        if v != 0:
          upper += ' '
          lower += c
        if v > 1:
          upper += str(v)
          lower += ' ' * len(str(v))
      
      prev = term

  print(upper)
  print(lower)

if __name__ == '__main__':
  case_ls : list[tuple[str, str]] = []
  
  with open('input.txt', 'r') as f:
    while True:
      line1 = f.readline().strip()
      if line1[0] == '#':
        break
      line2 = f.readline().strip()
      case_ls.append((line1, line2))
      
  for (l1, l2) in case_ls:
    p1 = read_terms(l1)
    p2 = read_terms(l2)
    
    p3 : list[Term] = []
    for t1 in p1:
      for t2 in p2:
        p3.append(t1.times(t2))
    p3.sort(key=cmp_to_key(cmp_term))
    
    print_ploy(p3)
