#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a);i<=(b);i++)
#define fd(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
int a,b,k,n;
const int maxn=1000+5;
const double eps=1e-8;
int L[maxn],R[maxn];
double f[10][1<<10];
double s[2][maxn*maxn];
int pos;
map<pair<int,int>,int> Map;
inline void work(int T,int i,int j,int J,int K){
	//if(pos==i)printf("work(%d,%d,%d,%d)\n",i,j,J,K);
	if(Map.count(make_pair(J,K)))return ;
	Map[make_pair(J,K)]=1;
	if(f[T][i]-(.5*f[T-1][J]+.5*f[T-1][K])<=eps){
		//if(pos==i)printf("suc %d %d\n",i,j);
		fr(p,L[i],R[i]){
			int minc=max(max(L[J]-p,p-R[K]),0),maxc=min(min(R[J]-p,p-L[K]),p);
		//	if(s[T&1][p]>eps)printf("%d %d %d\n",p,minc,maxc);
			if(minc<=maxc){
				s[T&1^1][p+minc]+=.5/(p+1)*s[T&1][p];s[T&1^1][p+maxc+1]-=.5/(p+1)*s[T&1][p];
				s[T&1^1][p-minc+1]-=.5/(p+1)*s[T&1][p];s[T&1^1][p-maxc]+=.5/(p+1)*s[T&1][p];
			}
		}
	}
}
int main(){
	freopen("best.in","r",stdin);
	freopen("best.out","w",stdout);
	scanf("%d%d%d",&a,&b,&k);
	n=1<<k;
	double x=1.*b/n,now=0;
	fr(i,0,n){
		L[i]=ceil(now),R[i]=floor(now+x-eps);
		now+=x;
		printf("%d %d\n",L[i],R[i]);
		if(L[i]<=a&&a<=R[i])pos=i;
	}
	R[n]=10000000;
	f[0][n]=1;
	fr(T,1,k)
		fr(i,0,n){
			fr(j,0,i){
				int J=min(i+j,n);
				f[T][i]=max(f[T][i],.5*f[T-1][J]+.5*f[T-1][i-j]);
			}
		}
	//	printf("v=%lf\n",f[k][pos]);
	s[k&1][a]=1;
	fd(T,k,1){
		//fr(i,0,b)cout<<s[T&1][i]<<' ';
		//putchar(10);
		fr(i,0,b)s[T&1^1][i]=0;
		fr(i,0,n-1){
			Map.clear();
			fr(j,0,i){
				int J=min(i+j,n),K=i-j;
				work(T,i,j,J,K);
				if(J!=min(i+j+1,n))work(T,i,j,min(i+j+1,n),K);
				if(max(i-j-1,0)!=K){
					K=max(i-j-1,0);
					work(T,i,j,J,K);
					if(J!=min(i+j+1,n))work(T,i,j,min(i+j+1,n),K);
				}

			}
		}
		fr(i,0,b<<1|1)s[T&1^1][i]+=(i?s[T&1^1][i-1]:0);
		fr(i,b+1,b<<1|1)s[T&1^1][b]+=s[T&1^1][i],s[T&1^1][i]=0;
		s[T&1^1][b]+=s[T&1][b];
	}
	double ans=0;
	//fr(i,0,b)printf("%.2lf ",s[0][i]);
	//	printf("\n");
	fr(i,0,b)ans+=s[0][i];
	printf("%.8lf\n",ans);
	return 0;
}
