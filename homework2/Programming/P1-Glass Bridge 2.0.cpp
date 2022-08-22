#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <climits>
/*
discussion with  b08902149 徐晨祐 & p10922001 黃佳琪 & b08208032 胡材溢 & b05504066 李旻翰
*/

using namespace std;

long long NEG_INF = LONG_LONG_MIN;
vector<vector<vector<long long>>> dp;


void helper(int m, int n, int k, vector<vector<long long>> &mp, deque<int> &offset){
	//table_size = k
	dp.resize(k);
	for(int table = 0;table < k;table++)
		dp[table].resize(m+1);
	for(int table = 0;table < k;table++)
		for(int i = 0;i <= m;i++)
			dp[table][i].resize(n+1, 0);
	long long Max;
	long long left, up, left2, up2;
	for(int i = 1;i <= m;i++)
		for(int j = 1;j <= n;j++){
			if(i == 1 && j == 1)
				continue;
			left = (j == 1) ? NEG_INF : dp[k-1][i][j-1];
			up = (i == 1) ? NEG_INF : dp[k-1][i-1][j];
			Max = max(left, up);
			up2 = (i - offset[k-1] >= 1) ? dp[k-1][i-offset[k-1]][j] : NEG_INF;
			Max = max(up2, Max);
			left2 = (j - offset[k-1] >= 1) ? dp[k-1][i][j-offset[k-1]] : NEG_INF;
			Max = max(left2, Max);
			if(Max == NEG_INF || mp[i][j] == NEG_INF)
				dp[0][i][j] = NEG_INF;
			else
				dp[0][i][j] = Max + mp[i][j];
			for(int jump = 1;jump < k;jump++){
				up2 = (i - offset[jump-1] >= 1) ? dp[jump-1][i-offset[jump-1]][j] : NEG_INF;
				left2 = (j - offset[jump-1] >= 1) ? dp[jump-1][i][j-offset[jump-1]] : NEG_INF;
				dp[jump][i][j] = max({left2, up2, dp[jump-1][i][j]});
			}
		}
		
		
	long long ans = dp[0][m][n];
	if(ans != NEG_INF){
		cout << "Passable" << endl;
		cout << ans << endl;
		deque<pair<int, int>> res;
		int cur_k = k - 1;
		int i = m;
		int j = n;
		while(i > 0 && j > 0){
			if(dp[0][i][j] == dp[cur_k][i][j]){
				cur_k = k - 1;
				res.push_front({i, j});
			}
			else{
				cur_k--;
			}
			left = (j == 1) ? NEG_INF : dp[cur_k][i][j-1];
			up = (i == 1) ? NEG_INF : dp[cur_k][i-1][j];
			Max = max(up, left);
			
			up2 = (i - offset[cur_k] >= 1) ? dp[cur_k][i-offset[cur_k]][j] : NEG_INF;
			Max = max(up2, Max);
			
			left2 = (j - offset[cur_k] >= 1) ? dp[cur_k][i][j-offset[cur_k]] : NEG_INF;
			Max = max(left2, Max);
			if(Max == up)
				i--;
			else if(Max == left)
				j--;
			else if(i - offset[cur_k] >= 1 && Max == up2)
				i -= offset[cur_k];
			else if(j - offset[cur_k] >= 1 && Max == left2)
				j -= offset[cur_k];
		}
		cout << res.size() << endl;
		for(auto it : res)
			cout << it.first << ' ' << it.second << endl;
	}
	else
		cout << "Impassable" << endl;
	dp.clear();
	
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t--){
		int m, n, k;
		cin >> m >> n >> k;
		int orig_k = k;
		deque<int> hash_table;
		while(k - k / 3 > 0){
			if(k <= 3)
				k--;
			hash_table.push_front(k - k / 3);
			k -= k / 3;
		}
		int table_size = hash_table.size();
		
		deque<int> offset;
		
		for(int i = 0;i < table_size - 1;i++)
			offset.push_back(hash_table[i+1] - hash_table[i]);
		
		offset.push_back(orig_k - hash_table[table_size - 1]);
		
		string data;
		vector<vector<long long>> mp(m+1, vector<long long>(n+1, 0));
		for(int i = 1;i <= m;i++)
			for(int j = 1;j <= n;j++){
				cin >> data;
				if(data == "X")
					mp[i][j] = NEG_INF;
				else
					mp[i][j] = stoll(data);
			}
		helper(m, n, table_size, mp, offset);
	}
}