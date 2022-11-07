/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 21时00分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2010;
const int INF = 0x3f3f3f3f;

int n, k, a[maxn][maxn], Min[maxn][3], Max[maxn][3], ans, sum, x;
int p[maxn];
bool vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    REP(i, 1, n) Min[i][1] = Min[i][2] = INF;
    REP(i, 1, n)
    {
        getchar();
        REP(j, 1, n)
        {
            char c = getchar(); 
            if ( c == 'B' ) 
            {
                a[i][j] = 1;
                Min[i][1] = min(Min[i][1], j);
                Max[i][1] = max(Max[i][1], j);
                Min[j][2] = min(Min[j][2], i);
                Max[j][2] = max(Max[j][2], i);
            }
        }
    }
    REP(i, 1, n) { if ( !Max[i][1] ) ++ x; if ( !Max[i][2] ) ++ x; }
    REP(i, 1, n - k + 1)
    {
        REP(j, 1, n) if ( Max[j][2] && i <= Min[j][2] && Max[j][2] <= i + k - 1 ) vis[j] = true; else vis[j] = false;
        sum = 0;
        REP(j, 1, k) if ( vis[j] ) ++ sum;
        mem(p);
        REP(j, i, i + k - 1) 
        {
            if ( Max[j][1] && (Max[j][1] - Min[j][1] + 1) <= k ) 
            {
                int X = max(1, min(Max[j][1] - k + 1, Min[j][1]));
                ++ p[X]; -- p[Min[j][1] + 1];
            }
        }
        REP(j, 1, n) p[j] += p[j - 1];
        // REP(j, 1, n) printf("%d ", p[j]); puts("");
        ans = max(ans, sum + p[1]);
        REP(j, 2, n - k + 1)
        {
            if ( vis[j - 1] ) -- sum; if ( vis[j + k - 1] ) ++ sum;
            // sum -= p[j - 1]; sum += p[j + k - 1];
            ans = max(ans, sum + p[j]);
        }
    }
    printf("%d\n", ans + x);
    return 0;
}
