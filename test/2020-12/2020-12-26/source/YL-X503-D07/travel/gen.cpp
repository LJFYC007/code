/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年12月26日 星期六 15时12分22秒
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
    int n = 1000; printf("%d 50000 50000\n", n);
    srand(time(0));
    REP(i, 2, n) printf("%d %d\n", i ,rand() % (i - 1) + 1);
    return 0;
}
