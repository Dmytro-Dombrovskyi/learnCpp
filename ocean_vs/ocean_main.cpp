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
        std::cout << std::endl;
		my_Ocean.MoveCitizens();
		my_Ocean.ShowTable();
		my_Ocean.ShowCitizens( );
	}
	catch(std::logic_error &log_err) { std::cerr << log_err.what(); }
	catch(std::exception &ex) { std::cerr << ex.what( ); }
	catch(...) { std::cerr << "Unknown error!"; }

	std::cout << "\nDone!";
	std::cin.get();
	return 0;
}
