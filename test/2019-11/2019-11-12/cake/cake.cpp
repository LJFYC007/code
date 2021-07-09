/***************************************************************
	File name: cake.cpp
	Author: ljfcnyali
	Create time: 2019年11月12日 星期二 08时57分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;

int T, n, m, a[maxn], b[maxn], N, M, ans;

inline void Solve(int L, int R)
{
    if ( -m <= L && R <= m ) 
    {
        REP(i, 1, N) if ( abs(a[i]) > m ) ++ ans;
        ans += 2; return ;
    }
    if ( L < -m && m < R )
    {
        REP(i, 1, N) 
        {
            int x = i == 1 ? -n : a[i - 1], y = a[i];
            // printf("%d %d\n", x, y);
            if ( -m <= x && y <= m ) ans += 2;
            else ++ ans;
        }
        ++ ans;
        return ;
    }
    ans += N + 1;
}

signed main()
{
    freopen("cake.in", "r", stdin);
    freopen("cake.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld%lld%lld", &n, &m, &N, &M);
        REP(i, 1, N) scanf("%lld", &a[i]);
        REP(i, 1, M) scanf("%lld", &b[i]);
        sort(a + 1, a + N + 1);
        sort(b + 1, b + M + 1);
        ans = 0;
        REP(i, 1, M)
        {
            int L = i == 1 ? -n : b[i - 1];
            int R = b[i]; Solve(L, R);
        }
        if ( !M ) Solve(-n, n); 
        else Solve(b[M], n);
        printf("%lld\n", ans);
    }
    return 0;
}

