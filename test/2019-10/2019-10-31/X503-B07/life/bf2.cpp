/***************************************************************
	File name: life.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 08时25分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 300010;

int n, m, l[maxn], r[maxn], g[maxn], a[maxn], ret, last, ans;
multiset<int> Set;

int main()
{
    freopen("life.in", "r", stdin);
    freopen("life.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m) scanf("%d%d%d", &l[i], &r[i], &g[i]);
    int now = 1;
    REP(i, 1, m)
    {
        if ( last < l[i] ) { Set.clear(); ret = 0; }
        while ( now <= r[i] ) { ret += a[now]; if ( a[now] ) last = now; ++ now; }
        if ( ret ) { Set.insert(g[i]); ans += g[i]; -- ret; }
        else 
        {
            auto it = Set.begin(); 
            if ( *it < g[i] ) { ans = ans - *it + g[i]; Set.erase(*it); Set.insert(g[i]); }
        }
        printf("%d ", ans); 
    }
    printf("%d\n", ans);
    return 0;
}
