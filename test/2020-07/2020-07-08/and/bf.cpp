/***************************************************************
	File name: and.cpp
	Author: ljfcnyali
	Create time: 2020年07月08日 星期三 10时52分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, m, f[maxn];
struct node { int op, x, l, r, val; } Q[maxn];

inline int DFS(int w, int x, int op)
{
    if ( !x ) return 1;
    if ( (w >> x - 1) & 1 ) return DFS(w, x - 1, (n >> x - 1) & 1 ? 0 : 1);
    if ( !op ) return 2 * DFS(w, x - 1, 0);
    if ( (n >> x - 1) & 1 ) return DFS(w, x - 1, 0) + DFS(w, x - 1, 1);
    return DFS(w, x - 1, 1);
}

inline int Get(int l, int r, int L, int R)
{
    l = max(l, L);
    r = min(r, R);
    if ( l > r ) return 0;
    return r - l + 1;
}

signed main()
{
    freopen("and.in", "r", stdin);
    freopen("and.out", "w", stdout);
    scanf("%lld%lld", &n, &m); 
    -- n;
    REP(i, 0, n) f[i] = DFS(i, 16, 1);
    REP(i, 1, m)
    {
        scanf("%lld%lld%lld%lld", &Q[i].op, &Q[i].x, &Q[i].l, &Q[i].r);
        if ( Q[i].op == 0 ) scanf("%lld", &Q[i].val);
        else
        {
            int ans = 0;
            REP(j, 1, i - 1)
            {
                if ( Q[j].op == 1 ) continue ;
                int x = Q[j].x | Q[i].x;
                ans = (ans + (f[x] * Get(Q[j].l, Q[j].r, Q[i].l, Q[i].r) % Mod) * Q[j].val) % Mod;
            }
            printf("%lld\n", (ans + Mod) % Mod);
        }
    }
    return 0;
}
