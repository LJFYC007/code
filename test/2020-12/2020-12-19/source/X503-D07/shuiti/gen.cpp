/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年12月19日 星期六 09时34分29秒
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
    freopen("shuiti.in", "w", stdout);
    int n = 150; printf("%d\n", n);
    srand(time(0));
    REP(i, 1, n) { REP(j, 1, n) printf("%d ", i == j ? 0 : rand() % 1000000000); puts(""); }
    REP(i, 1, n) { REP(j, 1, n) printf("%d ", i == j ? 0 : rand() % 1000000000); puts(""); }
    return 0;
}
