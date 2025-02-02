def main():
    n, m, v = map(int, input().split())
    s = [list(map(int, list(input()))) for _ in range(n)]
    t = [list(map(int, list(input()))) for _ in range(n)]
    print(1)
    takoyaki_pos = []
    takoyaki_target = []
    for i in range(n):
        for j in range(n):
            if s[i][j] == 1:
                takoyaki_pos.append((i, j))
            if t[i][j] == 1:
                takoyaki_target.append((i, j))
    remove = [[], []]
    for i in range(len(takoyaki_pos)):
        for j in range(len(takoyaki_target)):
            if takoyaki_pos[i] == takoyaki_target[j]:
                remove[0].append(i)
                remove[1].append(j)
    remove[0].sort(reverse=True)
    remove[1].sort(reverse=True)
    for i in remove[0]:
        takoyaki_pos.pop(i)
    for i in remove[1]:
        takoyaki_target.pop(i)
    print(takoyaki_pos[0][0] + 1, takoyaki_pos[0][1])
    now = (takoyaki_pos[0][0] + 1, takoyaki_pos[0][1])
    ans = []

    while takoyaki_target:
        # たこ焼きを取る
        min_dist = 1e9
        min_idx = -1
        for i in range(len(takoyaki_pos)):
            dist = abs(takoyaki_pos[i][0] - now[0]) + abs(takoyaki_pos[i][1] - now[1])
            if dist < min_dist:
                min_dist = dist
                min_idx = i
        for i in range(abs(takoyaki_pos[min_idx][0] - now[0])):
            if takoyaki_pos[min_idx][0] > now[0]:
                ans.append("D.")
            else:
                ans.append("U.")
        for i in range(abs(takoyaki_pos[min_idx][1] - now[1])):
            if takoyaki_pos[min_idx][1] > now[1]:
                ans.append("R.")
            else:
                ans.append("L.")
        ans[-1] = ans[-1][0] + "P"
        now = takoyaki_pos[min_idx]
        takoyaki_pos.pop(min_idx)

        # たこ焼きを置く
        min_dist = 1e9
        min_idx = -1
        for i in range(len(takoyaki_target)):
            dist = abs(takoyaki_target[i][0] - now[0]) + abs(takoyaki_target[i][1] - now[1])
            if dist < min_dist:
                min_dist = dist
                min_idx = i
        for i in range(abs(takoyaki_target[min_idx][0] - now[0])):
            if takoyaki_target[min_idx][0] > now[0]:
                ans.append("D.")
            else:
                ans.append("U.")
        for i in range(abs(takoyaki_target[min_idx][1] - now[1])):
            if takoyaki_target[min_idx][1] > now[1]:
                ans.append("R.")
            else:
                ans.append("L.")
        ans[-1] = ans[-1][0] + "P"
        now = takoyaki_target[min_idx]
        takoyaki_target.pop(min_idx)
    for a in ans:
        print(a)

if __name__ == '__main__':
    main()