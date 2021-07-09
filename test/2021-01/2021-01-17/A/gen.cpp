/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年01月17日 星期日 09时07分11秒
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
    freopen("input.txt", "w", stdout);
    int n = rand() % 5000 + 1, m = rand() % 5000 + 1, q = rand() % 5000 + 1;
    // int n, m, q; n = m = q = 500000; 
    srand(time(0));
    printf("%d %d %d\n", n, m, q);
    REP(i, 1, n) printf("%d ", rand() % (m + 1)); puts("");
    REP(i, 1, q)
    {
        int l = rand() % n + 1, r = rand() % n + 1;
        printf("%d %d %d %d\n", rand() % 2 + 1, min(l, r), max(l, r), rand() % m + 1);
    }
    return 0;
}
