/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月29日 星期三 09时37分58秒
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
    freopen("A.in", "w", stdout);
    int n = 250, m = n * (n - 1) / 3; printf("%d %d\n", n, m);
    srand(time(0));
    REP(i, 1, n) printf("%d ", rand() % 1000 + 1); puts("");
    REP(i, 1, m) 
    {
        int u = rand() % n + 1, v = rand() % n + 1;
        while ( u == v ) u = rand() % n + 1;
        printf("%d %d\n", u, v);
    }
    return 0;
}
