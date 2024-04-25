maximum_cycle_length_dict = {1:1}

def algorithm (n : int) -> int :
  seq = []

  while n not in maximum_cycle_length_dict:
    seq.append(n)
    if n % 2 == 0:
      n = n // 2
    else:
      n = 3 * n + 1
  
  length = maximum_cycle_length_dict[n]

  while len(seq) > 0:
    length += 1
    maximum_cycle_length_dict[seq.pop()] = length

  return length

if __name__ == "__main__":
  while True:
    raw_in = input()
    if raw_in == '':
      break
    
    in1, in2 = map(int, raw_in.split())
    
    max_len = 1

    for i in range(max(in1, in2), min(in1, in2)-1, -1):
      if max_len == 525:
        break
      
      if i in maximum_cycle_length_dict:
        max_len = max(maximum_cycle_length_dict[i], max_len)
      else:
        max_len = max(algorithm(i), max_len)

    print(in1, in2, max_len)
