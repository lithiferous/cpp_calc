#include "iostream"
#include "iomanip"
#include "fstream"
#include "math.h"

using namespace std;

class rectangle {
private:
	float m_length, m_wide;
public:
	rectangle(float length, float wide)
	{
		m_length = length;
		m_wide = wide;
	}
public:
	float square() const
	{
		return this->m_length * this->m_wide;
	}

	float perimeter() const
	{
		return (m_length + m_wide) * 2;
	}
};

class triangle {
private:
	float m_a, m_b, m_c;
public:
	triangle(float a, float b, float c):
		m_a(a),
		m_b(b),
		m_c(c)
	{
	}
public:
	float perimeter() const
	{
		return m_a + m_b + m_c;
	}

	float square() const
	{
		float halfP = perimeter() / 2;
		return sqrt(halfP * (halfP - m_a) * (halfP - m_b) * (halfP - m_c));
	}
};


int main()
{
	const rectangle a(10, 5);
	const triangle b( 7, 3, 9 );
		cout << "square: "
		<< a.square() << " " << a.perimeter() << "\n"
		<< "triangle: "
		<< b.square() << " " << b.perimeter() << "\n";
}
