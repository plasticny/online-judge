from heapq import heappush, heappop

class Signal:
    def __init__ (self, d):
        self.g = d - 5
        self.yr = d + 5
        self.is_green = True

def solve (time_ls) -> int:
    """
    There may be a faster method
    """
    green_cnt = len(time_ls)

    q = []
    for d in time_ls:
        signal = Signal(d)
        heappush(q, (signal.g, signal.g, signal))

    while True:
        time_passed, _, signal = heappop(q)
        signal.is_green = not signal.is_green

        next_time = time_passed
        if signal.is_green:
            green_cnt += 1
            if green_cnt == len(time_ls):
                return time_passed
            next_time += signal.g
        else:
            green_cnt -= 1
            next_time += signal.yr

        if next_time <= 18000:
            heappush(q, (next_time, signal.g, signal))
        elif not signal.is_green:
            return -1

def show_time (s):
    str_just = lambda x: str(x).rjust(2, '0')
    h = str_just(int(s / 3600))
    s %= 3600
    m = str_just(int(s / 60))
    s %= 60
    s = str_just(s)
    print(f"{h}:{m}:{s}")

def read_nums (line):
    res = []
    for token in line.split(' '):
        if token != '':
            res.append(int(token))
    return res

def main (file):
    time_ls = []

    for line in file.readlines():
        if line[-1] == '\n':
            line = line[:-1]
        num_ls = read_nums(line) 

        if not any(num_ls):
            return

        for num in num_ls:
            if num == 0:
                s = solve(time_ls)
                if s != -1:
                    show_time(s)
                else:
                    print("Signals fail to synchronise in 5 hours")
                time_ls = []
            else:
                time_ls.append(num)

if __name__ == "__main__":
    with open('input.txt', 'r') as file:
        main(file)

