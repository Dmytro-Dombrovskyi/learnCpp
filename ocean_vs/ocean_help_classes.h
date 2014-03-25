#pragma once
#ifndef OCEAN_HELP_CLASSES_H
#define OCEAN_HELP_CLASSES_H
#include <iostream>
#include <stdexcept>
#include <exception>
#include <cstdlib>

// help class ocean for saving numbers of citizens
class CounterCitizen
{
private:
	enum object_ { civil, block, predator, cell };
	static const int nTypes_; // defined in ocean_help_classes.cpp
	size_t nCivil_;
	size_t nBlock_;
	size_t nPredator_;
	size_t nCell_;
public:
	// default formula for calculating citizens
	// (for creating )
	explicit CounterCitizen(const size_t value,
									const size_t divideValue = 4)	{
		const size_t tempSize = value * value;
		nCivil_ = nBlock_ = nPredator_ = tempSize / divideValue;
		nCell_ = tempSize - nCivil_ - nBlock_ - nPredator_;
	}

	virtual ~CounterCitizen() {}

	size_t Get_nCivil() const { return nCivil_; }
	size_t Get_nBlock() const { return nBlock_; }
	size_t Get_nPredator() const { return nPredator_; }
	size_t Get_nCell() const { return nCell_; }

	int Get_nTypes() const {return nTypes_;}

	bool Is_nCivil() const { return nCivil_ ? true : false; }
	bool Is_nBlock() const { return nBlock_ ? true : false; }
	bool Is_nPredator() const { return nPredator_ ? true : false; }
	bool Is_nCell() const { return nCell_ ? true : false; }

	bool Check_For_Citizens() const	{
		if(Is_nCivil() && Is_nBlock() &&
			Is_nPredator() && Is_nCell())
			return true;
		else
			return false;
	}

	bool Check_Citizens_By_Number(const int number) const	{
		switch(number)	{
			case civil:
				return Is_nCivil();
			case block:
				return Is_nBlock();
			case predator:
				return Is_nPredator();
			case cell:
				return Is_nCell();
			default:
				throw std::logic_error("Error choice in method Check_Citizens_By_Number!");
		}
	}

	void Minus_Citizen_By_Number(const int number)	{
		switch(number)	{
			case civil:	--nCivil_;
				break;
			case block: --nBlock_;
				break;
			case predator: --nPredator_;
				break;
			case cell: --nCell_;
				break;
			default:
				throw std::logic_error("Error choice in method: Minus_Citizen_By_Number!");
		}
	}

	void Minus_one_Civil()	{	if(nCivil_) --nCivil_;	}
	void Plus_one_Cell()	{	++nCell_; }

	// show number of citizens
	void Show_Citizens() const	{
		std::cout << "nCivil_:   " << nCivil_ << std::endl;
		std::cout << "nBlock_:   " << nBlock_ << std::endl;
		std::cout << "nPredator: " << nPredator_ << std::endl;
		std::cout << "nCell_:    " << nCell_ << std::endl;
	}
};

// write coordinates for method move in class Ocean
class coordinates
{
	int y_coord;
	int x_coord;
public:
	void Set_Coordinates(int y, int x)
	{ y_coord = y; x_coord = x; }

	int Get_Y_Coord() const { return y_coord; }
	int Get_X_Coord() const { return x_coord; }
};

// Check possible steps by inputed coordinates
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
	Side_For_Step(const int i_max_coord,  const int i_y_coord,
					  const int i_x_coord)
					  :maximal_coord_(i_max_coord),
					  y_coord_(i_y_coord),
					  x_coord_(i_x_coord) {
		// check for possible steps
		Right = (x_coord_ < maximal_coord_);
		Down = (y_coord_ < maximal_coord_);
		Left = (x_coord_ > 0);
		Up = (y_coord_ > 0);
	}
	virtual  ~Side_For_Step() {}

	bool Can_Go_Right() const { return Right; }
	bool Can_Go_Down() const { return Down; }
	bool Can_Go_Left() const { return Left; }
	bool Can_Go_Up() const { return Up; }
};

#endif
