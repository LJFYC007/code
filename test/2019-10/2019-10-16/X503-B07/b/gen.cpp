/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月16日 星期三 10时38分09秒
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
    int n = 3000, m = 3000, k = 500;
    printf("%d %d %d\n", n, m, k);
    REP(i, 1, n) { REP(j, 1, m) printf("%d ", rand() % 2 + 1); puts(""); }
    return 0;
}
