/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月26日 星期六 10时19分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int main()
{
    freopen("b.in", "w", stdout);
    int n = 2000;
    printf("%d\n", n);
    REP(i, 2, n) printf("%d ", rand() % (i - 1) + 1); puts("");
    return 0;
}
