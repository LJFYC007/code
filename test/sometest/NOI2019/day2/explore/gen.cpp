/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年07月18日 星期四 11时34分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 60010;

bool a[maxn];

int main()
{
    freopen("input.txt", "w", stdout);
    int n = 1598, m = n / 2, Lm = 17 * n, Lq = 17 * n, Lc = 0;
    printf("%d %d %d\n", Lm, Lq, Lc);
    printf("%d %d\n", n, m);
    srand(time(0));
    REP(i, 1, m)
    {
        int u = rand() % n, v = rand() % n;
        while ( u == v || a[u] || a[v] ) { v = rand() % n; u = rand() % n; }
        a[u] = a[v] = true;
        printf("%d %d\n", u, v);
    }
    return 0;
}
