#include <iostream>
#include "ocean.h"

int main() {
	srand (time (NULL));
	ocean a(7);
	a.show_citizens ();	
	a.fill_table ();
	a.show_citizens ();
	a.show_table ();
	a.move_citizens (1);
	a.show_table ();
	a.move_citizens (1);
	a.show_table ();
	
	std::cout << "\nDone!";
	std::cin.get();
	return 0;
}
