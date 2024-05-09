FACE_IDX : dict[chr, int] = {
  '2': 0, '3': 1, '4': 2,
  '5': 3, '6': 4, '7': 5,
  '8': 6, '9': 7, 'T': 8,
  'J': 9, 'Q': 10, 'K': 11,
  'A': 12
}
SUIT_IDX : dict[chr, int] = {
  'C': 0, 'D': 1, 'H': 2, 'S': 3
}
VALUES : list[str] = [
  'highest-card', 'one-pair', 'two-pairs',
  'three-of-a-kind', 'straight', 'flush',
  'full-house', 'four-of-a-kind', 'straight-flush'
]

def check_straight (face_cnt : list[int], min_face_idx : int) -> bool:
  # handle 'A'
  if min_face_idx != -1 and face_cnt[12] != 0 and check_straight(face_cnt, -1):
    return True
  
  end_idx = min_face_idx + 5
  if end_idx > 13:
    return False

  for idx in range(min_face_idx + 1, end_idx):
    if face_cnt[idx] == 0:
      return False
  return True

# [has 4 of kind, has 3 of kind, number of pair]
def process_face_cnt (face_cnt : list[int], min_face_idx : int, max_face_idx : int) -> tuple[bool, bool, int]:
  has_3kind = False
  pair_cnt = 0
  for idx in range(min_face_idx, max_face_idx + 1):
    cnt = face_cnt[idx]
    if cnt == 4:
      return [True, False, 0] # last 2 not matter
    elif cnt == 3:
      has_3kind = True
    elif cnt == 2:
      pair_cnt += 1
  return [False, has_3kind, pair_cnt]

def cal_value (hand_ls : list[int], card_ls : list[str]) -> int:
  face_cnt = [0] * 13
  min_face_idx = 13
  max_face_idx = 0

  prev_suit = None
  is_flush = True
  
  # process hand
  for hand in hand_ls:
    face = card_ls[hand][0]
    suit = card_ls[hand][1]
    
    if prev_suit is not None:
      is_flush = is_flush and prev_suit == suit
    prev_suit = suit
      
    face_idx = FACE_IDX[face]
    face_cnt[face_idx] += 1
    
    if max_face_idx < face_idx:
      max_face_idx = face_idx
    if min_face_idx > face_idx:
      min_face_idx = face_idx

  is_straight = check_straight(face_cnt, min_face_idx)
  [has_4kind, has_3kind, pair_cnt] = process_face_cnt(face_cnt, min_face_idx, max_face_idx)
  
  # return value
  if is_straight and is_flush:
    return 8
  if has_4kind:
    return 7
  if has_3kind and pair_cnt > 0:
    return 6
  if is_flush:
    return 5
  if is_straight:
    return 4
  if has_3kind:
    return 3
  if pair_cnt != 0:
    return pair_cnt
  return 0

def dfs (hand_ls : list[int], hand_idx : int, deck_idx : int, card_ls : list[str]) -> int:
  max_value = cal_value(hand_ls, card_ls)
  
  if hand_idx == 5 or max_value == 8:
    return max_value
  
  next_deck_idx = deck_idx + 1
  for idx in range(hand_idx, 5):
    next_hand_ls = hand_ls.copy()
    next_hand_ls[idx] = deck_idx
    max_value = max(max_value, dfs(next_hand_ls, idx + 1, next_deck_idx, card_ls))
  return max_value

def solve (card_ls : list[str]):
  hand_ls : list[int] = [0, 1, 2, 3, 4]
  
  value = dfs(hand_ls, 0, 5, card_ls)
  
  for i in range(0, 10):
    if i == 0:
      print('Hand:', end=' ')
    elif i == 5:
      print('Deck:', end=' ')
    print(card_ls[i], end=' ')
  print('Best hand:', VALUES[value])

if __name__ == "__main__":
  with open('input.txt', 'r') as f:
    for line in f:
      if line[-1] == '\n':
        line = line[:-1]
      solve(line.split(' '))
