#include "ocean.h"
// constructor by default
ocean::ocean (size_t i_size) : table_size (i_size) {
	size_t divide_val = 4;
	num_civl = num_pred = (i_size * i_size) / divide_val;
	num_obst = i_size * i_size / (divide_val + 1);
	num_cell = i_size * i_size - num_civl - num_pred - num_obst;
	try {
		table = new cell**[table_size];
		for(size_t i = 0; i < table_size; ++i) {
			table[i] = new cell*[table_size];
		}
		for(size_t i = 0; i < table_size; ++i) {
			for(size_t j = 0; j < table_size; ++j) {
				table[i][j] = nullptr;
			}
		}
	}
	catch(std::bad_alloc &ex) {
		table = nullptr;
		std::cerr << "Bad alloc exception: " << ex.what ();
		abort();
	}
	catch(...) {
		std::cerr << "Error! Process was terminated by unknown reason.";
		abort();
	}
}

// constructor 2 with number of citizens
ocean::ocean (size_t i_n, size_t civ_num,
							size_t pred_num, size_t obst_num ) :
							table_size (i_n), num_civl (civ_num),
							num_pred (pred_num), num_obst (obst_num),
							table (nullptr) {
	num_cell = table_size * table_size - num_civl - num_pred - num_obst;

	if(table_size && (num_cell > (table_size * 2))) {
		try {
			table = new cell**[table_size];
			for(size_t i = 0; i < table_size; ++i) {
				table[i] = new cell*[table_size];
			}
			for(size_t i = 0; i < table_size; ++i) {
				for(size_t j = 0; j < table_size; ++j) {
					table[i][j] = nullptr;
				}
			}
		}
		catch(std::bad_alloc &ex) {
			table = nullptr;
			std::cerr << "Bad alloc exception: " << ex.what();
			abort();
		}
		catch(...) {
			std::cerr << "Error! Process was terminated by unknown reason.";
			abort();
		}
	}
}

// destructor for class ocean
ocean::~ocean () {
	for(size_t i = 0; i < table_size; ++i) {
		for(size_t j = 0; j < table_size; ++j) {
			delete table[i][j];
			table[i][j] = nullptr;
		}
	}
	for(size_t i = 0; i < table_size; ++i) {
		delete[]table[i];
		table[i] = nullptr;
	}
	delete[]table;
	table = nullptr;
}

// assignment constructor for class ocean
ocean & ocean::operator=(const ocean &a) {
	if(this != &a) {
		// creating temporary class variable
		try {
			cell ***temp = new cell**[a.table_size];
			for(size_t i = 0; i < a.table_size; ++i) {
				temp[i] = new cell*[a.table_size];
			}
			for(size_t i = 0; i < a.table_size; ++i) {
				for(size_t j = 0; j < a.table_size; ++j) {
					if(a.table[i][j] == nullptr) {
						temp[i][j] = nullptr;
					}
					else
						temp[i][j] = new cell(*(a.table[i][j]));//////////////////
				}
			}
			// delete data in current class
			for(size_t i = 0; i < table_size; ++i) {
				for(size_t j = 0; j < table_size; ++j) {
					delete table[i][j];
					table[i][j] = nullptr;
				}
			}
			for(size_t i = 0; i < table_size; ++i) {
				delete[]table[i];
				table[i] = nullptr;
			}
			delete[]table;

			// assignment current class new data
			table = temp;
			table_size = a.table_size;
			num_civl = a.num_civl;
			num_pred = a.num_pred;
			num_obst = a.num_obst;
			num_cell = a.num_cell;
			move = a.move;
		}
		catch(std::bad_alloc &ex) {
			table = nullptr;
			std::cerr << "Bad alloc exception: " << ex.what ();
			abort();
		}
		catch(...) {
			std::cerr << "Process was terminated by unknown error!";
			abort();
		}
	}
	return *this;
}
// copy constructor for class ocean
ocean::ocean (const ocean &a) {
	try {
		// get new memory for current class
		table = new cell**[a.table_size];
		for(size_t i = 0; i < a.table_size; ++i) {
			table[i] = new cell*[table_size];
		}
		for(size_t i = 0; i < a.table_size; ++i) {
			for(size_t j = 0; j < a.table_size; ++j) {
				table[i][j] = new cell (*(a.table[i][j]));
			}
		}
		// assignment current class new data
		table_size = a.table_size;
		num_civl = a.num_civl;
		num_pred = a.num_pred;
		num_obst = a.num_obst;
		num_cell = a.num_cell;
		move = a.move;
	}
	catch(std::bad_alloc &ex) {
		table = nullptr;
		std::cerr << "Bad alloc exception: " << ex.what ();
		abort();
	}
	catch(...) {
		std::cerr << "Process was terminated by unknown error!";
		abort();
	}
}
////
void ocean::clean_table () {
	for(size_t y = 0; y < table_size; ++y) {
		for(size_t x = 0; x < table_size; ++x) {
			delete table[y][x];
			table[y][x] = nullptr;
		}
	}
}
// fill data in current class ocean
void ocean::fill_table () {
	clean_table ();
	objects_counter fill (num_civl, num_pred, num_obst, num_cell);
	int current_type = 0;
	const int types_of_objects = 4;

	while(fill.total_objects() > 0) {
		for(size_t y = 0; y < table_size; ++y) {
			for(size_t x = 0; x < table_size; ++x) {
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
void ocean::create_new_citizen (const int type_of_obj,
										  const size_t y_coord, const size_t x_coord) {
	try {
		switch(type_of_obj) {
		case r_civil:
			table[y_coord][x_coord] = new civil;
			break;
		case r_predt:
			table[y_coord][x_coord] = new predator;
			break;
		case r_obstk:
			table[y_coord][x_coord] = new obstacle;
			break;
		case r_clean:
			table[y_coord][x_coord] = new cell;
			break;
		default:
			throw std::invalid_argument
				("Error! Wrong value for assignment.");
		}
	}
	catch(std::invalid_argument &ex) {
		std::cerr << "Can't get object:" << ex.what ();
		abort ();
	}
	catch(std::bad_alloc &ex) {
		delete table[y_coord][x_coord];
		std::cerr << ex.what ();
		abort ();
	}
}

// show table by console
void ocean::show_table () const {
	for(size_t y = 0; y < table_size; ++y) {
		for(size_t x = 0; x < table_size; ++x) {
			if(table[y][x] != nullptr)
				table[y][x]->draw ();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// show numbers of citizens, obsticals and other placec in the ocean
void ocean::show_citizens () const {
	std::cout << "Full place in ocean: "
		<< (num_civl + num_pred + num_obst + num_cell) << std::endl;
	std::cout << "Civil citizens: " << num_civl << std::endl;
	std::cout << "Predators     : " << num_pred << std::endl;
	std::cout << "Obstacles     : " << num_obst << std::endl;
	std::cout << "Clean place   : " << num_cell << std::endl;
}
void ocean::move_citizens (int steps) {
	const int possible_sides = 4;

	move.set_max_coord (table_size - 1);

	for(int movement = 0; movement < steps; ++movement) {
		for(size_t y_cord = 0; y_cord < table_size; ++y_cord) {
			for(size_t x_cord = 0; x_cord < table_size; ++x_cord)
			{
				int rand_step = rand () % possible_sides;
				move.set_coord (y_cord, x_cord, rand_step);

				if(check_steps()) {
					go_citizen ();
				}
			}
		}
	}
}

bool ocean::check_steps () {
	const char civl_s = 'c';
	const char pred_s = 'p';
	const char cell_s = '-';
	if((table[move.get_y_current ()][move.get_x_current ()]->get_symbol () == pred_s &&
		(table[move.get_y_compared ()][move.get_x_compared ()]->get_symbol () == civl_s ||
		table[move.get_y_compared ()][move.get_x_compared ()]->get_symbol () == cell_s))
		||
		(table[move.get_y_current ()][move.get_x_current ()]->get_symbol () == civl_s &&
		table[move.get_y_compared ()][move.get_x_compared ()]->get_symbol () == cell_s)) {
		return true;
	}
	else {
		return false;
	}
}
void ocean::go_citizen () {
	delete table[move.get_y_compared ()][move.get_x_compared ()];
	table[move.get_y_compared ()][move.get_x_compared ()] =
		new cell (*table[move.get_y_current ()][move.get_x_current ()]);

	delete table[move.get_y_current ()][move.get_x_current ()];
	table[move.get_y_current ()][move.get_x_current ()] = new cell;
}


