/***************************************************************
	File name: aqours.cpp
	Author: ljfcnyali
	Create time: 2020年10月25日 星期日 11时27分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6010;
const int Mod = 1e9 + 7;

int n, k, f[maxn][maxn], a[maxn], g[maxn][maxn], ans, lst[28], h[maxn];
char s[maxn];
bool vis[28];

signed main()
{
    freopen("aqours.in", "r", stdin);
    freopen("aqours.out", "w", stdout);
    scanf("%d%d", &n, &k);
    scanf("%s", s + 1);
    REP(i, 1, n) if ( s[i] != '_' ) a[i] = s[i] - 'a' + 1; else a[i] = 27;
    f[0][0] = h[0] = 1;    
    REP(i, 1, 27) lst[i] = -1;
    REP(i, 1, n + 1) 
    {
        REP(j, 1, i) 
        {
            f[i][j] = h[j - 1];
            if ( lst[a[i]] != -1 ) f[i][j] = (f[i][j] - f[lst[a[i]]][j - 1]) % Mod;
        }
        REP(j, 0, i) 
        {
            int pos = lst[a[i]];
            if ( pos != -1 ) h[j] = (h[j] - f[pos][j]) % Mod;
            h[j] = (h[j] + f[i][j]) % Mod;
        }
        lst[a[i]] = i;
    }
    g[0][0] = 1;
    REP(j, 1, n) 
    {
        int sum = 0;
        REP(i, j, n)
        {
            sum = (sum + g[i - 1][j - 1]) % Mod;
            g[i][j] = sum;
            if ( i >= k ) sum = (sum - g[i - k][j - 1]) % Mod;
        }
    }
    REP(i, 1, n)
    {
        int ret = f[n + 1][i + 1];
        ans = (ans + 1ll * ret * g[n][i]) % Mod; 
    }
    printf("%d\n", (ans + Mod) % Mod);
    return 0;
}
