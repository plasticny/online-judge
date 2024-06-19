UNIT_LS : list[int] = [1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000]

dp : list[list[int]] = [[1] * 11, []]

def get_dp_idx (idx : int):
  if idx % 2 == 0:
    return idx
  return idx - 1

def solve (n : float) -> int:
  idx = int(n * 20)
  
  if idx + 1 > len(dp):
    for row_idx in range(len(dp), idx + 1):
      dp.append([])
      if row_idx % 2 != 0:
        continue
      
      dp[row_idx].append(1)
      for unit_idx in range(1, 11):
        uj = row_idx - UNIT_LS[unit_idx]
        dp[row_idx].append(dp[row_idx][unit_idx - 1] + (0 if uj < 0 else dp[get_dp_idx(uj)][unit_idx]))
  
  return dp[get_dp_idx(idx)][-1]

if __name__ == '__main__':
  with open('input.txt', 'r') as file:
    while True:
      n = float(file.readline())
      if n == 0.00:
        break
      print('{:>6.2f}{:>17}'.format(n, solve(n)))
