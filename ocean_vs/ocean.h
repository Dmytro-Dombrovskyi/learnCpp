#pragma once
#ifndef OCEAN_H_INCLUDED
#define OCEAN_H_INCLUDED
//#include "ocean_help_classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include "citizens.h"

// help class ocean
class CounterCitizen
{
private:
	enum object_ { civil, block, predator, cell };
	static const int nTypes_;
	size_t nCivil_;
	size_t nBlock_;
	size_t nPredator_;
	size_t nCell_;
public:
	explicit CounterCitizen(const size_t value,
									const size_t divideValue = 4)
	{
		const size_t tempSize = value * value;
		nCivil_ = nBlock_ = nPredator_ = tempSize / divideValue;
		nCell_ = tempSize - nCivil_ - nBlock_ - nPredator_;
	}

	virtual ~CounterCitizen() {}

	const size_t Get_nCivil() const { return nCivil_; }
	const size_t Get_nBlock() const { return nBlock_; }
	const size_t Get_nPredator() const { return nPredator_; }
	const size_t Get_nCell() const { return nCell_; }

	const int Get_nTypes() const { return nTypes_; }

	const bool Is_nCivil() const { return nCivil_ ? true : false; }
	const bool Is_nBlock() const { return nBlock_ ? true : false; }
	const bool Is_nPredator() const { return nPredator_ ? true : false; }
	const bool Is_nCell() const { return nCell_ ? true : false; }

	const bool Check_For_Citizens() const
	{
		if(Is_nCivil() && Is_nBlock() &&
			Is_nPredator() && Is_nCell())
			return true;
		else
			return false;
	}

	const bool Check_Citizens_By_Number(const int number) const
	{
		switch(number)
		{
			case civil:
				return Is_nCivil();
			case block:
				return Is_nBlock();
			case predator:
				return Is_nPredator();
			case cell:
				return Is_nCell();
			default:
				throw std::exception
					("Error choice in method Check_Citizens_By_Number!");
		}
	}

	void Minus_Citizen_By_Number(const int number)
	{
		switch(number)
		{
			case civil:	--nCivil_;
				break;
			case block: --nBlock_;
				break;
			case predator: --nPredator_;
				break;
			case cell: --nCell_;
				break;
			default:
				throw std::exception
					("Error choice in method: Minus_Citizen_By_Number!");
		}
	}

	void Minus_one_Civil()
	{
		if(nCivil_) --nCivil_;
	}

	void Plus_one_Cell()
	{
		++nCell_;
	}


	void Show_Citizens() const
	{
		std::cout << "nCivil_:   " << nCivil_ << std::endl;
		std::cout << "nBlock_:   " << nBlock_ << std::endl;
		std::cout << "nPredator: " << nPredator_ << std::endl;
		std::cout << "nCell_:    " << nCell_ << std::endl;
	}
};
//class coordinates;
class Side_For_Step;

class coordinates
{
	int y_coord;
	int x_coord;
public:
	void Set_Coordinates(int y, int x)
	{ y_coord = y; x_coord = x; }

	const int Get_Y_Coord() const { return y_coord; }
	const int Get_X_Coord() const { return x_coord; }
};

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
	//void CheckSteps(coordinates &, coordinates &);
public:
	explicit Ocean (const size_t); // constructor	
	virtual ~Ocean (); // destructor
	Ocean & operator=(const Ocean &a); // assignment constructor
	Ocean (const Ocean &a); // copy constructor

	const size_t GetTableSize( ) const { return tableSize_; }
	
	void FillTable ();
	void ShowTable () const ; // show table by console

	void ShowCitizens( ) const;
	void MoveCitizens (/*int steps = 1*/);

	void PredatorEatCivil(const coordinates &current, const coordinates & compared) 
	{ 
		// delete Civil citizen
		delete table_[compared.Get_Y_Coord( )] [compared.Get_X_Coord( )];
		counter->Minus_one_Civil( );
		// move predator to new place
		table_[compared.Get_Y_Coord( )][compared.Get_X_Coord( )] = new Predator;
		delete table_[current.Get_Y_Coord( )][current.Get_X_Coord( )];
		// create Cell on previous place
		table_[current.Get_Y_Coord( )][current.Get_X_Coord( )] = new Cell;
		counter->Plus_one_Cell( );
	}
	
	//void Go_Right( );
};




class Side_For_Step
{
private:
	int maximal_coord_;
	int y_coord_;
	int x_coord_;
protected:
	bool Right;
	bool Down;
	bool Left;
	bool Up;	
public:
	Side_For_Step(const int i_max_coord,
					  const int i_y_coord,
					  const int i_x_coord)
					  :maximal_coord_(i_max_coord), y_coord_(i_y_coord),
					  x_coord_(i_x_coord)
	{
		// check for possible steps			
		Right = (x_coord_ < maximal_coord_);
		Down = (y_coord_ < maximal_coord_);
		Left = (x_coord_ > 0);
		Up = (y_coord_ > 0);
	}
	virtual  ~Side_For_Step( ) {}
	const bool Can_Go_Right() const { return Right; }
	const bool Can_Go_Down() const { return Down; }
	const bool Can_Go_Left() const { return Left; }
	const bool Can_Go_Up() const { return Up; }
};

#endif
