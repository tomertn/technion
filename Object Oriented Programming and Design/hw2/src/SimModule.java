package homework2;

import java.util.*;


abstract class SimModule<E, T> implements Simulatable<E>{
    /**
     * Abstraction function:
     * A single simulatable object. every object in the simulator will extend it.
     * works generically with E represents label and T object, and HashMap modules represents the 
     * graph modules
     *
     * Representation invariant:
     * label != null
     *
     * @param <E> type of label
     * @param <T> type of data
     */

    private E label;
    private HashMap<E, SimModule<E, T>> modules;

    
    /**
     * @throws NullPointer 
     * @requires label != null
     * @modifies this. 
     * @effects c'tor.
     */

    public SimModule(E label) throws NullPointer {
    	if(label==null)
        	throw new NullPointer("label is null");
        this.label = label;
        checkRep();
        modules = null;
    }

    
    /**
     * @throws NullPointer 
     * @requires t != null
     * @modifies this 
     * @effects store t in this.
     */
    public abstract boolean addProducts(T t) throws NullPointer;
    
    /**
     * @requires rec != null
     * @modifies this and rec. 
     * @effects store data stored in channel to rec.
     */
    public abstract boolean giveProducts(SimModule<E, T> rec) throws NullPointer;
    
    /**
     * @requires 
     * @modifies  
     * @effects return the content in a String.
     */
    public abstract String getContent();

    /**
     * @throws NullPointer 
     * @requires graph != null && modules != null
     * @modifies modules. 
     * @effects make a simulation step.
     */
    @Override
    public void simulate(BipartiteGraph<E> graph) {
        checkRep();
        try {
	        if(graph==null)
	        	throw new NullPointer("graph is null");
	        if(modules==null)
	        	throw new NullPointer("modules is null");
	        Vector<E> list_children = graph.getChildrenVector(getLabel());
	        for (E entry : list_children)
	        {
	           SimModule<E, T> rec = modules.get(entry);
	           if (giveProducts(rec))
	              break;
	        }
        } 
        // NullPointer print the message
        catch (NullPointer e) {
        }
        checkRep();
    	
    }
    /**
     * @requires 
     * @modifies  
     * @effects return the label of this.
     */
    public E getLabel()
    {
        checkRep();
        return label;
    }
    public void  setMap(HashMap<E, SimModule<E, T>> modules)
    {
        checkRep();
        this.modules = modules;
        checkRep();
    }

    private void checkRep()
    {
        assert ( label != null);
    }
}
