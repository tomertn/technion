package homework2;

import java.util.*;
abstract public class Filter<E, T> extends SimModule<E, T> {
    /**
     * Abstraction function:
     * Filter represents a simulatable object of type filter.
     * this.objects represents the stored data.
     * filters "process" objects.
     *
     * Representation invariant:
     * objects != null
     *
     *
     * @param <E> type of labels
     * @param <T> type of data
     */


    protected Queue<T> objects;

    /**
     * @requires label != null
     * @effects creates new filter with the label.
     * @throws NullPointer 
     */
    public Filter(E label) throws NullPointer
    {
        super(label);
        objects = new LinkedList<>();
        checkRep();
    }

    /**
     * @modifies
     * @effects 
     * @return the filter content in String.
     */
    @Override
    public String getContent() {
        checkRep();
        String str= new String("");
        for(T obj : objects)
            str = new String(str + obj.toString() + " ");
        checkRep();
        return str;
    }

    private void checkRep()
    {
        assert  objects != null;
    }

}
