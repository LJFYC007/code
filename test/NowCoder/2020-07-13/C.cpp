/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年07月13日 星期一 15时23分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, d[maxn], cnt;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ d[u];}

inline vector<int> DFS(int u, int fa)
{
    vector<vector<int> > a, b; a.clear(); b.clear();
    vector<int> ans;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        ans = DFS(v, u);
        if ( ans.size() == 2 ) a.push_back(ans);
        else b.push_back(ans);
    }
    ans.clear();
    if ( !a.size() && !b.size() ) { ans.push_back(u); return ans; }
    if ( a.size() == 1 )
    {
        if ( !b.size() ) { ans = a[0]; return ans; }
        ++ cnt; printf("%d %d\n", a[0][0], b[0][0]); b[0][0] = a[0][1];
        a.clear();
    }
    int m = a.size(), x = 0;
    if ( m != 0 ) 
    {
        if ( m % 2 == 1 ) x = 3;
        if ( m % 2 == 0 && !b.size() )
        {
            for ( int i = 2; i + 1 < m; i += 2 ) 
            {   
                ++ cnt; printf("%d %d\n", a[i][0], a[i + 1][0]);
                ++ cnt; printf("%d %d\n", a[i][1], a[i + 1][1]);
            }
            ++ cnt; printf("%d %d\n", a[0][0], a[1][0]);
            ans.push_back(a[0][1]);
            ans.push_back(a[1][1]);
            return ans;
        }
        for ( int i = x; i + 1 < m; i += 2 ) 
        {   
            ++ cnt; printf("%d %d\n", a[i][0], a[i + 1][0]);
            ++ cnt; printf("%d %d\n", a[i][1], a[i + 1][1]);
        }

        if ( m % 2 == 1 ) 
        {
            if ( !b.size() )
            {
                ++ cnt; printf("%d %d\n", a[0][0], a[1][0]);
                ++ cnt; printf("%d %d\n", a[0][1], a[2][0]);
                ans.push_back(a[1][1]);
                ans.push_back(a[2][1]);
                return ans;
            }
            ++ cnt; printf("%d %d\n", a[0][0], a[1][0]);
            ++ cnt; printf("%d %d\n", a[1][1], a[2][0]);
            ++ cnt; printf("%d %d\n", a[0][1], a[2][1]);
        }
    }

    if ( b.size() % 2 == 0 ) 
    {
        ans.push_back(b[0][0]);
        ans.push_back(b[1][0]);
        for ( int i = 2; i + 1 < b.size(); i += 2 ) 
        {
            ++ cnt; printf("%d %d\n", b[i][0], b[i + 1][0]);
        }
    }
    else
    {
        ans.push_back(b[0][0]);
        for ( int i = 1; i + 1 < b.size(); i += 2 ) 
        {
            ++ cnt; printf("%d %d\n", b[i][0], b[i + 1][0]);
        }
    }
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    if ( n == 1 ) { puts("0"); return 0; }
    if ( n == 2 ) { printf("1\n1 2\n"); return 0; }
    int Root;
    REP(i, 1, n) if ( d[i] > 1 ) { Root = i; break ; }
    int num = 0;
    REP(i, 1, n) if ( d[i] == 1 ) ++ num;
    printf("%d\n", (num + 1) / 2);
    vector<int> a = DFS(Root, 0);
    if ( a.size() == 1 ) { ++ cnt; printf("%d %d\n", Root, a[0]); }
    else { ++ cnt; printf("%d %d\n", a[0], a[1]); }
    assert(cnt == (num + 1) / 2);
    return 0;
}
