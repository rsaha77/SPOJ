#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdio>
#include <vector>
#include <string>
#include <bitset>
#include <numeric>
#include <utility>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL; typedef vector <int> vi; typedef pair<int,int> pii; typedef map <int,int> mii; template <class T> inline T max(T a,T b,T c) {return (max(max(a,b),c));} template <class T> inline T min(T a,T b,T c) {return (min(min(a,b),c));} template <class T> inline T sqr(T x) {return x*x;} inline int inp() {int n=0,s=1;char p=getchar_unlocked();if(p=='-')s=-1;while((p<'0'||p>'9')&&p!=EOF&&p!='-')p=getchar_unlocked();if(p=='-')s=-1,p=getchar_unlocked();while(p>='0'&&p<='9')n=(n<<3)+(n<<1)+(p-'0'),p=getchar_unlocked();return n*s;} void out(int x){if(x<0)putchar_unlocked('-'),x=-x;int ll=0,dd[10];while(x)dd[ll++]=x%10,x/=10;if(!ll)dd[ll++]=0;while(ll--)putchar_unlocked(dd[ll]+48);} inline int ins(int x,int y,int m,int n){return (x>=1&&x<=m&&y>=1&&y<=n);} template <class T> inline T gcd(T a,T b){return (!b? a : gcd(b,a%b));} template <class T> inline T ABS(T x){return ((x)>0?(x):(-(x)));}
const int N = 1e4 + 11;
 
vector <pii> g[N];
int anc[N][42], dis[N], lev[N], b[N], e[N], tm, logn;
 
void dfs(int u, int p) {
  b[u] = tm++;
  anc[u][0] = p;
  for(int i=1; i<=logn; ++i)
    if(anc[u][i-1] == -1) break;
    else anc[u][i] = anc[anc[u][i-1]][i-1];
  for(int i=0; i < g[u].size(); ++i) {
    int v = g[u][i].first;
    int d = g[u][i].second;
    if(v != p) {
      dis[v] = dis[u] + d;
      lev[v] = lev[u] + 1;
      dfs(v,u);
    }
  }
  e[u] = tm-1;
}
 
bool upper(int p, int q) {
  return b[q] >= b[p] && e[q] <= e[p];
}
 
int lca(int a, int b) {
  if(upper(a,b)) return a;
  if(upper(b,a)) return b;
  for(int i=logn; i>=0; --i) if(anc[a][i] > 0)
    if(!upper(anc[a][i],b))
      a = anc[a][i];
  return anc[a][0];
}
 
int search(int u, int len) {
  int klev = lev[u] - len;
  int stp=1;
  while(1<<stp <= lev[u]) stp++; stp--;
  for(int i=stp; i>=0; i--)
    if(lev[u] - (1<<i) >= klev)
      u = anc[u][i];
  return u;
}
 
int main() {
  #ifndef ONLINE_JUDGE
    freopen("in3.txt","r",stdin);
  #endif
  for(int tc=1,t=inp(); tc<=t; ++tc) {
    int n=inp();
    if(tc > 1) {
      for(int i=1; i<=n; ++i) {
        g[i].clear();
      }
    }
    for (int i=0; i<n; ++i){
      int u=inp(), v=inp(), w=inp();
      g[u].push_back(make_pair(v,w));
      g[v].push_back(make_pair(u,w));
    }
    int root = 1;
    logn = 1;
    while ((1 << logn) <= n) ++logn;
    memset(anc,-1,sizeof(anc));
    tm = dis[root] = lev[root] = 0, dfs(root,-1);
    char choice[7];
    while(true) {
      scanf("%s",choice);
      if(choice[1] == 'O') break;
      int so=inp(), si=inp();
      int l = lca(so,si), ans;
      if(choice[1] == 'I') out(dis[so] + dis[si] - 2*dis[l]);
      else {
        int k=inp(); --k;
        if(lev[so] - lev[l] >= k) ans = search(so,k);
        else ans = search(si, (lev[so] + lev[si] - 2*lev[l] - k));
        out(ans);
      }
      putchar_unlocked('\n');
    }
    putchar_unlocked('\n');
  }
}
 
 
