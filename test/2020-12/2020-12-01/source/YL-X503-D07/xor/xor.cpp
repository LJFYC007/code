/***************************************************************
	File name: xor.cpp
	Author: ljfcnyali
	Create time: 2020年12月01日 星期二 11时11分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
int a[4][4];

int main()
{
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    REP(i, 1, (1 << n) - 1) { REP(j, 1, (1 << m) - 1) printf("%d", (i + j) % 2 ^ 1); puts(""); }
    return 0;
}
