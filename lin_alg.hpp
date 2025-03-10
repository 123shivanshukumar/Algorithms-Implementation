#include<vector>
std::vector<std::vector<long long int>>& mat_mul(std::vector<std::vector<long long int>>& A, const std::vector<std::vector<long long int>>& B, bool inplace = true, long long int p = 1000000007){
    int p = B[0].size();
    int m = B.size();
    int n = A.size(); // n*m m*p
    std::vector<long long int>row(m,0);
    std::vector<std::vector<long long int>>C(n,row);
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < p; j++){
            for(int k = 0; k < m; k++){
                C[i][j] = (C[i][j] +  (A[i][k]*B[k][j])%p)%p;
            }
        }
    }
    if(inplace){A = C;}
    return C;
}
std::vector<std::vector<long long int>>& mat_power(std::vector<std::vector<long long int>>& A, long long int n, bool inplace = true, long long int p = 1000000007){
    int m = A.size();
    std::vector<long long int> row(m, 0);
    std::vector<std::vector<long long int>> product(m, row);
    std::vector<std::vector<long long int>> factor = A; 

    for(int j = 0; j < m ; j++){
        product[j][j] = 1;
    }

    while(n){
        if(n%2){
            mat_mul(product,factor,true,p);
        }
        mat_mul(factor,factor,true,p);
        n = (n>>1);
    }
    if(inplace){
        A = product;
    }
    return product;
}
// multiplies in place 
void add( std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C,bool sub){
    int n = A.size(), m = A[0].size();
    C.resize(n);
    C.assign(n,std::vector<int>(m));
    for(int j = 0 ; j < n ; j++){
        for(int i = 0; i < m ; i++){
            C[j][i] = sub?A[j][i] - B[j][i]:A[j][i] + B[j][i] ;
        }
    }
}



void mat_mul_strassen(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C){
    // do the mem efficient approcah also
    int n = A.size(), m = A[0].size(), p = B[0].size();
    // both are powers of 2
    int n_half = n/2, m_half = m/2, p_half = p/2;
    
    // for odd pad with 0s for better implementation
    std::vector<std::vector<int>> a00(n_half, std::vector<int>(m_half)), b00(m_half, std::vector<int>(p_half)) ;
    std::vector<std::vector<int>> a01(n_half, std::vector<int>(m_half)), b01(m_half, std::vector<int>(p_half)) ;
    std::vector<std::vector<int>> a10(n_half, std::vector<int> (m_half)), b10(m_half, std::vector<int> (p_half));
    std::vector<std::vector<int>> a11(n_half, std::vector<int> (m_half)), b11(m_half, std::vector<int> (p_half));

    std::vector<std::vector<int>> m1(n_half, std::vector<int>(p_half)), m2(n_half, std::vector<int>(p_half)), m3(n_half, std::vector<int>(p_half)), m4(n_half, std::vector<int>(p_half));
    std::vector<std::vector<int>> m5(n_half, std::vector<int>(p_half)), m6(n_half, std::vector<int>(p_half)), m7(n_half, std::vector<int>(p_half));

    // padded wth zeroes app

    for(int i = 0; i < n_half ; i++){
        for(int j = 0 ; j < m_half ; j++){
            a00[i][j] = A[i][j];
            a01[i][j] = A[i][j+m_half];
            a10[i][j] = A[i+n_half][j];
            a11[i][j] = A[i+n_half][j+m_half];
        }
    }
    for(int i = 0; i < m_half ; i++){
        for(int j = 0 ; j < p_half ; j++){
            b00[i][j] = B[i][j];
            b01[i][j] = B[i][j+p_half];
            b10[i][j] = B[i+m_half][j];
            b11[i][j] = B[i+m_half][j+p_half];
        }
    }
    
    std::vector<std::vector<int>> c1, c2, c3,c4,c5,c6,c7,c8,c9,c0;

    add(a00,a11,c1,false);
    add(a10,a11,c8,false);
    add(b00,b11,c2,false);
    add(b01,b11,c3,true);
    add(b10,b00,c4,true);
    add(a00,a01,c5,false);
    add(a10,a00,c6,true);
    add(a01,a11,c7,true);
    add(b00,b01,c9,false);
    add(b10,b11,c0,false);

    mat_mul_strassen(c1,c2,m1);
    mat_mul_strassen(c8,b00,m2);
    mat_mul_strassen(a00,c3,m3);
    mat_mul_strassen(a11,c4,m4);
    mat_mul_strassen(c5,b11,m5);
    mat_mul_strassen(c6,c9,m6);
    mat_mul_strassen(c7,c0,m7);

    std::vector<std::vector<int>>c00,c01,c10,c11,c_temp1,c_temp2;
    
    add(m1,m4,c_temp1,false);
    add(c_temp1,m5,c_temp2,true);
    add(c_temp2,m7,c00,false);

    add(m3,m5,c01,false);
    add(m2,m4,c10,false);

    add(m1,m2,c_temp1,true);
    add(c_temp1,m3,c_temp2,false);
    add(c_temp2,m6,c11,false);

    for(int i = 0; i < n_half ; i++){
        for(int j = 0 ; j < p_half ; j++){
            C[i][j] = c00[i][j];
            C[i][j+p_half] = c01[i][j];
            C[i+n_half][j] = c10[i][j];
            C[i+n_half][j+p_half]  = c11[i][j];
        }
    }
}
void toeplitz_vector(std::vector<std::vector<int>>& A, std::vector<int>& v){

}

void invert_mat(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& A_inv){    // using gaussian elimination

}
void sys_eqn();
int determinant_gauss(std::vector<std::vector<int>>& A ){

}
// matrix inversion and strassen
// clean up code and set up repo
