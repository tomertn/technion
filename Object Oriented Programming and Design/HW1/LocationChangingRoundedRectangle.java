package homework1;
 
import java.awt.*;
 
    /**
     * A LocationChangingRoundedRectangle is a rounded Rectangle Shape that can change its location.
     * set of properties: {location, color,shape, size, velocity}
     */ 
public class LocationChangingRoundedRectangle extends LocationChangingRectangle {
    // Abstraction Function:
    // represents a moveable Rectangle Shape with location at this.getLocation()
    // color at this.getColor(), velocity at this.getVelocityX and this.getVelocityY 
    // and size at this.getSize() (inherits all) .
     
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
    public LocationChangingRoundedRectangle(Point location, Color color, int width, int height ) {
        super(location, color ,width ,height);
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
    	int arcWidth = 10, arcHeight = 10;
        g.setColor(getColor());
        g.fillRoundRect((int)getLocation().getX(), (int)getLocation().getY(),
        		(int)getSize().getWidth(), (int)getSize().getHeight(), arcWidth, arcHeight);

    }
    
 
    /**
     * @effects Creates and returns a copy of this.
     */
    @Override
    public Object clone() {
    	LocationChangingRoundedRectangle newLocationChangingRectangle = null;
        newLocationChangingRectangle = (LocationChangingRoundedRectangle)super.clone();
        
        return newLocationChangingRectangle;
    }
    
}