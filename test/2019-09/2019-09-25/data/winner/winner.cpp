#include <bits/stdc++.h>
#define F(i, l, r) for(int i = (l), _end_ = (int)(r); i <= _end_; ++i)
#define f(i, r, l) for(int i = (r), _end_ = (int)(l); i >= _end_; --i)
#define Set(a, v) memset(a, v, sizeof(a))
#define file(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
using namespace std;
#define int long long
bool chkmin(int &a, int b) {return b < a ? a = b, 1 : 0;}
bool chkmax(int &a, int b) {return b > a ? a = b, 1 : 0;}

inline int read() {
 int x = 0, fh = 1; char ch = getchar();
    for (; !isdigit(ch); ch = getchar() ) if (ch == '-') fh = -1;
    for (; isdigit(ch); ch = getchar() ) x = (x<<1) + (x<<3) + (ch ^ '0');
    return x * fh;
}
int n,m,tot;
struct node{
  int id,x;
}g[200005],d[100005];
long long ans;
int a[200005],pos[400005],tree[1600005],lazy[1600005];
bool cmp(node a,node b){
     if(a.x==b.x)return a.id<b.id;
	 else return a.x<b.x;
}
#define mid ((l+r)>>1)
inline void pushdown(int x){
    if(lazy[x]){
        tree[x<<1]+=lazy[x];lazy[x<<1]+=lazy[x];
        tree[x<<1|1]+=lazy[x];lazy[x<<1|1]+=lazy[x];
        lazy[x]=0;
    }
}
inline void update(int x,int l,int r,int L,int R,int y){
    if(l>R||r<L)return;
    if(l>=L&&r<=R){
        tree[x]+=y;lazy[x]+=y;
        return;
    }
    pushdown(x);
    update(x<<1,l,mid,L,R,y);
    update(x<<1|1,mid+1,r,L,R,y);
    tree[x]=min(tree[x<<1],tree[x<<1|1]);
}
inline int query(int x,int l,int r,int L,int R){
    if(l>R||r<L)return 1e9;
    if(l>=L&&r<=R)return tree[x];
    pushdown(x);
    return min(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
}
signed main () {
#ifndef ONLINE_JUDGE
file("winner5");
#endif
    n=read();
	m=read();
	tot=n+m;
	F(i,1,n)a[i]=read();
	sort(a+1,a+n+1);
    F(i,1,n)g[i].x=a[i],g[i].id=i;
	F(i,1,m){
	    int bb=read(),cc=read();
		d[i].id=i;
        d[i].x=cc-bb;
		g[i+n].id=i+n;
		g[i+n].x=bb;
	}
	sort(g+1,g+tot+1,cmp);
     sort(d+1,d+m+1,cmp);
	 F(i,1,tot)pos[g[i].id]=i;
     int i,j; 
	 for(i=n,j=m;i;i--,j--){
        update(1,1,tot,pos[i],tot,-1);
        for(;j;j--){
			int k=pos[d[j].id+n];
			if(query(1,1,tot,1,k-1)>=0&&query(1,1,tot,k,tot)>=-1&&(long long )a[i]+d[j].x>0){
                ans+=a[i]+d[j].x;
				update(1,1,tot,k,tot,1);
                break;
            }
        }
        if(!j)break;
    }
	  printf("%lld\n",ans);
	return 0;
}
