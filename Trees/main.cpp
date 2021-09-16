#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pb push_back
#define F first
#define S second
#define ii pair<int,int>

const ll N = 2e5 + 5, M = 3e5 + 50, LOG = 19, mod = 1000000007, INF = 1e8;
vector<int> adj[N];
bool vis[N];
int par[N], siz[N], depth[N];
int up[LOG][N];
unordered_map<int,int> mp[N];

void init(int n) {
  for (int i=0; i<=n; ++i) {
    adj[i].clear();
    vis[i] = false;
    par[i] = 0;
    siz[i] = 0;
  }
}

void addEdges(int u, int v) {
  adj[u].pb(v);
  adj[v].pb(u);
}

int getSize(int u, int p) {
  siz[u] = 1;
  for (auto v : adj[u]) {
    if (v != p && !vis[v]) {
      siz[u] += getSize(v, u);
    }
  }
  return siz[u];
}

int getCentroid(int u, int p, int s) {
  for (auto v : adj[u]) {
    if (v != p && !vis[v] && siz[v] * 2 > s) {
      return getCentroid(v, u, s);
    }
  }
  return u;
}

void initCentroid(int u, int p) {
  getSize(u, -1);
  int c = getCentroid(u, -1, siz[u]);
  par[c] = p;
  vis[c] = true;
  for (auto v : adj[c]) {
    if (!vis[v]) {
      initCentroid(v, c);
    }
  }
}

void buildLCA(int u, int p) {
  for (auto v : adj[u]) {
    if (v != p) {
      depth[v] = depth[u] + 1;
      up[0][v] = u;
      for (int i=1; i<LOG; ++i)
        up[i][v] = up[i-1][up[i-1][v]];
      buildLCA(v, u);
    }
  }
}

int get_lca(int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);
  int k = depth[a] - depth[b];
  for (int i=0; i<LOG; ++i) {
    if (k&(1<<i)) a = up[i][a];
  }
  if (a == b) return a;
  for (int i=LOG-1; i>=0; --i) {
    if (up[i][a] != up[i][b]) {
      a = up[i][a];
      b = up[i][b];
    }
  }
  return up[0][a];
}

int dist(int a, int b) {
  return depth[a] + depth[b] - 2 * depth[get_lca(a,b)];
}

int main() {
 // ios_base::sync_with_stdio(0);
    //cin.tie(0); cout.tie(0);

  int n, k;
  cin >> n >> k;
  int a, b;
  for (int i=0; i<n-1; ++i) {
    cin >> a >> b;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  buildLCA(1, -1);
  initCentroid(1, -1);
  int j, d;
  ll ans = 0;
  for (int i=1; i<=n; ++i) {
    j = par[i];
    while (j != -1) {
      d = dist(i, j);
      if (d > k) break;
      if (d == k) ++ans;
      else {
        ans += mp[j][k - d];
        ++mp[j][d];
      }
      cout << i << " "  << j << " " << " " << d << " "  << ans << "\n";
      j = par[j];
    }
  }
  cout << ans;


  return 0;
}