//
// Implementation of point class.
//
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

point& point::operator=( point const& that )
{
	this->x = that.x;
	this->y = that.y;
	return *this;
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


