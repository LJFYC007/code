/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年01月17日 星期日 09时06分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, q, a[maxn], b[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q); REP(i, 1, n) scanf("%d", &a[i]);
    while ( q -- ) 
    {
        int op, l, r, x; scanf("%d%d%d%d", &op, &l, &r, &x);
        if ( op == 1 ) REP(i, l, r) a[i] = x;
        else REP(i, l, r) b[a[i]] += x;
    }
    REP(i, 1, m) printf("%d\n", b[i]);
    return 0;
}
