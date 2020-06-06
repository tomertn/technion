package homework1;
 
import java.awt.*;
 
    /**
     * A LocationChangingRectangle is a Rectangle Shape that can change its location.
     * set of properties: {location, color,shape, size, velocity}
     */ 
public class LocationChangingRectangle extends LocationChangingShape {
     
    private Dimension size;
 
    // Abstraction Function:
    // represents a moveable Rectangle Shape with location at this.getLocation()
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
     * @effects Initializes an Rectangle in a given location. 
     * @param location of shape
     * @param color of shape
     * @param height of shape
     * @param width of shape
     */
    public LocationChangingRectangle(Point location, Color color, int width, int height ) {
        super(location, color);
        size = new Dimension(width, height);
        checkRep();
    }
     
     
    /**
     * @return the bounding rectangle of this.
     */
    @Override
    public  Rectangle getBounds() {
        checkRep();
        Rectangle bounds = new Rectangle((int)getLocation().getX(), (int)getLocation().getY(),
        								(int)size.getWidth(),(int)size.getHeight());
        checkRep();
        return bounds;
    }
     
     
    /**
     * @modifies graph
     * @effects draws this onto g.
     */
    @Override
    public void draw(Graphics g) {
    	if(g == null) {
    		System.out.println("graphic var is null");
    		return;
    	}
        checkRep();
        g.setColor(getColor());
        g.fillRect((int)getLocation().getX(), (int)getLocation().getY(), 
        		(int)size.getWidth(), (int)size.getHeight());
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
     *          dimension.
     *          If this cannot be resized to the specified dimension,
     *          this is not modified, throws ImpossibleSizeException
     *          (the exception suggests an alternative dimension that is
     *           supported by this).
     */
    @Override
    public void setSize(Dimension dimension) throws ImpossibleSizeException {
        checkRep();
        if((dimension.getHeight() <= 0) || (dimension.getWidth() <=0))
        {
        	throw new ImpossibleSizeException(this.getSize());
        }
        this.size.setSize((int) dimension.getWidth(), (int) dimension.getHeight() );
        checkRep();
    }
     
    /**
     * check representation invariant.
     * @throws AssertionError violate representation invariant.
     */   
    private void checkRep() {
    	assert size != null;
        assert ((size.getHeight() > 0) && (size.getWidth() > 0));
    }
 
    /**
     * @effects Creates and returns a copy of this.
     */
    @Override
    public Object clone() {
        checkRep();
        LocationChangingRectangle newLocationChangingRectangle = null;
        try {
        	newLocationChangingRectangle = (LocationChangingRectangle)super.clone();
        	newLocationChangingRectangle.setSize((Dimension)this.getSize());
		} 
        catch (ImpossibleSizeException e) {
			e.printStackTrace();
		}
        checkRep();
        return newLocationChangingRectangle;
    }
    
}