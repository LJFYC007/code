/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年01月16日 星期四 10时03分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int p[200010];

int main()
{
    freopen("seq.in", "w", stdout);
    srand(time(0));
    int n = 200000; printf("%d\n", n);
    REP(i, 1, n) p[i] = i;
    random_shuffle(p + 1, p + n + 1);
    REP(i, 1, n) printf("%d ", p[i]); puts("");
    return 0;
}
