/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2020年09月29日 星期二 19时37分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e7 + 10;
const int Mod = 998244353;

int n, m, fac[maxn], inv[maxn], ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
    freopen("hippocentaur.in", "r", stdin);
    freopen("hippocentaur.out", "w", stdout);
    n = maxn - 10;
    fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    scanf("%lld", &n);

    ans = (4 * C(2 * n, n) - n * n - 3) % Mod;
    ans = (2 * ans - (n + 1) * (n + 1)) % Mod;
    cout << (ans + Mod) % Mod << endl;
    return 0;
}
