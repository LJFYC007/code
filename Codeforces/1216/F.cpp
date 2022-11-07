/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年09月21日 星期六 16时30分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
typedef long long LL;
#define int long long

const int maxn = 200010;
const int INF = 1000000000000000ll;

int n, k, ans;
char s[maxn];
bool vis[maxn];

inline void DFS(int l, int r)
{
    if ( l < 1 ) l = 1;
    if ( r < 1 ) return ;
    REP(i, l, r) 
    {
        if ( s[i] == '1' )
        {
            int sum = 0;
            REP(j, max(1ll, i - k), min(n, i + k)) { if ( !vis[j] ) sum += j; vis[j] = true; }
            if ( sum < i ) { ans += sum; break ; }
            ans += i;
            DFS(i - k - k - 1, i - 1);
            return ;
        }
    }
    DFS(l - 1, l - 1);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d%I64d", &n, &k);
    scanf("%s", s + 1);
    DFS(n - k, n);
    REP(i, 1, n) if ( !vis[i] ) ans += i;
    printf("%I64d\n", ans);
    return 0;
}
