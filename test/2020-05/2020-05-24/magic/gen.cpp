/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年05月24日 星期日 08时58分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned int 
typedef long long LL;

const int maxn = 110;

bool a[maxn][maxn];

signed main()
{
    freopen("magic.in", "w", stdout);
    srand(time(0));
    int n = 100, m = 500, q = 100;
    printf("%u %u %u\n", n, m, q);
    REP(i, 1, n) printf("%u ", rand() * rand() + 1); puts("");
    REP(i, 1, m)
    {
        int u = rand() % n + 1, v = rand() % n + 1; 
        while ( a[u][v] ) { u = rand() % n + 1; v = rand() % n + 1; }
        a[u][v] = a[v][u] = true;
        printf("%u %u\n", u, v);
    }
    REP(i, 1, q)
    {
        int x = rand() * rand() + 1;
        printf("%u\n", x);
    }
    return 0;
}
