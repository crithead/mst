#include <cmath>
#include <stdexcept>

#include "edge.hpp"
#include "point.hpp"

edge::edge()
{
	throw std::runtime_error( "an edge must be initialized with  vertices" );
}

edge::edge( const point& one, const point& two ) :
	a( one ), b( two ), length( calc_length( one, two ) )
{
	if ( a == b )
		throw std::invalid_argument( "an edge must have distinct vertices" );
	if ( b < a ) {
		point t = a;
		a = b;
		b = t;
	}
}

edge::edge( const edge& that ) :
	a( that.a ), b( that.b ), length( that.length )
{
}

edge::~edge()
{
}

point edge::get_a( void ) const
{
	return a;
}

point edge::get_b( void ) const
{
	return b;
}

float edge::get_length( void ) const
{
	return this->length;
}

float edge::calc_length( const point& a, const point& b ) const
{
	int dx = a.get_x() - b.get_x();
	int dy = a.get_y() - b.get_y();
	return static_cast<float>(
			std::sqrt( static_cast<double>( dx * dx + dy * dy ) ) );
}

edge& edge::operator=( edge const& that )
{
	if ( this != &that ) {
		this->a = that.a;
		this->b = that.b;
		this->length = that.length;
	}
	return *this;
}

bool edge::operator==( const edge& that ) const
{
	return ( this->a == that.a ) && ( this->b == that.b );
}

bool edge::operator!=( const edge& that ) const
{
	return !(*this == that);
}


