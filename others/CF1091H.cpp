/***************************************************************
	File name: CF1091H.cpp
	Author: ljfcnyali
	Create time: 2020年10月26日 星期一 08时10分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, f, m, sg[maxn], prime[maxn], tot, ans;
bitset<maxn> Set[110], sta;
bool vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = maxn - 10;
    for ( int i = 2; i <= n; ++ i ) 
    {
        if ( !vis[i] ) { prime[++ tot] = i; Set[0][i] = 1; }
        for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j )
        {
            vis[i * prime[j]] = true;
            if ( i % prime[j] == 0 ) break ;
        }
    }
    REP(i, 1, tot) REP(j, 1, tot)
    {
        int x = prime[i] * prime[j];
        if ( x > n ) break ; Set[0][x] = 1;
    }

    scanf("%d%d", &n, &f); Set[0][f] = 0;
    sta = Set[0];
    m = 2e5;
    REP(i, 1, m)
    {
        sg[i] = 0;
        while ( Set[sg[i]][i] ) ++ sg[i];
        Set[sg[i]] |= sta << i;
    }
    REP(i, 1, n)
    {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        ans ^= sg[b - a - 1];
        ans ^= sg[c - b - 1];
    }
    if ( ans ) puts("Alice\nBob");
    else puts("Bob\nAlice");
    return 0;
}
