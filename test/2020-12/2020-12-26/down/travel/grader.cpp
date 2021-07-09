#include <bits/stdc++.h>
#include "travel.h"
namespace test_lib {

    const int MAXN = 1005;
	
	struct edge{int v,nex;}e[MAXN*2];
	
    static int n,limA,limB,cntA,cntB,cnt,tot,x,y,reported_edge;
	static int head[MAXN],l[MAXN][MAXN],r[MAXN][MAXN],si[MAXN][MAXN],flag[MAXN][MAXN];
	
	void report(int x,int y){
		if(x<1||x>n||y<1||y>n){
			puts("Invalid edge.");
			fprintf(stderr,"Wrong answer!\n");
			exit(0);
		}
		if(flag[x][y]==0){
			puts("You report a wrong edge or report an edge twice!");
			fprintf(stderr,"Wrong answer!\n");
			exit(0);
		}
		flag[x][y]=flag[y][x]=0;reported_edge++;
	}
	bool check_in(int a,int b,int c){return l[a][b]<=l[a][c]&&r[a][b]>=r[a][c];}
	int check(int x,int y,std::vector<int> h){
		if(h.size()>n){
			puts("Invalid set.");
			fprintf(stderr,"Wrong answer!\n");
			exit(0);
		}
		if(x<1||x>n||y<1||y>n){
			puts("Invalid point.");
			fprintf(stderr,"Wrong answer!\n");
			exit(0);
		}
		cntA++;
		if(cntA>limA){
			puts("Too many queries!");
			fprintf(stderr,"Wrong answer!\n");
			exit(0);
		}
		if(h.size()==0){
			puts("Check operation should contain at least one point.");
			fprintf(stderr,"Wrong answer!\n");
			exit(0);	
		}
		int flag1=0,flag2=0;
		for(int i=0;i<h.size();i++){
			if(h[i]<1||h[i]>n){
				puts("Invalid point.");
				fprintf(stderr,"Wrong answer!\n");
				exit(0);
			}
			if(check_in(x,y,h[i])) flag1=1;
			else flag2=1;
			if(flag1+flag2==2) break;
		}
		return flag1+flag2*2;
	}
	int find(int x,int y){
		if(x<1||x>n||y<1||y>n){
			puts("Invalid point.");
			fprintf(stderr,"Wrong answer!\n");
			exit(0);
		}
		cntB++;
		if(cntB>limB){
			puts("Too many queries.");
			fprintf(stderr,"Wrong answer!\n");
			exit(0);
		}
		return si[x][y];
	}
	void add(int a,int b){cnt++;e[cnt].v=b;e[cnt].nex=head[a];head[a]=cnt;}
    void dfs(int a,int fa,int op){
    	l[op][a]=++tot;int i=head[a];si[op][a]=1;
    	while(i!=0){
    		if(e[i].v!=fa) dfs(e[i].v,a,op),si[op][a]+=si[op][e[i].v]; 
    		i=e[i].nex;
		}
		r[op][a]=tot;
	}
	void main() {
        scanf("%d%d%d",&n,&limA,&limB);reported_edge=0;cntA=cntB=cnt=0;
        for(int i=1;i<n;i++) scanf("%d%d",&x,&y),add(x,y),add(y,x),flag[x][y]=flag[y][x]=1;
    	for(int i=1;i<=n;i++){tot=0;dfs(i,0,i);}
		solve(n,limA,limB);
		if(reported_edge!=n-1){
			puts("You haven't report all edge.");
			fprintf(stderr,"Wrong answer!\n");
			exit(0);
		} 
		puts("Accept!");
		fprintf(stderr,"Ok, you ask %d times problem A and %d times problem B.",cntA,cntB);
	}
}
void solve(int n,int limA,int limB);
void report(int x,int y){test_lib::report(x,y);}
int check(int x,int y,std::vector<int> h){return test_lib::check(x,y,h);}
int find(int x,int y){return test_lib::find(x,y);}
int main() {

    test_lib::main();

    return 0;
}
