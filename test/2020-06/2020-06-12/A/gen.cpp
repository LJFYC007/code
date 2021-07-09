/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年05月24日 星期日 10时25分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

bool vis[maxn];

int main()
{
    freopen("A.in", "w", stdout);
    srand(time(0));
    int n = 200000, m = 10000; printf("%d %d\n", n, m);
    REP(i, 1, n) printf("%d ", rand() % 1000000 + 1); puts("");
    REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    return 0;
}
