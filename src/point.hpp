#ifndef MST_POINT_H
#define MST_POINT_H

class point
{
public:
	point();
	point( int, int );
	point( const point& );
	~point();

	int get_x( void ) const;
	int get_y( void ) const;
	void set_x( int );
	void set_y( int );

	point& operator=( point const& );
	bool operator==( const point& ) const;
	bool operator!=( const point& ) const;
	bool operator<( const point& ) const;
private:
	int x;
	int y;
};

#endif // MST_POINT_H

