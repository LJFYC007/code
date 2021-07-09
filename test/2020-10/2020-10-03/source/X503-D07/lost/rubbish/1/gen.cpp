/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月03日 星期六 09时55分14秒
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
    freopen("lost.in", "w", stdout);
    srand(time(0));
    int n = 500000; printf("%d\n", n);
    REP(i, 1, n) printf("%d ", (LL)rand() * rand() % 1000000000 + 1); puts("");
    // REP(i, 2, n) printf("%d ", i - 1); puts("");
    REP(i, 2, n) printf("%d ", rand() % (i - 1) + 1); puts("");
    return 0;
}
