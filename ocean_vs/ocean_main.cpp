#include <iostream>
#include "ocean.h"

int main() {
	srand (time (NULL));
	ocean my_ocean (5);
	my_ocean.show_citizens ();	
	my_ocean.fill_table ();
	my_ocean.show_citizens ();
	
	
	std::cout << "\nDone!";
	std::cin.get();
	return 0;
}
