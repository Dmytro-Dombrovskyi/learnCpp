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
public:
	explicit Ocean (const size_t); // constructor	
	virtual ~Ocean (); // destructor
	Ocean & operator=(const Ocean &a); // assignment constructor
	Ocean (const Ocean &a); // copy constructor

	const size_t GetTableSize( ) const { return tableSize_; }


	void CreateTable (const size_t);
	void CleanTable ();
	void FillTable ();
	void ShowTable () const ; // show table by console

	void ShowCitizens () const;
	void MoveCitizens (int steps);
	
};

class CounterCitizen {
private:	
	size_t nCivil;
	size_t nBlock;
	size_t nPredator;
	size_t nCell;
public:
	explicit CounterCitizen (const size_t value, 
			const size_t divideValue = 4) {		
		const size_t tempSize = value * value;
		nCivil = nBlock = nPredator = tempSize / divideValue;
		nCell = tempSize - nCivil - nBlock - nPredator;
	}

	virtual ~CounterCitizen ( ) { }

	const size_t Get_nCivil( ) const { return nCivil; }
	const size_t Get_nBlock( ) const { return nBlock; }
	const size_t Get_nPredator( ) const { return nPredator; }
	const size_t Get_nCell( ) const { return nCell; }

	const bool Is_nCivil( ) const { return nCivil ? true : false; }
	const bool Is_nBlock( ) const { return nBlock ? true : false; }
	const bool Is_nPredator( ) const { return nPredator ? true : false; }
	const bool Is_nCell( ) const { return nCell ? true : false; }
	const bool Is_nCitizens( ) const
	{
		if(Is_nCivil() == 0 && Is_nBlock() == 0 && Is_nPredator() == 0 && Is_nCell() == 0)
	}
	//void 

};

#endif
