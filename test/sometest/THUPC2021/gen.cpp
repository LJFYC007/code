/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年12月12日 星期六 13时18分41秒
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
    freopen("input.txt", "w", stdout);
    int n = rand() % 20 + 10, k = 3; printf("%d %d\n", n, k);
    // srand(time(0));
    // REP(i, 1, n) REP(j, 1, n) if ( i != j ) printf("%d %d %d %d\n", i, j, rand(), rand());
    return 0;
}
