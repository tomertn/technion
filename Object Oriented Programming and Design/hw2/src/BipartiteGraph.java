package homework2;
import java.util.*;
import java.util.Map.Entry;
public class BipartiteGraph<L> {
	
	/**
	 * Abstraction function:
	 * represents a bipartite graph, with black nodes at this.Blacks
	 * and white nodes at this.Whites and parents connection in this.Parents.
	 * Edges between parent and child are at this.Blacks.values() and this.Blacks.values()
	 *  
	 * Representation invariant: 
	 * Vertices can be connected if and only if they are in different partitions (WHITE/BLACK).
	 * All vertices have different label.
	 * All edges that get inside a node have different label.
	 * All edges that get outside a node have different label.
	 * 
	 * @param <L> type of labels
	 */
	
	private Map<L,Map<L,L>> Blacks;
	private Map<L,Map<L,L>> Whites;
	private Map<L,Map<L,L>> Parents;
	
	/**
     * @requires 
     * @modifies this
     * @effects Create new object of this class.
     */
	
	public BipartiteGraph() {
		Blacks = new HashMap<>();
		Whites = new HashMap<>();
		Parents = new HashMap<>();
		checkRep();
	}
	
	/**
     * @requires node != null
     * @modifies this.Blacks
     * @effects Adds a black node represented by the L node to the
     * 			this.Blacks.
     */
	public void addBlackNode(L node) {
		checkRep();
		if(Blacks.containsKey(node) || Whites.containsKey(node)) {
			System.out.println("Node already exist!");
			checkRep();
			return;
		}
		// Taking care of duplicates 
		if(Parents.put(node , new HashMap<L,L>())!=null) {
			System.out.println("map.put() added a key that already exist");
		}
		if(Blacks.put(node , new HashMap<L,L>())!=null) {
			System.out.println("map.put() added a key that already exist");
		}
		checkRep();
	}
	
	/**
     * @requires node != null
     * @modifies this.Whites
     * @effects Adds a white node represented by the L node to the
     * 			this.Whites. 
     */
	public void addWhiteNode(L node) {
		checkRep();
		if(Blacks.containsKey(node) || Whites.containsKey(node)) {
			System.out.println("Node already exist!");
			checkRep();
			return;
		}
		// taking care of duplicates
		if(Parents.put(node , new HashMap<L,L>())!=null) {
			System.out.println("map.put() added a key that already exist");
		}
		if(Whites.put(node , new HashMap<L,L>())!=null) {
			System.out.println("map.put() added a key that already exist");
		}
		checkRep();
	}
	
	/**
     * @requires node != null
     * @modifies 
     * @effects return a String : "Black" if the node in this.Blacks, 
     * 			"White" if the node in this.Whites, 
     * 			null otherwise.
     * @return a String as detailed above.
     */
	private String getMapColor(L node) {
		checkRep();
		if(Blacks.containsKey(node)) {
			checkRep();
			return "Black";
		}
		if(Whites.containsKey(node)) {
			checkRep();
			return "White";
		}
		checkRep();
		return null;
	}
	
	/**
     * @requires edge_name != null && parent != null && child != null
     * @modifies this.Blacks , this.Whites (depend on parent color), this.Parents
     * @effects add edge between parent and a child in the suitable map (Blacks 
     * if parent is Black, White otherwise). Not doing anything if parent or child does not exist.
     * @return 
     */
	public void addEdge(L edge_name, L parent, L child) {
		checkRep();
		if(getMapColor(parent)==null || getMapColor(child)==null) {
			System.out.println("Node does not exist!");
			checkRep();
			return;
		}
		if(getMapColor(parent).equals(getMapColor(child))) {
			System.out.println("parent and child have the same color!");
			checkRep();
			return;
		}
		Map<L,Map<L,L>> parent_color_map = Blacks;
		if(getMapColor(parent).equals("White")) {
			parent_color_map = Whites;
		}
		
		if(parent_color_map.get(parent).containsKey(edge_name)) {
			System.out.println("Edge already connected to parent!");
			checkRep();
			return;
		}
		
		for (Entry<L, Map<L, L>> entry : parent_color_map.entrySet()) {
			if(entry.getValue().containsKey(edge_name) && entry.getValue().get(edge_name) == child) {
				System.out.println("Edge already connected to child!");
				checkRep();
				return;
			}
		}
		//taking care of duplicates
		if(Parents.get(child).put(edge_name, parent)!=null) {
			System.out.println("map.put() added a key that already exist");
		}
		if(parent_color_map.get(parent).put(edge_name,child)!=null) {
			System.out.println("map.put() added a key that already exist");
		}
		checkRep();
	}
	
	/**
     * @requires child != null
     * @modifies 
     * @effects 
     * @return Vector<L> of parents of a the given child's list.
     */
	public Vector<L> getParentsList(L child){
		checkRep();
		if(child == null) {
			System.out.println("Node is null");
			checkRep();
			return null;
		}
		if(!Parents.containsKey(child)) {
			System.out.println("Node does not exist");
			checkRep();
			return null;
		}
		checkRep();
		return new Vector<L>(Parents.get(child).values());
	}
	
	/**
     * @requires 
     * @modifies 
     * @effects 
     * @return Set<L> of the black nodes in the Graph.
     */
	public Set<L> getBlackNodes(){
		checkRep();
		return Blacks.keySet();
	}
	
	/**
     * @requires 
     * @modifies 
     * @effects 
     * @return Set<L> of the black nodes in the Graph.
     */
	public Set<L> getWhiteNodes(){
		checkRep();
		return Whites.keySet();
	}
	
	/**
     * @requires parent != null
     * @modifies 
     * @effects 
     * @return Vector<L> of children of a the given parent's list.
     */
	
	public Vector<L> getChildrenVector(L parent){
		checkRep();
		if(parent == null) {
			System.out.println("Node is null");
			checkRep();
			return null;
		}
		if(!Blacks.containsKey(parent) && !Whites.containsKey(parent)) {
			System.out.println("Node does not exist");
			checkRep();
			return null;
		}
		Map<L,Map<L,L>> parent_color_map = Blacks;
		if(getMapColor(parent).equals("White"))
			parent_color_map = Whites;
		checkRep();
		return new Vector<L>(parent_color_map.get(parent).values());
	}
	/**
     * @requires parent != null && edge_name != null
     * @modifies 
     * @effects 
     * @return L represents the child connected to given parent and edge.
     */
	public L getChildByEdgeAndParent(L edge_name,L parent) {
		checkRep();
		if(!Blacks.containsKey(parent) && !Whites.containsKey(parent)) {
			System.out.println("Node does not exist");
			checkRep();
			return null;
		}
		
		Map<L,Map<L,L>> parent_color_map = Blacks;
		if(getMapColor(parent).equals("White"))
			parent_color_map = Whites;
		
		checkRep();
		return parent_color_map.get(parent).get(edge_name);
	}
	
	/**
     * @requires parent != null && edge_name != null
     * @modifies 
     * @effects 
     * @return L represents the child connected to given parent and edge.
     */
	public L getParentByEdgeAndChild(L edge_name,L child) {
			checkRep();
			if(!Parents.containsKey(child)) {
				System.out.println("Node does not exist");
				checkRep();
				return null;
			}	
			checkRep();
			return Parents.get(child).get(edge_name);
		}
	
	/**
     * @requires parent != null && child != null
     * @modifies 
     * @effects 
     * @return L represents the edge connected to given parent and child.
     */
	public L getEdgeByParentAndChild(L parent,L child) {
		checkRep();
		if(!Blacks.containsKey(parent) && !Whites.containsKey(parent)) {
			System.out.println("Node does not exist");
			checkRep();
			return null;
		}	
		
		Map<L,Map<L,L>> parent_color_map = Blacks;
		if(getMapColor(parent).equals("White"))
			parent_color_map = Whites;
			
		Map<L,L> inner_map = parent_color_map.get(parent);
		for (Entry<L, L> entry : inner_map.entrySet()) {
			if(entry.getValue() == child) {
				checkRep();
				return entry.getKey();
			}
		}
		checkRep();
		return null;
	}
	
	
	/**
     * @requires 
     * @modifies 
     * @effects 
     * @return String with all edges' labels concat
     */
	public String getAllEdges() {
		checkRep();
		String string_list = "";
        for (Entry<L, Map<L, L>> entry : Blacks.entrySet()) {
        	for(Entry<L, L> entry_in : entry.getValue().entrySet())
        		string_list += entry_in.getKey();
    			string_list += " ";

        }
        for (Entry<L, Map<L, L>> entry : Whites.entrySet()) {
        	for(Entry<L, L> entry_in : entry.getValue().entrySet())
        		string_list += entry_in.getKey();
        		string_list += " ";
        }
        checkRep();
        return string_list;
	}
	
	private void checkRep() {
		for (Entry<L, Map<L, L>> entry : Blacks.entrySet()) {
			assert !Whites.containsKey(entry.getKey());
		}
		
		for (Entry<L, Map<L, L>> entry : Blacks.entrySet()) {
			for (Entry<L, L> entry1 : entry.getValue().entrySet()) {
				assert Whites.containsKey(entry1.getValue());
			}	
		}
		
		for (Entry<L, Map<L, L>> entry : Whites.entrySet()) {
			for (Entry<L, L> entry1 : entry.getValue().entrySet()) {
				assert Blacks.containsKey(entry1.getValue());
			}	
		}
		
		// Map already take care of edges with the same name outside a node,
		// thanks to addEdge method.
		// Map already take care of edges with the same name inside a node,
		// thanks to addEdge method and Parents Map.
		
	}

}
