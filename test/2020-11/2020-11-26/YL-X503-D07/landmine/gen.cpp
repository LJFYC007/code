/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月26日 星期四 11时33分05秒
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
    freopen("landmine.in", "w", stdout);
    int n = 20; printf("%d\n", n); srand(time(0));
    REP(i, 1, n) printf("%d ", rand() % 3 + 1); puts("");
    REP(i, 1, n) printf("%d ", rand() % 3 + 1); puts("");
    REP(i, 1, n) printf("%d ", rand() % 3 + 1); puts("");
    REP(i, 1, n) printf("%d ", rand() % 3 + 1); puts("");
    return 0;
}
