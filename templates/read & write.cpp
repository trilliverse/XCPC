// 不能关闭流同步 因为getchar
template <typename T>
inline void read(T &x) {
    x = 0; T f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    x *= f;
}

// 递归实现常数较大，用栈实现
template <typename T>
inline void write(T x, bool mode = 1) {
    static int st[50];
    int top = 0;
    x < 0 ? x = -x, putchar('-') : 0;
    do st[++top] = x % 10, x /= 10; while (x);
    while (top) putchar(st[top--] | 48);
    mode ? putchar('\n') : putchar(' ');
}