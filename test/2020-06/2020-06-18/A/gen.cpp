/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年06月18日 星期四 10时47分48秒
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
    int n = 50, m = 100;
    printf("%d %d %d\n", n, m, 0);
    REP(i, 1, m) printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    return 0;
}
