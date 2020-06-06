package homework1;
import java.awt.Point;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Dimension;
 
/**
 * A LocationChangingNumberedOval is a Ovel Shape that can change its location using its step()
 * method. A LocationChaningOvel has a velocity property that determines the speed
 * of location changing. each LocationChangingNumberedOval has serial number.
 * Thus, a typical LocationChaningOvel consists of the following set of
 * properties: {location, color, shape, size, velocity, number}
 */
public class LocationChangingNumberedOval extends LocationChangingOval {
     
    private static int ovalCnt = 0;
    private int serailNum; 
     
     
    // Abstraction Function:
    // represents a moveable Rectangle Oval Shape with top left boundary box location at this.getLocation()
    // color at this.getColor(), velocity at this.getVelocityX ,this.getVelocityY (inherits)
    // , size at this.size, serial number this.serailNum and static counter this.ovalCnt.
     
    // Representation invariant:
    // size != null
    // size.height > 0 
    // size.width > 0
    // -5 <= velocityX <= 5 and velocityX != 0 and -5 <= velocityY <= 5 and velocityY != 0
 	// Color and location are not null;
 	// this.location.getX()>=0 and this.location.getY()>=0
    // serailNum > 0
    // ovalCnt >= 0.
    
    /**
     * @effects Initializes this with a a given location, color, height, width.
     * @param location of shape
     * @param color of shape
     * @param height of shape
     * @param width of shape
     */
    public LocationChangingNumberedOval(Point location, Color color, int width, int height) {
        super(location, color, width, height);
        ovalCnt++;
        serailNum = ovalCnt;
        checkRep();
    }
    
    
     
    /**
     * @modifies graph
     * @effects Draws this.
     */
    @Override
    public void draw(Graphics g) { 
        checkRep();
        super.draw(g);
        g.setColor(Color.white);
        g.drawString(String.valueOf(this.serailNum), (int)getBounds().getCenterX(), (int)getBounds().getCenterY());
        checkRep();
    }
    
    /**
     * @modifies this
     * @effects increment counter, and assign the counter to the serial number.
     */
    private void setNum()  {
        checkRep();
        ovalCnt++;
        this.serailNum = ovalCnt;
        checkRep();
        return;
    }
    /**
     * @modifies this
     * @effects reset counter.
     */
    public static void resetCounter() {
    	ovalCnt = 0;
    }
    /**
     * @throws assert if representation invariant is violate.
     */   
    private void checkRep() {
        assert ((ovalCnt>=0) && (serailNum>0));
    }
    
    /**
     * @effects Creates and returns a copy of this.
     */
    @Override
    public Object clone() {
        checkRep();
        LocationChangingNumberedOval newNumOval = null;
        newNumOval = (LocationChangingNumberedOval)super.clone();
        newNumOval.setNum();
        checkRep();
        return newNumOval;
    }
   
}