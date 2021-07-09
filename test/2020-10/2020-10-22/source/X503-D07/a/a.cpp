/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2020年10月22日 星期四 08时38分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, m, ans, fac[maxn], inv[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int A(int n, int m) { return n < m ? 0 : fac[n] * inv[n - m] % Mod; }

signed main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 2, n + 1)
        if ( i < m ) 
        {
            int ret = A(n, i - 1) * (i - 1) % Mod;        
            int sum = A(n, i - 1) * power(n, m - i - 1) % Mod;
            ret = ret * sum % Mod;
            int val = (ret * n * 2 - ret * (i - 1)) % Mod;
            ans = (ans + val) % Mod;
        }
        else if ( i == m ) 
        {
            int ret = A(n, i - 1) * (i - 1) % Mod;
            int val = ret * A(n, i - 1) * 2 % Mod;
            int sum = ret * A(n - 1, i - 2) % Mod;
            val = (val - sum * (i - 1)) % Mod;
            ans = (ans + val) % Mod;
        }
        else 
        {
            int l = i - m - 1;
            int val = A(n - l, m) * A(n - l - 1, m - 1) % Mod; 
            val = val * m * 2 % Mod;
            int t = A(n - l, m) * A(n - l - 1, m - 1) % Mod;
            val = (val - t) % Mod;

            t = A(n - l, m) * (m - 1) % Mod;
            t = t * A(n - l - 2, m - 2) % Mod;
            t = t * (m - 1) % Mod;
            val = (val - t) % Mod;

            ans = (ans + A(n, l) * val) % Mod;
        }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
} 
