/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月14日 星期二 10时10分44秒
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
    freopen("clear.in", "w", stdout);
    srand(time(0));
    int n = 50, m = 50, t = 1000;
    printf("%d %d %d\n", n, m, t);
    REP(i, 1, n) printf("%d ", rand() % 100000 + 1); puts("");
    REP(i, 1, m) printf("%d ", rand() % 100000 + 1); puts("");
    REP(i, 1, t) printf("%d %d\n", rand() % 70000 + 1, rand() % 70000 + 1);
    return 0;
}
