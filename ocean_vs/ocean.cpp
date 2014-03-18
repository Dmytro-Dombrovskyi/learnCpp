#include "ocean.h"
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
	int current_type = 0;
	const int types_of_objects = 4;
	enum object { civil, block, predaor, cell };
		for(size_t y = 0; y < tableSize_; ++y) {
			for(size_t x = 0; x < tableSize_; ++x) {
				current_type = rand () % types_of_objects;

				if(fill.get_object (current_type)) {
					create_new_citizen (current_type, y, x);
				}
				else {
					if(fill.total_objects() == 0)
						break;
					else {
						if(x)
							--x;
					}
				}
			}
		}
	}
}
//void ocean::create_new_citizen (const int type_of_obj,
//										  const size_t y_coord, const size_t x_coord) {
//	try {
//		switch(type_of_obj) {
//		case r_civil:
//			table[y_coord][x_coord] = new civil;
//			break;
//		case r_predt:
//			table[y_coord][x_coord] = new predator;
//			break;
//		case r_obstk:
//			table[y_coord][x_coord] = new obstacle;
//			break;
//		case r_clean:
//			table[y_coord][x_coord] = new cell;
//			break;
//		default:
//			throw std::invalid_argument
//				("Error! Wrong value for assignment.");
//		}
//	}
//	catch(std::invalid_argument &ex) {
//		std::cerr << "Can't get object:" << ex.what ();
//		abort ();
//	}
//	catch(std::bad_alloc &ex) {
//		delete table[y_coord][x_coord];
//		std::cerr << ex.what ();
//		abort ();
//	}
//}
//
//// show table by console
//void ocean::show_table () const {
//	for(size_t y = 0; y < table_size; ++y) {
//		for(size_t x = 0; x < table_size; ++x) {
//			if(table[y][x] != nullptr)
//				table[y][x]->draw ();
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
//}
//
//// show numbers of citizens, obsticals and other placec in the ocean
//void ocean::show_citizens () const {
//	std::cout << "Full place in ocean: "
//		<< (num_civl + num_pred + num_obst + num_cell) << std::endl;
//	std::cout << "Civil citizens: " << num_civl << std::endl;
//	std::cout << "Predators     : " << num_pred << std::endl;
//	std::cout << "Obstacles     : " << num_obst << std::endl;
//	std::cout << "Clean place   : " << num_cell << std::endl;
//}
//void ocean::move_citizens (int steps) {
//	const int possible_sides = 4;
//
//	move.set_max_coord (table_size - 1);
//
//	for(int movement = 0; movement < steps; ++movement) {
//		for(size_t y_cord = 0; y_cord < table_size; ++y_cord) {
//			for(size_t x_cord = 0; x_cord < table_size; ++x_cord)
//			{
//				int rand_step = rand () % possible_sides;
//				move.set_coord (y_cord, x_cord, rand_step);
//
//				if(check_steps()) {
//					go_citizen ();
//				}
//			}
//		}
//	}
//}
//
//bool ocean::check_steps () {
//	const char civl_s = 'c';
//	const char pred_s = 'p';
//	const char cell_s = '-';
//	if((table[move.get_y_current ()][move.get_x_current ()]->get_symbol () == pred_s &&
//		(table[move.get_y_compared ()][move.get_x_compared ()]->get_symbol () == civl_s ||
//		table[move.get_y_compared ()][move.get_x_compared ()]->get_symbol () == cell_s))
//		||
//		(table[move.get_y_current ()][move.get_x_current ()]->get_symbol () == civl_s &&
//		table[move.get_y_compared ()][move.get_x_compared ()]->get_symbol () == cell_s)) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//void ocean::go_citizen () {
//	delete table[move.get_y_compared ()][move.get_x_compared ()];
//	table[move.get_y_compared ()][move.get_x_compared ()] =
//		new cell (*table[move.get_y_current ()][move.get_x_current ()]);
//
//	delete table[move.get_y_current ()][move.get_x_current ()];
//	table[move.get_y_current ()][move.get_x_current ()] = new cell;
//}


