/* ----------------------------------------------------------------------------
* Copyright &copy; 2016 Brendan Phan <brendanphan1@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */


#include <random>
#include <iostream>
#include "neighborhood.h"
#include "constants.h"
#include "shape.h"
#include <chrono>
#include <thread>
namespace 
{
	unsigned int mtrand(unsigned int low, unsigned int high)
	{
		static std::random_device rd;
		static std::mt19937 mt(rd());  // engine (mersenne twister)

		return std::uniform_int_distribution<unsigned int>(low, high)(mt);
	}

}
Neighborhood::Neighborhood(unsigned int size_x, unsigned int size_y)
	: size_x(size_x), size_y(size_y) 
{
	neighborhood_ = new Shape[size_x * size_y]();
	for (int filled = 0; filled < size_x*size_y*RATIO_FILLED; ) 
	{
		unsigned int x = mtrand(0, size_x - 1);
		unsigned int y = mtrand(0, size_y - 1);
		if (get(x, y).getType() == "empty")
		{
			set(x, y, mtrand(0, 1) ? Shape("triangle")
				: Shape("square"));
			filled++;
		}
	}
}
Neighborhood::~Neighborhood()
{
	delete[] neighborhood_;
}
Shape Neighborhood::get(unsigned int x, unsigned int y) const
{
	if (x > size_x || y > size_y)
	{
		std::cerr << "ERROR: `Neighborhood::get`: index out of bounds\n";
		exit(1);
	}
	return neighborhood_[y * size_x + x];
}
void Neighborhood::set(unsigned int x, unsigned int y, const Shape & s)
{
	if (x > size_x || y > size_y)
	{
		std::cerr << "ERROR: `Neighborhood::get`: index out of bounds\n";
		exit(1);
	}
	neighborhood_[y * size_x + x] = s;
}
void Neighborhood::move(unsigned int old_x, unsigned int old_y) 
{
	for (;;) 
	{
		unsigned int x = mtrand(0, size_x - 1);
		unsigned int y = mtrand(0, size_y - 1);
		if (get(x, y).getType() == "empty") 
		{
			set(x, y, get(old_x, old_y));
			set(old_x, old_y, Shape("empty"));
			break;
		}
	}
}
void Neighborhood::animate(unsigned int frames)
{
	Buffer b(size_x*Shape::size_x, size_y*Shape::size_y);
	for (unsigned int i = 0; i < frames; i++)
	{
		for (unsigned int y = 0; y < size_y; y++)
		{
			for (unsigned int x = 0; x < size_x; x++)
			{
				neighborhood_[y*size_x + x].drawToBuffer(b, x * Shape::size_x, y * Shape::size_y);
			}
		}
		b.draw();
		for (unsigned int y = 0; y < size_y; y++)
			 {
					for (unsigned int x = 0; x < size_x; x++)
					{
						if (!neighborhood_[y*size_x + x].isHappy(*this, x, y))
						move(x, y);
					}
			}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
