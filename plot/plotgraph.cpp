//
// Plot a graph to a PNG file.
//
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <vector>

#include <pngwriter.h>

#include "edge.hpp"
#include "point.hpp"

using namespace std;

static void get_dimensions( const vector<edge> &, point&, point& );
static string get_savename( const string& filename );
static vector<edge>& load( const string& filename );
static void plot( const vector<edge>&, const string& savefile );
static void print( vector<edge>& );

static bool debug_print = false;

int main( int argc, char **argv )
{
	int status = 0;

	cout << "Plot Graph" << endl;

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

		try {
			// Load the list of edges from a file
			vector<edge>& edges = load( filename );

			if ( debug_print )
				print( edges );

			// Save the PNG image to a file
			string savename = get_savename( filename );
			if ( debug_print )
				cout << "Output file: " << savename << endl;

			// Plot the edges to a PNG image
			plot( edges, savename );

			// Clean up
			// TODO: use unique_ptr to manage memory
			delete &edges;
		}
		catch (const bad_alloc& e) {
			cout << "File         : " << filename << endl;
			cout << "Out of memory: " << e.what() << endl;
			status++;
		}
		catch (const exception& e) {
			cout << "File     : " << filename << endl;
			cout << "Exception: " << e.what() << endl;
			status++;
		}
	}

	return status;
}

static void print( vector<edge>& );
//
// Load a set of edges from a file.
//
static vector<edge>& load( const string& filename )
{
	if ( debug_print )
		cout << __FUNCTION__ << "( filename = " << filename << " )" << endl;

	ifstream in( filename );
	vector<edge> *edgelist = new vector<edge>;

	while ( true ) {
		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		float wt;
		in >> x1 >> y1 >> x2 >> y2 >> wt;
		if ( ! in.good() )
			break;
		edgelist->emplace_back( edge( point( x1, y1 ), point( x2, y2 ) ) );
	}

	in.close();

	return *edgelist;
}

//
// Calculate the translation offset from graph-relative coordinates to
// image-relative coordinates.
//
// Move the entire image into Quadrant I
//
static point calculate_translation_offset( const point& ul, const point& lr )
{
	return point( abs( ul.get_x() ), abs( lr.get_y() ) );
}

//
// Get the upper-left and lower-right coordinate extremes from the vertices
// in a set of edges.
//
static void get_dimensions( const vector<edge> &edges, point& ul, point& lr )
{
	ul.set_x( numeric_limits<int>::max() );
	ul.set_y( numeric_limits<int>::max() );
	lr.set_x( numeric_limits<int>::min() );
	lr.set_y( numeric_limits<int>::min() );

	for ( auto& e : edges ) {
		// Find upper-left corner
		if ( e.get_a().get_x() < ul.get_x() )
			ul.set_x( e.get_a().get_x() );
		if ( e.get_a().get_y() < ul.get_y() )
			ul.set_y( e.get_a().get_y() );
		if ( e.get_b().get_x() < ul.get_x() )
			ul.set_x( e.get_b().get_x() );
		if ( e.get_b().get_y() < ul.get_y() )
			ul.set_y( e.get_b().get_y() );
		// Find lower-right corner
		if ( e.get_a().get_x() > lr.get_x() )
			lr.set_x( e.get_a().get_x() );
		if ( e.get_a().get_y() > lr.get_y() )
			lr.set_y( e.get_a().get_y() );
		if ( e.get_b().get_x() > lr.get_x() )
			lr.set_x( e.get_b().get_x() );
		if ( e.get_b().get_y() > lr.get_y() )
			lr.set_y( e.get_b().get_y() );
	}
}

//
// Translate from graph-relative coordinates to image-relative coordinates.
//
static point translate( const point& offset, const point& a )
{
	return point( a.get_x() + offset.get_x(), a.get_y() + offset.get_y() );
}

//
// Generate a PNG image plot for a set of edges and write it to the
// specified file.
//
static void plot( const vector<edge>& edges, const string& savefile )
{
	point upper_left;
	point lower_right;
	get_dimensions( edges, upper_left, lower_right );

	int width = lower_right.get_x() - upper_left.get_x();
	int height = lower_right.get_y() - upper_left.get_y();

	point offset = calculate_translation_offset( upper_left, lower_right );

	pngwriter image( width, height, 65535, savefile.c_str() );

	// Draw axes
	image.line( offset.get_x(), height, offset.get_x(), 1, 0.5, 0.5, 0.5 );
	image.line( 0, offset.get_y(), width, offset.get_y(), 0.5, 0.5, 0.5 );

	// Plot the edges
	for ( auto& e : edges ) {
		point a = translate( offset, e.get_a() );
		point b = translate( offset, e.get_b() );
		image.line( a.get_x(), a.get_y(), b.get_x(), b.get_y(), 0.0, 0.5, 0.5 );
		image.cross( a.get_x(), a.get_y(), 4, 4, 0, 0, 0 );
		image.cross( b.get_x(), b.get_y(), 4, 4, 0, 0, 0 );
	}

	// Close the image to write it to a file.
	image.close();
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
// Replace the data filename extension with ".png"
//
static string get_savename( const string& filename )
{
	string savename( filename );
	size_t last_dot = savename.find_last_of( '.' );
	savename.replace( last_dot, string::npos, ".png" ); 
	return savename;
}

