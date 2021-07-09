/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年06月13日 星期六 10时03分56秒
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
    freopen("B.in", "w", stdout);
    int n = 5; printf("%d\n", n);
    srand(time(0));
    REP(i, 1, n) printf("%d ", rand() % 20 + 1); puts("");
    REP(i, 2, n) printf("%d ", rand() % (i - 1) + 1); puts("");
    return 0;
}
