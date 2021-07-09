#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define FIR first
#define SEC second
#define ll long long
#define db long double
using namespace std;
template <class T>
inline void rd(T &x) {
	x=0; char c=getchar(); int f=1;
	while(!isdigit(c)) { if(c=='-') f=-1; c=getchar(); }
	while(isdigit(c)) x=x*10-'0'+c,c=getchar(); x*=f;
}
const int N=45;
namespace CIRU {
	db Pi=acos(-1.0),eps=1e-10,eps2=1e-30;
	int sgn(db x) { return x<-eps?-1:(x>eps); }
	int sgn2(db x) { return x<-eps2?-1:(x>eps2); }
	struct Point {
		db x,y;
		Point (db x=0,db y=0): x(x),y(y) {}
		friend Point operator -(Point A,Point B) { return Point(A.x-B.x,A.y-B.y); }
		friend Point operator +(Point A,Point B) { return Point(A.x+B.x,A.y+B.y); }
		db len2() { return x*x+y*y; }
		db len() { return sqrt(x*x+y*y); }
	};
	struct Cir {
		Point o; db r,r2;
		Cir(Point o,db r=0,db r2=0): o(o),r(r),r2(r2) {}
	};
	bool cmpr(Cir A,Cir B) { return A.r<B.r; } 
	db Cross(Point A,Point B) { return A.x*B.y-A.y*B.x; }
	Point Move(Point A,db a,db l) {
		A.x+=cos(a)*l,A.y+=sin(a)*l;
		return A;
	}	
	vector<Cir> p,tmp;
	struct item {
		db p; int x;
		item(db p=0,db x=0): p(p),x(x) {}
		friend bool operator <(item A,item B) { return A.p<B.p; }
	}S[N<<1];
	db sol() {
		sort(p.begin(),p.end(),cmpr);
		for(int i=0;i<p.size();++i) {
			int flg=0;
			for(int j=i+1;j<p.size()&&!flg;++j) {
				db d=(p[i].o-p[j].o).len();
				if(sgn(d+p[i].r-p[j].r)<=0) flg=1;
			}
			if(!flg) tmp.PB(p[i]);
		}
		p=tmp,tmp.clear();
		db ans=0;
		for(int i=0;i<p.size();++i) {
			int cnt=0;
			for(int j=0;j<p.size();++j) if(i!=j) {
				db len2=(p[i].o-p[j].o).len2(),len=sqrt(len2);
				if(sgn(len-(p[j].r+p[i].r))>=0) continue;
				if(sgn(len-fabs(p[j].r-p[i].r))<=0) continue;
				Point t=p[j].o-p[i].o; db ag=atan2(t.y,t.x);
				db a=acos((p[i].r*p[i].r+t.len2()-p[j].r*p[j].r)/(2*t.len()*p[i].r));
				db a1=ag-a,a2=ag+a;
				if(a1<=-Pi) S[++cnt]=item(a1+Pi*2,1),S[++cnt]=item(-Pi,1);
				else S[++cnt]=item(a1,1);
				if(a2>=Pi) S[++cnt]=item(-Pi,1),S[++cnt]=item(a2-Pi*2,-1);
				else S[++cnt]=item(a2,-1);
			}
			S[++cnt]=item(-Pi,0);
			S[++cnt]=item(Pi,0);
			sort(S+1,S+cnt+1);
			int ps=1,now=0;
			while(ps<=cnt)
			{
				int fr=ps;
				while(ps<=cnt&&sgn(S[ps].p-S[fr].p)==0) now+=S[ps++].x;
				if(now==0&&ps<=cnt)
				{
					db Ag=S[ps].p-S[fr].p;
					ans+=p[i].r*p[i].r*Ag/2-p[i].r*p[i].r*sin(Ag)/2;
					Point t1=Move(p[i].o,S[fr].p,p[i].r),t2=Move(p[i].o,S[ps].p,p[i].r);
					ans+=Cross(t1,t2)/2;
				}
			}
		}
		p.clear();
		return ans;
	}			
	void addcir(db x,db y,db r2) { p.PB(Cir(Point(x,y),sqrt(r2),r2)); }
}
db eps=1e-13;
int sgn(db x) { return x<-eps?-1:(x>eps); }
struct Point {
	db x,y,z;
	Point(db x=0,db y=0,db z=0): x(x),y(y),z(z) {}
	friend Point operator -(Point A,Point B) { return Point(A.x-B.x,A.y-B.y,A.z-B.z); }
	db len() { return sqrt(x*x+y*y+z*z); }
	db len2() { return x*x+y*y+z*z; }
};
int n;
struct Sph {
	Point o; db r;
}S[N];
map<db,db> mp; 
db cal(db h) {
	map<db,db>::iterator it=mp.lower_bound(h-eps);
	if(sgn(h-(it->first))==0) return it->second;
	for(int i=1;i<=n;++i) {
		db d=fabs(S[i].o.z-h);
		if(sgn(d-S[i].r)>=0) continue;
		CIRU::addcir(S[i].o.x,S[i].o.y,S[i].r*S[i].r-d*d);
	}
	db res=CIRU::sol();
	return mp[h]=res;
} 
db simpson(db l,db r) { return (cal(l)+4*cal((l+r)/2)+cal(r))*(r-l)/6; } 
db gao(db l,db r) {
	db m=(l+r)/2;
	db A=simpson(l,m),B=simpson(m,r),C=simpson(l,r);
	if(sgn(A+B-C)==0) return C;
	return gao(l,m)+gao(m,r);
}
vector<db> H; 
int main() {
	rd(n);
	for(int i=1;i<=n;++i) {
		scanf("%Lf%Lf%Lf%Lf",&S[i].o.x,&S[i].o.y,&S[i].o.z,&S[i].r);
		H.PB(S[i].o.z-S[i].r);
		H.PB(S[i].o.z+S[i].r);
	}
	db ans=0;
	sort(H.begin(),H.end());
	for(int i=0;i<H.size();++i) {
		int j=i;
		while(j+1<H.size() && sgn(H[j+1]-H[i])==0) ++j;
		if(j+1<H.size()) ans+=gao(H[i],H[j+1]);
		i=j;
	}
	printf("%.3Lf",ans); 
//	printf("%.10Lf",ans);
//	cerr<<endl<<mp.size()<<endl;
	return 0;
} 
