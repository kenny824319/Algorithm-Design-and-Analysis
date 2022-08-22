#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

auto array = vector<pair<long long, long long>>({});
long long ans = 0;
long long a, b, c;

bool cmp(pair<long long, long long> x, pair<long long, long long> y){
	return x.second < y.second;
}


pair<long long, long long> L[2000001]; 
pair<long long, long long> R[2000001];

void merge_query(int l, int m, int r){
	int i, j;
    int n1 = m - l + 1;
    int n2 = r - m;

	for (i = 0; i < n1; i++)
        L[i] = array[l + i];
	
    for (j = 0; j < n2; j++)
		R[j] = array[m + 1 + j];

	
	
	i = 0;
	j = 0;
	int flag = 0;
	
	for(i = 0;i < n1;i++){
		while(a * R[j].first <= L[i].first * b + c || L[i].second == R[j].second){//找到比p[i]* (b / a) + (c / a)大的j
			j++;
			if(j == n2){
				flag = 1;
				break;
			}
		}
		ans += (n2 - j);
		if(flag == 1)
			break;
	}
	
	i = 0;
	j = 0;
	int k = l;
    
	while(i < n1 && j < n2){
		if(L[i].first <= R[j].first)
			array[k++] = L[i++];
		else
            array[k++] = R[j++];
    }
 

    while (i < n1)
        array[k++] = L[i++];
 
    while (j < n2)
        array[k++] = R[j++];
}

void merge_sort(int l, int r){
    if (l < r){
		int m = l + (r - l) / 2;
		if(array[l].second == array[r].second){
			merge_sort(l, m);
			merge_sort(m + 1, r);
			merge_query(l, m, r);
		}
		else{			
			int prev = m;
			int next = m+1;
			int flag = 0;
			while(prev < r){
				if(array[prev].second != array[next].second){
					m = prev;
					flag = 1;
					break;
				}
				prev = next;
				next++;
			}
			if(!flag){
				next = m-1;
				while(prev > l){
					if(array[prev].second != array[next].second){
						m = next;
						break;
					}
					prev = next;
					next--;
				}
			}
			merge_sort(l, m);
			merge_sort(m + 1, r);
			merge_query(l, m, r);
		}
    }
}

int main(){
	int n, i;
	
	cin >> n >> a >> b >> c;
	
	for(i = 0;i < n;i++){
		long long p, z;
		cin >> p >> z;
		array.push_back({p, z});
	}
	
	sort(array.begin(), array.end(), cmp);
	
	merge_sort(0, n-1);
	
	cout << ans << '\n';
	
}