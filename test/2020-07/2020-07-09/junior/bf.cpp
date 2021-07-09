/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年07月09日 星期四 10时10分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, f[maxn][2], g[maxn], a[maxn], ans;
char P[maxn], S[maxn];

inline void Solve(int n)
{
    REP(i, 1, n) REP(j, 0, 1) f[i][j] = 0;
    f[1][a[1]] = 1;
    for ( int i = 1; i < n; i += 2 ) 
        for ( int j = i + 2; j <= n; j += 2 ) 
            REP(k, 0, 1)
            {
                if ( !f[i][k] ) continue ;
                int now = a[j];
                for ( int o = j - 1; o > i + 1; o -= 2 ) 
                {
                    now = now | (a[o] << 1);
                    now = now | (a[o - 1] << 2);
                    now = g[now];
                }
                now = now | (a[i + 1] << 1);
                now = now | (k << 2);
                now = g[now];
                f[j][now] = 1;
            }
}

inline void DFS(int x)
{
    if ( x == n + 1 ) 
    {
        // REP(i, 1, n) printf("%d ", a[i]); puts("");
        Solve(n); if ( f[n][1] == 1 ) ++ ans;
        // printf("%d\n", f[n][1]);
        return ; 
    }
    if ( S[x] != '?' ) { a[x] = S[x] - '0'; DFS(x + 1); return ; }
    a[x] = 1; DFS(x + 1);
    a[x] = 0; DFS(x + 1);
}
 
int main()
{
    freopen("junior.in", "r", stdin);
    freopen("junior1.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%s", P); 
        g[0] = P[0]; g[1] = P[4]; g[2] = P[2]; g[3] = P[6]; g[4] = P[1]; g[5] = P[5]; g[6] = P[3]; g[7] = P[7];
        REP(i, 0, 7) g[i] = g[i] - '0';

        ans = 0;
        scanf("%s", S + 1); n = str(S + 1);
        DFS(1);
        printf("%d\n", ans);
    }
    return 0;
}
