/***************************************************************
	File name: amino.cpp
	Author: ljfcnyali
	Create time: 2021年01月11日 星期一 08时35分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned int 
typedef long long LL;

const int maxn = 1e5 + 10;

int L, l1, l2, q, f[20010][1 << 9], ans;
char s[20];

inline void DFS1(int x, int now, int val, int w)
{
    if ( x == l1 + 1 ) { f[now][val] += w; return ; }
    DFS1(x + 1, now * 3 + s[x] - '0', val, w);
    DFS1(x + 1, now * 3 + 2, val, w);
}

inline void DFS2(int x, int now, int val)
{
    if ( x == l2 + 1 ) { ans += f[val][now]; return ; } 
    if ( s[l1 + x] == '*' ) { DFS2(x + 1, now * 2, val); DFS2(x + 1, now * 2 + 1, val); }
    else DFS2(x + 1, now * 2 + s[l1 + x] - '0', val);
}

signed main()
{
    freopen("amino.in", "r", stdin);
    freopen("amino.out", "w", stdout);
    scanf("%d%d", &L, &q); l1 = L / 2; l2 = L - l1;
    while ( q -- ) 
    {
        char c = getchar(); while ( c != 'I' && c != 'Q' ) c = getchar();
        getchar(); REP(i, 1, L) s[i] = getchar();
        if ( c == 'I' ) 
        {
            int val = 0, w; scanf("%d", &w);
            REP(i, l1 + 1, l1 + l2) val = val * 2 + (s[i] - '0');
            DFS1(1, 0, val, w);
        }
        else
        {
            ans = 0;
            int val = 0; REP(i, 1, l1) val = val * 3 + (s[i] == '*' ? 2 : s[i] - '0');
            DFS2(1, 0, val);
            printf("%u\n", ans); 
        }
    }
    return 0;
}
