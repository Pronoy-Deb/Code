// Complexity: O()

inline long double sn(long double d) {
    return sin(d * M_PI / 180);
}

inline long double csc(long double d) {
    return (1 / sin(d * M_PI / 180));
}

inline long double cs(long double d) {
    return cos(d * M_PI / 180);
}

inline long double sc(long double d) {
    return (1 / cos(d * M_PI / 180));
}

inline long double tn(long double d) {
    return tan(d * M_PI / 180);
}

inline long double ct(long double d) {
    return (1 / tan(d * M_PI / 180));
}

inline long double sni(long double v) {
    return asin(v) * 180 / M_PI;
}

inline long double csci(long double v) {
    return asin(1 / v) * 180 / M_PI;
}

inline long double csi(long double v) {
    return acos(v) * 180 / M_PI;
}

inline long double sci(long double v) {
    return acos(1 / v) * 180 / M_PI;
}

inline long double tni(long double v) {
    return atan(v) * 180 / M_PI;
}

inline long double cti(long double v) {
    return atan(1 / v) * 180 / M_PI;
}