#pragma once
#ifndef OCEAN_H_INCLUDED
#define OCEAN_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include "citizens.h"
#include "ocean_help_classes.h"


// class ocean
class Ocean {
private:
	size_t tableSize_;
	Cell ***table_;
	CounterCitizen *counter;
	void CreateTable(const size_t);
	void CleanTable();
	void CreateNewCitizen(CounterCitizen &temp,
								 const int type_object,
								 const size_t y_coord,
								 const size_t x_coord);
	void PredatorEatCivil(const coordinates &current,
								 const coordinates &compared);
public:
	explicit Ocean (const size_t); // constructor
	virtual ~Ocean (); // destructor
	Ocean & operator=(const Ocean &a); // assignment constructor
	Ocean (const Ocean &a); // copy constructor

	size_t GetTableSize( ) const { return tableSize_; }

	void FillTable ();
	void ShowTable () const ; // show table by console

	void ShowCitizens() const {
		counter->Show_Citizens();
	}
	void MoveCitizens (int steps = 1);
};

#endif
