/***************************************************************
	File name: bondorudo.cpp
	Author: ljfcnyali
	Create time: 2020年12月03日 星期四 08时40分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m;
bool vis[maxn], use[maxn];

int main()
{
    freopen("bondorudo.in", "r", stdin);
    freopen("bondorudo.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if ( m == n - 1 ) 
    {
        puts("1");
        REP(i, 1, n - 1) printf("%d %d\n", i, i + 1);
        return 0;
    }
    int now = n + 1;
    REP(i, 1, n)
    {
        if ( now > m ) break ;
        if ( vis[i] ) continue ; ++ now;
        vis[i] = vis[(i + 1) % n + 1] = true;
    }
    bool flag = true;
    REP(i, 1, n) flag &= vis[i];
    if ( flag ) puts("3");
    else puts("2");

    REP(i, 1, n) printf("%d %d\n", i, i % n + 1);
    mem(vis); now = n + 1;
    REP(i, 1, n)
    {
        if ( now > m ) break ;
        if ( vis[i] ) continue ; ++ now;
        vis[i] = vis[(i + 1) % n + 1] = true;
        use[i] = true;
        printf("%d %d\n", i, (i + 1) % n + 1);
    }
    REP(i, 1, n)
    {
        if ( now > m ) break ; 
        if ( use[i] ) continue ; ++ now;
        use[i] = true;
        printf("%d %d\n", i, (i + 1) % n + 1);
    }
    return 0;
}
