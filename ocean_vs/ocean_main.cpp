#include <iostream>
#include "ocean.h"

int main() {
	srand (static_cast<unsigned int>(time (NULL)));
	try
	{
		Ocean my_Ocean(3);
		my_Ocean.FillTable();
		my_Ocean.ShowTable();
		my_Ocean.ShowCitizens();

		my_Ocean.MoveCitizens();
		my_Ocean.ShowTable();
		my_Ocean.ShowCitizens( );
	}
	catch(std::exception &ex) { std::cerr << ex.what( ); }
	

	std::cout << "\nDone!";
	std::cin.get();
	return 0;
}
