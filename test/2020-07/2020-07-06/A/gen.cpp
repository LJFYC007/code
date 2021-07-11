/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月06日 星期一 20时12分00秒
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
    int n = 100000; printf("%d\n", n);
    REP(i, 2, n) printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % 10 + 1);
    puts("");
    REP(i, 2, n) printf("%d %d %d\n", i, rand() % (i - 1) + 1, rand() % 10 + 1);
    return 0;
}