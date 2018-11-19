/*
*
* by UnitedTimur (c) 2018
*
*/

#include "BoolMatrix.h"

bm::bm(int row, int column) : row(row), column(column), vector(nullptr)
{
	if (this->row > 0)
	{
		vector = new bv[row];
		if (this->column > 0)
		{
			for (int i = 0; i < row; i++)
			{
				vector[i] = bv(column);
			}
		}
	}
}

bm::bm(char ** arr, int row) : row(0), column(0), vector(nullptr)
{
	if (row > 0)
	{
		this->row = row;
		column = strlen(arr[0]);
		vector = new bv[this->row];

		for (int i = 0; i < this->row; i++)
		{
			vector[i] = bv(arr[i]);
		}
	}
}

bm::bm(const bm & tmp)
{
	if (this != &tmp)
	{
		row = tmp.row;
		column = tmp.column;

		vector = new bv[row];
		for (int i = 0; i < row; i++)
		{
			vector[i] = tmp.vector[i];
		}
	}
}

void bm::resize(const int row, const int column)
{
	if (row >= 0 && column >= 0)
	{
		bv * temp = new bv[row];

		for (int i = 0; i < row; i++)
		{
			temp[i] = bv(row);
		}

		for (int i = (this->row < row ? this->row : row) - 1; i >= 0; i--)
		{
			temp[i] |= vector[i];
		}

		delete[] vector;
		vector = temp;
		this->row = row;
		this->column = column;
	}
}

void bm::setRow(const int index, const bv & tmp)
{
	if (index >= 0 && index <= row)
	{
		vector[index].setZero(0, column);
		vector[index] |= tmp;
	}
}

void bm::print()
{
	for (int i = 0; i < row; i++)
	{
		vector[i].print();
		cout << endl;
	}
}

int bm::weight()
{
	int count{};

	for (int i = 0; i < row; i++)
	{
		count += vector[i].weigth();
	}

	return count;
}

bm & bm::logAnd(const int index, const bv & tmp)
{
	if (index >= 0 && index < row)
	{
		vector[index] &= tmp;
	}

	return *this;
}

bm & bm::logOr(const int index, const bv & tmp)
{
	if (index >= 0 && index < row)
	{
		vector[index] |= tmp;
	}

	return *this;
}

bm & bm::logXor(const int index, const bv & tmp)
{
	if (index >= 0 && index < row)
	{
		vector[index] ^= tmp;
	}

	return *this;
}

bm & bm::slipLeft(const int index, const int number)
{
	if (index >= 0 && index < row)
	{
		vector[index] <<= number;
	}

	return *this;
}

bm & bm::slipRight(const int index, const int number)
{
	if (index >= 0 && index < row)
	{
		vector[index] >>= number;
	}

	return *this;
}

bm & bm::operator=(const bm & tmp)
{
	if (this != &tmp)
	{
		delete[] vector;
		row = tmp.row;
		column = tmp.column;

		vector = new bv[row];

		for (int i = 0; i < row; i++)
		{
			vector[i] = tmp.vector[i];
		}
	}

	return *this;
}

bm & bm::operator&=(const bm & tmp)
{
	if (this != &tmp)
	{
		for (int i = 0; i < row; i++)
		{
			logAnd(i, tmp[i]);
		}
	}

	return *this;
}

bm & bm::operator|=(const bm & tmp)
{
	if (this != &tmp)
	{
		for (int i = 0; i < row; i++)
		{
			logOr(i, tmp[i]);
		}
	}

	return *this;
}

bm & bm::operator^=(const bm & tmp)
{
	if (this != &tmp)
	{
		for (int i = 0; i < row; i++)
		{
			logXor(i, tmp[i]);
		}
	}

	return *this;
}

bm bm::operator&(const bm & tmp) const
{
	if (this != &tmp)
	{
		bm temp(*this);
		temp &= tmp;
		return temp;
	}

	return *this;
}

bm bm::operator|(const bm & tmp) const
{
	if (this != &tmp)
	{
		bm temp(*this);
		temp |= tmp;
		return temp;
	}

	return *this;
}

bm bm::operator^(const bm & tmp) const
{
	if (this != &tmp)
	{
		bm temp(*this);
		temp ^= tmp;
		return temp;
	}

	return *this;
}

bm bm::operator~() const
{
	bm temp(row, column);
	for (int i = 0; i < row; i++)
	{
		temp.vector[i] = ~vector[i];
	}
	return temp;
}

bm & bm::operator<<=(const unsigned int & key)
{
	for (int i = 0; i < row; i++)
	{
		vector[i] <<= key;
	}

	return *this;
}

bm & bm::operator>>=(const unsigned int & key)
{
	for (int i = 0; i < row; i++)
	{
		vector[i] >>= key;
	}

	return *this;
}

bm bm::operator<<(const unsigned int & key) const
{
	bm temp(*this);
	temp <<= key;
	return temp;
}

bm bm::operator>>(const unsigned int & key) const
{
	bm temp(*this);
	temp >>= key;
	return temp;
}

bv bm::conjuction() const
{
	bv temp(column);

	temp.setOne(0, column);

	for (int i = 0; i < row; i++)
	{
		temp &= vector[i];
	}

	return temp;
}

bv bm::disjuction() const
{
	bv temp(column);

	for (int i = 0; i < row; i++)
	{
		temp |= vector[i];
	}

	return temp;
}

bv bm::logXor() const
{
	bv temp(column);
	for (int i = 0; i < row; i++)
	{
		temp ^= vector[i];
	}

	return temp;
}

const bv & bm::operator[](const int index) const
{
	if (index >= 0 && index < row)
	{
		return vector[index];
	}
	else
	{
		cerr << "//Fatal error. The index doesn't exist." << endl;
		system("pause");
		exit(1);
	}
}

istream & operator>>(istream & is, bm & tmp)
{
	int row = 0, column = 0;

	cout << "Enter the dimention of your boolean matrix at 'M x N', please." << endl;
	cout << "Enter the first dimention: ";
	cin >> row;
	cout << "Enter the secod dimention: ";
	cin >> column;

	if (row <= 0 || column <= 0)
	{
		cout << "//Fatal error. Enter the size of your boolean matrix!" << endl;
		system("pause");
		exit(1);
	}

	char ** arr = new char *[row] {};
	for (int i = 0; i < row; i++)
	{
		arr[i] = new char[column + 1]{};
		is >> arr[i];
		if (strlen(arr[i]) != column)
		{
			cout << "//Fatal Error. The length of string is more than column" << endl;
			system("pause");
			exit(1);
		}
	}

	tmp = bm(arr, row);

	for (int i = 0; i < row; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;

	return is;
}

ostream & operator<<(ostream & os, const bm & tmp)
{
	for (int i = 0; i < tmp.row; i++)
	{
		tmp.vector[i].print();
		os << endl;
	}

	return os;
}
