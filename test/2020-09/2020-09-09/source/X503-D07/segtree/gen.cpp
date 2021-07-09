/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年09月09日 星期三 21时03分39秒
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
    freopen("segtree.in", "w", stdout);
    srand(time(0));
    int n = 3000, m = 3000; printf("%d\n", n);
    REP(i, 1, n) printf("%d ", rand() % 200000 + 1); puts("");
    printf("%d\n", m);
    REP(i, 1, m)
    {
        int op = rand() % 2 + 1, l = rand() % n + 1, r = rand() % n + 1, x = rand() % 200000 + 1;
        printf("%d %d %d %d ", op, l, r, x);
        if ( op == 2 ) printf("%d\n", rand() % 100 + 1);
        else puts("");
    }
    return 0;
}
