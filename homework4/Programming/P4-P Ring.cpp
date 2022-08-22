#include<bits/stdc++.h>
#define ll long long
#define INF LONG_LONG_MAX
//discussion with b08902149 徐晨祐 & b08501098 柯晨緯
using namespace std;

vector<ll> pre_process(vector<ll> &ary){
	vector<ll> res;
	res.push_back(ary[0]);
	res.push_back(ary[0] + ary[1] - abs(ary[1]- ary[0]));
	for(int i = 2;i < ary.size();i++){
		ll temp = res[i-1];
		temp += ary[i];
		temp -= abs(ary[i] - ary[i-1]);
		temp += ary[i-1] * ((ary[i-2] & ary[i-1]) ^ (ary[i-1] | ary[i]) ^ (ary[i-2] + ary[i]));
		res.push_back(temp);
	}
	return res;
}

ll diff(vector<ll> &ring, int i){
	ll res = 0;
	if(i == 1) 
		res = ring[1] - abs(ring[1] - ring[0]);
	else{
		res += ring[i];
		res -= abs(ring[i] - ring[i-1]);
		res += ring[i-1] * ((ring[i-2] & ring[i-1]) ^ (ring[i-1] | ring[i]) ^ (ring[i-2] + ring[i]));
	}
	return res;
}

ll find_min(vector<vector<ll>> &dp, vector<ll> &prefix_sum, vector<ll> &ring){
	int N = dp.size();
	int M = dp[0].size();
	for(int i = 0;i < N;i++) dp[i][0] = prefix_sum[i];
	for(int j = 1;j < M;j++) dp[0][j] = INF;
	
	for(int i = 1;i < N;i++){
		for(int j = 1;j < M;j++){
			if(j > i) dp[i][j] = INF;
			else{
				if(dp[i-1][j] == INF) dp[i][j] = dp[i-1][j-1] + ring[i];
				else dp[i][j] = min(dp[i-1][j] + diff(ring, i), dp[i-1][j-1] + ring[i]);
				if(i > 1 && dp[i-2][j-1] != INF) dp[i][j] = min(dp[i][j], dp[i-2][j-1] + ring[i]+ring[i-1]-abs(ring[i] - ring[i-1]));
			}
		}
	}
	return dp[N-1][M-1];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	srand(423);
	int N, M;
	cin >> N >> M;
	vector<ll> ary;
	for(int i = 0;i < N;i++){
		ll data;
		cin >> data;
		ary.push_back(data);
	}
	ll ans = INF;
	if(N == M) ans = accumulate(ary.begin(),ary.end(),(ll)0);
	else{
		int k = 6 * N / M;
		ans = INF;
		while(k--){
			int rand_pos = rand() % N;
			vector<ll> ring;
			for(int i = rand_pos;i < N;i++) ring.push_back(ary[i]);
			for(int i = 0;i < rand_pos;i++) ring.push_back(ary[i]);
			vector<ll> prefix_sum = pre_process(ring);
			vector<vector<ll>> dp(N, vector<ll>(M));
			ans = min(ans, find_min(dp, prefix_sum, ring));
		}
	}
	cout << ans;
}