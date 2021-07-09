// luogu-judger-enable-o2
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

typedef long long ll;

const int maxn = 1e4 + 7, N = 1e7;

using namespace std;

ll ans;
int p[N + 7];
int prime[maxn], cnt;
int a[N + 7];
int flag[N + 7];

inline void init(int n)
{
    for (int i = 2; i <= n; i++) {
        if (!p[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            p[i * prime[j]] = true;
            if (!(i % prime[j])) break;
        }
    }
}

inline int ksm(int a, int n, int mod)
{
    int b = 1;
    while (n) {
        if (n & 1) b = 1ll * a * b % mod;
        a = 1ll * a * a % mod;
        n >>= 1;
    }
    return b;
}

int main(void)
{
    int n;
    cin >> n;
    init(sqrt(n + 1));
    for (int i = 1; i <= cnt; i++) {
        int x = prime[i];
        for (int j = x << 1; j <= n + 1; j += x) p[j] = 1;
    }
    for (int i = 1; i <= n; i++) {
        a[i] = i;
        if (i & 1 || p[i + 1]) flag[i] = 1;
    }
    for (int i = 1; i <= cnt; i++) {
        int x = prime[i];
        for (int j = x << 1; j <= n; j += x) {
            if (flag[j]) continue;
            if (p[j + 1] || ksm(2, j / x, j + 1) == 1) flag[j] = 1;
            while (!(a[j] % x)) a[j] /= x;
        }
    }
    for (int i = 1; i <= n; i++)
        if (!flag[i] && (a[i] == 1 || ksm(2, i / a[i], i + 1) > 1)) ans += i;
    printf("%.5lf\n", 2.0 * ans / n);
    
    return 0;
}