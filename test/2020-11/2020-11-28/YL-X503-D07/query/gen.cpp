/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali-akioi
	Create time: 2020年11月28日 星期六 09时32分43秒
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
    freopen("query.in", "w", stdout);
    int n = 50000, m = 50001;
    printf("%d %d\n", n, m);
    srand(time(0));
    REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    REP(i, 1, m) printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    return 0;
}
