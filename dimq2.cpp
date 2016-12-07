#include <iostream>

template<int L, int M, int T, int I, int Q, int N, int J>
class DimQ
{
  public:  
    double value;
    DimQ():value(0) {}
    DimQ(double v):value(v) {}

	// оператор Унарный минус
	DimQ& operator-() {
		DimQ * ret = new DimQ(-value);
		return *ret;
	}
    // операторы сложения и вычитания только для одинаковых размерностей
    DimQ& operator+(DimQ other) {
        DimQ * ret = new DimQ(value+other.value);
    	return *ret;
	}
    DimQ& operator-(DimQ other) {
        DimQ * ret = new DimQ(value-other.value);
    	return *ret;
	}
    // Операторы умножения и деления вынесены за описание класса.
};
// Операторы умножения и деления вынесены за описание класса. Два набора размерностей для разных аргументов
// умножение
template<int L, int M, int T, int I, int Q, int N, int J, int oL, int oM, int oT, int oI, int oQ, int oN, int oJ>
DimQ<L+oL,M+oM,T+oT,I+oI,Q+oQ,N+oN,J+oJ>& operator*(DimQ<L,M,T,I,Q,N,J> nom, DimQ<oL,oM,oT,oI,oQ,oN,oJ> denom) {
	// размерности нужно сложить
	DimQ<L+oL,M+oM,T+oT,I+oI,Q+oQ,N+oN,J+oJ> * new_type = new DimQ<L+oL,M+oM,T+oT,I+oI,Q+oQ,N+oN,J+oJ>(nom.value*denom.value);
	return *new_type;
}
// деление
template<int L, int M, int T, int I, int Q, int N, int J, int oL, int oM, int oT, int oI, int oQ, int oN, int oJ>
DimQ<L-oL,M-oM,T-oT,I-oI,Q-oQ,N-oN,J-oJ>& operator/(DimQ<L,M,T,I,Q,N,J> nom, DimQ<oL,oM,oT,oI,oQ,oN,oJ> denom) {
	// размерности нужно вычесть
	DimQ<L-oL,M-oM,T-oT,I-oI,Q-oQ,N-oN,J-oJ> * new_type = new DimQ<L-oL,M-oM,T-oT,I-oI,Q-oQ,N-oN,J-oJ>(nom.value/denom.value);
	return *new_type;
}

// вывод в поток с размерностью
template<int L, int M, int T, int I, int Q, int N, int J>
std::ostream& operator<<(std::ostream& out, const DimQ<L,M,T,I,Q,N,J>& dimq)
{
	std::string str = " "; // здесь формируется размерность
	// для типов скорость, ускорение и ньютон сделаем красивый вывод
	if (L==1 && M==0 && T==-1 && I==0 && Q==0 && N==0 && J==0)
        return out << dimq.value << " m/s" ;
	
	if (L==1 && M==0 && T==-2 && I==0 && Q==0 && N==0 && J==0)
        return out << dimq.value << " m/s^2" ;
	
	if (L==1 && M==1 && T==-2 && I==0 && Q==0 && N==0 && J==0)
        return out << dimq.value << " kg*m/s^2"; //Newton
	
	if (L!=0) { // метр
		str += "m";
		if (L!=1) str += "^(" + std::to_string(L) + ")";
	}
	if (M!=0) { // килограмм
        if ( str.length()>0 ) str+="*"; // если не пусто, то знак умножения допишем
		str += "kg";
		if (M!=1) str += "^(" + std::to_string(M) + ")"; // степени отличные от первой выведем
	}
	if (T!=0) { // секунда
        if ( str.length()>0 ) str+="*";
		str += "s";
		if (T!=1) str += "^("  + std::to_string(T) + ")";
	}
	if (I!=0) { // ампер
        if ( str.length()>0 ) str+="*";
		str += "A";
		if (I!=1) str += "^(" + std::to_string(I) + ")";
	}
	if (Q!=0) { // кельвин
        if ( str.length()>0 ) str+="*";
		str += "K";
		if (Q!=1) str += "^(" + std::to_string(Q) + ")";
	}
	if (N!=0) { // моль
        if ( str.length()>0 ) str+="*";
		str += "mol";
		if (N!=1) str += "^(" + std::to_string(N) + ")";
	}
	if (J!=0) { // кандела
        if ( str.length()>0 ) str+="*";
		str += "cd";
		if (J!=1) str += "^(" + std::to_string(J) + ")";
	}
    return out << dimq.value <<  str ;
}

typedef DimQ<1, 0, 0, 0, 0, 0, 0> Length; // введем базовые типы
typedef DimQ<0, 1, 0, 0, 0, 0, 0> Mass;
typedef DimQ<0, 0, 1, 0, 0, 0, 0> Time;
typedef DimQ<0, 0, 0, 1, 0, 0, 0> Current; // Ампер
typedef DimQ<0, 0, 0, 0, 1, 0, 0> Temperature;
typedef DimQ<0, 0, 0, 0, 0, 1, 0> Mole;
typedef DimQ<0, 0, 0, 0, 0, 0, 1> Candela;

typedef DimQ<1, 0, -1, 0, 0, 0, 0> Velocity ; // тип Скорость m/s
typedef DimQ<1, 0, -2, 0, 0, 0, 0> Acceleration; // тип Ускорение m/s^2
typedef DimQ<0, 0, 0, 0, 0, 0, 0> Dimensionless; // Безразмерный тип


int main() 
{
    
    Length l = {100}; // Длина
    Time t = {20}; // Время  
	// l2 = l+t; // дает ошибку как и положено

	Velocity v = l/t; // скорость 
	std::cout << v << "\n";

	Acceleration a = v/t; // ускорение
	std::cout << a << "\n";
	
	// тип переменной на усмотрение компилятора
	auto smth = v*a*a/t;
	std::cout << smth << "\n";
	 
	auto dimensionless = v/v; // безразмерная величина
	std::cout << dimensionless << "\n";
	
	// Ошибка компиляции!
	// Dimensionless d = v;
	// Mass m = v;
	// Amount a = d;
	
	Mass m = {5};
	auto newton = m*a;
	std::cout << newton << "\n";
}                                          
