#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 5;

int n, m;
int tr[maxn];

int lowbit(int x) { return x & -x; }

void Update(int x, int val) {
    while (x <= n) {
        tr[x] += val;       // one pos changed
        x = x + lowbit(x);  // x = fa[x]
    }
}

int Query(int x) {  // a[1]+...+a[x]
    int res = 0;
    while (x > 0) {
        res += tr[x];
        x = x - lowbit(x);  // [ ,x-lowbit(x)] ¡û[x-lowbit(x)+1, x]
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        Update(i, a);
    }

    while (m--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            int k;
            cin >> k;
            Update(x, k);
        } else {
            int y;
            cin >> y;
            cout << Query(y) - Query(x - 1) << "\n";
        }
    }
    return 0;
}
