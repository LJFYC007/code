/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 10时55分51秒
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
    freopen("big.in", "w", stdout);
    int n = 5, m = 5; printf("%d %d\n", n, m);
    srand(time(0));
    REP(i, 1, m) printf("%d ", rand() % (1 << n)); puts("");
    return 0;
}
