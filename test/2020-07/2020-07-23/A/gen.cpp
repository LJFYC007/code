/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月23日 星期四 10时08分52秒
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
    freopen("A.in", "w", stdout);
    srand(time(0));
    int n = 15, m = 15, q = 15; printf("%d %d %d\n", n, m, q);
    REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    REP(i, 1, q) printf("%d %d %d\n", 2, 5, 3);
    return 0;
}
