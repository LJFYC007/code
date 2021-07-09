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
    freopen("C.in", "w", stdout);
    srand(time(0));
    int n = 70000, m = 70000;
    printf("%d %d\n", n, m);
    REP(i, 2, n) 
    { 
        int u = i, v = 1, l = rand() % n + 1, r = rand() % n + 1;  
        if ( l > r ) swap(l, r);
        printf("%d %d %d %d\n", u, v, l, r);
    }
    REP(i, 1, m) printf("%d\n", i);
    return 0;
}
