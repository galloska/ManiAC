#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define psi pair<int,pii>

using namespace std;

struct MinCostFlow{
	typedef int cap_t;
	typedef double cost_t;
	typedef pair<cost_t, cap_t> CostFlow;
	const static cap_t MaxFlow = numeric_limits<cap_t>::max();

	bool iszerocap(cap_t cap) { return cap == 0; }

	struct edge {
		int target;
		cost_t cost;
		cap_t residual_capacity;
		cap_t orig_capacity;
		size_t revid;
	};

	int n;
	vector<vector<edge>> graph;
	vector<cost_t> pi;
	bool needNormalize, ranbefore;
	int lastStart;

	MinCostFlow(int n) : graph(n), n(n), pi(n, 0), needNormalize(false), 
		ranbefore(false) {}

	void addEdge(int s, int e, cost_t cost, cap_t cap) {
		if (s == e) return;
		edge forward = { e, cost, cap, cap, graph[e].size() };
		edge backward = { s, -cost, 0, 0, graph[s].size() };
		if (cost < 0 || ranbefore) needNormalize = true;
		graph[s].emplace_back(forward);
		graph[e].emplace_back(backward);
	}

	bool normalize(int s) {
		auto infinite_cost = numeric_limits<cost_t>::max();
		vector<cost_t> dist(n, infinite_cost);
		dist[s] = 0;
		queue<int> q;
		vector<int> v(n), relax_count(n);
		v[s] = 1; q.push(s);

		while(!q.empty()) {
			int cur = q.front();
			v[cur] = 0; q.pop();
			if (++relax_count[cur] >= n) return false;

			for (const auto &e : graph[cur]) {
				if (iszerocap(e.residual_capacity)) continue;
				auto next = e.target;
				auto ncost = dist[cur] + e.cost;
				if (dist[next] > ncost) {
					dist[next] = ncost;
					if (v[next]) continue;
					v[next] = 1; q.push(next);
				}
			}
		}
		for (int i = 0; i < n; i++) pi[i] = dist[i];
		return true;
	}

	CostFlow AugmentShortest(int s, int e, cap_t flow_limit) {
		auto infinite_cost = numeric_limits<cost_t>::max();
		auto infinite_flow = numeric_limits<cap_t>::max();
		priority_queue<CostFlow, vector<CostFlow>, greater<CostFlow>> pq;
		vector<pair<cost_t, cap_t>> dist(n, CostFlow(infinite_cost, 0));
		vector<int> from(n, -1), v(n);

		if (needNormalize || (ranbefore && lastStart != s)) normalize(s);
		ranbefore = true;
		lastStart = s;

		dist[s] = CostFlow(0, infinite_flow);
		pq.emplace(dist[s].first, s);
		while(!pq.empty()) {
			auto cur = pq.top().second; pq.pop();
			if (v[cur]) continue;
			v[cur] = 1;
			if (cur == e) continue;

			for (const auto &e : graph[cur]) {
				auto next = e.target;
				if (v[next]) continue;
				if (iszerocap(e.residual_capacity)) continue;

				auto ncost = dist[cur].first + e.cost - pi[next] + pi[cur];
				auto nflow = min(dist[cur].second, e.residual_capacity);
				if (dist[next].first <= ncost) continue;

				dist[next] = make_pair(ncost, nflow);
				from[next] = e.revid;
				pq.emplace(dist[next].first, next);
			}
		}

		/** augment the shortest path **/
		auto p = e;
		auto pathcost = dist[p].first + pi[p] - pi[s];
		auto flow = dist[p].second;
		if (iszerocap(flow)|| (flow_limit <= 0 && pathcost >= 0))
			return CostFlow(0, 0);
		if (flow_limit > 0) flow = min(flow, flow_limit);

		/* update potential */
		for (int i = 0; i < n; i++) {
			if (iszerocap(dist[i].second)) continue;
			pi[i] += dist[i].first;
		}

		while (from[p] != -1) {
			auto nedge = from[p];
			auto np = graph[p][nedge].target;
			auto fedge = graph[p][nedge].revid;
			graph[p][nedge].residual_capacity += flow;
			graph[np][fedge].residual_capacity -= flow;
			p = np;
		}
		return make_pair(pathcost * flow, flow);
	}

	CostFlow solve(int s, int e, cap_t flow_minimum = MaxFlow) {
		cost_t total_cost = 0;
		cap_t total_flow = 0;
		for(;;) {
			auto res = AugmentShortest(s, e, flow_minimum - total_flow);
			if (res.second <= 0) break;
			total_cost += res.first;
			total_flow += res.second;
		}
		return CostFlow(total_cost, total_flow);
	}
};

const int MAXN = 505;

lli X[MAXN];
lli Y[MAXN];
lli H[MAXN];
int valid[MAXN];

lli Distancia(int i,int j) {
	return (X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]) + 
		(H[i] - H[j]) * (H[i] - H[j]);
}

long double D(int i,int j) {
	return hypotl( hypotl(X[i] - X[j], Y[i] - Y[j]), H[i] - H[j]);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout<<fixed<<setprecision(9);
	int n,s,t,a;
	lli q, h;
	cin>>n>>s>>t>>q;
	q *= q;

	forn(i, n) 
		cin>>X[i]>>Y[i]>>H[i];

	forn(i, s) {
		cin>>a;
		valid[a - 1] = 1;
	}

	forn(i, t) {
		cin>>a;
		valid[a - 1] = 2;
	}

	MinCostFlow grafo(n + 2);
	int ini = n, fin = n + 1;
	forn(i, n) {
		if(valid[i] == 1)
			grafo.addEdge(ini, i, 0, 1);
		if(valid[i] == 2)
			grafo.addEdge(i, fin, 0, 1);
		forn(j, n)
			if(H[i] > H[j] && Distancia(i, j) <= q) 
				grafo.addEdge(i, j, D(i, j), s + t);
	}

	pair<double,int> ans = grafo.solve(ini, fin, t);
	if(ans.se == t) cout<<ans.fi<<endl;
	else cout<<"IMPOSSIBLE"<<endl;
	return 0;
}
