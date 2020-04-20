/**
 * Plot a graph to a PNG file.
 *
 * The graph is a list of edges.  An edge is a pair of vertices.
 */

package mst;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.StringTokenizer;
import java.util.Vector;

import javax.imageio.ImageIO;


public class PlotGraph
{
    /**
     * Generate a plot of each graph data file in the argument list.
     *
     * The special arguments <code>--verbose</code> and <code>--quiet</code>
     * enable or disable debugging messages.
     *
     * @param args a list of command line arguments
     *
     * The system return value is the number of files that were not
     * successfully processed.
     */
     public static void main(String[] args) {
         int status = 0;

         System.out.println("Plot Graph");

         for (int i = 0; i < args.length; i++) {
             if (args[i].equals("--verbose")) {
                 debugPrint = true;
                 continue;
             }
             if (args[i].equals("--quiet")) {
                 debugPrint = false;
                 continue;
             }

             String filename = new String(args[i]);
             try {
                 // Load the list of edges from a file
                 Vector<Edge> edges = load(filename);

                 if (debugPrint)
                     print(edges);

                 // Save the PNG image to a file
                 String savename = getSavename(filename);
                 debug("Output file: " + savename);

                 // Plot the edges to a PNG image
                 plot(edges, savename);
                 debug("\n");
             }
             catch (OutOfMemoryError e) {
                 System.err.println("File         : " + filename);
                 System.err.println("Out of memory: " + e);
                 status++;
             }
             catch (Exception e) {
                 System.err.println("File     : " + filename);
                 System.err.println("Exception: " + e);
                 status++;
             }
         }

         System.exit(status);
     }

    private static boolean debugPrint = false;

    /**
     * Print debugging messages when debugPrint is true.
     * @param s the message
     */
    private static void debug(String s) {
        if (debugPrint)
            System.out.println(s);
    }

    /**
     * Load a set of edges from a file.
     * @param filename the name of the data file
     * @return A Vector of Edges
     */
    private static Vector<Edge> load(String filename) {
        debug("load ( filename = " + filename + " )");

        Vector<Edge> edgeList = new Vector<Edge>();
        try {
            BufferedReader in = new BufferedReader(new FileReader(filename));
            String line = in.readLine();
            while (line != null && line.length() > 8) {
                StringTokenizer st = new StringTokenizer(line, "\t");
                int x1 = Integer.parseInt(st.nextToken());
                int y1 = Integer.parseInt(st.nextToken());
                int x2 = Integer.parseInt(st.nextToken());
                int y2 = Integer.parseInt(st.nextToken());
                @SuppressWarnings("unused")
                float wt = Float.parseFloat(st.nextToken());
                edgeList.add(new Edge(new Point(x1, y1), new Point(x2, y2)));
                line = in.readLine();
            }
            in.close();
        } catch (FileNotFoundException e) {
            System.out.println("FileNotFoundException: " + e);
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("IOException: " + e);
            e.printStackTrace();
        }

        return edgeList;
    }

    /**
     * Calculate the translation offset from graph-relative coordinates to
     * image-relative coordinates.
     *
     * Move the entire image into Quadrant I
     *
     * @param ul a Point in the upper left corner
     * @param lr a Point in the lower right corner
     * @param pad padding to make the image larger than the extreme points
     */
    private static Point calculateTranslationOffset(Point ul, Point lr, int pad) {
        return new Point(Math.abs(ul.getX()) + pad, Math.abs(lr.getY()) + pad);
    }

    /**
     * Get the upper-left and lower-right coordinate extremes from the vertices
     * in a set of edges.
     * @param edges a Vector of Edges
     * @param ul a ref to a Point wherein the upper left coordinate will be
     *         returned
     * @param lr a ref to a Point wherein the lower right coordinate will be
     *         returned
     */
    private static void getDimensions(Vector<Edge> edges, Point ul, Point lr) {
        ul.setX(Integer.MAX_VALUE);
        ul.setY(Integer.MAX_VALUE);
        lr.setX(Integer.MIN_VALUE);
        lr.setY(Integer.MIN_VALUE);

        Iterator<Edge> it = edges.iterator();
        while (it.hasNext()) {
            Edge e = it.next();
            // Find upper-left corner
            if ( e.getA().getX() < ul.getX() )
                ul.setX( e.getA().getX() );
            if ( e.getA().getY() < ul.getY() )
                ul.setY( e.getA().getY() );
            if ( e.getB().getX() < ul.getX() )
                ul.setX( e.getB().getX() );
            if ( e.getB().getY() < ul.getY() )
                ul.setY( e.getB().getY() );
            // Find lower-right corner
            if ( e.getA().getX() > lr.getX() )
                lr.setX( e.getA().getX() );
            if ( e.getA().getY() > lr.getY() )
                lr.setY( e.getA().getY() );
            if ( e.getB().getX() > lr.getX() )
                lr.setX( e.getB().getX() );
            if ( e.getB().getY() > lr.getY() )
                lr.setY( e.getB().getY() );
        }
    }

    /**
     * Generate a PNG image plot for a set of edges and write it to the
     * specified file.
     * @param edges A Vector of Edges
     * @param savename the name of a file to save the graph to
     */
    private static void plot(Vector<Edge> edges, String savename) {
        final int PAD = 10;
        Point upperLeft = new Point();
        Point lowerRight = new Point();

        getDimensions(edges, upperLeft, lowerRight);
        debug("upper-left : " + upperLeft.getX() + ", " + upperLeft.getY());
        debug("lower-right: " + lowerRight.getX() + ", " + lowerRight.getY());

        int width = roundUp(lowerRight.getX() - upperLeft.getX(), PAD);
        int height = roundUp(lowerRight.getY() - upperLeft.getY(), PAD);

        Point offset = calculateTranslationOffset(upperLeft, lowerRight, PAD);
        debug("offset : " + offset.getX() + ", " + offset.getY());

        BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = image.createGraphics();
        g2d.setBackground(Color.WHITE);
        g2d.clearRect(0, 0, width, height);

        // Draw axes
        g2d.setPaint(Color.GRAY);
        g2d.drawLine(offset.getX(), 0, offset.getX(), height);
        g2d.drawLine(0, offset.getY(), width, offset.getY());

        // Plot the edges
        Iterator<Edge> it = edges.iterator();
        while (it.hasNext()) {
            Edge e = it.next();
            Point a = translate(offset, e.getA());
            Point b = translate(offset, e.getB());

            // draw the edge
            g2d.setPaint(Color.CYAN);
            g2d.drawLine(a.getX(), a.getY(), b.getX(), b.getY());

            // draw a cross at each end point
            g2d.setPaint(Color.BLACK);
            g2d.drawLine(a.getX(), a.getY() - 2, a.getX(), a.getY() + 2);
            g2d.drawLine(a.getX() - 2, a.getY(), a.getX() + 2, a.getY());
            g2d.drawLine(b.getX(), b.getY() - 2, b.getX(), b.getY() + 2);
            g2d.drawLine(b.getX() - 2, b.getY(), b.getX() + 2, b.getY());
        }

        // Write the image to a file.
        try {
            File savefile = new File(savename);
            ImageIO.write(image, "png", savefile);
        } catch (IOException e) {
            System.out.println("IOException: " + e);
            e.printStackTrace();
        }
    }

    /**
     * Print a vector of edges (if verbose output is enabled).
     * @param edges a Vector of Edge
     */
    private static void print(Vector<Edge> edges)
    {
        if (!debugPrint)
            return;
        System.out.println("number of edges = " + edges.size());
        Iterator<Edge> it = edges.iterator();
        while (it.hasNext()) {
            Edge e = it.next();
            System.out.println( "(" +  e.getA().getX() + "," + e.getA().getY()
                + ") -> (" + e.getB().getX() + "," + e.getB().getY()
                + ") wt = " + e.getLength());
        }
        System.out.println("");
    }

    /**
     * Round the image dimension (width or height) up to the next multiple of m.
     * @param x initial dimension
     * @param m the number boundary
     * @return the adjusted dimension
     */
    private static int roundUp(int x, int m) {
        int q = (x + 2 * m) / m;
        return (q + 1) * m;
    }

    /**
     * Replace the data filename extension of ".csv" with ".png"
     * @param filename the name of the input file
     * @return the name of the output file
     */
    private static String getSavename(String filename) {
        if (!filename.endsWith(".csv"))
            throw new IllegalArgumentException("filename must end in '.csv'");
        String savename = filename.replace(".csv", ".png");
        return savename;
    }

    /**
     * Translate from graph-relative coordinates to image-relative coordinates.
     * @param offset the translation offset
     * @param a a Point to translate
     * @return the resulting Point
     */
    private static Point translate(Point offset, Point a) {
        return new Point(a.getX() + offset.getX(), a.getY() + offset.getY());
    }
}

