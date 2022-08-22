#include <iostream>
#include <climits>
#include <vector>

using namespace std;

int main(){
	int n;
	long long x, y, z;
	cin >> n >> x >> y >> z;
	auto num = vector<long long>(n, 0);
	for(int i = 0;i < n;i++)
		cin >> num[i];
	auto dp = vector<long long>(n, 0);
	
	dp[1] = x * num[0] + z * num[1];
	long long res = dp[1];
	for(int i = 2;i < n;i++){		
		dp[i] = max(x * num[i-1] + z * num[i], dp[i-1] - z * num[i-1] + y * num[i-1] + z * num[i]);
		res = max(res, dp[i]);
	}
	
	cout << res;
}