/***************************************************************
	File name: match.cpp
	Author: ljfcnyali
	Create time: 2020年11月13日 星期五 08时16分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int unsigned long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

LL S, P, T, n;
int a[maxn], tot;
__int128 t[maxn];
pii Stack[maxn];

int rnd() 
{
    S^=S<<13,S^=S>>17,S^=S<<5;
    return (S%P+P)%P;
}

inline int get(__int128 l, __int128 r) { return (l + r) * (r - l + 1) / 2; }

signed main()
{
    freopen("match.in", "r", stdin);
    freopen("match.out", "w", stdout);
    scanf("%lld%lld", &S, &P);
    scanf("%lld", &T); 
    while ( T -- ) 
    {
        scanf("%lld", &n); 
        REP(i, 1, n) a[i] = rnd();
        mem(t); tot = 1; Stack[1] = pii(0, 0); a[n + 1] = 0;
    
        REP(i, 1, n + 1)
        {
            int lst = i;
            while ( Stack[tot].first > a[i] )  
            {
                t[i - Stack[tot].second] += Stack[tot].first - max(a[i], Stack[tot - 1].first);
                lst = Stack[tot].second; -- tot;
            }
            if ( Stack[tot].first < a[i] ) Stack[++ tot] = pii(a[i], lst);
        }
        int ans = 0; __int128 now = 0;
        for ( int i = n; i >= 1; -- i ) 
        {
            ans += get(now + 1, now + t[i]) * i;
            now += t[i];
        }
        printf("%llu\n", ans);
    }
    return 0;
}
