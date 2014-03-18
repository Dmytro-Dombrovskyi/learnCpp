#include <iostream>
#include "ocean.h"

int main() {
	srand (time (NULL));
	//Ocean Ob_1(5);
	//std::cout << (Ob_1.GetTableSize( )) << std::endl;
	
	CounterCitizen CC1(5);
	bool n = CC1.Is_nBlock( );
	std::cout << n << std::endl;

	std::cout << "\nDone!";
	std::cin.get();
	return 0;
}
