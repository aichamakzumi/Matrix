#pragma once
#include <iostream>

using namespace std;

class A
{
	double value;
public:
	A() : value(0.0) {}
	A(double v) : value(v) {}
	A(const A& other) : value(other.value) {}

	A& operator=(const A& other);

	A operator+(const A& other) const;
	A operator-(const A& other) const;
	A operator*(const A& other) const;
	A operator/(const A& other) const;

	A& operator+=(const A& other);
	A& operator-=(const A& other);
	A& operator*=(const A& other);
	A& operator/=(const A& other);

	bool operator<(const A& other) const;
	bool operator>(const A& other) const;
	bool operator<=(const A& other) const;
	bool operator>=(const A& other) const;
	bool operator==(const A& other) const;
	bool operator!=(const A& other) const;

	friend ostream& operator<<(ostream& os, const A& a);
	friend istream& operator>>(istream& is, A& a);

	double getValue() const { return this->value; }
};

A& A::operator=(const A& other)
{
	if (this != &other)
		this->value = other.value;
	return *this;
}

A A::operator+(const A& other) const { return A(this->value + other.value); }
A A::operator-(const A& other) const { return A(this->value - other.value); }
A A::operator*(const A& other) const { return A(this->value * other.value); }
A A::operator/(const A& other) const
{
	return A(this->value / other.value);
}

A& A::operator+=(const A& other) { this->value += other.value; return *this; }
A& A::operator-=(const A& other) { this->value -= other.value; return *this; }
A& A::operator*=(const A& other) { this->value *= other.value; return *this; }
A& A::operator/=(const A& other)
{
	this->value /= other.value;
	return *this;
}

bool A::operator<(const A& other)  const { return this->value < other.value; }
bool A::operator>(const A& other)  const { return this->value > other.value; }
bool A::operator<=(const A& other) const { return this->value <= other.value; }
bool A::operator>=(const A& other) const { return this->value >= other.value; }
bool A::operator==(const A& other) const { return this->value == other.value; }
bool A::operator!=(const A& other) const { return this->value != other.value; }

ostream& operator<<(ostream& os, const A& a)
{
	os << a.value;
	return os;
}

istream& operator>>(istream& is, A& a)
{
	is >> a.value;
	return is;
}
