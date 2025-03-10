/*
Finds the kth smallest element in O(n) time, based on median of median select algorithm
Also contains Lomuto's and Hoare's algorithms for partitioning an array with given pivot
*/

#include<iostream>
#include<vector>
#include<algorithm>

int Lomuto_partition(std::vector<int>&vec, int pivot, int l, int r){ // vec[l...r]
    // swap pivot with the last element
    int temp = vec[pivot];
    vec[pivot] = vec[r];
    vec[r] = temp; 
    // set i to the l
    int i = l;
    int key = vec[r];
    for(int j = l; j < r ;j++){
        if(vec[j] < key){ // swap with i and update if found a smaller element
            temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            i++;
        }
    }
    // swap the pivot element with i and return its position in the array relative to l
    temp = vec[r];
    vec[r] = vec[i];
    vec[i] = temp;
    return i-l;
}
void Hoare_partition(std::vector<int>&vec, int pivot, int l, int r){
    int temp = vec[pivot];
    vec[pivot] = vec[l];
    vec[l] = temp;
    int key = vec[l];

    int start = l,end = r;
    while(start < end){ // if they do arrive at a common point it will be the same value == pivot hacne no issues
        while(start <=r && vec[start] < key){start++;}
        while(end >= l && vec[end] > key ){end--;}
        if(start <= r and end >= l){
            temp = vec[start];
            vec[start] = vec[end];
            vec[end] = temp;
        }
    }
}
// finds median of a 5 element array, if less elements, pad with +inf
int median(std::vector<int> vec, int l , int r){
    std::vector<int>temp;
    for(int j = 0 ; j < 5 ; j++){
        if(j+l<=r){temp.push_back(vec[j+l]);}
        else{temp.push_back(__INT32_MAX__);}
    } 
    std::sort(temp.begin(),temp.end());
    return temp[2];
}


int MoM_select(std::vector<int>&vec, int l, int r, int k){ 
    //base case : sort and find if size is smaller than 10
    if(r-l <= 9){
        std::sort(vec.begin()+l, vec.begin()+r+1);
        return vec[k+l];
    }
    // vector of subgroup medians
    std::vector<int>medians;
    int offset = (r-l+1)%5; // modulo wrt 5
    
    for(int j = l; j <= r - offset; j+=5 ){
        medians.push_back(median(vec,j,r));
    }
    
    if(offset !=0 ) medians.push_back(median(vec,r-offset+1,r)); 
    
    int n = medians.size();
    int mom = MoM_select(medians, 0, n - 1 ,n/2 ); // find the median of these medians
    
    int idx; // find index of the mom
    for(int j = l ; j <=r; j++){
        if(mom == vec[j]){idx = j;break;}
    }
    
    int p = Lomuto_partition(vec,idx,l,r); // partition and find the position of mom
    
    if(p == k){
        return mom;
    }
    else if(p > k){
        return MoM_select(vec,l,l+p-1,k);
    }
    else{
        return MoM_select(vec,p+1+l,r,k-(p+1)); 
    }
}
