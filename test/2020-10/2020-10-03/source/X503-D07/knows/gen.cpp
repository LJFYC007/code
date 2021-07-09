/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月03日 星期六 11时24分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int a[maxn];

int main()
{
    freopen("knows.in", "w", stdout);
    srand(time(0));
    int n = 200000; printf("%d\n", n);
    REP(i, 1, n) a[i] = i; random_shuffle(a + 1, a + n + 1);
    REP(i, 1, n) printf("%d ", a[i]); puts("");
    REP(i, 1, n) printf("%d ", rand() % 10000 + 1); puts("");
    return 0;
}
