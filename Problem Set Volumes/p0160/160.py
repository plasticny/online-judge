PRIME_LS = [
     2,  3,  5,  7, 11,
    13, 17, 19, 23, 29,
    31, 37, 41, 43, 47,
    53, 59, 61, 67, 71,
    73, 79, 83, 89, 97
]

def solve (n, dp, last_idx):
    if dp[n] is not None:
        return dp[n]
    
    prev = solve(n - 1, dp, last_idx)

    num = n
    dp[n] = []
    for idx, prime in enumerate(PRIME_LS):
        cnt = 0
        while num != 1 and num % prime == 0:
            cnt += 1
            num = int(num / prime)
        cnt += prev[idx]

        dp[n].append(cnt)
        if cnt != 0:
            last_idx[n] = idx

    return dp[n]

if __name__ == "__main__":
    n_ls = []

    with open('input.txt', 'r') as file:
        for line in file.readlines():
            n = int(line)
            if n == 0:
                break
            n_ls.append(n)

    dp = [None] * 101
    dp[2] = [0] * 25
    dp[2][0] = 1

    last_idx = [None] * 101

    for n in n_ls:
        cnt_ls = solve(n, dp, last_idx)
        print(f"{str(n).rjust(3, ' ')}! =", end='')

        cnt = 0
        for i in range(0, last_idx[n] + 1):
            print(f"{str(dp[n][i]).rjust(3, ' ')}", end='')
            cnt += 1
            if cnt == 15:
                print('\n      ', end='')
                cnt = 0
        print()

