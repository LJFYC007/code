/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年11月11日 星期一 09时59分33秒
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
    srand(time(0));
    freopen("b.in", "w", stdout);
    int n = 1000; printf("%d\n", n);
    REP(i, 1, n) printf("%d ", rand() % n + 1); puts("");
    return 0;
}
