/***************************************************************
	File name: CF932E.cpp
	Author: ljfcnyali
	Create time: 2020年05月27日 星期三 16时18分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 1e9 + 7;

int S[maxn][maxn], n, k, ans;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);

    S[0][0] = 1;
    REP(i, 1, k) REP(j, 1, i) S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % Mod;

    REP(i, 1, min(n, k))
    {
        int ret = power(2, n - i);
        int sum = 1;
        REP(j, n - i + 1, n) sum = sum * j % Mod;
        ret = ret * sum % Mod;
        ret = ret * S[k][i] % Mod;
        ans = (ans + ret) % Mod;
    }
    printf("%lld\n", ans);
    return 0;
}
