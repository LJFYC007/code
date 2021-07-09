/***************************************************************
	File name: P4767.cpp
	Author: ljfcnyali
	Create time: 2019年09月19日 星期四 10时28分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 3010;

int f[maxn][310], s[maxn][310], V, P, a[maxn], dis[maxn][maxn], sum[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &V, &P);
    REP(i, 1, V) scanf("%d", &a[i]);
    sort(a + 1, a + V + 1);
    REP(i, 1, V) sum[i] = sum[i - 1] + a[i];
    REP(i, 1, V) REP(j, i, V) 
    {
        int Mid = i + j >> 1;
        dis[i][j] = a[Mid] * (Mid - i + 1) - (sum[Mid] - sum[i - 1]);
        dis[i][j] += sum[j] - sum[Mid] - a[Mid] * (j - Mid);
    }
    memset(f, 0x3f, sizeof(f));
    REP(i, 1, V) f[i][1] = dis[1][i];
    REP(j, 2, P)
    {
        s[V + 1][j] = V;
        for ( int i = V; i >= 1; -- i )
        {
            REP(k, s[i][j - 1], s[i + 1][j]) 
                if ( f[k][j - 1] + dis[k + 1][i] < f[i][j] )
                {
                    f[i][j] = f[k][j - 1] + dis[k + 1][i];
                    s[i][j] = k;
                }
        }
    }
    printf("%d\n", f[V][P]);
    return 0;
 }
