#pragma once
#ifndef OCEAN_H_INCLUDED
#define OCEAN_H_INCLUDED
#include "ocean_help_classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include "citizens.h"

// help class ocean
class CounterCitizen {
	size_t nCivil;
	size_t nBlock;
	size_t nPredator;
	size_t nCell;
	CounterCitizen (const size_t value, const size_t divideValue = 4) {
		const size_t tempSize = value * value;
		nCivil = nBlock = nPredator = tempSize / divideValue;		
		nCell = tempSize - nCivil - nBlock - nPredator;
	}
};

// class ocean 
class Ocean {
private:
	size_t tableSize_;
  Cell ***table_;
	
protected:
public:
	explicit Ocean (const size_t); // constructor	
	virtual ~Ocean (); // destructor
	Ocean & operator=(const Ocean &a); // assignment constructor
	Ocean (const Ocean &a); // copy constructor

	void FillTable ();
	void CleanTable ();
	void ShowTable () const ; // show table by console

	void ShowCitizens () const;
	void MoveCitizens (int steps);
	
};



#endif
