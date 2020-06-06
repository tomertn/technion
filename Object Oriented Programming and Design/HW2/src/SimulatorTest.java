package homework2;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class SimulatorTest {
	@Test
    public void testExample() throws NullPointer {
        SimulatorTestDriver driver = new SimulatorTestDriver();
        
        //create a graph
        driver.createSimulator("graph1");
        
 
        
        //add a pair of nodes
        driver.addParticipant("graph1", "p1","gold",150);
        driver.addParticipant("graph1", "p2","silver",150);
        driver.addChannel("graph1", "c1", 400);
        driver.addChannel("graph1", "c2", 400);

        //add an edge
        driver.addEdge("graph1", "p1", "c1", "edge1");
        driver.addEdge("graph1", "c1", "p2", "edge2");
        driver.addEdge("graph1", "p2", "c2", "edge3");
        driver.addEdge("graph1", "c2", "p1", "edge4");
        // check same color connect error
        driver.addEdge("graph1", "p2", "p1", "edge4");

        
        driver.sendTransaction("graph1", "c1", new Transaction("silver", 90));
        driver.sendTransaction("graph1", "c1", new Transaction("gold", 70));

        // //check simple simulate channel1 to p1
        driver.simulate("graph1");
        driver.simulate("graph1");

        assertEquals("check simple simulate p to p", "90.0", Double.toString(driver.getParticipantStorageAmount("graph1", "p2")));
        driver.sendTransaction("graph1", "c1", new Transaction("silver", 90));
        driver.simulate("graph1");
        driver.simulate("graph1");

        // //check simple simulate channel to p, no negative
        assertEquals("check simple simulate channel to p, no negative", "150.0", Double.toString(driver.getParticipantStorageAmount("graph1", "p2")));
        // //check simple simulate p to p
        assertEquals("check simple simulate p to p","70.0", Double.toString(driver.getParticipantStorageAmount("graph1", "p1")));

        // //check channel overflow
        driver.addParticipant("graph1", "p3","milk",120);
        driver.addChannel("graph1", "c3", 40);
        driver.addEdge("graph1", "c3", "p3", "edge5");
        driver.sendTransaction("graph1", "c3", new Transaction("milk", 60));
        driver.simulate("graph1");
        assertEquals("check channel overflow", "40.0", Double.toString(driver.getParticipantStorageAmount("graph1", "p3")));
        
        // //check channel blocked
        driver.addParticipant("graph1", "p4","milk",120);
        driver.addParticipant("graph1", "p5","milk",120);
        driver.addParticipant("graph1", "p6","banana",200);
        driver.addChannel("graph1", "c4", 100);
        driver.addChannel("graph1", "c5", 100);
        driver.addChannel("graph1", "c6", 100);
        driver.addEdge("graph1", "p4", "c4", "edge6");
        driver.addEdge("graph1", "p5", "c4", "edge7");
        driver.addEdge("graph1", "c4", "p6", "edge8");
        driver.addEdge("graph1", "c5", "p4", "edge9");
        driver.addEdge("graph1", "c6", "p5", "edge10");
        driver.sendTransaction("graph1", "c5", new Transaction("banana", 100));
        driver.sendTransaction("graph1", "c6", new Transaction("banana", 100));
        driver.simulate("graph1");
        driver.simulate("graph1");
        assertEquals("check channel blocked", "100.0", Double.toString(driver.getParticipantStorageAmount("graph1", "p6")));
        driver.simulate("graph1");
        assertEquals("check channel blocked", "200.0", Double.toString(driver.getParticipantStorageAmount("graph1", "p6")));

     // //check recycl 
        driver.addParticipant("graph1", "p7","milk",120);
        driver.addParticipant("graph1", "p8","milk",120);
        driver.addParticipant("graph1", "p9","tomer",70);
        driver.addParticipant("graph1", "p10","tomer",200);
        driver.addChannel("graph1", "c10", 100);

        driver.addChannel("graph1", "c7", 100);
        driver.addChannel("graph1", "c8", 100);
        driver.addChannel("graph1", "c9", 100);
        driver.addEdge("graph1", "p7", "c7", "edge13");
        driver.addEdge("graph1", "p8", "c7", "edge14");
        driver.addEdge("graph1", "c7", "p9", "edge15");
        driver.addEdge("graph1", "c8", "p7", "edge16");
        driver.addEdge("graph1", "c9", "p8", "edge17");
        driver.addEdge("graph1", "p9", "c10", "edge19");
        driver.addEdge("graph1", "c10", "p10", "edge20");

        driver.sendTransaction("graph1", "c8", new Transaction("tomer", 100));
        driver.sendTransaction("graph1", "c9", new Transaction("shalev", 100));
        driver.simulate("graph1");
        driver.simulate("graph1");
        driver.simulate("graph1");
        assertEquals("check channel blocked", "100.0", Double.toString(driver.getParticipantToRecycleAmount("graph1", "p9")));
        driver.printAllEdges("graph1");
        assertEquals("check channel blocked", "30.0", Double.toString(driver.getParticipantStorageAmount("graph1", "p10")));


	}
}
