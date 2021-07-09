/***************************************************************
	File name: correct.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 20时26分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 20010;

int n, a[maxn], q, dis[maxn], Mod;
bool vis[maxn];
queue<int> Q;

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &n);
    memset(dis, 0x3f, sizeof(dis));
    dis[0] = 0;
    REP(i, 1, n) 
    { 
        scanf("%d", &a[i]); if ( i == 1 ) Mod = a[i];
        dis[a[i] % Mod] = min(dis[a[i] % Mod], a[i]); 
        Q.push(a[i] % Mod); vis[a[i] % Mod] = true; 
    }
    // REP(i, 0, Mod - 1) printf("%d ", dis[i]); puts("");
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(i, 2, n)
        {
            int v = (u + a[i]) % Mod; 
            if ( dis[v] > dis[u] + a[i] ) 
            {
                dis[v] = dis[u] + a[i];
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    // REP(i, 0, Mod - 1) printf("%d ", dis[i]); puts("");
    scanf("%d", &q);
    REP(i, 1, q)
    {
        int x; scanf("%d", &x);
        if ( dis[x % Mod] <= x ) puts("Acesrc!");
        else puts("Acesrc?");
    }
    return 0;
}
