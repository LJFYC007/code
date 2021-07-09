/***************************************************************
	File name: network.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月28日 星期六 11时16分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 5e6 + 10;

int n, m, ans[maxn], belong[maxn];
pii a[maxn], pre1[maxn], pre2[maxn];
bool vis[maxn], use[maxn];

int main()
{
    freopen("network.in", "r", stdin);
    freopen("network.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d%d", &a[i].x, &a[i].y);

    for ( int i = 1; i <= n; i += 2 ) 
    {
        belong[i] = i + 1; belong[i + 1] = i;
        if ( i == n ) belong[i] = i;
    }
    REP(i, 1, m)
    {
        int x = a[i].x, y = a[i].y, u = belong[x], v = belong[y];
        pre1[i] = pii(x, u); pre2[i] = pii(y, v);
        if ( x == v ) continue ;
        if ( x == u ) { belong[x] = y; belong[y] = x; belong[v] = v; }
        else if ( y == v ) { belong[x] = y; belong[y] = x; belong[u] = u; }
        else { belong[x] = y; belong[y] = x; belong[u] = v; belong[v] = u; }
    }
    REP(i, 1, n) if ( belong[i] <= i ) use[i] = true; 

    for ( int i = m; i >= 1; -- i ) 
    {
        int x = a[i].x, y = a[i].y, u = pre1[i].y, v = pre2[i].y;

        if ( x == v ) 
        {
            if ( use[x] ) ans[i] = 0;
            else ans[i] = 1;
        }
        else if ( x == u ) 
        { 
            if ( use[y] ) ans[i] = 1; else ans[i] = 0;
            use[x] = true; use[y] = false;
        }
        else if ( y == v ) 
        {
            if ( use[x] ) ans[i] = 0; else ans[i] = 1;
            use[y] = true; use[x] = false;
        }
        else 
        {
            if ( !use[x] )
            {
                ans[i] = 1; 
                if ( !use[u] ) { use[x] = true; use[y] = false; }
            }
            else 
            {
                ans[i] = 0;
                if ( !use[v] ) { use[x] = false; use[y] = true; }
            }
        }
    }

    REP(i, 1, n) vis[i] = true;
    REP(i, 1, m)
    {
        if ( ans[i] == 1 ) swap(a[i].x, a[i].y);
        vis[a[i].x] |= vis[a[i].y];
        vis[a[i].y] = false;
    }

    int num = 0;
    REP(i, 1, n) num += vis[i];
    // REP(i, 1, m) printf("%d", ans[i]); puts("");
    
    if ( num < (n + 1) / 2 ) puts("NO");
    else 
    {
        puts("YES");
        REP(i, 1, m) printf("%d", ans[i]); puts("");
    }
    return 0;
}
