package homework2;

import java.util.*;


public class Simulator<E, T> {
    /**
     * Abstraction function:
     * Simulator represents the working space of the pipes and filters.
     * this.graph represents the pipes and filters by graph.Blacks <- pipes and graph.Whites <- filters. 
     *
     * Representation invariant:
     * graph != null, modules != null
     *
     *
     * @param <E> type of labels
     * @param <T> type of data
     */

    private BipartiteGraph<E> graph;
    private HashMap<E, SimModule<E, T>> modules;

    /**
     * @modifies this
     * @effects create new simulator.
     */
    public Simulator(){
    	graph = new BipartiteGraph<>();
        modules = new HashMap<>();
        checkRep();
    }
    
    /**
     * @throws NullPointer 
     * @requires all inputs are not null 
     * @modifies this.graph
     */
    public void addEdge(E parent_label, E child_label, E edge_label) throws NullPointer{
        checkRep();
        if(parent_label==null) {
        	throw new NullPointer("parent is null");
        }
        if(child_label==null) {
        	throw new NullPointer("child is null");
        }
        if(edge_label==null) {
        	throw new NullPointer("edge is null");
        }
        graph.addEdge(edge_label,parent_label,child_label);
        checkRep();
    }
    
    /**
     * @requires label does not exist in all pipes of the simulator
     * 			all parameters are not null
     * @modifies this
     * @effects add pipe to the simulator
     * @throws LabelIsNull if label = null or pipe==null
     */
    public void addPipe(E label, Pipe<E,T> pipe) throws  NullPointer {
        checkRep();
        if(label==null) {
        	throw new NullPointer("label is null");
        }
        if(pipe==null) {
        	throw new NullPointer("pipe is null");
        }
        graph.addBlackNode(label);
        modules.put(label,pipe);
        pipe.setMap(modules);
        checkRep();
    }

    /**
     * @requires label does not exist in all filters of the simulator
     * 				all params are not null
     * @modifies this.
     * @effects add filter to the simulator
     * @throws LabelIsNull if label = null or filter==null
     */
    public void add_filter(E label, Filter<E,T> filter) throws  NullPointer {
        checkRep();
        if(label==null) {
        	throw new NullPointer("label is null");
        }
        if(filter==null) {
        	throw new NullPointer("pipe is null");
        }
        graph.addWhiteNode(label);
        modules.put(label,filter);
        filter.setMap(modules);
        checkRep();
    }


    /**
     * @throws NullPointer 
     * @modifies modules. 
     * @effects make a simulation step.
     */
    public void simulate() throws NullPointer {
        checkRep();
        
        Set<E> objects = graph.getWhiteNodes();
        Set<E> Channels = graph.getBlackNodes();
        
        for (E entry : objects)
            modules.get(entry).simulate(graph);
        for (E entry : Channels)
            modules.get(entry).simulate(graph);

        checkRep();
    }


    /**
     * @requires label exist in pipes
     * @modifies this.
     * @effects store the trans in a given pipe
     */
    public void giveTransaction(E label, T trans) throws NullPointer{
        checkRep();
        if(label==null) {
        	throw new NullPointer("label is null");
        }
        if(trans==null) {
        	throw new NullPointer("pipe is null");
        }
        if (!modules.containsKey(label))
        {
            System.out.println("node does not exist");
            return;
        }
        modules.get(label).addProducts(trans);
        checkRep();
    }

    /**
     * @requires label exist in pipes
     * @return pipe elements in a String.
     * @throws NullPointer 
     */
    public String getContent(E label) throws NullPointer {
        checkRep();
        if(label==null) {
        	throw new NullPointer("label is null");
        }
        if (!modules.containsKey(label))
        {
        	System.out.println("node does not exist");
            return null;
        }
        checkRep();
        return modules.get(label).getContent();
    }
    
    /**
     * @return a string with the name of all the edges in the graph
     */
    public String getAllEdges() {
        checkRep();
        return graph.getAllEdges();
    }

    /**
     * @requires there is a filter with the given label, label is not null
     * @return a copy of the filter with the given label .
     * @throws NullPointer 
     */
    public SimModule<E, T> getSimModule(E label) throws NullPointer {
        checkRep();
        if(label==null) {
        	throw new NullPointer("label is null");
        }
        if (!modules.containsKey(label))
        {
        	System.out.println("Node does not exist");
            return null;
        }
        checkRep();
        return modules.get(label);
    }

    private void checkRep()
    {
        assert graph != null;
        assert modules != null;
    }


}
