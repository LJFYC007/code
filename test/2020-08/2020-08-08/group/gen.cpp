/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年08月08日 星期六 10时44分46秒
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
    freopen("group.in", "w", stdout);
    int n = 40; printf("%d\n", n);
    srand(time(0));
    REP(i, 1, 2 * n) a[i] = i - 1;
    random_shuffle(a + 1, a + 2 * n + 1);
    REP(i, 1, n) printf("%d %d\n", a[2 * i - 1], a[2 * i]);
    return 0;
}
