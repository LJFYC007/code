/***************************************************************
	File name: class.cpp
	Author: ljfcnyali
	Create time: 2020年01月18日 星期六 09时00分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 10;
const int Mod = 1e9 + 7;

int n, m, a[maxn], p[maxn], f[maxn][maxn], ans;

inline void DFS(int x)
{
    if ( x == 2 * m + 1 ) 
    {
        REP(i, 1, m) p[i] = i;
        int ret = 0;
        do
        {
            int sum = 0;
            REP(i, 1, m) sum = sum + f[a[p[i]]][a[i + m]];
            ret = max(ret, sum);
        } while ( next_permutation(p + 1, p + m + 1) );
        // REP(i, 1, m * 2) printf("%d ", a[i]); puts("");
        // printf("%d\n", ret);
        ans += ret; ans %= Mod;
        return ; 
    }
    REP(i, 1, n) { a[x] = i; DFS(x + 1); }
}

signed main()
{
    freopen("class.in", "r", stdin);
    freopen("class.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    memset(f, 0x3f, sizeof(f));
    REP(i, 1, n) f[i][i] = 0;
    REP(i, 1, n - 1) 
    { 
        int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); 
        f[u][v] = f[v][u] = w;
    }
    REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    DFS(1);
    printf("%lld\n", ans);
    return 0;
}
