/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 10时29分00秒
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
    freopen("w.in", "w", stdout);
    int n = 10; printf("%d\n", n);
    srand(time(0));
    REP(i, 2, n) printf("%d %d %d %d\n", i, rand() % (i - 1) + 1, rand() % 2, rand() % 3);
    return 0;
}
