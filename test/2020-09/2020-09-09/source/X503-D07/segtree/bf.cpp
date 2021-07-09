/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年09月09日 星期三 21时00分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], m, b[maxn];

int main()
{
    freopen("segtree.in", "r", stdin);
    freopen("segtree1.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    scanf("%d", &m);
    while ( m -- ) 
    {
        int op, l, r, x, k; scanf("%d%d%d%d", &op, &l, &r, &x);
        if ( op == 1 ) REP(i, l, r) a[i] = max(a[i], x);
        else
        {
            int num = 0; scanf("%d", &k);
            REP(i, l, r) if ( a[i] < x ) b[++ num] = a[i];
            if ( num < k ) puts("-1");
            else
            {
                sort(b + 1, b + num + 1);
                REP(i, 1, k) printf("%d ", b[i]); puts("");
            }
        }
    }
    return 0;
}
