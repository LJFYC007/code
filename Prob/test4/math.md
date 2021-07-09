枚举 $gcd(i,j)$ : $\sum_{t=1}^n\sum_{i=1}^{\lfloor\frac{n}{i}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{i}\rfloor}[gcd(i,j)=1]i\times j\times t^2\times \phi(t)$

令 $f(n)=\sum_{i=1}^n\sum_{j=1}^n[gcd(i,j)=1]i\times j$　可以化简为 $\sum_{i=1}^n\sum_{j=1}^n\sum_{d|i,d|j}\mu(d)\times i\times j$

调整 $d$ 的枚举顺序得到 $\sum_{d=1}^n\mu(d)\times d^2\times g(\lfloor\frac{n}{d}\rfloor)$，其中 $g(n)=\frac{(n\times(n+1))^2}{4}$

所以原式可以化为 $\sum_{t=1}^nt^2\phi(t)f(\lfloor\frac{n}{t}\rfloor)$

其中可以线性筛预处理出 $i^2\phi(i)$ 和 $i^2\mu(i)$ 的前缀和

因为求解 $f(n)$ 和求解整个答案各需要一个整除分块，所以总复杂度为 $O(n)$

```c++
/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2019年10月08日 星期二 16时13分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 30000010;
const int Mod = 998244353;

int prime[maxn], tot, phi[maxn], miu[maxn], n;
bool vis[maxn];

inline int Solve(int x)
{
    int i = 1; LL ans = 0;
    while ( i <= x )
    {
        int j = x / (x / i); LL sum = (miu[j] - miu[i - 1] + Mod) % Mod;
        LL tmp = ((x / i) * (x / i + 1) / 2) % Mod; 
        tmp = (tmp * tmp) % Mod;
        ans = (ans + tmp * sum) % Mod;
        i = j + 1;
    }
    return ans;
}

signed main()
{
    scanf("%d", &n);
    phi[1] = miu[1] = 1;
    REP(i, 2, n)
    {
        if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; miu[i] = -1; }
        for ( int j = 1; j <= tot && (LL)i * prime[j] <= (LL)n; ++ j ) 
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) { miu[i * prime[j]] = 0; phi[i * prime[j]] = (phi[i] * prime[j]) % Mod; break ; }
            miu[i * prime[j]] = -miu[i];
            phi[i * prime[j]] = (phi[i] * phi[prime[j]]) % Mod;
        }
    }
    REP(i, 1, n) phi[i] = (phi[i - 1] + phi[i] * (i * i % Mod)) % Mod;
    REP(i, 1, n) miu[i] = (miu[i - 1] + miu[i] * (i * i % Mod)) % Mod;
    int i = 1; LL ans = 0;
    while ( i <= n ) 
    {
        int j = n / (n / i); LL sum = (phi[j] - phi[i - 1] + Mod) % Mod;
        ans = (ans + sum * Solve(n / i)) % Mod;
        i = j + 1;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
```

