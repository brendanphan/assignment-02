/* ----------------------------------------------------------------------------
* Copyright &copy; 2016 Brendan Phan <brendanphan1@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

#include "buffer.h"
#include "constants.h"
#include "neighborhood.h"
#include "shape.h"

void test_buffer() {
	Buffer b(TERM_SIZE_X, TERM_SIZE_Y);
	for (unsigned int y = 0; y < b.size_y; y++)
		for (unsigned int x = 0; x < b.size_x; x++)
			if ((x - 40)*(x - 40) + (y - 10)*(y - 10) == 50)
				b.set(x, y, '*');
	for (unsigned int y = 0; y < b.size_y; y++) {
		b.set(0, y, '|');
		b.set(b.size_x - 1, y, '|');
	}
	for (unsigned int x = 0; x < b.size_x; x++) {
		b.set(x, 0, '-');
		b.set(x, b.size_y - 1, '-');
	}
	b.draw();
}

void test_shape() {
	Buffer b(TERM_SIZE_X, TERM_SIZE_Y);
	Shape triangle("triangle");
	Shape square("square");
	for (unsigned int y = 0; y <= b.size_y - Shape::size_y; y += Shape::size_y) {
		for (unsigned int x = 0; x <= b.size_x - Shape::size_x * 2; x += Shape::size_x * 2) {
			triangle.drawToBuffer(b, x + Shape::size_x*((y + 0) % 2), y);
			square.drawToBuffer(b, x + Shape::size_x*((y + 1) % 2), y);
		}
	}
	b.draw();
}

int main() {
	test_buffer();
    test_shape();
	unsigned int size_x = TERM_SIZE_X/Shape::size_x;
	unsigned int size_y = TERM_SIZE_Y/Shape::size_y;
	Neighborhood(size_x, size_y).animate(1000);
	system("pause");
	return 0;  
}

