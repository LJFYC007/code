/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2020年04月19日 星期日 08时13分06秒
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

int n, m, x0, a, b, c, f[maxn][20];
map<int, int> g;

namespace Subtask1
{
    inline int main()
    {
        int x = x0; x %= m; a %= m; b %= m; c %= m;
        REP(i, 1, n) x = (a * (x * x % m) + b * x + c) % m;
        printf("%lld\n", x);
        return 0;
    }
}

namespace Subtask2
{
    inline int main()
    {
        a %= m; b %= m; c %= m;
        REP(i, 0, m - 1) f[i][0] = (a * (i * i % m) + b * i + c) % m;
        REP(i, 1, 19) REP(j, 0, m - 1) f[j][i] = f[f[j][i - 1]][i - 1];
        int x = x0 % m;
        while ( n >= (1 << 19) ) { x = f[x][19]; n -= (1 << 19); }
        for ( int i = 18; i >= 0; -- i ) if ( n >= (1 << i) ) { x = f[x][i]; n -= (1 << i); }
        printf("%lld\n", x);
        return 0;
    }
}

inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%lld%lld%lld%lld%lld%lld", &x0, &a, &b, &c, &n, &m);
    if ( m <= maxn ) return Subtask2 :: main();
    if ( n <= maxn ) return Subtask1 :: main();    
	x0 += b / a / 2;
	int x = power(2, n, m - 1);
	int ans = power(a, x - 1, m) * power(x0, x, m) % m - b / a / 2;
    printf("%lld\n", (ans + m) % m);
    return 0;
}
