inline ll read() {  
    ll x = 0, f = 1;  
    char ch = getchar();  
    while (ch < '0' || ch > '9') {  
        if (ch == '-')  
            f = -1;  
        ch = getchar();  
    }  
    while (ch >= '0' && ch <= '9') {  
        x = x * 10 + ch - '0';  
        ch = getchar();  
    }  
    return x * f;  
}  
inline void print(ll x) {  
    if (x < 0) {  
        putchar('-');  
        x = -x;  
    }  
    if (x > 9)  
        print(x / 10);  
    putchar(x % 10 + '0');  
}  
  
ll mul(ll a, ll b, ll mod) {  
    a %= mod;  
    b %= mod;  
    ll c = (long double)a * b / mod;  
    ll ans = a * b - c * mod;  
    return (ans % mod + mod) % mod;  
}  
ll pow_mod(ll x, ll n, ll mod) {  
    ll res = 1;  
    while (n) {  
        if (n & 1)  
            res = mul(res, x, mod);  
        x = mul(x, x, mod);  
        n >>= 1;  
    }  
    return (res + mod) % mod;  
}  
bool Miller_Rabbin(ll a, ll n) {  
    // n-1 to (2^r)*d  
    ll s = n - 1, r = 0;  
    while ((s & 1) == 0) {  
        s >>= 1;  
        r++;  
    }  
  
    ll k = pow_mod(a, s, n);   
    // 二次探测
    if (k == 1) return true;  
    for (int i = 0; i < r; i++, k = k * k % n) {  
        if (k == n - 1) return true;  
    }  
    return false;  
}  
bool isprime(ll n) {  
    // 这里可以随机取值进行探测 探测次数可以自己定
    ll times = 7;  
    ll prime[100] = {2, 3, 5, 7, 11, 233, 331};  
    for (int i = 0; i < times; i++) {  
        if (n == prime[i]) return true;  
        if (Miller_Rabbin(prime[i], n) == false) return false;  
    }  
    return true;  
}  