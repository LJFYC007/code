/***************************************************************
	File name: easy.cpp
	Author: ljfcnyali
	Create time: 2019年09月27日 星期五 13时54分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 4010;

int n, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
double f[maxn], ans;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS(int u, int fa)
{
    f[u] = 0; int son = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u);
        ++ son;
    }
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[u] += 1.0 / 2.0 * (f[v] + W[i]);
    }
}

int main()
{
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    scanf("%d", &n);    
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    REP(i, 1, n)
    {
        DFS(i, 0);
        double sum = 0;
        for ( int j = Begin[i]; j; j = Next[j] ) 
        {
            int v = To[j];
            sum += f[v] + W[j];
        }
        sum *= 2;
        // cerr << sum << endl;
        ans += sum / n;
    }
    printf("%.3lf\n", ans);
    return 0;
}
