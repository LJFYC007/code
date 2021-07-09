/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2020年10月11日 星期日 17时37分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 2e5 + 10;

int n, ans, c[maxn], a[maxn], b[maxn];
char s[maxn], t[maxn];
vector<int> p1[26], p2[26];

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] += val; }

inline int get(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    scanf("%s", s + 1); 
    REP(i, 1, n) t[i] = s[i];
    reverse(t + 1, t + n + 1);
    for ( int i = n; i >= 1; -- i ) 
    {
        a[i] = i;
        p2[s[i] - 'a'].push_back(i);
    }
    REP(i, 1, n) { b[i] = p2[t[i] - 'a'].back(); p2[t[i] - 'a'].pop_back(); }

    REP(i, 1, n)
    {
        ans += i - get(b[i]) - 1;
        add(b[i], 1);
    }
    printf("%lld\n", ans);
    return 0;
}
