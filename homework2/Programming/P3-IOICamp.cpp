#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define ll long long
/*
discussion with b08902149 徐晨祐 & b08501098 柯晨緯 & b05504066 李旻翰 & p10922001 黃佳琪
*/

using namespace std;

class node{
	public:
		ll start;
		ll end;
		ll unit;
		ll pay;
		
		node(ll start, ll end, ll unit, ll pay): start(start), end(end), unit(unit), pay(pay){}
		node(){}
};
bool cmp_p(node a, node b){
	return a.pay > b.pay;
}
bool cmp_s(node a, node b){
	return a.start < b.start;
}

struct cmp_e{
    bool operator()(node a, node b){
        return a.end > b.end;
    }
};

ll helper(vector<node> &array, int index){
	
	vector<node> arr;
	for(int i = 0; i <= index; i++){
		arr.push_back(array[i]);
	}
	sort(arr.begin(), arr.end(), cmp_s);
	priority_queue<node, vector<node>, cmp_e> pq;
	int n = arr.size();
	int i = 0;
	ll p = 0;
	ll ans = 0;
	ll start;
	while(!(i == n && pq.empty())){
		if(i != n)
			start = arr[i].start;
		while(pq.empty() || (p >= start && i < n && start == arr[i].start)){
			pq.push(arr[i]);
			i++;
		}
		node curr_task = pq.top();
		pq.pop();
		ll now_do_unit;
		ll limit_time = curr_task.end;
		ll curr_start = curr_task.start;
		if(i < n)//後面還有任務 
			limit_time = min(limit_time, arr[i].start - 1);
		if(p < curr_start)
			p = curr_start;
		now_do_unit = min(limit_time - p + 1, curr_task.unit);
		p += now_do_unit;
		curr_task.unit -= now_do_unit;
		if(curr_task.unit > 0)
			pq.push(curr_task);
		ans += now_do_unit;
		while(!pq.empty() && (pq.top().end < p))
			pq.pop();
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	vector<node> array;
	while(t--){
		ll start, end, unit, pay;
		cin >> start >> end >> unit >> pay;
		array.push_back(node(start, end, unit, pay));
	}
	sort(array.begin(), array.end(), cmp_p);
	
	ll prev = array[0].unit;
	ll ans = prev * array[0].pay;
	for(int i = 1; i < array.size(); i++){
		ll cur = helper(array, i);
		ans += (cur - prev) * array[i].pay;
		prev = cur;
	}
	cout << ans;
	
}