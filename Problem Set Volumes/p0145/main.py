CHARGE_TABLE : dict[chr, tuple[float, float, float]] = {
  'A': [0.1, 0.06, 0.02],
  'B': [0.25, 0.15, 0.05],
  'C': [0.53, 0.33, 0.13],
  'D': [0.87, 0.47, 0.17],
  'E': [1.44, 0.8, 0.3]
}
TIMEZONE = [
  [0, 8], [8, 18], [18, 22], [22, 24]
]

class Call:
  def __init__(self, line : str) -> None:
    items : list[str] = line[:-1].split(' ')
    self.distance : chr = items[0][0]
    self.number : str = items[1]
    self.srt_h : int = int(items[2])
    self.srt_m : int = int(items[3])
    self.end_h : int = int(items[4])
    self.end_m : int = int(items[5])
  
  def get_srt_range (self) -> int:
    for idx, h in enumerate(TIMEZONE[:-1]):
      if self.srt_h < h[1]:
        return idx
    return 3
  
  def get_end_range (self) -> int:
    t : int = self.end_h * 100 + self.end_m
    if t == 0:
      return 3
    if t <= 800:
      return 0
    if t <= 1800:
      return 1
    if t <= 2200:
      return 2
    return 3
  
  def do_day_change (self) -> bool:
    if self.srt_h != self.end_h:
      return self.srt_h > self.end_h
    return self.srt_m > self.end_m
  
  def cal_min_diff (self, h1 : int, m1 : int, h2 : int, m2 : int) -> int:
    return (h2 - h1) * 60 + (m2 - m1)
  
  def get_min (self) -> tuple[int, int, int, int]:
    res = [0, 0, 0, 0]
    
    if self.srt_h == self.end_h and self.srt_m == self.end_m:
      return res
    
    srt_range : int = self.get_srt_range()
    end_range : int = self.get_end_range()
    day_change : bool = self.do_day_change()
    
    if not day_change and srt_range == end_range:
      res[srt_range] += self.cal_min_diff(self.srt_h, self.srt_m, self.end_h, self.end_m)
      return res
    
    timezones = range(srt_range + 1, end_range) if not day_change else [*range(srt_range + 1, 4), *range(0, end_range)]
    
    res[srt_range] += self.cal_min_diff(self.srt_h, self.srt_m, TIMEZONE[srt_range][1], 0)
    for r in timezones:
      res[r] += (TIMEZONE[r][1] - TIMEZONE[r][0]) * 60
    res[end_range] += self.cal_min_diff(TIMEZONE[end_range][0], 0, self.end_h, self.end_m)
    
    return res

def solve (call : Call):
  [morn_min, day_min, even_min, night_min] = call.get_min()
  charge_ls : tuple[float, float, float] = CHARGE_TABLE[call.distance]
  total : float = day_min * charge_ls[0] + even_min * charge_ls[1] + (morn_min + night_min) * charge_ls[2]
  print(
    "{:>10}{:>6}{:>6}{:>6}{:>3}{:>8}".format(
      call.number, day_min, even_min, morn_min + night_min, call.distance, round(total, 2)
    )
  )

if __name__ == '__main__':
  with open('input.txt', 'r') as file:
    while True:
      line : str = file.readline()
      if line[0] == '#':
        break
      solve(Call(line))
