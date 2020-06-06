package homework1;

import java.awt.*;


/**
 * A Shape is an abstraction of a shape object. A typical Shape consists of
 * a set of properties: {location, color, shape, size}.
 * Shapes are mutable and cloneable.
 */
public abstract class Shape implements Cloneable {

	private Point location;
	private Color color;

	
	// TODO: Write Abstraction Function
	// Represents a Shape, with top left pixel at this.location and color
	// at this.color.
	
	// TODO: Write Representation Invariant
	// Color and location are not null;
	// this.location.getX()>=0 and this.location.getY()>=0
	
	
	/**
	 * @effects Initializes this with a a given location and color.
	 * @param location of the top left shape
	 * @param color of the shape
	 */
    public Shape(Point location, Color color) {
    	setLocation(location);
    	setColor(color);
    	checkRep();
    }


    /**
     * @return the top left corner of the bounding rectangle of this.
     */
    public Point getLocation() {
    	// TODO: Implement this method
    	checkRep();
    	return (Point)this.location.clone(); // Point is a mutable object	
    }


    /**
     * @modifies this
     * @effects Moves this to the given location, i.e. this.getLocation()
     * 			returns location after call has completed.
     */
    public void setLocation(Point location) {
    	checkRep();
    	this.location = (Point)location.clone();
    	checkRep();
    }


    /**
     * @modifies this
     * @effects Resizes this so that its bounding rectangle has the specified
     * 			dimension.
     * 			If this cannot be resized to the specified dimension =>
     * 			this is not modified, throws ImpossibleSizeException
     * 			(the exception suggests an alternative dimension that is
     * 			 supported by this).
     */
    public abstract void setSize(Dimension dimension)
    	throws ImpossibleSizeException;

    
    /**
     * @return the bounding rectangle of this.
     */
    public abstract Rectangle getBounds();
  

    /**
     * @return true if the given point lies inside the bounding rectangle of
     * 		   this and false otherwise.
     */
    public boolean contains(Point point) {
    	checkRep();
    	return getBounds().contains(point);
    }
        

    /**
     * @return color of this.
     */
    public Color getColor() {
    	checkRep();
    	return color;
    }


    /**
     * @modifies this
     * @effects Sets color of this.
     */
    public void setColor(Color color) {
    	checkRep();
    	this.color = color;
    	checkRep();
    }


    /**
     * @modifies g
     * @effects Draws this onto g.
     */
    public abstract void draw(Graphics g);


    /**
     * @effects Creates and returns a copy of this.
     */
    @Override
    public Object clone() {
    	// TODO: Implement this method
    	checkRep();
    	Shape newShape = null;
    	try {
    		// shallow copy
    		newShape = (Shape)super.clone();
    		// deep copy:
    		newShape.setColor((Color)this.getColor());  
            newShape.setLocation((Point)this.getLocation());
    	}
    	catch (CloneNotSupportedException e)
        {
            e.printStackTrace();
            checkRep();
            return null;
        }
        checkRep();
        return newShape;
    }
    
    /**
     * @effects assert if Rep invariant is violated.
     */
    private void checkRep() {
    	assert this.location != null;
    	assert this.color != null;
    	assert this.location.getX() >= 0;
    	assert this.location.getY() >= 0;
    }
}