#include "ocean.h"

const int CounterCitizen::nTypes_ = 4; // static private member

// constructor by default
Ocean::Ocean (const size_t i_size)
	: tableSize_(i_size) 
{
	this->CreateTable (tableSize_);	
	counter = new CounterCitizen (tableSize_);
}
// get new memory to member table
void Ocean::CreateTable (const size_t i_size) {
	table_ = new Cell**[i_size];
	for(size_t i = 0; i < i_size; ++i) {
		table_[i] = new Cell*[i_size];
	}
	for(size_t i = 0; i < i_size; ++i) {
		for(size_t j = 0; j < i_size; ++j) {
			table_[i][j] = nullptr;
		}
	}
}

// delete all memory in current class
void Ocean::CleanTable () {
	for(size_t i = 0; i < tableSize_; ++i) {
		for(size_t j = 0; j < tableSize_; ++j) {
			delete table_[i][j];
			table_[i][j] = nullptr;
		}
	}
	for(size_t i = 0; i < tableSize_; ++i) {
		delete[]table_[i];
		table_[i] = nullptr;
	}
	delete[]table_;
	table_ = nullptr;	
}

// destructor for class ocean
Ocean::~Ocean () {
	this->CleanTable ();	
	delete counter;
	counter = nullptr;
}

// assignment constructor for class ocean
Ocean & Ocean::operator=(const Ocean &a) {
	if(this != &a) {		
		Cell ***temp = new Cell**[a.tableSize_];
		for(size_t i = 0; i < a.tableSize_; ++i) {
			temp[i] = new Cell*[a.tableSize_];
		}
		for(size_t i = 0; i < a.tableSize_; ++i) {
			for(size_t j = 0; j < a.tableSize_; ++j) {
				if(a.table_[i][j] == nullptr)
					temp[i][j] = nullptr;					
				else
					temp[i][j] = new Cell(*(a.table_[i][j]));
			}
		}
		// delete data in current class
		this->CleanTable ();
		tableSize_ = a.tableSize_;
		table_ = temp;
		counter = a.counter;		
	}
	return *this;
}
// copy constructor for class ocean
Ocean::Ocean (const Ocean &a) {	
	// get new memory for current class
	table_ = new Cell**[a.tableSize_];
	for(size_t i = 0; i < a.tableSize_; ++i) {
		table_[i] = new Cell*[tableSize_];
	}
	for(size_t i = 0; i < a.tableSize_; ++i) {
		for(size_t j = 0; j < a.tableSize_; ++j) {
			table_[i][j] = new Cell (*(a.table_[i][j]));
		}
	}
	tableSize_ = a.tableSize_;
	counter = a.counter;
}

// fill data in current class ocean
void Ocean::FillTable () {		
	CounterCitizen Citizens(*counter);
	const int number_types = Citizens.Get_nTypes();	
	int current_type = 0;	
	
	for(size_t y = 0; y < tableSize_; ++y)
	{
		for(size_t x = 0; x < tableSize_; ++x)
		{
			current_type = rand() % number_types;

			if(Citizens.Check_Citizens_By_Number(current_type))
			{
				CreateNewCitizen(Citizens, current_type, y, x);
			}
			else --x;
		}
	}
}

void Ocean::CreateNewCitizen (CounterCitizen & temp,
										const int type_object,
										const size_t y_coord, 
										const size_t x_coord) {
	enum { civil, block, predator, cell };
	switch(type_object) {
		case civil:
		table_[y_coord][x_coord] = new Civil;
		temp.Minus_Citizen_By_Number(civil);
		break;
	case block:
		table_[y_coord][x_coord] = new Block;
		temp.Minus_Citizen_By_Number(block);
		break;
	case predator:
		table_[y_coord][x_coord] = new Predator;
		temp.Minus_Citizen_By_Number(predator);
		break;
	case cell:
		table_[y_coord][x_coord] = new Cell;
		temp.Minus_Citizen_By_Number(cell);
		break;
	default:
		throw std::invalid_argument
			("Error! Wrong value for assignment.");
	}	
}

// show table by console
void Ocean::ShowTable () const {
	for(size_t y = 0; y < tableSize_; ++y) {
		for(size_t x = 0; x < tableSize_; ++x) {
			if(table_[y][x] != nullptr)
				table_[y][x]->Draw ();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Ocean::ShowCitizens() const
{
	counter->Show_Citizens();
}

void Ocean::MoveCitizens (/*int steps*/) {	
	//const int possible_sides = /*4*/ 1;
	const size_t max_coord = tableSize_ - 1;
	coordinates current;
	coordinates compare;
	Predator *ptrPredator;
	Civil		*ptrCivil;
	
	
	for(size_t y_cord = 0; y_cord <= max_coord; ++y_cord)
	{
		for(size_t x_cord = 0; x_cord <= max_coord; ++x_cord)
		{	
			if(table_[y_cord][x_cord]->IsMovable( ))
			{
				current.Set_Coordinates(y_cord, x_cord);				
				Side_For_Step Possible_Sides(max_coord, y_cord, x_cord);
				if((ptrPredator = dynamic_cast<Predator*>(table_[y_cord][x_cord])))
				{					
					if(Possible_Sides.Can_Go_Right() &&
						(ptrCivil = dynamic_cast<Civil*>(table_[y_cord][x_cord + 1])) )
					{
						compare.Set_Coordinates(y_cord, (x_cord + 1));
						PredatorEatCivil(current, compare);
					}
					else if(Possible_Sides.Can_Go_Down() && (ptrCivil = dynamic_cast<Civil*>(table_[y_cord + 1][x_cord])))
					{
						compare.Set_Coordinates(y_cord + 1, x_cord);
						PredatorEatCivil(current, compare);
					}
					else if(Possible_Sides.Can_Go_Left() && (ptrCivil = dynamic_cast<Civil*>(table_[y_cord][x_cord - 1])))
					{
						compare.Set_Coordinates(y_cord, x_cord - 1);
						PredatorEatCivil(current, compare);
					}
					else if(Possible_Sides.Can_Go_Up( ) && (ptrCivil = dynamic_cast<Civil*>(table_[y_cord - 1][x_cord])))
					{
						compare.Set_Coordinates(y_cord - 1, x_cord);
						PredatorEatCivil(current, compare);
					}
				}
			}
		}
	}	
}