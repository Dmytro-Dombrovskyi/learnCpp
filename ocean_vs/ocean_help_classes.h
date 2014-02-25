#pragma once
#ifndef OCEAN_HELP_CLASSES_H
#define OCEAN_HELP_CLASSES_H
#include <iostream>
#include <stdexcept>
#include <cstdlib>
// change for copy
class objects_counter {
private:
	enum { r_civil, r_predt, r_obstk, r_clean };
	size_t N_civil;
	size_t N_predt;
	size_t N_obstc;
	size_t N_clean;

public:
	objects_counter () {}
	objects_counter (const size_t, const size_t,
									 const size_t, const size_t);
	virtual ~objects_counter () {}
	void set_objects (const size_t, const size_t,
									 const size_t, const size_t);
	bool get_object (const int);

	inline void minus_civil () { --N_civil; }
	inline void minus_predt () { --N_predt; }
	inline void minus_obstc () { --N_obstc; }
	inline void minus_clean () { --N_clean; }

	inline bool can_civil_created () {	return (N_civil) ? true : false; }
	inline bool can_predt_created () { return (N_predt) ? true : false; }
	inline bool can_obstc_created () { return (N_obstc) ? true : false; }
	inline bool can_clean_created () { return (N_clean) ? true : false; }

	void get_table () {
		std::cout << "N_civil: " << N_civil << std::endl;
		std::cout << "N_predt: " << N_predt << std::endl;
		std::cout << "N_obstc: " << N_obstc << std::endl;
		std::cout << "N_clean: " << N_clean << std::endl;
		std::cout << std::endl;
	}
	inline bool counter_clean () const {
		return (N_civil == 0 && N_predt == 0 && N_obstc == 0 && N_clean == 0) ? true : false;
	}
	inline size_t total_objects () const { return N_civil + N_predt + N_obstc + N_clean; }
};

class coordinate {
private:
	enum side { right, left, up, down };
	side move;
	size_t y_current;
	size_t x_current;
	size_t y_compared;
	size_t x_compared;
	size_t max_coordinate;

	void go_right ();
	void go_left ();
	void go_up ();
	void go_down ();
public:
	coordinate () {}
	virtual ~coordinate () {}
	inline size_t get_y_current () const { return y_current; }
	inline size_t get_x_current () const { return x_current; }
	inline size_t get_y_compared () const { return y_compared; }
	inline size_t get_x_compared () const { return x_compared; }

	inline void set_max_coord (const size_t i_max) { max_coordinate = i_max; }
	void set_coord (const size_t, const size_t, const int);
};

#endif
