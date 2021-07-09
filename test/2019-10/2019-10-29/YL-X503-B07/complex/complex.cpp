/***************************************************************
	File name: complex.cpp
	Author: ljfcnyali
	Create time: 2019年10月29日 星期二 09时46分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, a[maxn], b[maxn];

namespace Subtask1
{
    int num, sum[1010];

    inline bool Check(int len)
    {
        mem(sum); num = 0;
        int ret = b[len];
        REP(i, 1, len)
        {
            ++ sum[a[i]];
            if ( sum[a[i]] == 1 ) ++ num;
            if ( sum[a[i]] == ret ) -- num;
        }
        if ( !num ) return true;
        REP(i, len + 1, n)
        {
            ++ sum[a[i]];
            if ( sum[a[i]] == 1 ) ++ num;
            if ( sum[a[i]] == ret ) -- num;
            -- sum[a[i - len]];
            if ( !sum[a[i - len]] ) -- num;
            if ( sum[a[i - len]] == ret - 1 ) ++ num;
            if ( !num ) return true;
        }
        return false;
    }

    inline int main()
    {
        for ( int i = n; i >= 1; -- i ) if ( Check(i) ) { printf("%d\n", i); return 0; }
        printf("0\n");
        return 0;
    }
}

namespace Subtask2
{
    int sum[maxn];

    inline int Solve(int L, int R, int x)
    {
        if ( L > R ) return 0;
        REP(i, L, R) sum[a[i]] = 0;
        REP(i, L, R) ++ sum[a[i]];
        int last = L, ans = 0;
        REP(i, L, R)
            if ( sum[a[i]] < x ) 
            {
                ans = max(ans, Solve(last, i - 1, x));
                last = i + 1;
            }
        if ( last == L ) ans = R - L + 1;
        else ans = max(ans, Solve(last, R, x));
        return ans;
    }

    inline int Check(int x)
    {
        return Solve(1, n, x);
    }

    inline int main()
    {
        int L = 1, R = n, ans = 0;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1, val = Check(b[Mid]);
            if ( val >= Mid ) { ans = val; L = Mid + 1; }
            else R = Mid - 1;
        }
        printf("%d\n", ans);
        return 0;
    }
}

int main()
{
    freopen("complex.in", "r", stdin);
    freopen("complex.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) scanf("%d", &b[i]);
    if ( n <= 1500 ) return Subtask1 :: main();
    return Subtask2 :: main();
}
