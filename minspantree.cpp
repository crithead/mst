//
// Find a minimum spanning tree in a graph.
//
#include <iostream>
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
	cout << __FUNCTION__ << endl;
	cout << "filename = " << filename << endl;
}

static void print( vector<point>& pts )
{
	cout << __FUNCTION__ << endl;
	cout << "number of points = " << pts.size() << endl;
}

static void print( vector<edge>& egs )
{
	cout << __FUNCTION__ << endl;
	cout << "number of edges = " << egs.size() << endl;
}

static void find_mininimum_spanning_tree(
		const vector<point>& points,
		vector<edge>& edges )
{
	cout << __FUNCTION__ << endl;
}
