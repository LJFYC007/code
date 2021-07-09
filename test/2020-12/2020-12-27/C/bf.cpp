/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年12月27日 星期日 10时32分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, k, h[maxn], a[maxn];
struct node { int sum1, sum2, sum, ans, lazy, vis; } Tree[maxn << 2];

/*
inline void Modify(int root, int l, int r, int pos, int val)
{
    if ( l == r ) 
    { 
        Tree[root].sum = Tree[root].ans = val; 
        Tree[root].vis = abs(val) > k;
        if ( val < k ) Tree[root].sum1 = k - val;
        if ( val > -k ) Tree[root].sum2 = val + k;
        return ; 
    }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    PushUp(root);
}
*/

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, n) { scanf("%lld", &h[i]); a[i] = h[i] - h[i - 1]; }
    // REP(i, 1, n) cout << a[i] << " "; cout << endl;
    // REP(i, 1, n) Modify(1, 1, n, i, a[i]);
    while ( m -- ) 
    {
        int op, l, r, c; scanf("%lld%lld%lld", &op, &l, &r);
        if ( op == 1 ) 
        {
            int sum = 0, ans = 0; REP(i, 1, l - 1) sum += a[i];
            REP(i, l, r) { sum += a[i]; ans += sum; }
            printf("%lld\n", ans);
        }
        else if ( op == 2 ) 
        {
            scanf("%lld", &c);
            a[l] += c; a[r + 1] -= c;
        }
        else if ( op == 3 ) 
        {
            REP(i, l + 1, r)
            {
                if ( abs(a[i]) <= k ) continue ;
                if ( a[i] > k ) 
                {
                    REP(j, i + 1, r) if ( a[j] < k ) 
                    {
                        int t = min(a[i] - k, k - a[j]);
                        a[i] -= t; a[j] += t; 
                        if ( a[i] == k ) break ; 
                    }
                    a[r + 1] += a[i] - k; a[i] = k;
                }
                else 
                {
                    for ( int j = i - 1; j > l; -- j ) if ( a[j] > -k ) 
                    {
                        int t = min(-k - a[i], a[j] + k);
                        a[i] += t; a[j] -= t;
                        if ( a[i] == -k ) break ; 
                    }
                    a[l] -= -k - a[i]; a[i] = -k;
                }
            }
        }
    }
    return 0;
}
