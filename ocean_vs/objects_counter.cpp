#include "ocean_help_classes.h"
objects_counter::objects_counter (const size_t i_civil, const size_t i_predt,
											 const size_t i_obstc, const size_t i_clean) {
	try {
		N_civil = i_civil;
		N_predt = i_predt;
		N_obstc = i_obstc;
		N_clean = i_clean;
	}
	catch(...) {
		std::cerr << "Objects wasn't assignment: ";
		std::abort ();
	}
}
void objects_counter::set_objects (const size_t i_civil, const size_t i_predt,
											  const size_t i_obstc, const size_t i_clean) {
	try {
		N_civil = i_civil;
		N_predt = i_predt;
		N_obstc = i_obstc;
		N_clean = i_clean;
	}
	catch(...) {
		std::cerr << "Objects wasn't assignment: ";
		std::abort ();
	}
}
bool objects_counter::get_object (const int type_obj) {
	bool opportunity = false;
	try {
		switch(type_obj) {
		case r_civil:
			if((opportunity = can_civil_created ())) {
				minus_civil ();
			}
			break;
		case r_predt:
			if((opportunity = can_predt_created ())) {
				minus_predt ();
			}
			break;
		case r_obstk:
			if((opportunity = can_obstc_created ())) {
				minus_predt ();
			}
			break;
		case r_clean:
			if((opportunity = can_clean_created ())) {
				minus_predt ();
			}
			break;
		default:
			throw std::invalid_argument
				("Error! Wrong value for assignment.");
		}
	}
	catch(std::invalid_argument &ex) {
		std::cerr << ex.what ();
		abort ();
	}
	return opportunity;
}
