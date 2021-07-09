/***************************************************************
	File name: rotate.cpp
	Author: ljfcnyali
	Create time: 2019年09月04日 星期三 19时24分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int n, a[maxn], ans, sum[maxn][2];
vector<int> p[maxn];

int main()
{
    freopen("rotate.in", "r", stdin);
    freopen("rotate.out", "w", stdout);
    scanf("%d", &n);
    for ( int i = 1; i <= 2 * n - 1; i += 2 )
    {
        scanf("%d", &a[i]); a[i] = a[i] * 2 - 1;
    }
    for ( int i = 1; i <= 2 * n - 1; i += 2 )
    {
        if ( a[i] == i ) sum[i][0] = sum[i][1] = 1;
        int x = (a[i] + i) / 2;
        p[x].push_back(abs(a[i] - i) / 2);
    }
    REP(i, 1, 2 * n - 1) sum[i][0] += sum[i - 1][0];
    for ( int i = 2 * n - 1; i >= 1; -- i ) sum[i][1] += sum[i + 1][1];
    REP(i, 1, 2 * n - 1)
    {
        sort(p[i].begin(), p[i].end());
        REP(j, 0, p[i].size() - 1)
            ans = max(ans, j + 1 + sum[i - p[i][j] - 1][0] + sum[i + p[i][j] + 1][1]);
    }
    printf("%d\n", ans);
    return 0;
}
