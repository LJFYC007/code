/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年09月09日 星期三 22时17分54秒
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
    freopen("travel.in", "w", stdout);
    int n = 300, m = 1000, q = 500; printf("%d %d %d\n", n, m, q);
    REP(i, 2, n) printf("%d ", rand() % (i - 1) + 1); puts("");
    REP(i, 1, n) printf("%d ", rand() % m + 1); puts("");
    REP(i, 1, q)
    {
        int x = 5;
        // int x = rand() % 4 + 2;
        printf("%d ", x);
        REP(j, 1, x) printf("%d ", rand() % n + 1); puts("");
    }
    return 0;
}
