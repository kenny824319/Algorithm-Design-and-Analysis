#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
/*discussion with b10902021 張佑亘 & b05504066 李旻翰*/

int main(){
	int n;
	cin >> n;
	vector<int> num(n+1);
	for(int i = 1;i <= n;i++)
		cin >> num[i];
	auto dp = vector<vector<long long>>(n+1, vector<long long>(n+1, -1));
	auto gcd_table = vector<vector<long long>>(n+1, vector<long long>(n+1, 1));
	int i, j;
	long long gcd_num, gcd_num2;
	for(i = 1;i <= n;i++)
		for(j = i+1;j <= n;j++)
			gcd_table[i][j] = gcd(num[i], num[j]);
	for(i = 1, j = i + 1;j <= n;i++, j++){//len = 2
		gcd_num = gcd_table[i][j];
		if(gcd_num > 1)
			dp[i][j] = gcd_num;
	}
	for(i = 1, j = i + 2;j <= n;i++, j++){//len = 3
		gcd_num = gcd_table[i][j-1];
		gcd_num2 = gcd_table[j-1][j];
		if(gcd_num > 1 && gcd_num2 > 1 && gcd_table[i][j] > 1)
			dp[i][j] = gcd_num + gcd_num2;
	}
	long long case1, case2, case3;
	long long gcd_ij, gcd_il, gcd_lj;
	for(int len = 4;len <= n;len++)
		for(i = 1, j = i + len - 1; j <= n;i++, j++){
			case1 = case2 = case3 = -1;
			gcd_ij = gcd_table[i][j];
			if(dp[i+1][j-1] != -1 && gcd_ij > 1){//case1
				case1 = dp[i+1][j-1] + gcd_ij;
			}
			for(int l=i+1;l < j;l++){//case2
				gcd_il = gcd_table[i][l];
				gcd_lj = gcd_table[l][j];
				if(l == i+1){
					if(gcd_il > 1 && gcd_lj > 1 && gcd_table[i][j] > 1 && dp[l+1][j-1] != -1)
						case2 = max(gcd_il + gcd_lj + dp[l+1][j-1], case2);
				}
				else if(l == j-1){
					if(gcd_il > 1 && gcd_lj > 1 && gcd_table[i][j] > 1 && dp[i+1][l-1] != -1)
						case2 = max(gcd_il + gcd_lj + dp[i+1][l-1], case2);
				}
				else if(dp[i+1][l-1] != -1 && dp[l+1][j-1] != -1 && gcd_il > 1 && gcd_lj > 1 && gcd_table[i][j] > 1){
					case2 = max(dp[i+1][l-1] + dp[l+1][j-1] + gcd_il + gcd_lj, case2);
				}
			}
			for(int m = i+1;m < j-1;m++){//case3
				if(dp[i][m] != -1 && dp[m+1][j] != -1)
					case3 = max(dp[i][m]+dp[m+1][j], case3);
			}
			dp[i][j] = max({case1, case2, case3});
		}
	cout << dp[1][n];
}