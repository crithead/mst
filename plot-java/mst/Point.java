/**
 *  A point on a graph.
 */
package mst;

/**
 * A Point
 */
class Point
{
    /**
     * Construct a point with X and Y coordinates.
     * @param x the horizontal coordinate
     * @param y the vertical coordinate
     */
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Construct a point at the <em>origin</em>.
     */
    public Point() {
        this(0, 0);
    }

    /**
     * Construct a point as a copy of another Point.
     * @param p a Point object
     */
    public Point(Point p) {
        this(p.getX(), p.getY());
    }

    /**
     * Get the X coordinate.
     * @return the x-coordinate value
     */
    public int getX() {
        return this.x;
    }

    /**
     * Get the Y coordinate.
     * @return the y-coordinate value
     */
    public int getY() {
        return this.y;
    }

    /**
     * Set the X coordinate.
     * @param x the new value for the x-coordinate
     */
    public void setX(int x) {
        this.x = x;
    }

    /**
     * Set the Y coordante.
     * @param y the new value for the y-coordinate
     */
    public void setY(int y) {
        this.y = y;
    }

    /**
     * Compare another Points to this one for equality.
     * @param p a Point
     * @return <string>true</strong> if the Point has the same X and Y
     *         coordiantes as this Point and <strong>flase</strong> if
     *         they differ.
     */
    public boolean equals(Point p) {
        if (this.x == p.getX() && this.y == p.getY())
            return true;
        else
            return false;
    }

    //Point operator=( Point const& );
    //bool operator!=( const Point& ) const;
    //bool operator<( const Point& ) const;

    /**
     * Point A is less than Point B, if it's distance from y = -x is more
     * negative.
     *
     * TODO Does this cover all the cases?
     * @param p Another Point
     * @return true/false
     */
    public boolean lessThan(Point p) {
        boolean isLessThan = false;

        if ( this.equals(p) ) {
            isLessThan = false;
        } else if ( this.x < p.getX() && this.y < p.getY() ) {
            isLessThan = true;
        } else {
            double SQRT_2 = 1.4142135623731;
            // distance from a point to the line y = -x
            double da = (double)(Math.abs(-1 * this.x + this.y)) / SQRT_2;
            double db = (double)(Math.abs(-1 * p.getX() + p.getY())) / SQRT_2;
            if ( da < db )
                isLessThan = true;
            else
                isLessThan = false;
        }

        return isLessThan;
    }

    /**
     * Compares this Point to another Point to determine which is closer to
     * the line x = -y.
     *
     * @param p Another Point
     * @return the value 0 if Point p is numerically equal to this Point;
     *      a value less than 0 if this Point is numerically less than
     *      Point p; and a value greater than 0 if this Point is
     *      numerically greater than Point p.
     */
    public int compareTo(Point p) {
        int value = 0;

        if ( this.equals(p) ) {
            value = 0;
        } else if ( this.x < p.getX() && this.y < p.getY() ) {
            value = -1;
        } else {
            double SQRT_2 = 1.4142135623731;
            // distance from a point to the line y = -x
            double da = (double)(Math.abs(-1 * this.x + this.y)) / SQRT_2;
            double db = (double)(Math.abs(-1 * p.getX() + p.getY())) / SQRT_2;
            if ( da < db )
                value = -1;
            else
                value = 1;
        }

        return value;
    }

    private int x;
    private int y;
}

