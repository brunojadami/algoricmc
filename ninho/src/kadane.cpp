#include<vector>
using namespace std;

// Simple version.
int kadane(vector<int> &array){
	int resp = 0, tmp_resp = 0;
	for(int i = 0; i < array.size(); i++){
		tmp_resp = max(0, tmp_resp + array[i]);
		resp = max(resp, tmp_resp);
	}
	return resp;
}

// Version which returns also the subsequence indexes.
// 
// The indexes returned are of the longest subsequence.
// Both if's can be ajusted in order to return other types of
// indexes.
int kadane(vector<int> &array, int &start_index, int &end_index){
	int resp = 0, tmp_resp = 0;
	int ind = 0;
	bool update_flag = false;
	for(int i =0; i < array.size(); i++){
		if(tmp_resp + array[i] < 0){
			update_flag = true;
			tmp_resp = 0;
		}
		else{
			if(update_flag)
				ind = i;
			update_flag = false;
			tmp_resp = tmp_resp + array[i];
		}

		if(resp <= tmp_resp){
			start_index = ind;
			end_index = i;
			resp = tmp_resp;
		}
	}
	return resp;
}
