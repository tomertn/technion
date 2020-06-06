package homework2;

import static org.junit.Assert.*;
import org.junit.Test;


/**
 * BipartiteGraphTest contains JUnit block-box unit tests for BipartiteGraph.
 */
public class BipartiteGraphTest {

	@Test
    public void testExample() {
        BipartiteGraphTestDriver driver = new BipartiteGraphTestDriver();
        
        //create a graph
        driver.createGraph("graph1");
        
        //add a pair of nodes
        driver.addBlackNode("graph1", "n1");
        driver.addWhiteNode("graph1", "n2");
        
        //add an edge
        driver.addEdge("graph1", "n1", "n2", "edge");
        
        //check neighbors
        assertEquals("wrong black nodes", "n1", driver.listBlackNodes("graph1"));
        assertEquals("wrong white nodes", "n2", driver.listWhiteNodes("graph1"));
        assertEquals("wrong children", "n2", driver.listChildren ("graph1", "n1"));
        assertEquals("wrong children", "", driver.listChildren ("graph1", "n2"));
        assertEquals("wrong parents", "", driver.listParents ("graph1", "n1"));
        assertEquals("wrong parents", "n1", driver.listParents ("graph1", "n2"));
	}
	
	@Test
    public void testExample2() {
        BipartiteGraphTestDriver driver = new BipartiteGraphTestDriver();

        //  TODO: Add black-box tests

        
        //create a graph
        driver.createGraph("graph2");
        
        //add a pair of nodes
        driver.addBlackNode("graph2", "n1");
        driver.addWhiteNode("graph2", "n2");
        driver.addWhiteNode("graph2", "n3");
        driver.addWhiteNode("graph2", "n4");
        driver.addBlackNode("graph2", "n5");
        driver.addBlackNode("graph2", "n1");
        
        //add an edge
        driver.addEdge("graph2", "n1", "n2", "edge");
        driver.addEdge("graph2", "n1", "n2", "edge");
        driver.addEdge("graph2", "n1", "n3", "edge");
        driver.addEdge("graph2", "n2", "n5", "edge");
        driver.addEdge("graph2", "n1", "n3", "edge2");
        driver.addEdge("graph2", "n5", "n3", "edge2");
        driver.addEdge("graph2", "n2", "n3", "edge3");
        
        
        assertEquals("wrong black nodes", "n1 n5", driver.listBlackNodes("graph2"));
        assertEquals("wrong white nodes", "n2 n3 n4", driver.listWhiteNodes("graph2"));
        assertEquals("wrong children", "n2 n3", driver.listChildren ("graph2", "n1"));
        assertEquals("wrong children", "n5", driver.listChildren ("graph2", "n2"));
        assertEquals("wrong parents", "", driver.listParents ("graph2", "n1"));
        assertEquals("wrong parents", "n1", driver.listParents ("graph2", "n2"));
        assertEquals("wrong child in egde", "n2", driver.getChildByEdgeLabel("graph2","n1","edge"));
        assertEquals("wrong parents in egde", "n1", driver.getParentByEdgeLabel("graph2","n2","edge"));

    }
	
	@Test
    public void testExample3() {
		BipartiteGraph<Integer> g =new BipartiteGraph<Integer>();
		g.addBlackNode(1);
		g.addBlackNode(2);
		g.addBlackNode(2);// test 2 black node with same name
		g.addBlackNode(3);
		g.addWhiteNode(1);// test 2 black and white node with same name
		g.addWhiteNode(4);
		g.addWhiteNode(5);
		g.addWhiteNode(6);
		g.addWhiteNode(6); //test 2 white node with same name
		
		g.addEdge(10, 1, 4);
		g.addEdge(10, 2, 4); // check 2 same edge to same child
		g.addEdge(11, 1, 4); // check 2 diff edge to same child from same parent
		g.addEdge(12, 1, 2); // check edge between 2 black node 
		g.addEdge(13, 5, 3);
		g.addEdge(10, 4, 3);// test same edge name from 2 side of 4;
		g.addEdge(100, 4, 4); // test node to himself
		
		assertEquals("wrong black nodes", "[1, 2, 3]", g.getBlackNodes().toString());
        assertEquals("wrong white nodes", "[4, 5, 6]", g.getWhiteNodes().toString());
        assertEquals("wrong edge", "10", g.getEdgeByParentAndChild(1, 4).toString());
        assertEquals("wrong edge", "4", g.getParentByEdgeAndChild(10, 3).toString());
        assertEquals("wrong edge", "3", g.getChildByEdgeAndParent(10, 4).toString());
	}
    
    
    
  
}
