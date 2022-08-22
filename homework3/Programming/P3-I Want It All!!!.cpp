#include<bits/stdc++.h>
#define ll long long
using namespace std;
//reference : https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
//discuss with b08902149 徐晨祐
ll INF = LONG_LONG_MAX;

class GraphNode{
	public:
		int id;
		vector<tuple<int, ll, int>> adjacency;
		int discovered;
		GraphNode(){}
		GraphNode(int id):id(id), discovered(0){}
};
class Info{
	public:
		ll cost;
		int parent;
		int edge_id;
};

vector<GraphNode> Graph;

ll get_minimal_spanning_tree(int start){
	int V = Graph.size();
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	
	vector<ll> key(V, INF);
	vector<int> parent(V, -1);
	vector<bool> inMST(V, false);
	key[start-1] = 0;
	pq.push(make_pair(key[start-1], start));
	ll ans = 0;
	while (!pq.empty()){
		pair<ll, int> tmp = pq.top();
		ll cost = tmp.first;
		int u = tmp.second;
		pq.pop();
		if(inMST[u - 1] == true) continue;
	
		inMST[u - 1] = true;
		ans += cost;
		for(int i = 0;i < Graph[u-1].adjacency.size();i++){
			int v, edge_id;
			ll weighted;
			tie(v, weighted, edge_id) = Graph[u-1].adjacency[i];
			if (inMST[v - 1] == false && key[v - 1] > weighted){
				key[v - 1] = weighted;
				pq.push(make_pair(key[v-1], v));
				parent[v - 1] = u;
			}
		}
	}
	
	return ans;
}

vector<Info> get_shortest_path_tree(int start){
	int V = Graph.size();
	
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	
	vector<ll> delta(V, INF);
	delta[start-1] = 0;
	vector<Info> res_array(V); 
	
	pq.push({delta[start-1], start});
	
	while(!pq.empty()){
		int u = pq.top().second;
		
		pq.pop();
		
		for(int i = 0;i < Graph[u-1].adjacency.size();i++){
			int v, edge_id;
			ll weighted;
			tie(v, weighted, edge_id) = Graph[u-1].adjacency[i];
			if(delta[v-1] > delta[u-1] + weighted){
				delta[v-1] = delta[u-1] + weighted;
				pq.push({delta[v-1], v});
				res_array[v-1].cost = delta[u-1] + weighted;
				res_array[v-1].parent = u;
				res_array[v-1].edge_id = edge_id;
			}
			else if(delta[v-1] == delta[u-1] + weighted && res_array[v-1].cost > weighted){
				res_array[v-1].cost = weighted;
				res_array[v-1].parent = u;
				res_array[v-1].edge_id = edge_id;
			}
		}
	}
	
	return res_array;
}


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int v1, v2;
	ll weighted;
	int node_num, edge_num;
	cin >> node_num >> edge_num;
	vector<ll> edge_weight;
	for(int i = 1; i <= node_num; i++)
		Graph.push_back(GraphNode(i));
	for(int i = 0; i < edge_num; i++){
		cin >> v1 >> v2 >> weighted;
		edge_weight.push_back(weighted);
		Graph[v1-1].adjacency.push_back({v2, weighted, i+1});
		Graph[v2-1].adjacency.push_back({v1, weighted, i+1});
	}
	vector<Info> spt_res = get_shortest_path_tree(1);
	ll spt_cost = 0;
	vector<int> final_edge;
	for(int i = 1;i < spt_res.size();i++){
		spt_cost += edge_weight[spt_res[i].edge_id-1];
		final_edge.push_back(spt_res[i].edge_id);
	}
	
	ll mst_cost = get_minimal_spanning_tree(1);
	if(spt_cost == mst_cost){
		cout << "Yes\n";
		for(auto it : final_edge) cout << it << ' ';
	}
	else
		cout << "No";
	
}