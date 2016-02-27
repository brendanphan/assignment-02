/* ----------------------------------------------------------------------------
* Copyright &copy; 2016 Brendan Phan <brendanphan1@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

#include "buffer.h"
#include <iostream>

Buffer::Buffer(unsigned int size_x, unsigned int size_y)
	: size_x(size_x), size_y(size_y)
{
	data_ = new char[size_x*size_y];
	for (unsigned int i = 0; i < size_x*size_y; i++)
		data_[i] = ' ';
}
Buffer::~Buffer()
{
	delete[] data_;
}
char Buffer::get(unsigned int x, unsigned int y) const
{
	if (x > size_x || y > size_y)
	{
		std::cerr << "ERROR: `Buffer::get`: index out of bounds\n";
		exit(1);
	}
	return data_[y * size_x + x];
}
void Buffer::set(unsigned int x, unsigned int y, char c)
{
	if (x > size_x || y > size_y)
	{
		std::cerr << "ERROR: `Buffer::get`: index out of bounds\n";
		exit(1);
	}
	data_[y * size_x + x] = c;
}
void Buffer::set(unsigned int pos_x, unsigned int pos_y, std::string s)
{
	for (unsigned int i = 0, x = pos_x, y = pos_y; i < s.length(); i++)
	{
		if (s[i] == '\n')
		{
			y++;
			x = pos_x;
		}
		else
		{
			set(x++, y, s[i]);
		}
	}
}
void Buffer::draw() const
{
	for (unsigned int y = 0; y < size_y; y++)
	{
		for (unsigned int x = 0; x < size_x; x++)
		{
			std::cout << data_[y * size_x + x];
		}
		std::cout << std::endl;
	}
}
void Buffer::clear()
{
	data_ = new char[size_x*size_y];
	for (unsigned int i = 0; i < size_x*size_y; i++)
		data_[i] = ' ';
}

