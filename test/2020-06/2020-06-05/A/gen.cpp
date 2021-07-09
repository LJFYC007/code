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
    freopen("A.in", "w", stdout);
    srand(time(0));
    int n = 200000, m = 200000; printf("%d %d\n", n, m);
    int N = 1000000;
    REP(i, 1, n) printf("%d ", i); puts("");
    // REP(i, 1, n) printf("%d ", rand() % (N + 1)); puts("");
    REP(i, 1, n) printf("%d ", rand() % (2 * N) - N); puts("");
    REP(i, 1, m) 
    {
        int op = rand() % 2 + 1;
        if ( op == 2 ) printf("2 %d %d\n", rand() % n + 1, rand() % n + 1);
        else
        {
            printf("1 %d %d\n", rand() % n + 1, rand() % (2 * N) - n);
        }
    }
    return 0;
}
