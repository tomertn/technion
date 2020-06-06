package homework1;
 
import java.awt.*;
 
/**
 * A LocationChaningOvel is a Ovel Shape that can change its location using its step()
 * method. A LocationChaningOvel has a velocity property that determines the speed
 * of location changing.
 * Thus, a typical LocationChaningOvel consists of the following set of
 * properties: {location, color, shape, size, velocity}
 */
public class LocationChangingOval extends LocationChangingShape {
     
    private Dimension size;
 
    // Abstraction Function:
    // represents a moveable Rectangle Oval Shape with top left boundary box location at this.getLocation()
    // color at this.getColor(), velocity at this.getVelocityX and this.getVelocityY (inherits)
    // and size at this.size .
     
    // Representation invariant:
    // size != null
    // size.height > 0 
    // size.width > 0
    // -5 <= velocityX <= 5 and velocityX != 0 and -5 <= velocityY <= 5 and velocityY != 0
 	// Color and location are not null;
 	// this.location.getX()>=0 and this.location.getY()>=0
    
    
    /**
     * @effects Initializes this with a a given location, color, height, width.
     * @param location of shape
     * @param color of shape
     * @param height of shape
     * @param width of shape
     */
    public LocationChangingOval(Point location, Color color, int width, int height ) {
        super(location, color);
        this.size = new Dimension(width, height);
        checkRep();
    }
     
     
    /**
     * @return the bounding rectangle of this.
     */
    public  Rectangle getBounds() {
        checkRep();
        Rectangle bounds = new Rectangle((int)this.getLocation().getX(), (int)this.getLocation().getY(),
        		(int)this.size.getWidth(), (int)this.size.getHeight());
        checkRep();
        return bounds;
    }
     
     
    /**
     * @modifies g
     * @effects Draws this onto g.
     */
    public void draw(Graphics g) {  
        checkRep();
        if( g == null) {
        	System.out.println("Graphics is null");
        	return;
        }
        g.setColor(this.getColor());
        g.fillOval((int)this.getLocation().getX(), (int)this.getLocation().getY(), 
        		(int)this.size.getWidth(), (int)this.size.getHeight());
        checkRep();
    }
    /**
     * @return the size of this.
     */
    public Dimension getSize() {
    	checkRep();
    	return new Dimension(this.size);
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
    public void setSize(Dimension dimension) throws ImpossibleSizeException {
        checkRep();
        if((dimension.getHeight() <= 0) || (dimension.getWidth() <=0))
        {
        	throw new ImpossibleSizeException(this.getSize());
        }
        this.size.setSize((int)dimension.getWidth() , (int)dimension.getHeight());
        checkRep();
        return;
    }
     
    /**
     * @throws assert if representation invariant is violate.
     */   
    private void checkRep() {
        assert ((this.size.getWidth() > 0) && (this.size.getHeight() > 0));
    }
 
    /**
     * @effects Creates and returns a copy of this.
     */
    @Override
    public Object clone() {
        checkRep();
        LocationChangingOval newOval = null;
        try {
            newOval = (LocationChangingOval)super.clone();
			newOval.setSize((Dimension)this.getSize());
		} catch (ImpossibleSizeException e) {
			e.printStackTrace();
		}
        checkRep();
        return newOval;
    }
    
}