/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年01月12日 星期二 09时51分55秒
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
    freopen("relics.in", "w", stdout);
    int n = 9, m = 30; printf("%d %d\n", n, m);
    srand(time(0));
    REP(i, 1, n) printf("%d ", rand() % 5 + 1); puts("");
    REP(i, 1, m)
    {
        int l = rand() % n + 1, r = rand() % n + 1;
        printf("%d %d\n", min(l, r), max(l, r));
    }
    return 0;
}
