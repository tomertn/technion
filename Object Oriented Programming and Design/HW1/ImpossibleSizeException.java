package homework1;
import java.awt.*;

/**
 * An ImpossibleSizeException is an exception object. Thrown when trying to set
 * an illegal size in Shape object. Contains new legal size which the user can use.
 * ImpossibleSizeExceptions are immutable.
 */

public class ImpossibleSizeException extends Exception {
	
	/**
	 * auto generated key by the IDE
	 */
	private static final long serialVersionUID = 1L;
	
	
	/**
	 * @effects Initializes this.size with a a legal size by assigning abs value.
	 */
	private Dimension size;
	public ImpossibleSizeException(Dimension size) {
		this.size.setSize(Math.abs(size.getWidth()), Math.abs(size.getHeight())); 
	}
	
	/**
     * @return the legal size calculates in the constructor.
     */
	public Dimension getSize() {
		return this.size;
	}

}
