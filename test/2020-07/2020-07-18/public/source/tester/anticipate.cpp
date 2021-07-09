#include<bits/stdc++.h>
#define ll long long
#define lld long double
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 201000;
struct point{
	int x,y;
}p[N];
struct node{
	double l,r;
	int num;
};
int n,L,R,top;
vector<pair<double,int> > V1,V2;
vector<node> P;
pair<double,int> st[N];
double ans[N];
double calc(double w,int k){
	if(fabs(w-p[k].x)<1e-12) return R-L+p[k].y;
	if(w>=p[k].x) return R-L-(R-L)*(w-p[k].x)/(w-L)+p[k].y;
	else return R-L-(R-L)*(p[k].x-w)/(R-w)+p[k].y;
}
double get_w(double l,double r,int k1,int k2){
	while(l+1e-9<r){
		double mid=(l+r)/2;
		if(calc(mid,k1)>=calc(mid,k2)) l=mid;
		else r=mid;
	}
	return l;
}
int main(){
	freopen("anticipate.in","r",stdin);
	freopen("anticipate.out","w",stdout);
	int id;read(id);
	read(n);read(L);read(R);
	for(int i=1;i<=n;i++) read(p[i].x);
	for(int i=1;i<=n;i++) read(p[i].y);
	st[top=1]=make_pair(R,1);
	for(int i=2;i<=n;i++){
		while(top&&st[top].first<=p[i].x)
			V1.push_back(st[top--]);
		double w=p[i].x;
		while(top&&calc(st[top].first,st[top].second)<=calc(st[top].first,i))
			V1.emplace_back(p[i].x,st[top].second),w=st[top--].first;
		if(top){
			w=get_w(w,st[top].first,i,st[top].second);
			V1.emplace_back(p[i].x,st[top].second);
		}
		st[++top]=make_pair(w,i);
	}
	while(top) V1.push_back(st[top--]);
	st[top=1]=make_pair(L,n);
	for(int i=n-1;i;i--){
		while(top&&st[top].first>=p[i].x)
			V2.push_back(st[top--]);
		double w=p[i].x;
		while(top&&calc(st[top].first,st[top].second)<=calc(st[top].first,i))
			V2.emplace_back(p[i].x,st[top].second),w=st[top--].first;
		if(top){
			w=get_w(st[top].first,w,st[top].second,i);
			V2.emplace_back(p[i].x,st[top].second);
		}
		st[++top]=make_pair(w,i);
	}
	while(top) V2.push_back(st[top--]);
	double lst=R;
	for(auto&p:V2) P.push_back({p.first,lst,p.second}),lst=p.first;
	sort(P.begin(),P.end(),[](node a,node b){
		return a.l<b.l||a.l==b.l&&a.r<b.r;
	});
	int k=0;lst=L;
	for(auto&p:V1){
		while(k<P.size()&&P[k].l<=p.first){
			double l=max(lst,P[k].l),r=min(p.first,P[k].r);
			double w=get_w(l,r,p.second,P[k].num);
			ans[p.second]+=w-l;
			ans[P[k].num]+=r-w;
			if(P[k].r<=p.first) k++;
			else break;
		}
		lst=p.first;
	}
	for(int i=1;i<=n;i++)
		printf("%.12lf\n",ans[i]/(R-L));
	return 0;
}

