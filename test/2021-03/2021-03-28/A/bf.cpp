/***************************************************************
    File name: A.cpp
    Author: ljfcnyali
    Create time: 2021年03月28日 星期日 08时54分29秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;
 
const int maxn = 1e5 + 10;
 
int n, m, match[maxn], ans;
pii a[maxn], b[maxn];
bool vis[maxn];
 
inline bool DFS(int x)
{
    if ( vis[x] ) return false; vis[x] = true;
    REP(i, 1, n) if ( a[i].x <= b[x].x && a[i].y <= b[x].y ) 
    {
        if ( !match[i] || DFS(match[i]) ) 
        {
            match[i] = x;
            return true;
        }
    }
    return false;
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y); sort(a + 1, a + n + 1);
    REP(i, 1, m) scanf("%d%d", &b[i].x, &b[i].y);
    REP(i, 1, m) { mem(vis); if ( DFS(i) ) ++ ans; printf("%d ", ans); } puts("");
    return 0;
}
