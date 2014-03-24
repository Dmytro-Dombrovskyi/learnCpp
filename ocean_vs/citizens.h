// description: 
// created: 27.02.2014, by Dmytro Dombrovskyi.
// In this file i had put classes: cell, animal - base classes,
// and inheritat class such as : predators, civil, block.

#pragma once
#ifndef CITIZENS_H
#define CITIZENS_H

#include <iostream>

// base class cell
class Cell {
protected:
	friend class Ocean;
	char symbol_;
	explicit Cell (const char i_symbol = '-')
		: symbol_ (i_symbol) {}
	virtual ~Cell () {}

	virtual void Draw () const { std::cout << symbol_ << " "; }
	virtual char GetSymbol () const { return symbol_; }
	virtual bool IsMovable () const { return false; }
	virtual bool CanBeEaten () const { return true; }
};

// virtual class block(not movable)
class Block : public Cell {
public:
	explicit Block (const char symbol = '|')
		: Cell (symbol) {}
	virtual ~Block () {}
	virtual bool CanBeEaten () const { return false; }
};

// virtual base class for citizen in the ocean
class Animal : public Cell {
protected:
	explicit Animal (const char symbol)
		: Cell (symbol) {}

	virtual bool IsMovable () const { return true; }
	virtual bool CanBeEaten( ) const = 0;
	virtual bool IsCivil( ) const { return false; }
	virtual bool IsPredator( ) const { return false; }
};

// movable class civil citizens  
class Civil : public Animal {
public:
	explicit Civil (const char i_civil_symbol = 'c')
		: Animal (i_civil_symbol) {}
	virtual bool IsCivil () const { return true; }
	virtual bool CanBeEaten( ) const { return true; }
};

// class predator, which can eat other citizens and movable
class Predator : public Animal {
public:
	explicit Predator (const char symbol = '*')
		: Animal (symbol) {}
	virtual bool IsPredator () const { return true; }
	virtual bool CanBeEaten( ) const { return false; }
};

#endif // citizens