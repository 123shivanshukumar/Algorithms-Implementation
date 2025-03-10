#include<iostream>
#include<vector>

/*Maximum subarry Sum*/
// using DnC
struct quadrapule
{
    int left, right, max_sum,sum;
    quadrapule(int l, int r, int ms, int s):left(l),right(r),max_sum(ms),sum(s){}
};

int max_subarray_sum_dnc(std::vector<int>&vec){
    return max_subarray_sum_dnc_helper(vec, 0, vec.size() - 1).max_sum;

}   
quadrapule max_subarray_sum_dnc_helper(std::vector<int>& vec, int l, int r){
    if(l == r){
        return quadrapule(0, 0, std::max(0,vec[l]), vec[l]);
    }
    int mid = (l+r)/2;
    quadrapule left_ans = max_subarray_sum_dnc_helper(vec,l,mid);
    quadrapule right_ans = max_subarray_sum_dnc_helper(vec,mid+1,r);

    int left_max = std::max(left_ans.left, left_ans.sum + right_ans.left);
    int right_max = std::max(left_ans.right + right_ans.sum, right_ans.right);
    int mid_max = left_ans.right + right_ans.left;

    int max_sum  = std::max(left_max,right_max);
    max_sum = std::max(max_sum, mid_max);

    return quadrapule(left_max,right_max, max_sum, left_ans.sum + right_ans.sum); // subarray can be phi
}

// using DP
int max_subarray_sum_dp(std::vector<int>& vec){
    int n = vec.size();
    int mss_local, mss_global = 0;
    mss_local = vec[0];
    for(int j = 1; j < n ; j++){
        mss_local = std::max(vec[j], vec[j] + mss_local);
        mss_global = std::max(mss_global,mss_local);
    }
    return mss_global;
}
