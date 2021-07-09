#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#define N 100005
#define ll long long
#define mod 1000000007
using namespace std;
int n,m,cnt=1,len,fl;
int si[N],t1[N],t2[N];
int s1[N],s2[N],s3[N],s4[N];
vector< pair<int,int> >hk[N];
// s1 - sum of num , s2 sum of mi , s3 - sum of mx , s4 - sum of mi*mx
int adt(int a,int b){
	if(a+b>=mod) return a+b-mod;
	return a+b;
}
struct BIT{
	int tree[N],len;
	void rebuild(int a){len=a;for(int i=0;i<=len;i++) tree[i]=0; }
	void add(int a,int v){while(a<=len){tree[a]=adt(tree[a],v);a+=a&-a;}}
	int find(int a){int an=0;while(a>0){an=adt(an,tree[a]);a-=a&-a;}return an;}
}T[6];
struct qus{int l,r,ans;}s[N];
struct str{int l,r,sum;vector<int>hi;}e[4*N];
void build(int li,int ri,int no){
	if(li==ri) return;
	int mid=(li+ri)>>1;
	e[no].l=++cnt;e[no].r=++cnt;
	build(li,mid,e[no].l);build(mid+1,ri,e[no].r);
}
void add(int li,int ri,int no,int mb1,int mb2,int v){
	if(li>mb2||ri<mb1) return;
	if(li>=mb1&&ri<=mb2){e[no].hi.push_back(v);return;}
	int mid=(li+ri)>>1;
	add(li,mid,e[no].l,mb1,mb2,v);add(mid+1,ri,e[no].r,mb1,mb2,v);
	if(mb1<=mid&&mb2>=mid+1) e[no].hi.push_back(v);
}
void add_by_num(int li,int ri,int v){
	li-=fl;ri-=fl;if(li>ri) return;
	T[1].add(li,v);T[1].add(ri+1,mod-v);
	int tmp=(ll)s1[li+fl-1]*v%mod;T[0].add(li,mod-tmp);
	tmp=(ll)s1[ri+fl]*v%mod;T[0].add(ri+1,tmp); 
}
void add_by_mi(int li,int ri,int v){
	li-=fl;ri-=fl;if(li>ri) return;
	T[2].add(li,v);T[2].add(ri+1,mod-v);
	int tmp=(ll)s2[li+fl-1]*v%mod;T[0].add(li,mod-tmp);
	tmp=(ll)s2[ri+fl]*v%mod;T[0].add(ri+1,tmp); 
}
void add_by_mx(int li,int ri,int v){
	li-=fl;ri-=fl;if(li>ri) return;
	T[3].add(li,v);T[3].add(ri+1,mod-v);
	int tmp=(ll)s3[li+fl-1]*v%mod;T[0].add(li,mod-tmp);
	tmp=(ll)s3[ri+fl]*v%mod;T[0].add(ri+1,tmp); 
}
void add_by_sum(int li,int ri,int v){
	li-=fl;ri-=fl;if(li>ri) return;
	T[4].add(li,v);T[4].add(ri+1,mod-v);
	int tmp=(ll)s4[li+fl-1]*v%mod;T[0].add(li,mod-tmp);
	tmp=(ll)s4[ri+fl]*v%mod;T[0].add(ri+1,tmp); 
}
int find(int a){
	a-=fl;
	int ans=T[0].find(a);
	ans=adt(ans,(ll)T[1].find(a)*s1[a+fl]%mod);
	ans=adt(ans,(ll)T[2].find(a)*s2[a+fl]%mod);
	ans=adt(ans,(ll)T[3].find(a)*s3[a+fl]%mod);
	ans=adt(ans,(ll)T[4].find(a)*s4[a+fl]%mod);
	return ans; 
}
void solve(int li,int ri,int no){
	if(li==ri){
		e[no].sum=(ll)si[li]*si[li]%mod;
		for(int i=0;i<e[no].hi.size();i++) s[e[no].hi[i]].ans=adt(s[e[no].hi[i]].ans,e[no].sum);
		return;
	}
	int mid=(li+ri)>>1;
	solve(li,mid,e[no].l);solve(mid+1,ri,e[no].r);e[no].sum=adt(e[e[no].l].sum,e[e[no].r].sum);
	int mi=1e9+1,mx=-1e9-1;s1[mid]=s2[mid]=s3[mid]=s4[mid]=0;
	for(int i=mid+1;i<=ri;i++){
		mi=min(mi,si[i]);mx=max(mx,si[i]);
		s1[i]=1;s2[i]=mi;s3[i]=mx;s4[i]=(ll)mi*mx%mod;
		t1[i]=mi;t2[i]=mx;
	}
	for(int i=0;i<=4;i++) T[i].rebuild(ri-mid);
	for(int i=mid+1;i<=ri;i++) s1[i]=adt(s1[i-1],s1[i]),s2[i]=adt(s2[i-1],s2[i]);
	for(int i=mid+1;i<=ri;i++) s3[i]=adt(s3[i-1],s3[i]),s4[i]=adt(s4[i-1],s4[i]);
	int l=mid,r=mid;mi=1e9+1;mx=-1e9-1;fl=mid;
	for(int i=0;i<e[no].hi.size();i++){
		int tmp=e[no].hi[i];
		int lk=max(li,s[tmp].l),rk=min(ri,s[tmp].r);
		if(lk==li&&rk==ri) continue;
		hk[lk].push_back(make_pair(rk,tmp));
	}
	for(int i=mid;i>=li;i--){
		mi=min(mi,si[i]);mx=max(mx,si[i]);
		while(l<ri&&mi<=t1[l+1]) l++;
		while(r<ri&&mx>=t2[r+1]) r++;
		add_by_num(mid+1,min(l,r),(ll)mi*mx%mod);
		add_by_mi(l+1,r,mx);add_by_mx(r+1,l,mi);
		add_by_sum(max(l,r)+1,ri,1);
//		if(li==1&&ri==5) cout<<i<<" - "<<l<<" - "<<r<<" - "<<mi<<" - "<<mx<<" "<<find(ri)<<endl;
		for(int j=0;j<hk[i].size();j++){
			int t1=hk[i][j].first,t2=hk[i][j].second;
			s[t2].ans=adt(s[t2].ans,find(t1));
		}
	}
	e[no].sum=adt(e[no].sum,find(ri));
	for(int i=li;i<=mid;i++) hk[i].clear();
	for(int i=0;i<e[no].hi.size();i++){
		int tmp=e[no].hi[i];
		int lk=max(li,s[tmp].l),rk=min(ri,s[tmp].r);
		if(lk==li&&rk==ri) s[tmp].ans=adt(s[tmp].ans,e[no].sum);
	}
//	cout<<li<<" - "<<ri<<" - "<<e[no].sum<<endl;
}
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&si[i]);
	build(1,n,1);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&s[i].l,&s[i].r);
		add(1,n,1,s[i].l,s[i].r,i);
	}
	solve(1,n,1);
	for(int i=1;i<=m;i++) printf("%d\n",s[i].ans);
	return 0;
} 
