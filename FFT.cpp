#include<iostream>
#include<vector>
#include<cmath>
const double pi = acos(-1);
class Complex{
    double real;
    double imaginary;
    public:
        Complex(){}
        Complex(int n){
            real = cos(2*pi/n);
            imaginary = sin(2*pi/n);
        } // nth root of unity
        Complex(double r, double i):real(r), imaginary(i){}
        double get_real(){return real;}
        Complex operator*(Complex& other){
            double real_op = real*(other.real) - imaginary*(other.imaginary);
            double imaginary_op = imaginary*(other.real) + real*(other.imaginary);
            return Complex(real_op,imaginary_op);
        }
        Complex operator+(Complex other){
            return Complex(real + other.real, imaginary + other.imaginary);
        }
        Complex operator-(Complex other){
            return Complex(real - other.real, imaginary - other.imaginary);
        }
        Complex operator/(int scale){
            return Complex(real/scale,imaginary/scale);
        }
};
// lots of errors in indexing and size allocation - shud be faster and thought ful particularly in for loops
class Polynomial{
    int degree;
    std::vector<double>coefficients;
    public:
        Polynomial(){}
        Polynomial(std::vector<Complex>coeffs){
            degree = coeffs.size()-1;
            coefficients.resize(degree+1);
            for(int j = 0; j <=degree ; j++){
                coefficients[j] = coeffs[j].get_real();
            }
        }
        friend Polynomial operator*(Polynomial& p1, Polynomial& p2);
        friend std::istream& operator>>(std::istream&, Polynomial&);
        void pad(int deg_max, std::vector<Complex>& coeff){
            coeff.resize(deg_max);
            for(int j = 0; j <= degree ; j++){
                coeff[j] = Complex(coefficients[j],0);
            }
            for(int j = degree + 1; j < deg_max; j++){
                coeff[j] = Complex(0,0);
            }
        }
        double evaluate(double x){
            int j = coefficients.size()-1;
            double val = 0;
            while(j>=0){
                val = val*x + coefficients[j];j--;
            }
            
            return val;
        }
};
std::istream& operator>>(std::istream& stream, Polynomial& p){
    int n;stream>>n;
    p.degree = n;
    p.coefficients.resize(n+1);
    for(int j = 0 ; j <= n; j++){
        stream>>p.coefficients[j];
    }
    return stream;
}
void FFT(const std::vector<Complex> coeff, std::vector<Complex>& eval, int start, int offset, bool invert){ // set up base cases
    int n = coeff.size()/offset;
    if(n == 1){eval[0] = coeff[start];return;}
    std::vector<Complex> eval_left((n>>1));
    std::vector<Complex> eval_right((n>>1));
    FFT(coeff, eval_left, start, (offset<<1),invert);
    FFT(coeff, eval_right, start + offset, (offset<<1),invert);
    
    Complex wn;
    wn = invert?Complex(-n):Complex(n);
    Complex w(1,0);
    Complex temp;
    for(int j = 0; j < n/2 ; j++){
        temp = w*eval_right[j];
        eval[j] = eval_left[j] + temp; // why does not work with Complex &
        eval[j+n/2] = eval_left[j] - temp; 
        w = (w*wn);
    }
}

void point_wise_multiply( std::vector<Complex> eval_1,  std::vector<Complex> eval_2, std::vector<Complex>& eval){
    for(int j = 0 ; j < eval.size(); j++){
        eval[j] = (eval_1[j])*(eval_2[j]);
    }
}

void convolve(std::vector<Complex> coeff_1, std::vector<Complex> coeff_2, std::vector<Complex>& coeff_3){
    int deg = coeff_1.size();
    std::vector<Complex>eval_1(deg), eval_2(deg),eval(deg);
    FFT(coeff_1, eval_1, 0, 1, false);
    FFT(coeff_2, eval_2, 0, 1, false);
    point_wise_multiply(eval_1, eval_2, eval);
    coeff_3.resize(eval.size());
    FFT(eval, coeff_3, 0, 1, true); // interpolation
}

Polynomial operator*(Polynomial& p1, Polynomial& p2){
    int deg_max = std::max(p1.degree, p2.degree) + 1; // to take care of n-1
    int x = 1;
    while(x < deg_max){
        x = (x<<1); // deg at most 2^32
    }
    deg_max = (x<<1); // to finally double the degree -- now everything set 
    std::vector<Complex>coeff_1,coeff_2,coeff_3;
    p1.pad(deg_max, coeff_1);
    p2.pad(deg_max, coeff_2);

    convolve(coeff_1, coeff_2,coeff_3);
    for(auto& elt :coeff_3){
        elt = elt/deg_max;
    }
    Polynomial result(coeff_3);
    return result;
}


int main(){
    Polynomial p1, p2;
    std::cin>>p1>>p2;
    Polynomial p3 = p1*p2;
    double x;
    std::cin>>x;
    std::cout<<p3.evaluate(x)<<std::endl;
}


// takeaway was --  DO PROPER RESIZING AND INDEXING