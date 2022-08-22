#include<bits/stdc++.h>
#define ll long long
using namespace std;
//reference : b09902068 凌暄 & b05504066 李旻翰

class Node{
	public:
		int size;
		int pos;
		Node* parent;
		Node(int p, int s):pos(p), size(s), parent(this){}
		Node(){}
};
map<int, Node*> mp;

Node* find_root(Node* x){
	x->size--;
	if(x != x->parent)
		x->parent = find_root(x->parent);
	return x->parent;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int N, Q;
	cin >> N >> Q;
	vector<Node*> cat(N+1);
	vector<ll> num_array(N+1, 0);
	for(ll i = 0;i <= N;i++)
		num_array[i] = (i * (i - 1)) / 2;
	ll res = 0;
	for(int i = 1;i <= N;i++){
		int pos;
		cin >> pos;
		if(mp.count(pos) == 0){//map上原本沒貓
			Node* it = new Node(pos, 1);
			cat[i] = it;
			mp[pos] = it;
		}
		else{//map有貓
			Node* it = mp[pos];
			ll orig_num = num_array[it->size];
			it->size++;
			ll new_num = num_array[it->size];
			res += new_num - orig_num;
			cat[i] = it;
		}
	}
	for(int i = 0;i < Q;i++){
		int operation, cat_id, pos, radius;
		cin >> operation;
		if(operation == 1){
			cin >> pos >> radius;
			if(mp.count(pos) == 0){
				Node* it = new Node(pos, 0);
				mp[pos] = it;
			}
			Node* target_pos = mp[pos];
			auto it = mp.lower_bound(pos-radius);
			while(it != mp.end() && it->first <= pos + radius){
				if(it->second == target_pos){it++; continue;}
				it->second->parent = target_pos;
				ll decrease_num = num_array[it->second->size];
				ll orig_num = num_array[target_pos->size];
				target_pos->size += it->second->size;
				ll increase_num = num_array[target_pos->size] - orig_num;
				res = res - decrease_num + increase_num;
				it = mp.erase(it);
			}
			
		}
		else if(operation == 2){
			cin >> cat_id >> pos;
			Node* root = find_root(cat[cat_id]);
			if(root->size == 0)
				mp.erase(root->pos);
			ll decrease_num = num_array[root->size+1] - num_array[root->size];
			if(mp.count(pos) == 0){
				Node* it = new Node(pos, 0);
				mp[pos] = it;
			}
			Node* target_pos = mp[pos];
			ll orig_num = num_array[target_pos->size];
			target_pos->size++;
			ll increase_num = num_array[target_pos->size] - orig_num;
			cat[cat_id] = target_pos;
			res = res - decrease_num + increase_num;
		}
		cout << res << '\n';
	}
}