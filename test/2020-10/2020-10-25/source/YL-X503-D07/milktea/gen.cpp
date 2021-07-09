/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月25日 星期日 10时06分15秒
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
    freopen("milktea.in", "w", stdout);
    int n = 200000, m = n, k = n;
    srand(time(0));
    printf("%d %d %d\n", n, m, k);
    REP(i, 1, n) printf("%d ", rand() % 2000 - 1000); puts("");
    REP(i, 1, m)
    {
        int op = rand() % 2 + 1, l = rand() % n + 1, r = rand() % n + 1;
        if ( l > r ) swap(l, r);
        if ( op == 1 ) printf("%d %d %d %d\n", op, l, r, rand() % 2000 - 1000);
        else printf("%d %d %d\n", op, l, r);
    }
    REP(i, 1, k) { int l = rand() % m + 1, r = rand() % m + 1; printf("%d %d\n", min(l, r), max(l, r)); }
    return 0;
}
