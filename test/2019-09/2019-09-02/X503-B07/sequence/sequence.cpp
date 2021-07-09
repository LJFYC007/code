/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2019年09月02日 星期一 20时15分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1010;

int n, m, a[maxn], L, R; 
bool use[maxn][maxn], vis[maxn];

struct node
{
    int L, R, len;
} ans[maxn][maxn];

int main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);    
    REP(i, 1, n)
    {
        L = n + 1; R = 0; mem(vis);
        REP(j, i, n)
        {
            vis[a[j]] = true;
            L = min(L, a[j]); R = max(R, a[j]);
            if ( R - L == j - i ) use[i][j] = true;
        }
    }
    memset(ans, 0x3f, sizeof(ans));
    for ( int l = n; l >= 1; -- l )
        REP(i, 1, n - l + 1)
        {
            int j = i + l - 1;
            if ( use[i][j] ) ans[i][j].L = i, ans[i][j].R = j, ans[i][j].len = l;
            else
            {
                if ( ans[i - 1][j].len < ans[i][j + 1].len ) ans[i][j] = ans[i - 1][j];
                else ans[i][j] = ans[i][j + 1];
            }
        }
    scanf("%d", &m);
    REP(i, 1, m)
    {
        scanf("%d%d", &L, &R);
        printf("%d %d\n", ans[L][R].L, ans[L][R].R);
    }
    return 0;
}
