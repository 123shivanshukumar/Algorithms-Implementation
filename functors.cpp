#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;
int inversionCount2(vector<int>&arr, int low , int high){
    if(low == high){return 0;}
    if(high - low == 1){
        if(arr[high] < arr[low]){
            int temp = arr[high];
            arr[high] = arr[low];
            arr[low] = temp;
            return 1;
        }
        return 0;
    }
    int mid = (low+high)/2;//2
    int count = 0;
    count+= inversionCount2(arr, low , mid-1);//01
    count+= inversionCount2(arr, mid, high);//234
    vector<int>temp(high - low + 1);
    int cptr = high-low, bptr = high, aptr = mid - 1;
    while(bptr >= mid && aptr >= low){
        if(arr[aptr] > arr[bptr]){
            temp[cptr--] = arr[aptr--];
            count+= bptr-mid+1;
        }
        else{
            temp[cptr--] = arr[bptr--];
        }
    }
    while(aptr >= low){
        temp[cptr--] = arr[aptr--];
    }
    while(bptr >= mid){
        temp[cptr--] = arr[bptr--];
    }
    
    for(int j = low ; j <= high; j++){
        arr[j] = temp[j-low];
    }
    return count;
}
int inversionCount(vector<int> &arr) {
    return inversionCount2(arr, 0 , arr.size()-1);
}

int insertionSort(vector<int>arr)
{   
    int n = arr.size();
    int count = 0;
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            count++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // to account for the comparison in while
        arr[j + 1] = key;
    }
    return count;
}
int main(){
    srand(time(NULL));
    int size = rand()%50;
    vector<int>vec(size);
    vector<int>copy(size);
    for(int j = 0; j < size; j++){
        vec[j] = rand()%100;
        copy[j] = vec[j];
    }
    cout<<insertionSort(vec) - inversionCount(copy)<<endl;
    
}