/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年09月13日 星期日 19时48分39秒
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
    freopen("mst.in", "w", stdout);
    int n = 50, m = 2000, k = 10000; printf("%d %d %d\n", n, m, k);
    srand(time(0));
    REP(i, 1, n - 1) REP(j, 1, 40) printf("%d %d %d\n", i, i + 1, 100);
    REP(i, 1, n - 1) printf("%d %d %d\n", i, i + 1, 100);
    // REP(i, 1, n) REP(j, i + 1, n) printf("%d %d 100\n", i, j);
    REP(i, 1, m) printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, 100);
    return 0;
}
