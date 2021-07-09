/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年09月19日 星期六 09时27分35秒
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
    freopen("elysium.in", "w", stdout);
    // int n = 5, m = 4; printf("%d %d\n", n, m);
    int n = 500000, m = 500000; printf("%d %d\n", n, m);
    srand(time(0));
    REP(i, 2, n) printf("%d ", rand() % (i - 1) + 1); puts("");
    REP(i, 1, n) printf("%d ", rand() % 100 + 1); puts("");
    REP(i, 1, m) printf("%d %d %d\n", rand() % n + 1, rand() % 5, rand() % 100 + 1); 
    return 0;
}
