package homework2;

import java.util.*;

abstract public class Pipe<E, T> extends SimModule<E, T> {
    /**
     * Abstraction function:
     * Pipe represents a simulatable object of type pipe.
     * this.capacity represents the pipe capacity of objects.
     * this.Queue represents the pipe queue.
     * pipe transfer objects to filter.
     *
     * Representation invariant:
     * this.capacity > 0
     * Queue.size() <= capacity
     *
     *
     * @param <E> type of labels
     * @param <T> type of data
     */

    private int capacity;
    protected Queue<T> Queue;

    /**
     * @requires label != null, capacity > 0
     * @modifies this
     * @effects creates new pipe with label and capacity. if is_capacity==false,
     * 			assign the maximum value to capacity.
     * @throws NullPointer 
     */
    public Pipe(E label, int capacity, boolean is_capacity) throws NullPointer
    {
        super(label);
        Queue = new LinkedList<>();
        if (is_capacity == false)
            this.capacity = Integer.MAX_VALUE;
        else
            this.capacity = capacity;
        checkRep();
    }
    
    /**
     * @return the capacity of this.
     */
    public double getCapacity()
    {
        checkRep();
        return capacity;
    }

    /**
     * @modifies
     * @effects 
     * @return the pipe content in String.
     */
    @Override
    public String getContent() {
        checkRep();
        String str= new String("");
        for(T obj : Queue)
            str = new String(str + obj.toString() + " ");
        checkRep();
        return str;
    }

    
    private void checkRep()
    {
    	assert capacity > 0;
        assert Queue.size()<= capacity;
    }

}
