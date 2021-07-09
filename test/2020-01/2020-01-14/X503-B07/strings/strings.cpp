/***************************************************************
	File name: strings.cpp
	Author: ljfcnyali
	Create time: 2020年01月14日 星期二 08时21分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int T, n, ans;
string s[maxn], S;
bool vis[maxn];

inline int Solve()
{ 
    int sum = 0;
    REP(i, 0, S.length() - 1) if ( i + 2 < S.length() && S[i] == 'S' && S[i + 1] == 'A' && S[i + 2] == 'D' ) ++ sum;
    return sum;
}

inline void DFS(int x)
{
    if ( x == n + 1 ) 
    {
        ans = max(ans, Solve());
        return ;
    }
    REP(i, 1, n) if ( !vis[i] ) 
    {
        vis[i] = true;
        string t = S; S = S + s[i];
        DFS(x + 1);
        S = t; vis[i] = false;
    }
}

int main()
{
    freopen("strings.in", "r", stdin);
    freopen("strings.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n); ans = 0;
        REP(i, 1, n) cin >> s[i];
        DFS(1);
        printf("%d\n", ans);
    }
    return 0;
}
