import re
import sys

with open(sys.argv[1], "r") as f:
    lines = f.readlines()

lines = [line.strip() for line in lines]


W, H = len(lines[0]), len(lines)
map_of_chars = "".join(lines)


def get_char(col, row):
    i = row * W + col
    return map_of_chars[i]


def get_adjacent_positions(c, r):
    pp = []
    for p in (
        (c - 1, r - 1),
        (c, r - 1),
        (c + 1, r - 1),
        (c - 1, r),
        (c + 1, r),
        (c - 1, r + 1),
        (c, r + 1),
        (c + 1, r + 1),
    ):
        if 0 <= p[0] < W and 0 <= p[1] < H:
            pp.append(p)
    return pp


all_numbers_and_their_pos = []
for row, line in enumerate(lines):
    for m in re.finditer("\d+", line):
        nb = int(m.group())
        all_numbers_and_their_pos.append((nb, m.start(), m.end(), row))


def get_number_and_start_pos_at(col, row):
    nb = None
    start_pos = None
    for x, start, end, r in all_numbers_and_their_pos:
        if r == row and start <= col < end:
            nb = x
            start_pos = start, row
            break
    return nb, start_pos


def find_adjacent_numbers_and_their_pos(col, row):
    adj_numbers = set()
    for adj_pos in get_adjacent_positions(col, row):
        nb, nb_start_pos = get_number_and_start_pos_at(*adj_pos)
        if nb:
            adj_numbers.add((nb, nb_start_pos))
    return adj_numbers


ratios = []
for row, line in enumerate(lines):
    for col, ch in enumerate(line):
        if ch == "*":
            nbs_set = find_adjacent_numbers_and_their_pos(col, row)
            if len(nbs_set) == 2:
                pp = 1
                for x in nbs_set:
                    pp *= x[0]
                ratios.append(pp)


print(sum(ratios))
