/***************************************************************
	File name: travel.cpp
	Author: ljfcnyali
	Create time: 2020年11月01日 星期日 08时55分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;

int T, a, b, f[maxn], g[maxn];

inline int Skip(int x, int op)
{
    while ( x > 3 && x - (x / 2) * 2 == op ) x /= 2;
    return x;
}

inline pii Solve(int x)
{
    pii ans = pii(0, 0);
    if ( x == 1 ) return pii(-3, 0);
    // int y = x;
    // while ( y ) { cout << y % 2 ; y /= 2; } cout << " ";
    while ( x ) 
    {
        REP(j, 2, 60) 
        {
            if ( x == (1ll << j) ) return pii(-1, ans.y);
            if ( x + 1 == (1ll << j + 1) ) return pii(-2, ans.y);
        }
        int op = x - (x / 2) * 2;
        x = Skip(x, op); x /= 2;
        if ( x == 1 ) break ; ++ ans.y;
    }
    return ans;
}

signed main()
{
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &a, &b);

        int l1 = 0, l2 = 0, t;
        t = a; while ( t ) { f[++ l1] = t % 2; t /= 2; }
        t = b; while ( t ) { g[++ l2] = t % 2; t /= 2; }
        bool flag = false;
        REP(j, 1, min(l1, l2))
        {
            if ( f[l1 - j + 1] != g[l2 - j + 1] )
            {
                l1 = l1 - j + 2; f[l1] = 1;
                l2 = l2 - j + 2; g[l2] = 1;
                flag = true;
                break ; 
            }
        }
        if ( !flag ) 
        {
            int j = min(l1, l2) + 1;
            l1 = l1 - j + 2; f[l1] = 1;
            l2 = l2 - j + 2; g[l2] = 1;
        }
        a = 0; for ( int i = l1; i >= 1; -- i ) a = a * 2 + f[i];
        b = 0; for ( int i = l2; i >= 1; -- i ) b = b * 2 + g[i];
        // cout << a << " " << b << endl;

        pii x = Solve(a), y = Solve(b);
        int ans = INF;
        if ( x.x == -3 || y.x == -3 ) ans = x.y + y.y;
        else if ( x.x < 0 && y.x < 0 ) ans = x.y + y.y + (x.x != y.x);
        else if ( x.x < 0 || y.x < 0 ) ans = x.y + y.y + 1;
        else ans = x.y + y.y;
        printf("%lld\n", ans);
    }
    return 0;
}
