#ifndef MST_EDGE_H
#define MST_EDGE_H

#include "point.hpp"

// A graph edge.
// Regardless of what order the vertices are added to the 'edge',
// they will be arranged so that a < b.
//
class edge
{
public:
	edge( const point&, const point& );
	edge( const edge& );
	~edge();

	point get_a( void ) const;
	point get_b( void ) const;
	float get_length( void ) const;
	float calc_length( const point&, const point& ) const;

	edge& operator=( edge const& );
	bool operator==( const edge& ) const;
	bool operator!=( const edge& ) const;
private:
	edge(); // An edge must be initialized with end points
	point a;
	point b;
	float length;
};

#endif // MST_EDGE_H

