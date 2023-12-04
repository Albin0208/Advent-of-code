grid = open("input.txt", "r").read().splitlines()

cs = set()

for r, row in enumerate(grid):
    for c, ch in enumerate(row):
        if ch.isdigit() or ch == ".":
            continue
        for cr in [r - 1, r, r +1]:
            for cc in [c - 1, c, c +1]:
                if cr < 0 or cr >= len(grid) or cc < 0 or cc >= len(row) or not grid[cr][cc].isdigit():
                    continue
                while cc > 0 and grid[cr][cc - 1].isdigit():
                    cc -= 1
                cs.add((cr, cc))

ns = []

a = []

for r, c in cs:
    a.append((r, c))

# Sort the list of tuples by the first element in the tuple
a.sort(key=lambda tup: tup[0])

for r, c in a:
    print(r, c)

for r, c in cs:
    s = ""
    while c < len(grid[r]) and grid[r][c].isdigit():
        s += grid[r][c]
        c += 1
    ns.append(int(s))

print(sum(ns))
print(len(cs))