#include <iostream>

template<int L, int M, int T, int I, int Q, int N, int J>
class DimQ
{
  public:  
    double value;
    DimQ():value(0) {}
    DimQ(double v):value(v) {}

	// �������� ������� �����
	DimQ& operator-() {
		DimQ * ret = new DimQ(-value);
		return *ret;
	}
    // ��������� �������� � ��������� ������ ��� ���������� ������������
    DimQ& operator+(DimQ other) {
        DimQ * ret = new DimQ(value+other.value);
    	return *ret;
	}
    DimQ& operator-(DimQ other) {
        DimQ * ret = new DimQ(value-other.value);
    	return *ret;
	}
    // ��������� ��������� � ������� �������� �� �������� ������.
};
// ��������� ��������� � ������� �������� �� �������� ������. ��� ������ ������������ ��� ������ ����������
// ���������
template<int L, int M, int T, int I, int Q, int N, int J, int oL, int oM, int oT, int oI, int oQ, int oN, int oJ>
DimQ<L+oL,M+oM,T+oT,I+oI,Q+oQ,N+oN,J+oJ>& operator*(DimQ<L,M,T,I,Q,N,J> nom, DimQ<oL,oM,oT,oI,oQ,oN,oJ> denom) {
	// ����������� ����� �������
	DimQ<L+oL,M+oM,T+oT,I+oI,Q+oQ,N+oN,J+oJ> * new_type = new DimQ<L+oL,M+oM,T+oT,I+oI,Q+oQ,N+oN,J+oJ>(nom.value*denom.value);
	return *new_type;
}
// �������
template<int L, int M, int T, int I, int Q, int N, int J, int oL, int oM, int oT, int oI, int oQ, int oN, int oJ>
DimQ<L-oL,M-oM,T-oT,I-oI,Q-oQ,N-oN,J-oJ>& operator/(DimQ<L,M,T,I,Q,N,J> nom, DimQ<oL,oM,oT,oI,oQ,oN,oJ> denom) {
	// ����������� ����� �������
	DimQ<L-oL,M-oM,T-oT,I-oI,Q-oQ,N-oN,J-oJ> * new_type = new DimQ<L-oL,M-oM,T-oT,I-oI,Q-oQ,N-oN,J-oJ>(nom.value/denom.value);
	return *new_type;
}

// ����� � ����� � ������������
template<int L, int M, int T, int I, int Q, int N, int J>
std::ostream& operator<<(std::ostream& out, const DimQ<L,M,T,I,Q,N,J>& dimq)
{
	std::string str = " "; // ����� ����������� �����������
	// ��� ����� ��������, ��������� � ������ ������� �������� �����
	if (L==1 && M==0 && T==-1 && I==0 && Q==0 && N==0 && J==0)
        return out << dimq.value << " m/s" ;
	
	if (L==1 && M==0 && T==-2 && I==0 && Q==0 && N==0 && J==0)
        return out << dimq.value << " m/s^2" ;
	
	if (L==1 && M==1 && T==-2 && I==0 && Q==0 && N==0 && J==0)
        return out << dimq.value << " kg*m/s^2"; //Newton
	
	if (L!=0) { // ����
		str += "m";
		if (L!=1) str += "^(" + std::to_string(L) + ")";
	}
	if (M!=0) { // ���������
        if ( str.length()>0 ) str+="*"; // ���� �� �����, �� ���� ��������� �������
		str += "kg";
		if (M!=1) str += "^(" + std::to_string(M) + ")"; // ������� �������� �� ������ �������
	}
	if (T!=0) { // �������
        if ( str.length()>0 ) str+="*";
		str += "s";
		if (T!=1) str += "^("  + std::to_string(T) + ")";
	}
	if (I!=0) { // �����
        if ( str.length()>0 ) str+="*";
		str += "A";
		if (I!=1) str += "^(" + std::to_string(I) + ")";
	}
	if (Q!=0) { // �������
        if ( str.length()>0 ) str+="*";
		str += "K";
		if (Q!=1) str += "^(" + std::to_string(Q) + ")";
	}
	if (N!=0) { // ����
        if ( str.length()>0 ) str+="*";
		str += "mol";
		if (N!=1) str += "^(" + std::to_string(N) + ")";
	}
	if (J!=0) { // �������
        if ( str.length()>0 ) str+="*";
		str += "cd";
		if (J!=1) str += "^(" + std::to_string(J) + ")";
	}
    return out << dimq.value <<  str ;
}

typedef DimQ<1, 0, 0, 0, 0, 0, 0> Length; // ������ ������� ����
typedef DimQ<0, 1, 0, 0, 0, 0, 0> Mass;
typedef DimQ<0, 0, 1, 0, 0, 0, 0> Time;
typedef DimQ<0, 0, 0, 1, 0, 0, 0> Current; // �����
typedef DimQ<0, 0, 0, 0, 1, 0, 0> Temperature;
typedef DimQ<0, 0, 0, 0, 0, 1, 0> Mole;
typedef DimQ<0, 0, 0, 0, 0, 0, 1> Candela;

typedef DimQ<1, 0, -1, 0, 0, 0, 0> Velocity ; // ��� �������� m/s
typedef DimQ<1, 0, -2, 0, 0, 0, 0> Acceleration; // ��� ��������� m/s^2
typedef DimQ<0, 0, 0, 0, 0, 0, 0> Dimensionless; // ������������ ���


int main() 
{
    
    Length l = {100}; // �����
    Time t = {20}; // �����  
	// l2 = l+t; // ���� ������ ��� � ��������

	Velocity v = l/t; // �������� 
	std::cout << v << "\n";

	Acceleration a = v/t; // ���������
	std::cout << a << "\n";
	
	// ��� ���������� �� ���������� �����������
	auto smth = v*a*a/t;
	std::cout << smth << "\n";
	 
	auto dimensionless = v/v; // ������������ ��������
	std::cout << dimensionless << "\n";
	
	// ������ ����������!
	// Dimensionless d = v;
	// Mass m = v;
	// Amount a = d;
	
	Mass m = {5};
	auto newton = m*a;
	std::cout << newton << "\n";
}                                          
