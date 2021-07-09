/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2019年10月16日 星期三 09时15分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3010;
const int maxm = 1e5 + 10;

int a[maxn][maxn], n, m, k, sum[maxm], Max, p[maxn];
LL ans = 0;
bool flag = true;

namespace Subtask1
{
    inline int main()
    {
        REP(o, 1, n - k + 1)
        {
            int cnt = 0; mem(sum);
            REP(i, o, o + k - 1) REP(j, 1, k) { ++ sum[a[i][j]]; if ( sum[a[i][j]] == 1 ) ++ cnt; }
            Max = max(Max, cnt); ans += cnt;
            REP(j, k + 1, m)
            {
                REP(i, o, o + k - 1)
                {
                    -- sum[a[i][j - k]]; if ( !sum[a[i][j - k]] ) -- cnt;
                    ++ sum[a[i][j]]; if ( sum[a[i][j]] == 1 ) ++ cnt;
                }
                Max = max(Max, cnt); ans += cnt;
            }
        }
        printf("%d %lld\n", Max, ans);
        return 0;
    }
}

namespace Subtask2
{
    int f[maxn][maxn][3];

    inline int main()
    {
        REP(j, 1, m) 
        {
            REP(i, 1, k) ++ f[1][j][a[i][j]];
            REP(i, 2, n - k + 1)
            {
                f[i][j][1] = f[i - 1][j][1]; f[i][j][2] = f[i - 1][j][2];
                -- f[i][j][a[i - 1][j]]; ++ f[i][j][a[i + k - 1][j]];
            }
        }
        int cnt = 0;
        REP(i, 1, k) REP(j, 1, k) ++ p[a[i][j]]; 
        cnt = (p[1] ? 1 : 0) + (p[2] ? 1 : 0);
        REP(o, 1, n - k + 1)
        {
            if ( o != 1 ) 
            {
                REP(j, 1, k) { -- p[a[o - 1][j]]; ++ p[a[o + k - 1][j]]; }
                cnt = (p[1] ? 1 : 0) + (p[2] ? 1 : 0);
            }
            Max = max(Max, cnt); ans += cnt;
            REP(j, 1, 2) sum[j] = p[j];
            REP(j, k + 1, m)
            {
                sum[1] -= f[o][j - k][1]; sum[2] -= f[o][j - k][2];
                sum[1] += f[o][j][1]; sum[2] += f[o][j][2];
                cnt = (sum[1] ? 1 : 0) + (sum[2] ? 1 : 0);
                Max = max(Max, cnt); ans += cnt;
            }
        }
        printf("%d %lld\n", Max, ans);
        return 0;
    }
}

namespace Subtask3
{
    inline int main()
    {
        LL ans = (n - k + 1) * (m - k + 1);
        ans = ans * k * k;
        printf("%d %lld\n", k * k, ans);
        return 0;
    }
}

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, n) REP(j, 1, m) 
    {
        read(a[i][j]);
        if ( a[i][j] > 2 ) flag = false;
    }
    if ( n <= 500 ) return Subtask1 :: main();
    else if ( flag == true ) return Subtask2 :: main();
    else return Subtask3 :: main();
    return 0;
}
