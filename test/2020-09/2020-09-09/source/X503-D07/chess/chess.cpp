/***************************************************************
	File name: chess.cpp
	Author: ljfcnyali
	Create time: 2020年09月09日 星期三 19时04分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int T, n, q, sumx[maxn], sumy[maxn], A[maxn], B[maxn];
struct node 
{ 
    int x, y; 
    node (int a = 0, int b = 0) { x = a; y = b; }
} a[maxn];

signed main()
{
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &q);
        REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); a[i] = node(a[i].x - a[i].y, a[i].x + a[i].y); }
        REP(i, 1, n) { A[i] = a[i].x; B[i] = a[i].y; }
        sort(A + 1, A + n + 1); sort(B + 1, B + n + 1);
        REP(i, 1, n) { sumx[i] = sumx[i - 1] + A[i]; sumy[i] = sumy[i - 1] + B[i]; }
        REP(i, 1, q)
        {
            node t; scanf("%lld%lld", &t.x, &t.y);
            t = node(t.x - t.y, t.x + t.y);
            int ans = 0, pos = lower_bound(A + 1, A + n + 1, t.x) - A - 1;
            ans += t.x * pos - sumx[pos] + sumx[n] - sumx[pos] - t.x * (n - pos);
            pos = lower_bound(B + 1, B + n + 1, t.y) - B - 1;
            ans += t.y * pos - sumy[pos] + sumy[n] - sumy[pos] - t.y * (n - pos);
            printf("%lld\n", ans / 2);
        }
    }
    return 0;
}
