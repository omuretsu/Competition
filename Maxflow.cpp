#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <numeric>
#define rep(x, to) for (int x = 0; x < (to); x++)
#define REP(x, a, to) for (int x = (a); x < (to); x++)
#define foreach(itr, x) for (typeof((x).begin()) itr = (x).begin(); itr != (x).end(); itr++)


using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<long, long> PLL;


//dinic
class Graph {
	public:
		struct Edge {
			int to;
			int cap;
			int rev;
		};

		vector < vector<Edge> > G;
		vector<int> level;
		vector<int> iter;

		Graph(int n) {
			G.resize(n + 5);
			level.resize(n + 5, 0);
			iter.resize(n + 5, 0);
		}

		void add_edge(int from, int to, int cap) {
			G[from].push_back((Edge){to, cap, G[to].size()});
			G[to].push_back((Edge){from, 0, G[from].size() - 1});
		}

		//s:source
		int bfs(int s) {
			for (int i = 0; i < level.size(); i++) level[i] = -1;
			queue<int> que;
			level[s] = 0;
			que.push(s);
			while (!que.empty()) {
				int v = que.front(); que.pop();
				for (int i = 0; i < G[v].size(); i++) {
					Edge &e = G[v][i];
					if (e.cap > 0 && level[e.to] < 0) {
						level[e.to] = level[v] + 1;
						que.push(e.to);
					}
				}
			}
		}

		//t:sink
		int dfs(int v, int t, int f) {
			if (v == t) return f;
			for (int &i = iter[v]; i < G[v].size(); i++) {
				Edge &e = G[v][i];
				if (e.cap > 0 && level[v] < level[e.to]) {
					int d = dfs(e.to, t, min(f, e.cap));
					if (d > 0) {
						e.cap -= d;
						G[e.to][e.rev].cap += d;
						return d;
					}
				}
			}
			return 0;
		}

		//s:source
		//t:sink
		int max_flow(int s, int t) {
			int flow = 0;
			for (;;) {
				bfs(s);
				if (level[t] < 0) return flow;
				for (int i = 0; i < iter.size(); i++) iter[i] = 0;
				int f;
				while (f = dfs(s, t, 1e+9 + 7)) {
					flow += f;
				}
			}
		}
};



int main() {
	Graph graph(10);
	graph.add_edge(0, 1, 3);
	graph.add_edge(0, 2, 3);
	graph.add_edge(1, 2, 2);
	graph.add_edge(1, 3, 3);
	graph.add_edge(2, 4, 2);
	graph.add_edge(3, 4, 4);
	graph.add_edge(3, 5, 2);
	graph.add_edge(4, 5, 3);
	cout << graph.max_flow(0, 5) << endl;
	return 0;
}


