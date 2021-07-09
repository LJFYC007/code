/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 16时29分42秒
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
    freopen("score.in", "w", stdout);
    srand(time(0));
    int n = 1000, m = 500;
    printf("%d %d\n", n, m);
    REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    REP(i, 1, m) printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 1000 - 500);
    return 0;

    n = 6; m = 3; printf("%d %d\n", n, m);
    REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    REP(i, 1, m) printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 10 - 5);
    return 0;
}
