//
// Find a minimum spanning tree in a graph.
//
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

#include "edge.hpp"
#include "point.hpp"

using namespace std;

static void load( const string& filename, vector<point>& );
static void print( vector<point>& );
static void print( vector<edge>& );
static void find_mininimum_spanning_tree( const vector<point>&, vector<edge>& );

int main( int argc, char **argv )
{
	int status = 0;

	cout << "Minimum Spanning Tree" << endl;

	for( int i = 1; i < argc; i++ ) {
		string filename( argv[i] );

		try {
			vector<point> points;
			vector<edge> edges;

			load( filename, points );
			find_mininimum_spanning_tree( points, edges );
			print( points );
			print( edges );
		}
		catch (const exception& e) {
			cout << "File     : " << filename << endl;
			cout << "Exception: " << e.what() << endl;
			status++;
		}
	}

	return status;
}

//
// Load a set of points from a file.
//
static void load( const string& filename, vector<point>& pts )
{
	cout << __FUNCTION__ << "( filename = " << filename << " )" << endl;
	ifstream in( filename );
	while ( true ) {
		int x = 0, y = 0;
		in >> x >> y;
		if ( ! in.good() )
			break;
		pts.emplace_back( point( x, y ) );
	}
	in.close();
}

static void print( vector<point>& pts )
{
	cout << "number of points = " << pts.size() << endl;
	for ( auto& p : pts )
		cout << "(" << p.get_x() << ", " << p.get_y() << ")\t";
	cout << endl;
}

static void print( vector<edge>& egs )
{
	cout << "number of edges = " << egs.size() << endl;
	for ( auto& e : egs ) {
		cout << '(' << e.get_a().get_x() << ',' << e.get_a().get_y()
			<< ") -> (" << e.get_b().get_x() << ',' << e.get_b().get_y()
			<< ") wt = " << e.get_length() << endl;
	}
	cout << endl;
}


//
// Use Prim's algorithm for finding the minimum spanning tree of a set of
// points.  Assumes a completely connected, bidirectional graph.
//
// 1. Select a point.
// 2. Find the nearest point not in the tree to a point in the tree,
//    construct an edge, and add it to the tree.
// 3. 
//
static const float FMARK = numeric_limits<float>::max();
static const size_t SMARK = numeric_limits<size_t>::max();

struct item {
	size_t index;
	const point& pt;
	float cost;
	size_t near;
	item( size_t i, const point& p, float c = FMARK, size_t n = SMARK ) :
		index( i ), pt( p ), cost( c ), near( n ) {}
};

#if 0
// Determine if there are any available points to be added to the tree.
// Available points don't have a nearest (item.near == SMARK) point.
static bool points_available( vector<item>& items )
{
	for ( auto& i : items ) {
		if ( i.near == SMARK )
			return true;
	}
	return false;
}
#endif

static void print( vector<item>& items )
{
	cout << "index\tpoint\tcost\tnear" << endl;
	for ( auto& i : items ) {
		cout << i.index << '\t' << '(' << i.pt.get_x() << ',' << i.pt.get_y()
			<< ')' << '\t' << i.cost << '\t' << i.near << endl;
	}
}

static void find_mininimum_spanning_tree(
		const vector<point>& points,
		vector<edge>& edges )
{
	cout << __FUNCTION__ << endl;
	vector<item> point_table;

	size_t idx = 0;
	for ( auto& p : points )
		point_table.emplace_back( item( idx++, p ) );
	for (size_t i = 0; i < point_table.size(); i++ )
		assert( point_table[ i ].index == i );

	// This isn't Prim's algorithm.
	// It finds the shortest path to point 0.

	size_t this_index = 0;
	while ( this_index != SMARK ) {
		// The last point has no 'near' (it is near to another point)
		// so when this_index == SMARK all the points have been marked
		print( point_table );

		const point& p = point_table[ this_index ].pt;
		size_t index = SMARK;
		float cost = FMARK;
		for( auto& i : point_table ) {
			// point 'i' is available (and not the this index)
			if ( i.index != this_index && i.near == SMARK ) {
				float length = edge::calc_length( p, i.pt );
				if ( length < cost ) {
					index = i.index;
					cost = length;
				}
			}
		}
		point_table[ this_index ].cost = cost;
		point_table[ this_index ].near = index;
		this_index = index;
	}

	cout << "The final point_table" << endl;
	print( point_table );

	// Build the list of edges making up the spanning tree
	cout << "Build the list of edges" << endl;
	edges.clear();
	for (size_t i = 0; i < point_table.size(); i++ ) {
		// The last point connnected to the tree doesn't have a nearest
		// vertex (it's the nearest of another vertex) so skip it.
		if ( point_table[ i ].near == SMARK )
			continue;
		const point& u = point_table[ i ].pt;
		const point& v = point_table[ point_table[ i ].near ].pt;
		edges.emplace_back( edge( u, v ) );
	}
}

