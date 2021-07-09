/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年08月11日 星期二 09时34分26秒
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
    freopen("B.in", "w", stdout);
    srand(time(0));
    int n = 500000; REP(i, 1, n) printf("%c", rand() % 10 + 'a'); puts("");
    int q = 500000;
    printf("%d\n", q);
    REP(i, 1, q)
    {
        int l = rand() % n + 1, r = rand() % n + 1;
        printf("%d %d\n", min(l, r), max(l, r));
    }
    return 0;
}
