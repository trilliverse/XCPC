# 线性筛
```cpp
// 线性筛（欧拉筛）筛序 <=maxn 的质数
// isprime[i]=1 表示质数
// prime[i]: 第i个质数
// minprime[i]: i的最小质因子
```
- static
```cpp
struct EulerSieve{
    static vector<int> prime,minprime;
    static vector<bool> isprime;
    static void eulersieve(int n){
        minprime=vector<int>(n+1);
        isprime=vector<bool>(n+1,1);
        isprime[1]=0;
        minprime[1]=1;
        for(int i=2;i<=n;i++){
            if(isprime[i]){
                prime.push_back(i);
                minprime[i]=i;
            }
            for(int p:prime){
                if(i*p>n) break;
                isprime[i*p]=0;
                minprime[i*p]=p;
                if(i%p==0) break;
            }
        }
    }
};
```
- 非static，需要实例化
```cpp
struct EulerSieve{
    vector<int> prime,minprime;
    vector<bool> isprime;
    EulerSieve(int n){
        minprime=vector<int>(n+1);
        isprime=vector<bool>(n+1,1);
        isprime[1]=0;
        minprime[1]=1;
        for(int i=2;i<=n;i++){
            if(isprime[i]){
                prime.push_back(i);
                minprime[i]=i;
            }
            for(int p:prime){
                if(i*p>n) break;
                isprime[i*p]=0;
                minprime[i*p]=p;
                if(i%p==0) break;
            }
        }
    }
};
```
- 鼠鼠代码
```cpp
int prime[maxn], v[maxn]; 
void EulerSieve() {
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
```