#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], c[maxn], ans;
char s[10];
struct node
{
	int l, r, h; bool operator < (const node &a) const { return l < a.l; }
	node(int L = 0, int R = 0, int H = 0) { l = L; r = R; h = H; }
} ;
set<pii> Set;
set<node> S;

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] += val; }

inline int get(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; }

inline int Get(int l, int r, int h)
{
	int x = (r - l - 1) * h - get(r - 1) + get(l);
	return x;
}

signed main()
{
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) { scanf("%lld", &a[i]); add(i, a[i]); }
	int Max = 0; REP(i, 1, n) if ( a[i] >= Max ) { Set.insert(pii(i, a[i])); Max = a[i]; }
	Max = 0; for ( int i = n; i >= 1; -- i ) if ( a[i] >= Max ) { Set.insert(pii(i, a[i])); Max = a[i]; }
	Set.insert(pii(0, 0)); Set.insert(pii(n + 1, 0));
	for ( auto itl = Set.begin(); itl != Set.end(); ++ itl )
	{
		auto it = itl, itr = ++ itl; itl = it;
		if ( itr == Set.end() ) continue ;
		S.insert(node(itl -> first, itr -> first, min(itl -> second, itr -> second)));
	}
	for ( auto it : S ) ans += Get(it.l, it.r, it.h);
	while ( m -- )
	{
		scanf("%s", s + 1);
		if ( s[1] == 'P' ) { printf("%lld\n", ans);  }
		else
		{
			int x, v; scanf("%lld%lld", &x, &v); a[x] += v;
			auto itl = -- Set.lower_bound(pii(x, 0)), itr = Set.lower_bound(pii(x + 1, 0));
			if ( a[x] < itl -> second && a[x] < itr -> second ) { add(x, v); ans -= v; continue ; }
			auto itit = S.lower_bound(node(itl -> first, 0, 0)); ans -= Get(itit -> l, itit -> r, itit -> h); S.erase(itit);
			if ( Set.lower_bound(pii(x, 0)) -> first == x )
			{
				Set.erase(Set.lower_bound(pii(x, 0))); itit = S.lower_bound(node(x, 0, 0));
				ans -= Get(itit -> l, itit -> r, itit -> h); S.erase(itit);
			}
			Set.insert(pii(x, a[x])); add(x, v);
			S.insert(node(itl -> first, x, min(itl -> second, a[x])));
            ans += Get(itl -> first, x, min(itl -> second, a[x]));
			S.insert(node(x, itr -> first, min(itr -> second, a[x])));
            ans += Get(x, itr -> first, min(itr -> second, a[x]));
			if ( itl != Set.begin() )
			{
				auto IT = itl, it = -- itl; itl = IT;
				while ( a[x] > itl -> second && itl -> second <= it -> second )
				{
					int L = it -> first, Mid = itl -> first, R = x;
					Set.erase(itl);
                    auto p = S.lower_bound(node(L, 0, 0)); ans -= Get(p -> l, p -> r, p -> h); S.erase(p);
					p = S.lower_bound(node(Mid, 0, 0)); ans -= Get(p -> l, p -> r, p -> h); S.erase(p);
					ans += Get(L, R, min(it -> second, a[x])); S.insert(node(L, R, min(it -> second, a[x])));
					if ( it == Set.begin() ) break ;
					itl = it; IT = itl; it = -- itl; itl = IT;
				}
			}
			auto IT = itr, it = ++ itr; itr = IT;
			if ( it != Set.end() )
			{
				while ( a[x] > itr -> second && itr -> second <= it -> second )
				{
					int L = x, Mid = itr -> first, R = it -> first;
					Set.erase(itr);
					auto p = S.lower_bound(node(L, 0, 0)); ans -= Get(p -> l, p -> r, p -> h); S.erase(p);
					p = S.lower_bound(node(Mid, 0, 0)); ans -= Get(p -> l, p -> r, p -> h); S.erase(p);
					ans += Get(L, R, min(it -> second, a[x])); S.insert(node(L, R, min(it -> second, a[x])));
					itr = it; IT = itr; it = ++ itr; itr = IT;
					if ( it == Set.end() ) break ;
				}
			}
		}
	}
	return 0;
}
