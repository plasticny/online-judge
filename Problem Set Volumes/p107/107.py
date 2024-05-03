from math import log10

if __name__ == '__main__':
  while True:
    h, total = map(int, input().split())
    if h == 0 and total == 0:
      break

    i = 1
    n = -1
    while True:
      x = log10(total)/i
      n = round(10 ** x)
      
      if (n+1) ** i == h:
        break
      
      i += 1

    # output
    total_not_working = 0
    total_height = 0
    cur_height = h
    for j in range(i+1):
      cat_count = n ** j
      
      if j < i:
        total_not_working += cat_count
      
      total_height += cur_height * cat_count
      cur_height /= n+1

    print(total_not_working, int(total_height))
