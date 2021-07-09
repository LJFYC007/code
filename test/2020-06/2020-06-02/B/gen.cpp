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

int L[maxn], R[maxn];

int main()
{
    freopen("B.in", "w", stdout);
    srand(time(0));
    int n = 100000, m = 100000;
    printf("%d %d\n", n, m);
    REP(i, 1, n) printf("%d ", rand() % n + 1); puts("");
    printf("0 1\n");
    REP(i, 2, n) 
    { 
        int u = i, v = max(1, i - 2);
        printf("%d %d\n", u, v);
    }
    while ( m -- ) 
    {
        int op = rand() % 2 + 1, l = rand() % n + 1, r = rand() % n + 1;
        if ( l > r ) swap(l, r);
        printf("%d %d %d\n", op, l, r);
    }
    return 0;
}
