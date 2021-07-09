/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月02日 星期一 11时16分25秒
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
    int n = 500000, m = n - 1, k = n / 5;
    printf("%d %d %d\n", n, m, k);
    REP(i, 1, n) printf("1 "); puts("");
    REP(i, 1, n - 1) printf("%d %d\n", i, i + 1);
    return 0;
}
