/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月15日 星期三 10时53分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
    freopen("dag.in", "w", stdout);
    int n = 50000, m = 50000, q = 50000;
    srand(time(0));
    printf("%d %d %d\n", n, m, q);
    REP(i, 2, n) printf("%d %d\n", rand() % (i - 1) + 1, i);
    REP(i, n, m) 
    {
        int u = rand() % n + 1, v = rand() % n + 1;
        while ( u == v ) v = rand() % n + 1;
        if ( u > v ) swap(u, v);
        printf("%d %d\n", u, v);
    }
    REP(i, 1, q)
    {
        int op = rand() % 3 + 1;
        if ( op == 1 ) ++ op;
        if ( op <= 2 ) printf("%d %d %d\n", op, rand() % n + 1, rand() % 1000000 + 1);
        else printf("%d %d\n", op, rand() % n + 1);
    }
    return 0;
}
