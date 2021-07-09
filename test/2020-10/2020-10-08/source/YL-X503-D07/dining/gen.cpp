/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月08日 星期四 10时03分47秒
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
    freopen("dining.in", "w", stdout);
    srand(time(0));
    int n = 1000, m = 20000, s = rand() % n + 1, t = rand() % n + 1;
    printf("%d %d %d %d\n", n, m, s, t);
    REP(i, 1, m)
    {
        int u = rand() % n + 1, v = rand() % n + 1;
        while ( u == v ) v = rand() % n + 1;
        printf("%d %d %d\n", u, v, rand() % 100000 + 1);
    }
    return 0;
}
