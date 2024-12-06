/// Ternary Search:
void TS(auto &v) {
    int st = 0, ed = n - 1, mid1, mid2;
    while ((ed - st) > 3) {
        mid1 = st + (ed - st) / 3;
        mid2 = ed - (ed - st) / 3;
        if (v[mid1] < v[mid2]) st = mid1;
        else ed = mid2;
    }
    for (int i = mid1; i <= mid2; i++) cout << v[i] << ' ';
}
