/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2019年10月28日 星期一 14时28分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;
const int INF = 0x3f3f3f3f;

int n, m, h[maxn], f[maxn], Stack[maxn], tot, ans, g[maxn];

inline int X(int i) { return g[i] - (n + 1) * h[i]; }

#define Y(i) h[i]

inline double slope(int i, int j) { return (X(i) - X(j)) / (Y(j) - Y(i) + 1e-8); }

int main()
{
    freopen("medium.in", "r", stdin);
    freopen("medium.out", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        REP(i, 1, n) scanf("%d", &h[i]);
        sort(h + 1, h + n + 1);
        f[0] = INF;
        REP(i, 1, n) f[i] = (n - i + 1) * h[i];
        REP(o, 2, m)
        {
            tot = 0;
            memcpy(g,f,sizeof(int) * n + sizeof(int) );
            REP(i, 1, n)
            {
                while ( tot > 1 && slope(Stack[tot - 1], Stack[tot]) <= i ) -- tot;
                f[i] = g[Stack[tot]] + (h[i] - h[Stack[tot]]) * (n - i + 1); 
                while ( tot > 1 && slope(Stack[tot - 1], Stack[tot]) < slope(Stack[tot], i) ) -- tot;
                Stack[++tot] = i;
            }
        }
        ans = INF;
        REP(i, 1, n) ans = min(ans, f[i]);
        printf("%d\n", ans);
    }
    return 0;
}
