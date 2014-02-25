#include "ocean_help_classes.h"
#include <cstdlib>
void coordinate::set_coord (const size_t i_y, const size_t i_x, const int i_move) {
	y_current = i_y;	x_current = i_x;
	try {
		switch(i_move) {
		case right:	go_right ();
			break;
		case left:	go_left ();
			break;
		case up:		go_up ();
			break;
		case down:	go_down ();
			break;
		default:
			throw std::invalid_argument
				("Error! Impossible value for step side.");
		}
	}
	catch(std::invalid_argument &ex) {
		std::cerr << ex.what () << std::endl;
		abort ();
	}
}
void coordinate::go_right () {
	if(x_current == max_coordinate) {
		if(y_current == max_coordinate) {
			y_compared = 0;
			x_compared = 0;
		}
		else { // compare first cell in the next line
			y_compared = y_current + 1;
			x_compared = 0;
		}
	}
	else {	// compare next cell in current line
		y_compared = y_current;
		x_compared = x_current + 1;
	}
}
void coordinate::go_left () {
	if(x_current == 0) {
		if(y_current == 0) {
			y_compared = max_coordinate;
			x_compared = max_coordinate;
		}
		else {
			y_compared = y_current - 1;
			x_compared = max_coordinate;
		}
	}
	else {
		y_compared = y_current;
		x_compared = x_current - 1;
	}
}
void coordinate::go_up () {
	if(y_current == 0) {
		if(x_current == 0) {
			y_compared = max_coordinate;
			x_compared = max_coordinate;
		}
		else {
			y_compared = max_coordinate;
			x_compared = x_current - 1;
		}
	}
	else {
		y_compared = y_current - 1;
		x_compared = x_current;
	}
}
void coordinate::go_down () {
	if(y_current == max_coordinate) {
		if(x_current == max_coordinate) {
			y_compared = 0;
			x_compared = 0;
		}
		else {
			y_compared = 0;
			x_compared = x_current + 1;
		}
	}
	else {
		y_compared = y_current + 1;
		x_compared = x_current;
	}
}


////////////////////////////////////////////////////////////////

