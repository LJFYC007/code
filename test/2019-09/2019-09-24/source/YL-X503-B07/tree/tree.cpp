/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2019年09月25日 星期三 08时22分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 1000010;
const int Max = 10000000;

int n, a[maxn], l[maxn], r[maxn], f[maxn], prime[maxn], tot, p[maxn * 10];
bool vis[maxn * 10];
vector<int> t[maxn * 10];

inline void DFS(int L, int R, int fa)
{
    if ( L > R ) return ;
    REP(i, 0, (R - L + 1) / 2)
    {
        int x = L + i, y = R - i;
        if ( l[x] <= L && R <= r[x] ) 
        {
            f[x] = fa;
            DFS(L, x - 1, x); DFS(x + 1, R, x);
            return ;
        }
        if ( l[y] <= L && R <= r[y] ) 
        {
            f[y] = fa;
            DFS(L, y - 1, y); DFS(y + 1, R, y);
            return ;
        }
    }
    puts("impossible"); exit(0);
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 2, Max)
    {
        if ( !vis[i] ) { prime[++ tot] = i; p[i] = i; }
        for ( int j = 1; j <= tot && prime[j] * i <= Max; ++ j )
        {
            vis[i * prime[j]] = true;
            p[i * prime[j]] = prime[j];
            if ( i % prime[j] == 0 ) break ; 
        }
    }
    REP(i, 1, n)
    {
        scanf("%lld", &a[i]); int x = a[i];
        l[i] = 1; r[i] = n;
        while ( x != 1 ) 
        {
            t[p[x]].push_back(i);
            int tmp = p[x];
            while ( x != 1 && x % tmp == 0 ) x /= tmp;
        }
    }
    REP(i, 1, Max)
    {
        REP(j, 0, t[i].size() - 1)
        {
            if ( j > 0 ) l[t[i][j]] = max(l[t[i][j]], t[i][j - 1] + 1);
            if ( j < t[i].size() - 1) r[t[i][j]] = min(r[t[i][j]], t[i][j + 1] - 1);
        }
    }
    DFS(1, n, 0);
    REP(i, 1, n) printf("%lld ", f[i]); puts("");
    return 0;
}
