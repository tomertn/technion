package homework1;

import java.awt.*;
import java.util.*;


/**
 * A LocationChaningShape is a Shape that can change its location using its step()
 * method. A LocationChaningShape has a velocity property that determines the speed
 * of location changing.
 * Thus, a typical LocationChaningShape consists of the following set of
 * properties: {location, color, shape, size, velocity}
 */
public abstract class LocationChangingShape extends Shape implements Animatable {

	// TODO: Write Abstraction Function
	// Represents a moveable Shape, with top left pixel at this.location and color
	// at this.color (inherits), 
	// and the velocity in pixels/step at this.velocityX and this.velocityY. 
	
	// TODO: Write Representation Invariant
	// -5 <= velocityX <= 5 and velocityX != 0 and -5 <= velocityY <= 5 and velocityY != 0
	// Color and location are not null;
	// this.location.getX()>=0 and this.location.getY()>=0
	
	private int velocityX;
	private int velocityY;

	
	/**
	 * @effects Initializes this with a a given location and color. Each
	 *          of the horizontal and vertical velocities of the new
	 *          object is set to a random integral value i such that
	 *          -5 <= i <= 5 and i != 0
	 * @param location of the top left shape
	 * @param color of the shape
	 */
	LocationChangingShape(Point location, Color color) {
    	// TODO: Implement this constructor
		super(location, color);
		Random rand = new Random();
		int vX = rand.nextInt(10);
		vX -= 5;
		while(vX == 0 ) {
			vX = rand.nextInt(10);
			vX -= 5;
		}
		int vY = rand.nextInt(10);
		vY -= 5;
		while(vY == 0 ) {
			vY = rand.nextInt(10);
			vY -= 5;
		}
		this.velocityX = vX; this.velocityY = vY;
		checkRep();

    }


    /**
     * @return the horizontal velocity of this.
     */
    public int getVelocityX() {
    	// TODO: Implement this method
    	checkRep();
    	return this.velocityX;    	
    }


    /**
     * @return the vertical velocity of this.
     */
    public int getVelocityY() {
    	// TODO: Implement this method
    	checkRep();
    	return this.velocityY;
    }


    /**
     * @modifies this
     * @effects Sets the horizontal velocity of this to velocityX and the
     * 			vertical velocity of this to velocityY.
     */
    public void setVelocity(int velocityX, int velocityY) {
    	// TODO: Implement this method
    	checkRep();
    	this.velocityX = velocityX;
    	this.velocityY = velocityY;
    	checkRep();
    }


    /**
     * @modifies this
     * @effects Let p = location
     * 				v = (vx, vy) = velocity
     * 				r = the bounding rectangle of this
     *         	If (part of r is outside bound) or (r is within bound but
     *          adding v to p would bring part of r outside bound) {
     * 				If adding v to p would move r horizontally farther away
     * 				from the center of bound,
     * 					vx = -vx
     * 				If adding v to p would move r vertically farther away
     * 				from the center of bound,
     * 					vy = -vy
     *          }
     * 			p = p + v
     */
    public void step(Rectangle bound) {
    	checkRep();
    	Point p = this.getLocation();
    	Rectangle r = this.getBounds();
    	Rectangle next_rect = new Rectangle((int)r.getX()+velocityX,(int)r.getY()+velocityY,
    										(int)r.getWidth(),(int)r.getHeight());
    	if( !bound.contains(r) || !bound.contains(next_rect)) {
    		//check horizontal:
    		next_rect.setLocation((int)r.getX()+velocityX,(int)r.getY());
    		if(Math.abs(next_rect.getCenterX() - bound.getCenterX()) > 
    		Math.abs(r.getCenterX() - bound.getCenterX())) {
    			velocityX = -velocityX;
    		}
    		//check vertical:
    		next_rect.setLocation((int)r.getX(),(int)r.getY() + velocityY);
    		if(Math.abs(next_rect.getCenterY() - bound.getCenterY()) > 
    		Math.abs(r.getCenterY() - bound.getCenterY())) {
    			velocityY = -velocityY;
    		}
    		
    	}
    	Point newLocation = new Point((int)p.getX()+velocityX,(int)p.getY()+velocityY);
    	checkRep();		
    	this.setLocation(newLocation);	
    	checkRep();
    }

    /**
     * @effects Creates and returns a copy of this.
     */
    @Override
    public Object clone() {
    	// TODO: Implement this method
    	checkRep();
    	LocationChangingShape newShape = null;
    	// shallow copy
    	newShape = (LocationChangingShape)super.clone();
    	// deep copy:
    	newShape.setVelocity(this.velocityX,this.velocityY);
 
        checkRep();
        return newShape;
    }
    
    /**
     * @effects assert if Rep invariant is violated.
     */
    private void checkRep() {
    	assert this.getVelocityX() != 0;
    	assert this.getVelocityY() != 0;
    	assert Math.abs(this.getVelocityX()) <= 5;
    	assert Math.abs(this.getVelocityY()) <= 5;
    }
    
}
