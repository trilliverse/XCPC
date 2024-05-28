# 线性筛
## (筛选小于等于n的质数，prime存质数，minprime存最小质因子，isprime[i]=1表示i为质数)
static
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
非static，需要实例化
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