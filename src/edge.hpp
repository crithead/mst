#ifndef MST_EDGE_H
#define MST_EDGE_H

#include "point.hpp"

//
// An undirected graph edge with vertices 'a' and 'b'.
//
// Regardless of what order the vertices are added to the 'edge',
// they will be arranged so that a < b.
//
class edge
{
public:
	static float calc_length( const point&, const point& );

	// Construct an edge from two points.
	edge( const point&, const point& );
	// Construct an edge as a copy of another edge.
	edge( const edge& );
	// Destroy the edge.
	~edge();

	point get_a( void ) const;
	point get_b( void ) const;
	float get_length( void ) const;

	edge& operator=( edge const& );
	// Edges are equal if thay have the same vertices.
	// (a1 == a2 && b1 == b2 || a1 = b2 && b1 == a2 )
	bool operator==( const edge& ) const;
	bool operator!=( const edge& ) const;
private:
	edge(); // An edge must be initialized with end points
	point a;
	point b;
	float length;
};

#endif // MST_EDGE_H

