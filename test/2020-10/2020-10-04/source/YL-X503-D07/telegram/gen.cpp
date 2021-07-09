/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月04日 星期日 09时09分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[maxn];

int main()
{
    freopen("telegram.in", "w", stdout);
    int n = 500; printf("%d\n", n);
    srand(time(0));
    REP(i, 1, n) a[i] = rand() % 100000000 + 1;
    REP(i, 1, n) REP(j, 1, i - 1) printf("%d ", a[i] + a[j]); puts("");
    return 0;
}
