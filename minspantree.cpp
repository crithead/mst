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

// Cost and Index marks
static const float FMARK = numeric_limits<float>::max();
static const size_t SMARK = numeric_limits<size_t>::max();

// Tree table item
struct item {
	size_t index;
	const point& pt;
	float cost;
	size_t near;
	item( size_t i, const point& p, float c = FMARK, size_t n = SMARK ) :
		index( i ), pt( p ), cost( c ), near( n ) {}
};

static void find_minimum_spanning_tree( const vector<point>&, vector<edge>& );
static void load( const string& filename, vector<point>& );
static bool points_available( vector<item>& items );
static void print( vector<point>& );
static void print( vector<edge>& );
static void print( vector<item>& items );
static void print_csv( vector<edge>& );

static bool debug_print = false;

int main( int argc, char **argv )
{
	int status = 0;
	bool csv_edges = false;

	cout << "Minimum Spanning Tree" << endl;

	for( int i = 1; i < argc; i++ ) {
		string filename( argv[i] );
		if ( filename == "--verbose" ) {
			debug_print = true;
			continue;
		}
		if ( filename == "--quiet" ) {
			debug_print = false;
			continue;
		}
		if ( filename == "--csv" ) {
			csv_edges = true;
			continue;
		}

		try {
			vector<point> points;
			vector<edge> edges;

			load( filename, points );
			find_minimum_spanning_tree( points, edges );
			if ( debug_print )
				print( points );
			if ( csv_edges )
				print_csv( edges );
			else
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
// Find the minimum spanning tree of a set of points.
// Assumes a completely connected, bidirectional graph.
//
// 1. Select a point and add it to the tree.
// 2. Find the nearest point not in the tree to a point in the tree
//    and add it to the tree.
// 3. Repeat #2 until all points are in the tree.
//
static void find_minimum_spanning_tree(
		const vector<point>& points,
		vector<edge>& edges )
{
	if ( debug_print )
		cout << __FUNCTION__ << endl;

	vector<item> point_table;

	size_t table_index = 0;
	for ( auto& p : points )
		point_table.emplace_back( item( table_index++, p ) );
	for (size_t i = 0; i < point_table.size(); i++ )
		assert( point_table[ i ].index == i );

	// Put point 0 in the tree
	point_table[ 0 ].near = 0;
	point_table[ 0 ].cost = 0;

	while ( points_available( point_table ) ) {
		if ( debug_print )
			print( point_table );

		size_t tree_index = SMARK;
		size_t index = SMARK;
		float cost = FMARK;
		for ( auto& t : point_table ) {
			// skip points not in tree (unmarked)
			if ( t.near == SMARK )
				continue;
			for ( auto& i : point_table ) {
				// point 'i' is available (not in tree)
				if ( i.near == SMARK ) {
					float length = edge::calc_length( t.pt, i.pt );
					if ( length < cost ) {
						tree_index = t.index;
						index = i.index;
						cost = length;
					}
				}
			}
		}
		// Connect this point to the tree
		point_table[ index ].cost = cost;
		point_table[ index ].near = tree_index;
	}

	if ( debug_print ) {
		cout << "The final point_table" << endl;
		print( point_table );
	}

	// Build the list of edges making up the spanning tree
	if ( debug_print )
		cout << "Build the list of edges" << endl;
	edges.clear();
	for (size_t i = 0; i < point_table.size(); i++ ) {
		// The first point connnected to the tree has itself as the nearest
		// vertex (it's the nearest of another vertex) so skip it.
		if ( point_table[ i ].near == i )
			continue;
		const point& u = point_table[ i ].pt;
		const point& v = point_table[ point_table[ i ].near ].pt;
		edges.emplace_back( edge( u, v ) );
	}
}

//
// Load a set of points from a file.
//
static void load( const string& filename, vector<point>& pts )
{
	if ( debug_print )
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

//
// Print a vector of edges
//
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
// Print the "tree" table
//
static void print( vector<item>& items )
{
	cout << "index\tpoint\tcost\tnear" << endl;
	for ( auto& i : items ) {
		cout << i.index << '\t' << '(' << i.pt.get_x() << ',' << i.pt.get_y()
			<< ')' << '\t' << i.cost << '\t' << i.near << endl;
	}
}

//
// Print a vector of points
//
static void print( vector<point>& pts )
{
	cout << "number of points = " << pts.size() << endl;
	for ( auto& p : pts )
		cout << "(" << p.get_x() << ", " << p.get_y() << ")\t";
	cout << endl;
}

//
// Print a vector of edges (TAB separated)
//
static void print_csv( vector<edge>& egs )
{
	cout << "x1\ty1\tx2\ty2\twt" << endl;
	for ( auto& e : egs ) {
		cout <<  e.get_a().get_x() << '\t' << e.get_a().get_y() << '\t'
				<< e.get_b().get_x() << '\t' << e.get_b().get_y() << '\t'
				<< e.get_length() << endl;
	}
	cout << endl;
}

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

