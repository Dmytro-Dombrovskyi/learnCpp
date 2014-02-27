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
class CounterCitizen;

// class ocean 
class Ocean {
private:
	size_t tableSize_;
  Cell ***table_;
	CounterCitizen *counter;
protected:
public:
	explicit Ocean (const size_t); // constructor	
	virtual ~Ocean (); // destructor
	Ocean & operator=(const Ocean &a); // assignment constructor
	Ocean (const Ocean &a); // copy constructor

	void CreateTable (const size_t);
	void CleanTable ();
	void FillTable ();
	void ShowTable () const ; // show table by console

	void ShowCitizens () const;
	void MoveCitizens (int steps);
	
};

class CounterCitizen {
protected:
	friend class Ocean;
	size_t nCivil;
	size_t nBlock;
	size_t nPredator;
	size_t nCell;
	explicit CounterCitizen (const size_t value, 
													 const size_t divideValue = 4) {		
		const size_t tempSize = value * value;
		nCivil = nBlock = nPredator = tempSize / divideValue;
		nCell = tempSize - nCivil - nBlock - nPredator;
	}
	virtual ~CounterCitizen () {}
};


#endif
