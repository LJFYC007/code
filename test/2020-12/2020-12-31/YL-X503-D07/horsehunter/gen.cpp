/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年12月31日 星期四 10时25分05秒
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
    freopen("horsehunter.in", "w", stdout);
    srand(time(0));
    int n = rand() % 10000 + 1, q = rand() % 10000 + 1; printf("%d %d\n", n, q);
    REP(i, 1, n) printf("%d ", rand() % 100000 + 1); puts("");
    while ( q -- ) printf("%d %d\n", rand() % n + 1, rand() % 100000 + 1);
    return 0;
}
