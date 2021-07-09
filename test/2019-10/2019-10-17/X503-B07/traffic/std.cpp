/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年10月17日 星期四 19时42分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6010;
const int INF = 0x3f3f3f3f;

int n, a[maxn], b[maxn], dis1[maxn], dis2[maxn][maxn], f[maxn], ans;
vector<int> p[maxn];
bool vis[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

int main()
{
    // freopen("2.in", "r", stdin);
    freopen("traffic.in", "r", stdin);
    freopen("traffic.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 2, n) scanf("%d", &a[i]); a[1] = 1;
    REP(i, 2, n) scanf("%d", &b[i]);
    memset(dis2, 0x3f, sizeof(dis2));
    REP(i, 1, n) dis2[i][i] = 0;
    REP(j, 2, n)
    {
        int Min = INF, x;
        REP(i, b[j], j - 1) { dis2[i][j] = 1; if ( b[i] < Min ) { Min = b[i]; x = i; } }
        REP(i, 1, b[j] - 1) dis2[i][j] = dis2[i][x] + 1;
    }
    REP(i, 1, n)
    {
        REP(j, 0, n) p[j].clear();
        REP(j, 1, n) 
        {
            dis1[j] = dis2[i][j]; f[j] = j; 
            if ( dis1[j] <= n ) p[dis1[j]].push_back(j);
        }
        mem(vis);
        REP(j, 0, n)
            for ( auto u : p[j] ) 
            {
                int v = find(u);
                if ( vis[u] ) continue ; vis[u] = true;
                while ( v >= a[u] ) 
                {
                    dis1[v] = min(dis1[v], dis1[u] + 1);
                    f[v] = v - 1;
                    if ( !vis[v] ) p[dis1[v]].push_back(v);
                    v = find(v);
                }
            }
        REP(j, 1, n) ans ^= (i + j) * dis1[j];
    }
    printf("%d\n", ans);
    return 0;
}
