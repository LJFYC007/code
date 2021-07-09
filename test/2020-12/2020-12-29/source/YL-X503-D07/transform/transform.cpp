/***************************************************************
	File name: transform.cpp
	Author: ljfcnyali
	Create time: 2020年12月29日 星期二 08时53分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int INF = 0x3f3f3f3f;

int T, n, m, f[maxn][maxn];
char s[maxn], t[maxn];
bool vis[maxn][maxn];

inline int max(int a, int b) { return a > b ? a : b; }

int main()
{
    freopen("transform.in", "r", stdin);
    freopen("transform.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- )
    {
        scanf("%s", s + 1); n = str(s + 1);
        scanf("%s", t + 1); m = str(t + 1);
        REP(i, 1, n) REP(j, i, n) { f[i][j] = -INF; vis[i][j] = false; } 
        REP(i, 1, n) f[i][i] = s[i] == t[1];
        int ans = 0;
        REP(len, 1, n) REP(i, 1, n - len + 1)
        {
            int j = i + len - 1;
            if ( len != 1 ) 
            {
                f[i][j] = max(f[i][j - 1], f[i + 1][j]);
                if ( 0 <= f[i][j - 1] && f[i][j - 1] < m && t[f[i][j - 1] + 1] == s[j] ) f[i][j] = max(f[i][j], f[i][j - 1] + 1);
                if ( 0 <= f[i + 1][j] && f[i + 1][j] < m && t[f[i + 1][j] + 1] == s[i] ) f[i][j] = max(f[i][j], f[i + 1][j] + 1);
            }
            if ( f[i][j] >= m ) vis[i][j] = true;
            vis[i][j] |= vis[i + 1][j] | vis[i][j - 1];
            if ( vis[i][j] ) ++ ans;
        }
        printf("%d\n", ans);
    }
    return 0;
}
