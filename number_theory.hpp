#include<vector>
#include<iostream>
#include "lin_alg.hpp"
/*
    Part of Shishu's standard math library
*/
long long int gcd(long long int a, long long int b){
    a = std::abs(a);
    b = std::abs(b);
    if(a > b){
        if(b == 0){return a;}
        return gcd(b, a%b);
    }
    return gcd(b,a);
}
long long int binary_gcd(long long int a, long long int b){
    if(a < b){
        return binary_gcd(b,a);
    }
    if(b == 0){return a;}
    if(b == 1){return 1;}

    if(a%2){
        if(b%2){
            return binary_gcd((a-b)/2, b);
        }
        else{
            return binary_gcd(a,b/2);
        }
    }
    else{
        if(b%2){
            return binary_gcd(a/2,b);
        }
        else{
            return binary_gcd(a/2,b/2);
        }
    }
}

// primality testing 
void sieve(std::vector<int> & primes, int n){
    std::vector<bool>isPrime(n+1); // dont even store the even numbers
    isPrime[1] = false;
    for(int i = 4; i <= n; i+=2){
        isPrime[i] = false;
    }
    for(int j = 3 ; j*j  <= n ; j+=2){ // can just do till sqrt n because the divisors of all numbers <= n will be found
        if(isPrime[j]){
            for(int i = j*j ; i <= n ; i += j){
                isPrime[i] = false;
            }
        }
    }
    for(int j = 2 ; j <= n ; j++){
        if(isPrime[j]){
            primes.push_back(j);
        }
    }
}
// possible optimisation reduce mem by half by sroting only odd numbers
long long int sqrt(long long int n){
    long long int start = 1;
    long long int end = n;
    long long int mid = (start+end)/2;
    while(start <= end){
        if(mid*mid == n){return mid;}
        else if(mid*mid < n){
            start = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }
    return 0; // chumma 
}
void primes_in_range(std::vector<long long int>& primes ,long long int m, long long int n){ //
    // to check primality of of k, query k - m in the vector
    // segmented sieve  
    // for small numbers can do sieve directly, for larger numbers do sieve from j to n
    long long int r = sqrt(n);
    std::vector<int>primes_temp;

    sieve(primes_temp, r);
    // do sieve on these guys
    std::vector<bool> check(n-m+1,true);
    for(long long int p : primes_temp){
        for(long long int j = std::max(p*p, ((m+p-1)/p)*p); j <= n ; j+=p){
            check[j-m] = false;
        }
    }
    // m == 1 corresponds to index 0, 
    if(m == 1){check[0] = false;} // if m == 1, 1 never set to false
}

long long int fast_exp(long long int a, long long int n, long long int p){ // only for p = prime
    long long int factor = a;
    long long int product = 1;
    n = n%(p-1);
    while(n){
        if(n%2){
            product = (factor*product)%p;
        }
        factor = (factor*factor)%p;
        n = (n>>1);
    }
    return product;
}
long long int bin_pow(long long int a, long long int n, long long int p){ // for any p 
    if(n == 0){return 1;}
    long long int product = bin_pow(a,n/2,p);
    product = (product*product)%p;
    if(n%2){
        product = (product*a)%p;
    }
    return product;
}
long long int mod_inverse(long long int a, long long int p){ // computes modular inverse wrt p, modulo p
    return bin_pow(a,p-2,p); 
}

// factorisation of integers








/*
    F_2k+1 = F_k+1**2 + F_k **2 
    F_2k = 2*F_k*F_k+1 - F_k**2
*/
std::pair<long long int,long long int> fib_doubling(long long int n){
    if(n == 0){return {0,1};}
    std::pair<long long int, long long int>p = fib_doubling(n>>1);

    long long int a = p.first*p.first;
    long long int b = 2*p.second*p.first;
    long long int c = p.second*p.second;

    return {a+c, b-a};
}
long long int fibonacci(long long int n, long long int p = 1000000007){ // returns modulo 
    if(n < 2){return n;}
    std::vector<std::vector<long long int>> mat = {{1,1},{1,0}};
    mat_power(mat,n-1,true,p);
    return mat[0][0];
}


