#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define int long long
#define endl '\n'
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int gr(int r)
{
   uniform_int_distribution<int> uid(0,r-1);
   int val = uid(rng);
   return val+1;
}

int glr(int l, int r)
{
    int dif = r-l+1;
    int x = gr(dif) + l-1;
    return x;
}

int sz = 1;
int vecrand(vector<int> &v, map<int,int> &mp)
{
	int x = gr(sz)-1;
    mp[v[x]]++;
    int ans = v[x];
    if (mp[v[x]]==2){
	    swap(v[x],v[sz-1]);
	    sz--;
    }
	return ans;
}

#define cout outputFile[tc]


int32_t main()
{
    string file[10] = {"input/input00.txt", "input/input01.txt", "input/input02.txt", "input/input03.txt", "input/input04.txt", "input/input05.txt", "input/input06.txt", "input/input07.txt", "input/input08.txt", "input/input09.txt"};
    //string file[10] = {"input/input10.txt", "input/input11.txt", "input/input12.txt", "input/input13.txt", "input/input14.txt", "input/input15.txt", "input/input16.txt", "input/input17.txt", "input/input18.txt", "input/input19.txt"};
	//string file[10] = {"input/input20.txt", "input/input21.txt", "input/input22.txt", "input/input23.txt", "input/input24.txt", "input/input25.txt", "input/input26.txt", "input/input27.txt", "input/input28.txt", "input/input29.txt"};
	//string file[10] = {"input/input30.txt", "input/input31.txt", "input/input32.txt", "input/input33.txt", "input/input34.txt", "input/input35.txt", "input/input36.txt", "input/input37.txt", "input/input38.txt", "input/input39.txt"};
	//string file[10] = {"input/input40.txt", "input/input41.txt", "input/input42.txt", "input/input43.txt", "input/input44.txt", "input/input45.txt", "input/input46.txt", "input/input47.txt", "input/input48.txt", "input/input49.txt"};
    //string file[10] = {"input/input50.txt", "input/input51.txt", "input/input52.txt", "input/input53.txt", "input/input54.txt", "input/input55.txt", "input/input56.txt", "input/input57.txt", "input/input58.txt", "input/input59.txt"};
    //string file[10] = {"input/input60.txt", "input/input61.txt", "input/input62.txt", "input/input63.txt", "input/input64.txt", "input/input65.txt", "input/input66.txt", "input/input67.txt", "input/input68.txt", "input/input69.txt"};
    //string file[10] = {"input/input70.txt", "input/input71.txt" , "input/input72.txt" , "input/input73.txt", "input/input74.txt", "input/input75.txt", "input/input76.txt", "input/input77.txt", "input/input78.txt", "input/input79.txt"};
    // string file[10] = {"input/input80.txt", "input/input81.txt" , "input/input82.txt" , "input/input83.txt", "input/input84.txt", "input/input85.txt", "input/input86.txt", "input/input87.txt", "input/input88.txt", "input/input89.txt"};
    // string file[10] = {"input/input90.txt", "input/input91.txt" , "input/input92.txt" , "input/input93.txt", "input/input94.txt", "input/input95.txt", "input/input96.txt", "input/input97.txt", "input/input98.txt", "input/input99.txt"};
    // string file[10] = {"input/input100.txt", "input/input101.txt" , "input/input102.txt" , "input/input103.txt", "input/input104.txt", "input/input105.txt", "input/input106.txt", "input/input107.txt", "input/input108.txt", "input/input109.txt"};
    ofstream outputFile[10];
//	for (int i=0; i<10; i++) outputFile[i].open(file[i]);
    for (int i=0; i<10; i++) outputFile[i].open(file[i]);

    for(int tc=0; tc<10; tc++)
    {
//		int a = glr(1,1000000000), b = glr(1,1000000000);
//        cout<<a<<" "<<b<<endl;
        int n = glr(1 , 10) ;
        cout << n << endl ;
        vector<int> dum ;
        for(int i = 1 ; i <= n ; ++i){
            dum.push_back(i) ;
        }
        for(int i = 0 ; i < 2*n ; ++i){
            vector<int> A ;
            A = dum ;
            for(int i = n-1 ; i >= 0 ; --i){
                int j = glr(0 , i) ;
                //cout << i << " " << j << endl ;
                swap(A[i] , A[j]) ;
            }    
            for(int i = 0 ; i < A.size() ; ++i){
                cout << A[i] << " " ;
            }
            if(i == n-1){
                cout << endl ;
            }
            cout << endl ;
        }
    }          
    return 0;
}