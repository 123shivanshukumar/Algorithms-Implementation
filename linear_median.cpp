#include<iostream>
#include<vector>
#include<algorithm>
//shud do some leetcode and 450 Dsa to get coding fluency -- go through what errors annoyed you the most
// - what input 
// - what shud be avoided 
int Lomuto_partition(std::vector<int>&vec, int pivot, int l, int r){
    int temp = vec[pivot];
    vec[pivot] = vec[r];
    vec[r] = temp; 
    int i = l;
    int key = vec[r];
    for(int j = l; j < r ;j++){
        if(vec[j] < key){
            temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            i++;
        }
    }
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
// might have long long int 
int median(std::vector<int> vec, int l , int r){
    std::vector<int>temp;
    for(int j = 0 ; j < 5 ; j++){
        if(j+l<=r){temp.push_back(vec[j+l]);}
        else{temp.push_back(__INT32_MAX__);}
    } 
    std::sort(temp.begin(),temp.end());
    return temp[2];
}
// int access(std::vector<int>& vec,int l, int r, int i){} // to access the right elt / avoid padding

int MoM_select(std::vector<int>&vec, int l, int r, int k){ // correct
    if(r-l <= 9){
        std::sort(vec.begin()+l, vec.begin()+r+1);
        return vec[k+l];
    }
    std::vector<int>medians;
    int offset = (r-l+1)%5;
    for(int j = l; j <= r - offset; j+=5 ){
        medians.push_back(median(vec,j,r));
    }
    if(offset !=0 ) medians.push_back(median(vec,r-offset+1,r));
    int n = medians.size();
    int mom = MoM_select(medians, 0, n - 1 ,n/2 );
    
    int idx;
    for(int j = l ; j <=r; j++){
        if(mom == vec[j]){idx = j;break;}
    }
    // std::cout<<idx<<std::endl;
    int p = Lomuto_partition(vec,idx,l,r);
    // std::cout<<p<<std::endl;
    if(p == k){
        return mom;
    }
    else if(p > k){
        return MoM_select(vec,l,l+p-1,k);
    }
    else{
        return MoM_select(vec,p+1+l,r,k-(p+1)); // k is the rank in this subarray
    }
}


//testing functionalities
void print(std::vector<int>&v){for(auto elt:v){std::cout<<elt<<" ";}std::cout<<std::endl;}
void input(std::vector<int>&v){for(auto& elt:v){std::cin>>elt;}}
int main(){
    int size,k;
    std::cin>>size>>k;
    std::vector<int> vec(size);
    input(vec);
    std::cout<<MoM_select(vec,0,size-1,k)<<std::endl;
}
/*
deadline do all tehe alofs somehow in 30 mins common use all ur energy */