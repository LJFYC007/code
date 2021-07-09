/***************************************************************
	File name: chk.cpp
	Author: ljfcnyali
	Create time: 2020年08月08日 星期六 10时46分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[maxn], b[maxn], ans[maxn];

int main()
{
    freopen("group.in", "r", stdin);
    int n; scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &a[i], &b[i]);
    freopen("group.out", "r", stdin);
    char c;
    REP(i, 1, 2 * n) { c = getchar(); ans[i] = c - '0'; }
    int sum = 0;
    REP(i, 1, 2 * n) sum += ans[i] - 1;
    if ( sum != n ) { puts("WA"); exit(-1); }
    REP(i, 1, n) if ( ans[a[i] + 1] == ans[b[i] + 1] ) { cerr << a[i] << " " << b[i] << endl; puts("WA"); exit(-1); }
    puts("YES");
    return 0;
}
