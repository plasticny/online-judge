FACE_LS = ['J', 'Q', 'K', 'A']

def is_face (suit: chr) -> int:
    for idx, face in enumerate(FACE_LS):
        if suit == face:
            return idx
    return -1

def solve (p1_hand: list, p2_hand: list):
    to_play = 1
    is_covering = False
    table = []

    while len(p1_hand) != 0 and len(p2_hand) != 0:
        # pull card
        table.append(p1_hand.pop() if to_play > 0 else p2_hand.pop())
        print(to_play, table[-1])
       
        # if pull face card
        face_idx = is_face(table[-1][1])
        if face_idx != -1:
            is_covering = True
            to_play = (face_idx + 1) * (-1 if to_play > 0 else 1)
            continue

        # not change player
        if to_play != 1 and to_play != -1:
            to_play += (-1 if to_play > 0 else 1)
            continue
        
        if is_covering:
            if to_play == 1:
                p2_hand = table[::-1] + p2_hand
            else:
                p1_hand = table[::-1] + p1_hand
            table = []
            is_covering = False
        to_play *= -1
    # game loop end
    
    # game result 
    if len(p1_hand) == 0:
        print(f'1{str(len(p2_hand)).rjust(3, " ")}')
    else:
        print(f'2{str(len(p1_hand)).rjust(3, " ")}')

def main (file):
    card_ls = []
    for line in file.readlines():
        if line[0] == '#':
            break
        line = line[:-1]
        
        for card in line.split(' '):
            card_ls.append(card)

    for desk_srt in range(0, len(card_ls), 52):
        desk = card_ls[desk_srt:desk_srt + 52]
        p1_hand = []
        p2_hand = []
        for i in range(0, 52, 2):
            p1_hand.append(desk[i])
            p2_hand.append(desk[i + 1])
        solve(p1_hand, p2_hand)

if __name__ == "__main__":
    with open('input.txt', 'r') as file:
        main(file)

