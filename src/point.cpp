//
// Implementation of point class.
//
#include <cmath>
#include "point.hpp"

point::point() : x( 0 ), y( 0 )
{
}

point::point( int nx, int ny ) : x( nx ), y( ny )
{
}

point::point( const point& that ) : x( that.x ), y( that.y )
{
}

point::~point()
{
}

int point::get_x( void ) const
{
	return this->x;
}

int point::get_y( void ) const
{
	return this->y;
}

void point::set_x( int v )
{
	this->x = v;
}

void point::set_y( int v )
{
	this->y = v;
}

point& point::operator=( point const& that )
{
	this->x = that.x;
	this->y = that.y;
	return *this;
}

bool point::operator==( const point& that ) const
{
	return ( this->x == that.x ) && ( this->y == that.y );
}

bool point::operator!=( const point& that ) const
{
	return !( *this == that );
}

// Point A is less than Point B, if it's distance from y = -x is more
// negative.
// TODO Does this cover all the cases?
bool point::operator<( const point& that ) const
{
	bool less_than;

	if ( *this == that ) {
		less_than = false;
	}
	else if ( this->x < that.x && this->y < that.y ) {
		less_than = true;
	}
	else {
		const double SQRT_2 = 1.4142135623731;
		// distance from a point to the line y = -x
		double da = static_cast<double>( std::abs(-1 * this->x + this->y ) ) / SQRT_2;
		double db = static_cast<double>( std::abs(-1 * that.x + that.y ) ) / SQRT_2;
		if ( da < db )
			less_than = true;
		else
			less_than = false;
	}

	return less_than;
}

