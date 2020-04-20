package mst;

import java.lang.Math;

/**
 * A graph edge.
 */
class Edge {
    /**
     * Calclulate the distance between points.
     * @param a one point
     * @param b another point
     * @return the straight-line distance from point a to point b
     */
    public static float distance(Point a, Point b) {
        int dx = a.getX() - b.getX();
        int dy = a.getY() - b.getY();
        return (float)Math.sqrt((double)(dx * dx + dy * dy));
    }

    /**
     * Construct an edge from two distinct points.
     * @param a a Point
     * @param b another Point
     */
    Edge(Point a, Point b) {
        if (a.equals(b)) {
            throw new IllegalArgumentException("an edge must have distinct vertices");
        } else if (a.lessThan(b)) {
            this.a = new Point(a);
            this.b = new Point(b);
        } else {
            this.a = new Point(b);
            this.b = new Point(a);
        }
        this.length = distance(a, b);
    }

    /**
     * Construct an edge as a copy of another edge.
     * @param e A Edge object.
     */
    Edge(Edge e) {
        this(e.getA(), e.getB());
    }

    /**
     * Get end point A.
     * @return A ref to Point A.
     */
    public Point getA() {
        return this.a;
    }

    /**
     * Get end point B.
     * @return A ref to Point B.
     */
    public Point getB() {
        return this.b;
    }

    /**
     * Get the length of the edge.
     * @return the distance between A and B
     */
    public float getLength() {
        return this.length;
    }

    /**
     * Compare edges for equality.
     * Edges are equal if they have the same vertices.
     * (a1 == a2 && b1 == b2 || a1 = b2 && b1 == a2 )
     */
    public boolean equals(Edge e) {
        return (this.a.equals(e.getA()) && this.b.equals(e.getB())) ||
               (this.a.equals(e.getB()) && this.b.equals(e.getB()));
    }

    //public edge& operator=( edge const& );
    //public bool operator!=( const edge& ) const;

    @SuppressWarnings("unused")
    private Edge() {} // An edge must be initialized with end points
    private Point a;
    private Point b;
    private float length;
}

