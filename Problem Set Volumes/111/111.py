if __name__ == '__main__':
  n = int(input())
  
  ranking_ls = [0]*(n+1)
  for rank, num in enumerate(map(int, input().split())):
    ranking_ls[num] = rank

  while True:
    # (number, length)
    record_ls : list[tuple[int, int]] = []
    max_len = 0
          
    for num in map(int, input().split()):
      cur_rank = ranking_ls[num]
    
      max_sub_len = 1
      for prev_num, length in record_ls:
        if cur_rank > ranking_ls[prev_num]:
          max_sub_len = max(max_sub_len, length+1)
      
      record_ls.append((num, max_sub_len))
        
    for _, length in record_ls:
      max_len = max(max_len, length)
    print(max_len)
