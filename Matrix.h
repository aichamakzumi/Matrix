#pragma once
#include <iostream>

using namespace std;

template <class T>
class Matrix
{
	T**  data;
	int  rows;
	int  cols;

	void Allocate();
	void Deallocate();

public:
	Matrix();
	Matrix(int r, int c);
	Matrix(const Matrix<T>& other);
	~Matrix();

	Matrix<T>& operator=(const Matrix<T>& other);

	int getRows() const { return this->rows; }
	int getCols() const { return this->cols; }

	T& operator()(int i, int j);
	const T& operator()(int i, int j) const;

	void FillFromKeyboard();

	template <class Generator>
	void FillRandom(Generator gen);

	void Print(ostream& os = cout) const;

	Matrix<T> operator+(const Matrix<T>& other) const;
	Matrix<T> operator-(const Matrix<T>& other) const;
	Matrix<T> operator*(const Matrix<T>& other) const;
	Matrix<T> operator/(const Matrix<T>& other) const;

	Matrix<T>& operator+=(const Matrix<T>& other);
	Matrix<T>& operator-=(const Matrix<T>& other);
	Matrix<T>& operator*=(const Matrix<T>& other);
	Matrix<T>& operator/=(const Matrix<T>& other);

	T FindMax() const;
	T FindMin() const;

	friend ostream& operator<<(ostream& os, const Matrix<T>& m)
	{
		m.Print(os);
		return os;
	}

private:
	void CheckDimensions(const Matrix<T>& other) const;
};


template <class T>
void Matrix<T>::Allocate()
{
	this->data = new T*[this->rows];
	for (int i = 0; i < this->rows; ++i)
		this->data[i] = new T[this->cols];
}

template <class T>
void Matrix<T>::Deallocate()
{
	if (this->data)
	{
		for (int i = 0; i < this->rows; ++i)
			delete[] this->data[i];
		delete[] this->data;
		this->data = nullptr;
	}
}

template <class T>
Matrix<T>::Matrix() : data(nullptr), rows(0), cols(0) {}

template <class T>
Matrix<T>::Matrix(int r, int c) : rows(r), cols(c), data(nullptr)
{
	Allocate();
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			this->data[i][j] = T();
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& other) : rows(other.rows), cols(other.cols), data(nullptr)
{
	Allocate();
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			this->data[i][j] = other.data[i][j];
}

template <class T>
Matrix<T>::~Matrix()
{
	Deallocate();
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	if (this == &other)
		return *this;
	Deallocate();
	this->rows = other.rows;
	this->cols = other.cols;
	Allocate();
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			this->data[i][j] = other.data[i][j];
	return *this;
}

template <class T>
T& Matrix<T>::operator()(int i, int j)
{
	return this->data[i][j];
}

template <class T>
const T& Matrix<T>::operator()(int i, int j) const
{
	return this->data[i][j];
}

template <class T>
void Matrix<T>::FillFromKeyboard()
{
	cout << "Enter " << this->rows << "x" << this->cols << " matrix elements:" << endl;
	for (int i = 0; i < this->rows; ++i)
	{
		cout << "Row " << i + 1 << ": ";
		for (int j = 0; j < this->cols; ++j)
			cin >> this->data[i][j];
	}
}

template <class T>
template <class Generator>
void Matrix<T>::FillRandom(Generator gen)
{
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			this->data[i][j] = gen();
}

template <class T>
void Matrix<T>::Print(ostream& os) const
{
	for (int i = 0; i < this->rows; ++i)
	{
		for (int j = 0; j < this->cols; ++j)
			os << "\t" << this->data[i][j];
		os << endl;
	}
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
	CheckDimensions(other);
	Matrix<T> result(this->rows, this->cols);
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			result.data[i][j] = this->data[i][j] + other.data[i][j];
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
	CheckDimensions(other);
	Matrix<T> result(this->rows, this->cols);
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			result.data[i][j] = this->data[i][j] - other.data[i][j];
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
	CheckDimensions(other);
	Matrix<T> result(this->rows, this->cols);
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			result.data[i][j] = this->data[i][j] * other.data[i][j];
	return result;
}

template <class T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>& other) const
{
	CheckDimensions(other);
	Matrix<T> result(this->rows, this->cols);
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			result.data[i][j] = this->data[i][j] / other.data[i][j];
	return result;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) { *this = *this + other; return *this; }

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) { *this = *this - other; return *this; }

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) { *this = *this * other; return *this; }

template <class T>
Matrix<T>& Matrix<T>::operator/=(const Matrix<T>& other) { *this = *this / other; return *this; }

template <class T>
T Matrix<T>::FindMax() const
{
	T maxVal = this->data[0][0];
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			if (this->data[i][j] > maxVal)
				maxVal = this->data[i][j];
	return maxVal;
}

template <class T>
T Matrix<T>::FindMin() const
{
	T minVal = this->data[0][0];
	for (int i = 0; i < this->rows; ++i)
		for (int j = 0; j < this->cols; ++j)
			if (this->data[i][j] < minVal)
				minVal = this->data[i][j];
	return minVal;
}

template <class T>
void Matrix<T>::CheckDimensions(const Matrix<T>& other) const
{
	if (this->rows != other.rows || this->cols != other.cols)
		return;
}
