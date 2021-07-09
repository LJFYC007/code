/***************************************************************
	File name: HaHa
	Author: ljfcnyali
	Create time: 2019年12月16日 19时31分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2010;
const int Mod = 998244353;

int f[maxn][maxn], g[maxn][maxn], n;
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) REP(j, i, n) g[i][j] = g[i][j - 1] + (s[j] == '?');
    REP(len, 2, n) REP(i, 1, n - len + 1)
    {
        int j = i + len - 1;
        if ( s[i] != '(' ) f[i][j] += f[i + 1][j];
        if ( s[j] != ')' ) f[i][j] += f[i][j - 1];
        if ( s[i] != '(' && s[j] != ')' ) f[i][j] -= f[i + 1][j - 1];
        if ( s[i] != ')' && s[j] != '(' ) f[i][j] += f[i + 1][j - 1] + power(2, g[i + 1][j - 1]);
        f[i][j] %= Mod;
    }
    printf("%lld\n", (f[1][n] + Mod) % Mod);
    return 0;
}
