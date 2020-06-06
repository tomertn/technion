package homework1;

import java.awt.Rectangle;

/**
 * Animatables are objects that can be animated.
 * Animation is achieved by invoking a number of steps of small modifications,
 * movements, or transformations on this.
 */
public interface Animatable {

	/**
	 * @modifies this
	 * @effects Updates the state of this to the appropriate value for the
	 * 			next animation step. The argument bound indicates the area
	 * 			within which this is allowed to move.
	 */
    public void step(Rectangle bound);
}
