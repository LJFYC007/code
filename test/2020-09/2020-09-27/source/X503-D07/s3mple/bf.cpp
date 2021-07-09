/***************************************************************
	File name: s3mple.cpp
	Author: ljfcnyali
	Create time: 2020年09月27日 星期日 09时37分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;

int f[maxn][maxn * maxn], T, n, m, Mod, c[maxn][maxn];
int g[maxn]={1,2,3,5,6,8,10,13,14,16,18,21,23,26,29,33,34,36,38,41,43,46,49,53,55,58,61,65,68,72,76,81,82,84,86,89,91,94,97,101,103,106,109,113,116,120,124,129,131,134,137,141,144,148,152,157,160,164,168,173,177,182,187,193,194,196,198,201,203,206,209,213,215,218,221,225,228,232,236,241,243,246,249,253,256,260,264,269,272,276,280,285,289,294,299,305,307,310,313,317,320,324,328,333,336,340,344,349,353,358,363,369,372,376,380,385,389,394,399,405,409,414,419,425,430,436,442,449,450,452,454,457,459,462,465,469,471,474,477,481,484,488,492,497,499,502,505,509,512,516,520,525,528,532,536,541,545,550,555,561,563,566,569,573,576,580,584,589,592,596,600,605,609,614,619,625,628,632,636,641,645,650,655,661,665,670,675,681,686,692,698,705,707,710,713,717,720,724,728,733,736};

inline int F(int n, int m)
{
    if ( n == 1 ) return m == 1;
    if ( n == 0 ) return m == 0;
    if ( n < 0 || m < 0 || m >= g[n] ) return 0;
    if ( f[n][m] != -1 ) return f[n][m];
    int ret = 0;
    REP(i, 1, n)
    {
        int x = i - 1, y = n - i;
        int val = m - min(i, n - i + 1);
        int sum = 0;
        REP(j, 0, val) sum = (sum + F(x, j) * F(y, val - j)) % Mod;
        ret = (ret + sum * c[x + y][x]) % Mod;
    }
    f[n][m] = ret; return ret;
}

signed main()
{
    freopen("s3mple.in", "r", stdin);
    freopen("s3mple.out", "w", stdout);
    scanf("%lld", &Mod);
    n = maxn - 10; REP(i, 0, n) c[i][0] = 1;
    REP(i, 1, n) REP(j, 1, i) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % Mod;
    memset(f, -1, sizeof(f));
    REP(i, 0, 5) printf("%lld ", F(2, i)); puts("");
    REP(i, 0, 5) printf("%lld ", F(3, i)); puts("");
    while ( ~scanf("%lld%lld", &n, &m) ) 
        printf("%lld\n", (F(n, m) + Mod) % Mod);
    return 0;
}
