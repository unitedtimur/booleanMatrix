/*
*
* by UnitedTimur (c) 2018
*
*/

#pragma once
#include "BoolVector.h"

class bm
{
public:

	bm(int row = 0, int column = 0);
	bm(char ** arr, int size);
	bm(const bm &);

	void resize(const int, const int);
	void setRow(const int, const bv &);
	void print();

	int weight();

	bm & logAnd(const int, const bv &);
	bm & logOr(const int, const bv &);
	bm & logXor(const int, const bv &);
	bm & slipLeft(const int, const int);
	bm & slipRight(const int, const int);
	bm & operator=(const bm &);
	bm & operator&=(const bm &);
	bm & operator|=(const bm &);
	bm & operator^=(const bm &);
	bm operator&(const bm &) const;
	bm operator|(const bm &) const;
	bm operator^(const bm &) const;
	bm operator~() const;
	bm & operator<<=(const unsigned int &);
	bm & operator>>=(const unsigned int &);
	bm operator<<(const unsigned int &) const;
	bm operator>>(const unsigned int &) const;

	bv conjuction() const;
	bv disjuction() const;
	bv logXor() const;

	const bv & operator[](const int) const;

	friend istream & operator>>(istream &, bm &);
	friend ostream & operator<<(ostream &, const bm &);

private:

	int row, column;
	bv * vector;
};