// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>;
#include <iomanip>;

using namespace std;

template <class T>

class Equation {

public:
	T a, b, c;

	Equation(T _a = 0, T _b = 0, T _c = 0) {

		a = _a;
		b = _b;
		c = _c;
	}
	Equation(const Equation& equation) //копирующий конструктор
	{
		a = equation.a;
		b = equation.b;
		c = equation.c;
	}
	void print() {
		cout << a << "x^2";
		if (b < 0) {
			cout << b << "x";

		}
		else {
			cout << "+" << b << "x";

		}

		if (c < 0) {

			cout << c;

		}
		else {

			cout << "+" << c;

		}
		cout << endl;
	}

	T Disc() {


		return (b * b - 4 * a * c);
	}

	T* getX() {


		return getX(Disc());
	}
	int getResultCount() {
		T d = Disc();
		if (d == 0) {
			return 1;
		}
		else if (d > 0) {
			return 2;
		}
		else {
			return 0;
		}
	}
	T* getX(T d) {
		if (d < 0) {
			return NULL;
		}
		if (a != 0) {
			if (d == 0) {
				return ValueToMass(-b / (2 * a));
			}
			else {
				T x1 = ((-b + sqrt(d)) / (2 * a));
				T x2 = ((-b - sqrt(d)) / (2 * a));

				T* result = new T[2];
				result[0] = x1;
				result[1] = x2;
				return result;
			}
		}
		else if (b != 0) {
			ValueToMass(-c / b);
		}
		else {
			return NULL;
		}


	}
	void printResult() {
		T* result = getX();
		int size = getResultCount();
		if (size == 0) {
			cout << "NO RESULT!" << endl;
		}
		else if (size == 1) {
			cout << "x = " << result[0];
		}
		else if (size == 2) {
			cout << "x1 = " << result[0] << endl;
			cout << "x2 = " << result[1] << endl;
		}
	}
private:
	T* ValueToMass(T v) {
		T* result = new T[1];
		result[0] = v;
		return result;
	}
};



#include <iostream>
#include <locale.h>

template <class T2>
class Tran	
{
	T2* that;	
	T2* prev;	
public:
	Tran() :prev(NULL), that(new T2) {}	
	Tran(T2 t)
	{
		that = new T2(t);
		prev = NULL;
	}
	~Tran() { delete that;  delete prev; }	
	Tran& operator=(const Tran& obj);	
	void Show(int);	
	int BeginTrans();	
	void Commit();	
	void DeleteTrans(); 
	T2* operator->();	
};
template <class T2>
Tran<T2>& Tran<T2>::operator=(const Tran<T2>& obj)
{
	if (this != &obj)
	{
		delete that; 
		that = new T2(*(obj.that)); 
	}
	return *this;
}
template <class T2>
T2* Tran<T2>::operator->()	
{
	return that;
}

template <class T2>
int Tran<T2>::BeginTrans()
{
	delete prev;
	prev = that;
	that = new T2(*prev);
	if (!that) return 0;
	return 1;
}
template <class T2>
void Tran<T2>::Commit()
{
	delete prev;
	prev = NULL;
}
template <class T2>
void Tran<T2>::DeleteTrans()  
{
	if (prev != NULL)
	{
		delete that;	
		that = prev;	
		prev = NULL;	
	}
}



int main()
{
	setlocale(LC_ALL, "Russian");

	Equation<double> equation(-1, 2, 5);

	equation.print();

	equation.printResult();

	Equation<float> equation1(1, 1, 1);

	equation1.print();

	equation1.printResult();


	Tran<Equation<double>> tr(equation);
	tr->print();
	if (tr.BeginTrans()) 
	{
		tr->a = -1;
		tr->b = 2;
		tr->c = 5;
		tr.Commit();	
	}
	tr->print();
	if (tr.BeginTrans()) 
	{
		tr->a = 26;

		tr->print();
		tr.DeleteTrans();

	}
	tr->print();
	return 0;
}