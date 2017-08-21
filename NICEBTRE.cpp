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
#define SS(n) scanf("%s",n)
#define pn putchar_unlocked('\n')
#define ps putchar_unlocked(' ')
#define sz(s) int((s).size())
#define rep(i,n) for(int(i)=0; (i)<(n);++(i))
#define ru(i,a,b) for(int(i)=a;(i)<=(b);++(i))
#define rd(i,b,a) for(int(i)=b;(i)>=(a);--(i))
#define clr(a) memset(a,0,sizeof(a))
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
typedef long long LL; typedef vector <int> vi; typedef pair<int,int> pii; typedef map <int,int> mii; template <class T> inline T max(T a,T b,T c) {return (max(max(a,b),c));} template <class T> inline T min(T a,T b,T c) {return (min(min(a,b),c));} template <class T> inline T sqr(T x) {return x*x;} inline int inp() {int n=0,s=1;char p=getchar_unlocked();if(p=='-')s=-1;while((p<'0'||p>'9')&&p!=EOF&&p!='-')p=getchar_unlocked();if(p=='-')s=-1,p=getchar_unlocked();while(p>='0'&&p<='9')n=(n<<3)+(n<<1)+(p-'0'),p=getchar_unlocked();return n*s;} void out(int x){if(x<0)putchar_unlocked('-'),x=-x;int ll=0,dd[10];while(x)dd[ll++]=x%10,x/=10;if(!ll)dd[ll++]=0;while(ll--)putchar_unlocked(dd[ll]+48);} inline int ins(int x,int y,int m,int n){return (x>=1&&x<=m&&y>=1&&y<=n);} template <class T> inline T gcd(T a,T b){return (!b? a : gcd(b,a%b));} template <class T> inline T ABS(T x){return ((x)>0?(x):(-(x)));}
const int N = 1e5 + 11;

vector <int> edge[N];
int dis[N];
int ans;

void dfs(int u, int p) {
  rep(i,sz(edge[u])) {
    int v = edge[u][i];
    if(v != p) {
      dis[v] = dis[u] + 1;
      ans = max(ans, dis[v]);
      dfs(v,u);
    }
  }
}

//1:49 am to 2:03 am
char str[N];
int main() {
  #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
  #endif
  for(int tc=1,t=inp(); tc<=t; ++tc) {
    ans = 0;
    clr(dis);
    scanf("%s",str);
    int ln = strlen(str);
    rep(i,ln+2) edge[i].clear();
    stack <int> stk;
    stk.push(0);
    int curr = 0;
    for(int i=0; str[i]; ++i) {
      int cnt = str[i] == 'l' ? 0 : 2;
      int par = stk.top();
      stk.pop();
      while(cnt--) {
        ++curr;
        edge[par].pb(curr);
        stk.push(curr);
      }
    }
    dfs(0,0);
    out(ans); pn;
  }
}
