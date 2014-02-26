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

// base class cell
class cell {
protected:
	char c_symbol;
public:
	explicit cell (const char symbol = '-') :
		c_symbol (symbol) {}	// constructor
	virtual ~cell() {} // destructor
	virtual void draw () { std::cout << c_symbol << " "; }
	virtual char get_symbol () const { return c_symbol; }
	virtual bool can_pass () const { return true; }
	virtual bool is_movable () const { return false; }
};

// virtual class block(not movable)
class block : public cell {
public:
	explicit block (const char symbol = 'b') : cell (symbol) {}
	virtual bool is_movable () const { return false; }
	virtual bool can_pass () const { return false; }
	virtual void draw () = 0;
	virtual ~block () {}
};

class obstacle : public block {
public:
	explicit obstacle (const char symbol = '|') 
		: block (symbol) {}	
};

// virtual base class for citizen in the ocean
class animal : public cell {
public:
	explicit animal (const char symbol = 'a') 
		: cell (symbol) {}
	//virtual bool can_pass () const { return true; }
	virtual void draw () = 0;
	virtual bool is_movable () const { return true; }	
	virtual bool is_civil () const { return false; }
	virtual bool is_predator ()const { return false; }
	virtual ~animal () {}
};

// movable class civil citizens  
class civil : public animal {
public:
	explicit civil (const char symbol = 'c') : animal(symbol) {}
	virtual bool is_civil () const { return true; }
};

// class predator, which can eat other citizens and movable
class predator : public animal {
public:
    explicit predator(const char symbol = 'p') : animal(symbol) { }
		virtual bool is_predator () const { return true; }
};

class ocean {
private:
	enum ocean_citizen { r_civil, r_predt, r_obstk, r_clean };
	size_t table_size;
	size_t num_civl;
	size_t num_pred;
	size_t num_obst;
	size_t num_cell;

  cell ***table;
	coordinate move;
public:
	explicit ocean (size_t = 5); // constructor
	ocean (size_t i_n, size_t civ_num, size_t pred_num, size_t obst_num);
	virtual ~ocean (); // destructor
	ocean & operator=(const ocean &a); // assignment constructor
	ocean (const ocean &a); // copy constructor
	virtual void show_table () const ; // show table by console
	void show_citizens () const; // show citizens and place

	void fill_table ();
	void move_citizens (int = 1); // generate all possible moves of citizens

	void go_citizen ();
	void clean_table ();
	void create_new_citizen (const int, const size_t, const size_t);
	bool check_steps ();

	inline size_t get_num_cell  (void) const { return num_cell; }
	inline size_t get_civil_num (void) const { return num_civl; }
	inline size_t get_predator_num (void) const { return num_pred; }
	inline size_t get_obstical_num (void) const { return num_obst; }

	inline void set_cell_num  (const size_t cell_n)  { num_cell = cell_n; }
	inline void set_civil_num (const size_t civil_n) { num_civl = civil_n;}
	inline void set_predator_num (const size_t predator_n) { num_pred = predator_n; }
	inline void set_obstical_num (const size_t obstical_n) { num_obst = obstical_n; }

};


#endif
