/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年07月06日 星期一 14时29分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, sa[maxn], id[maxn], y[maxn];
vector<int> p[30];
vector<pii> a;
priority_queue<int, vector<int>, greater<int> > Q;
char s[maxn];
string ans;

inline void add(int num, char c) { REP(i, 1, num) ans += c; }

inline bool cmp(int a, int b, int k) { return y[a] == y[b] && y[a + k] == y[b + k]; }

inline void SA()
{
    int x[maxn], c[maxn], m = 26;
    REP(i, 1, n) x[i] = s[i] - 'a' + 1; 
    REP(i, 1, n) ++ c[x[i]]; REP(i, 1, m) c[i] += c[i - 1];
    for ( int i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;

    for ( int k = 1; k < n; k <<= 1 ) 
    {
        int tot = 0;
        REP(i, n - k + 1, n) y[++ tot] = i;
        REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;

        REP(i, 0, m) c[i] = 0;
        REP(i, 1, n) ++ c[x[i]]; REP(i, 1, m) c[i] += c[i - 1];
        for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];

        swap(x, y); x[sa[1]] = tot = 1;
        REP(i, 2, n) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? tot : ++ tot; 
        m = tot;
    }
    REP(i, 1, n) id[sa[i]] = i;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d", &k);
    scanf("%s", s + 1); n = str(s + 1);
    SA();
    REP(i, 1, n) p[s[i] - 'a'].push_back(i);        
    int now = 0;
    for ( int j = 25; j >= 0; -- j ) 
    {
        int last = -1, sum = 0; a.clear();
        for ( auto i : p[j] ) 
        {
            if ( i < now ) continue ;
            if ( last + 1 < i ) 
            {
                if ( sum > 0 ) a.push_back(pii(last, sum));
                sum = 0;
            }
            ++ sum; last = i;
        }
        if ( sum > 0 ) a.push_back(pii(p[j].back(), sum));
        if ( !a.size() ) continue ;
        if ( s[now + 1] == j + 'a' ) 
        {
            add(a[0].second, j + 'a');
            now = max(now, a[0].first);
            a.erase(a.begin());
        }
        if ( !a.size() ) continue ;
        int cnt = a.size();
        if ( k > cnt ) 
        {
            for ( auto i : a ) add(i.second, j + 'a');
            now = max(now, a.back().first);
            k -= cnt;
            continue ;
        }

        sum = 0;
        int num = 0, pos = 0;
        REP(i, 0, k - 2) { Q.push(a[i].second); sum += a[i].second; }
        REP(i, k - 1, a.size() - 1)
        {
            if ( sum + a[i].second > num || (sum + a[i].second == num && id[a[i].first] > id[pos]) )
            {
                num = sum + a[i].second;
                pos = a[i].first;
            }
            if ( !Q.empty() && a[i].second > Q.top() ) 
            { 
                sum = sum - Q.top() + a[i].second;
                Q.pop(); 
                Q.push(a[i].second); 
            }
        }
        add(num, j + 'a');
        REP(i, pos + 1, n) ans += s[i];

        break ; 
    }
    cout << ans << endl;
    return 0;
}
