// File: Battery.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef BATTERY_HPP
#define BATTERY_HPP

// Public

// Private
#include "nnb/graphics/TextureContainer.hpp"

int const PHOTOCOST = 70;
float const WATT = 16;

class Battery {
public:
	Battery();
	~Battery();

	bool decrease();
	void logic();
	void render() const;

private:
	nnb::TextureContainer powerbar;
	float power;
	int lastDecrease;
	int lastBlinkChange;
	bool on;
} ;

#endif
