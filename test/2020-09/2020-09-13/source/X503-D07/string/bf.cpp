/***************************************************************
	File name: string.cpp
	Author: ljfcnyali
	Create time: 2020年09月13日 星期日 08时50分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, f[maxn];
char s[maxn], t[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline void Merge(int a, int b)
{
    int fx = find(a), fy = find(b);
    if ( fx != fy ) f[fx] = fy;
}

int main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    scanf("%s", s + 1); n = str(s + 1);
    scanf("%d", &m);
    REP(i, 1, n) f[i] = i;
    REP(i, 1, m)
    {
        int a, b, l; scanf("%d%d%d", &a, &b, &l);
        REP(j, 1, l) Merge(a + j - 1, b + j - 1);
    }
    REP(i, 1, n) if ( s[i] == '1' ) t[find(i)] = '1';    
    REP(i, 1, n) printf("%d", t[find(i)] == '1' ? 1 : 0); puts(""); 
    return 0;
}
