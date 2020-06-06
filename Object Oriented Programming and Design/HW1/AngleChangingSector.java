package homework1;
import java.awt.*;

public class AngleChangingSector extends Shape implements Animatable {
	
	private Dimension size;
	private int current_angle;
	private int section;
	
    // Abstraction Function:
    // represents a moveable sector in Oval Shape with top left boundary box location at this.getLocation()
    // color at this.getColor() (inherits)
    // and size at this.size , start angle of the sector in this.current_angle and section size at this.section .
     
    // Representation invariant:
    // size != null 
    // size.height > 0 
    // size.width > 0
	// this.current_angle and this.section are between 0 to 360
	
	public AngleChangingSector(Point location, Color color,int width, 
			int height,int start_angle,int section) {
		super(location,color);
		 this.size = new Dimension(width, height);
		 this.current_angle=start_angle;
		 this.section=section;
	     checkRep();
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
        g.fillArc((int)this.getLocation().getX(), (int)this.getLocation().getY(),
        		(int)this.size.getWidth(), (int)this.size.getHeight(),this.current_angle,this.section);
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
	 * @modifies this
	 * @effects Updates the state of this to the appropriate value for the
	 * 			next animation step. The argument bound indicates the area
	 * 			within which this is allowed to move.
	 */
    public void step(Rectangle bound) {
    	if(!bound.contains(this.getBounds())) {
    		System.out.println("Step is not allowed");
    		return;
    	}
    	checkRep();
    	this.current_angle = (this.current_angle + 1)%360;
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
     * @effects Creates and returns a copy of this.
     */
    @Override
    public Object clone() {
        checkRep();
        AngleChangingSector newArc = null;
        try {
        	newArc = (AngleChangingSector)super.clone();
        	newArc.setSize((Dimension)this.getSize());
		} catch (ImpossibleSizeException e) {
			e.printStackTrace();
		}
        checkRep();
        return newArc;
    }
    
    /**
     * @throws assert if representation invariant is violate.
     */   
    private void checkRep() {
        assert ((this.size.getWidth() > 0) && (this.size.getHeight() > 0));
        assert ((this.current_angle >= 0) && (this.current_angle<360));
        assert ((this.section >= 0) && (this.section<360));
    }
	

}
