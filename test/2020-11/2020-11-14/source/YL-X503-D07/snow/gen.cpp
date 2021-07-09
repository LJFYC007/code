/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月15日 星期日 15时24分19秒
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
    freopen("snow.in", "w", stdout);
    int n = 1000, q = 1000; printf("%d %d\n", n, q);
    srand(time(0));
    REP(i, 1, n) printf("%d ", rand() % 10 + 1); puts("");
    REP(i, 2, n) printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % 10 + 1);
    // REP(i, 2, n) printf("%d %d %d\n", i, i - 1, rand() % 10 + 1);
    REP(i, 1, q) printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 10 + 1);
    return 0;
}
