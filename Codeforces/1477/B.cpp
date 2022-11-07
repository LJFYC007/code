/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>

const int maxn = 1e6 + 10;

int n, q, T, a[maxn];
char s[maxn], ss[maxn];
#define ls(x) t[x].lc
#define rs(x) t[x].rc
pii b[maxn];

struct node{
	int lc,rc;
	int sum,tag;
}t[maxn<<1];
int tot,root;
inline void pushup(int x){
	t[x].sum=t[ls(x)].sum+t[rs(x)].sum;
}
inline void pushdown(int x,int l,int r){
	if ( t[x].tag == -1 ) return ;
	int mid=l+r>>1;
	t[ls(x)].sum=(mid-l+1)*t[x].tag,t[ls(x)].tag=t[x].tag;
	t[rs(x)].sum=(r-mid)*t[x].tag,t[rs(x)].tag=t[x].tag;
	t[x].tag=-1;
}
int build(int l,int r){
	int x=++tot; t[x].tag = -1;
	if(l==r){t[x].sum=a[l];return x;}
	int mid=l+r>>1;
	ls(x)=build(l,mid),rs(x)=build(mid+1,r);
	pushup(x);
	return x;
}
void modify(int o,int l,int r,int x,int y,int val){
	if(l==x&&r==y){t[o].sum=(r-l+1)*val,t[o].tag=val;return;}
	int mid=l+r>>1;
	pushdown(o,l,r);
	if(y<=mid)modify(ls(o),l,mid,x,y,val);
	else if(x>mid)modify(rs(o),mid+1,r,x,y,val);
	else modify(ls(o),l,mid,x,mid,val),modify(rs(o),mid+1,r,mid+1,y,val);
	pushup(o);
}
int query(int o,int l,int r,int x,int y){
	if(l==x&&r==y)return t[o].sum;
	int mid=l+r>>1;
	pushdown(o,l,r);
	if(y<=mid)return query(ls(o),l,mid,x,y);
	else if(x>mid)return query(rs(o),mid+1,r,x,y);
	else return query(ls(o),l,mid,x,mid)+query(rs(o),mid+1,r,mid+1,y);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- )
	{
		scanf("%d%d", &n, &q);
		scanf("%s", s + 1); scanf("%s", ss + 1);
		REP(i, 1, n) a[i] = ss[i] - '0';
		tot = 0; root = build(1, n);
		bool flag = true;
		REP(i, 1 ,q) scanf("%d%d", &b[i].first, &b[i].second);
		for ( int i = q; i >= 1; -- i )
		{
			int l = b[i].first, r = b[i].second;
			int num = query(root, 1, n, l, r), len = r - l + 1;
			if ( num < (len + 1) / 2 )
			{
				modify(root, 1, n, l, r, 0);
			}
			else if ( (len - num) < (len + 1) / 2 )
			{
				modify(root, 1, n, l, r, 1);
			}
			else flag = false;
		}
		REP(i, 1, n) if ( s[i] - '0' != query(root, 1, n, i, i) ) flag = false;
		if ( flag ) puts("YES");
		else puts("NO");
	}
    return 0;
}
