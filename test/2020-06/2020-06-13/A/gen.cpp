/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年06月13日 星期六 10时19分59秒
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
    srand(time(0));
    int n = 400, m = 100000, k = 16, q = 200000;
    // int n = 5, m = 6, k = 2, q = 2;
    printf("%d %d %d\n", n, m, k);
    REP(i, 1, m) printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 100000 + 1);
    REP(i, 1, k) printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    printf("%d\n", q);
    REP(i, 1, q) printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    return 0;
}
