// Minimum number of knight moves from (x,y) to (0,0) in non-negative infinite chessboard

int64_t knight(int64_t x, int64_t y) {
    int64_t cnt = max({(x + 1) >> 1, (y + 1) >> 1, (x + y + 2) / 3});
    while ((cnt % 2) != (x + y) % 2) ++cnt;
    if (x == 1 && !y) return 3;
    if (y == 1 && !x) return 3;
    if (x == y && x == 2) return 4;
    return cnt;
}