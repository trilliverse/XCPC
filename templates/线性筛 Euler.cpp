int prime[maxn], v[maxn];  
// prime[i]: 第i个质数
// v[i]: i的最小质因子
void init_prime() {
    int cnt = 0;
    for (int i = 2; i <= maxn; i++) {
        if (v[i] == 0) {
            prime[++cnt] = i;
            v[i] = i;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= maxn; j++) {
            v[i * prime[j]] = prime[j];
            if (prime[j] == v[i]) break;
        }
    }
}