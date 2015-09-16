#ifndef MST_POINT_H
#define MST_POINT_H

class point
{
public:
	point();
	point( int, int );
	point( const point& );
	~point();
	point& operator=( point const& );
	int get_x( void ) const;
	int get_y( void ) const;
	void set_x( int );
	void set_y( int );
private:
	int x;
	int y;
};

#endif // MST_POINT_H

