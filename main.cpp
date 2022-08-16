//This program defines the fractional data type as a separate class definition and comprises of mathematical operations on fractions

#include<iostream>
//Asserting that the fraction is proper, i.e. gcd(numerator, denominator) is one
class Fraction{
	public:
	int n_;//numerator: an Integer
	unsigned int d_;//denominator: a Natural Number

	explicit Fraction(int n = 1, int d = 1): n_(d< 0 ? -n : n), d_(d<0 ? -d : d)
		{
			Reduce();
		}//cannot be used for implicit conversion and copy-initialization
	Fraction(const Fraction& f): n_(f.n_), d_(f.d_){ }// Copy Constructor

	~Fraction(){}//
	Fraction& operator=(const Fraction& f){n_ = f.n_; d_ = f.d_; return *this; } //Copy Assignment Operator

	static void Write(const Fraction& f){//Printing the fractions in the format of n/d
		std::cout<< f.n_; 
		if((f.n_ != 0) && (f.d_ != 1)) std::cout<< "/" << f.d_;
	}

	static void Read(Fraction& f){ //Taking input fractions in the form of n/d
		std::cin>> f.n_ >>f.d_;
		f.Reduce();
	}

/*	friend ostream& operator<<(ostream& os, const Fraction& f){
		os << f.n_ ;
		if((f.n_ !=0) && (f.d_ !=1)) os << "/"<<f.d_;
		return os;
	}

	friend istream& operator>>(istream& is, Fraction& f){
		is>> f.n_ >> f.d_ ;
		Multiply(f);
		return is;
	}
*/
	static const Fraction UNITY;// Defining the basic fraction
	static const Fraction Zero;//Defining Zero/One

	Fraction Negate() const {return Fraction(-n_, d_);} //To multiply the fraction by Negative One: Unary Operation
	Fraction Preserve() const{return *this;} //Maintaining the same value: Unary Operation
	Fraction& Componendo(){return *this= Add(Fraction::UNITY);}//Unary Operation
	Fraction& Dividendo(){return *this = Subtract(Fraction::UNITY);}//Unary Operation
	Fraction Add(const Fraction& f2) const{//Adding fractions, Does not change the current object: Binary Operation
		unsigned int d = Fraction::lcm(d_, f2.d_);
		int n = n_ * (d / d_) + f2.n_*(d/f2.d_);
		return Fraction(n,d);
	}
		
	Fraction Subtract(const Fraction& f2) const{//Binary Operation
		return Add(f2.Negate());	
	}
		
	Fraction Multiply(const Fraction& f2) const{//Binary Operation
		return Fraction(n_*f2.n_, d_*f2.d_);	
	}
		
	Fraction Divide(const Fraction& f2) const{//Binary Operation
		return Multiply(f2.Invert());
	}	
		
	Fraction Modulus(const Fraction& f2) const{
		if(f2.n_ == 0) {throw "Divide by 0 is Undefined \n";}
		Fraction tf = Divide(f2);
		Fraction f = Subtract(Fraction(static_cast<int>(tf.n_ / tf.d_)).Multiply(f2));
		return f;
	}
	Fraction Invert() const{//Inverting a fraction: Unary Operation
		if(d_ == 0) throw "Division by 0 is Undefined \n";
		return Fraction(d_, n_);
	}
	
	double Doube() const {//Converting a fraction of form p/q to format double: Unary Operation
		return static_cast<double>(n_) / static_cast<double>(d_);
	}	
	bool Equal(const Fraction& f2) const{//Comparing two fractions, Not changing the current object: Binary Operation
		return ((n_ == f2.n_)&&(d_ == f2.d_));
	}	
	bool NotEqual(const Fraction& f2) const{ //Binary Operation
		return !(Equal(f2));
	}	
	bool Less(const Fraction& f2) const{//Binary Operation
		return Subtract(f2).n_ < 0;
	}	
	bool LessEqual(const Fraction& f2) const{//Binary Operation	
		return !Greater(f2);
	}	
	bool Greater(const Fraction& f2) const{ //Binary Operation
		return Subtract(f2).n_ > 0;
	}
	
	bool GreaterEqual(const Fraction& f2) const{//Binary Operation
		return !Less(f2);
	}
	
	static int gcd(int a, int b){//Computing Greatest Common Divisor of two numbers
		while(a != b)
			if(a>b) a = a-b;
			else b = b-a;
		return a;
	}	

	static int lcm(int a, int b){//Computing Least Common Multiple of two numbers
		return (a/ gcd(a,b))*b;
	}

	Fraction& Reduce(){//Reduing a fraction to it;s proper form
		if(d_ == 0) {throw "Fraction with Denominator 0 is undefined";}
		if(d_ < 0){ n_ = -n_;
			    d_ = static_cast<unsigned int>(-static_cast<int>(d_));
			    return *this;
	}
	
	if(n_ ==0) {d_ = 1; return *this;}
	unsigned int n= (n_ > 0) ? n_ : -n_ , g = gcd(n,d_);
	n_ /= static_cast<int>(g);//conversion of g is required to perform the division of n_ and g
	d_ /= g;
	return *this;
	}
};	

int main(){
	std::cout<<"Testing the Fractions Data Type" << std::endl;
	Fraction F1(5,3);
	Fraction F2(3,7);
	std::cout<< "Fractions initialised Successfully " << std::endl;
	std::cout<<"Fraction F1(5,3)= " ;
	Fraction::Write(F1);
	std::cout<< std::endl;
	std::cout<<"Fraction F2(3,7)= ";
	Fraction::Write(F2);
	std::cout<<std::endl;
	std::cout<<"Fractions F1 and F2 after Multiplication gives ";
	Fraction::Write(F1.Multiply(F2));
	std::cout<<std::endl;
	return 0;
// Some more statements to test the correction of all Unary and Binary Operations on Fractions defined as User Defined Data Types

}
