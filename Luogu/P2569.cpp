/***************************************************************
	File name: P2569.cpp
	Author: ljfcnyali
	Create time: 2019年07月30日 星期二 19时53分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2010;
const int INF = 0x3f3f3f3f;

int f[maxn][maxn], n, MaxP, w, AP[maxn], BP[maxn], AS[maxn], BS[maxn], ans;

struct node
{
    int pos, val;
} p1, p2;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &MaxP, &w);
    REP(i, 1, n) scanf("%d%d%d%d", &AP[i], &BP[i], &AS[i], &BS[i]);
    memset(f, -0x3f, sizeof(f));
    REP(i, 1, n) REP(j, 0, AS[i]) f[i][j] = -AP[i] * j;
    REP(i, 1, n)
    {
        deque<node> Q;
        REP(j, 0, MaxP)
        {
            f[i][j] = max(f[i][j], f[i - 1][j]);
            if ( i - w <= 1 ) continue ; 
            if ( !Q.empty() ) f[i][j] = max(f[i][j], Q.front().val - j * AP[i]);
            p1.pos = j; p1.val = f[i - w - 1][j] + j * AP[i];
            while ( !Q.empty() && Q.front().pos <= j - AS[i] ) Q.pop_front();
            while ( !Q.empty() && Q.back().val <= p1.val ) Q.pop_back();
            Q.push_back(p1);
        }
        if ( i - w <= 1 ) continue ;
        while ( !Q.empty() ) Q.pop_back();
        for ( int j = MaxP; j >= 0; -- j )
        {
            if ( !Q.empty() ) f[i][j] = max(f[i][j], Q.front().val - j * BP[i]);
            p1.pos = j; p1.val = f[i - w - 1][j] + j * BP[i];
            while ( !Q.empty() && Q.front().pos >= j + BS[i] ) Q.pop_front();
            while ( !Q.empty() && Q.back().val <= p1.val ) Q.pop_back();
            Q.push_back(p1);
        }
    }
    REP(i, 0, MaxP) ans = max(ans, f[n][i]); 
    printf("%d\n", ans);
    return 0;
}
