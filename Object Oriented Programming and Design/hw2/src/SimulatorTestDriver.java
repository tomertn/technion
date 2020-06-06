package homework2;

import java.util.HashMap;
import java.util.Map;

/**
 * This class implements a testing driver for Simulator. The driver manages
 * Simulators for recycling channels
 */
public class SimulatorTestDriver {

	private Map<String, Simulator<String, Transaction>> simulators;

	/**
	 * @modifies this
	 * @effects Constructs a new test driver.
	 */
	public SimulatorTestDriver() {
		simulators = new HashMap<>();
	}

	/**
	 * @requires simName != null
	 * @modifies this
	 * @effects Creates a new simulator named simName. The simulator's graph is
	 *          initially empty.
	 */
	public void createSimulator(String simName) {
		simulators.put(simName, new Simulator<String, Transaction>());
		}

	/**
	 * @throws NullPointer 
	 * @requires createSimulator(simName) 
     *           && channelName != null && channelName has
	 *           not been used in a previous addChannel()  or
	 *           addParticipant() call on this object
	 *           limit > 0
	 * @modifies simulator named simName
	 * @effects Creates a new Channel named by the String channelName, with a limit, and add it to
	 *          the simulator named simName.
	 */
	public void addChannel(String simName, String channelName, int limit) throws NullPointer    {
		simulators.get(simName).addPipe(channelName, new Channel(channelName, limit));
		}

	/**
	 * @throws NullPointer 
	 * @requires createSimulator(simName) && participantName != null 
	 *           && participantName has not been used in a previous addParticipant(), addChannel()
	 *           call on this object
	 *			 amount > 0
	 *			 product must be a single word, without special characters/number and also in lowercase
	 * @modifies simulator named simName
	 * @effects Creates a new Participant named by the String participantName and add
	 *          it to the simulator named simName.
	 */
	public void addParticipant(String simName, String participantName, String product, int amount) throws NullPointer  {
		simulators.get(simName).add_filter(participantName, new Participant(participantName, product, amount));	}

	/**
	 * @throws NullPointer 
	 * @requires createSimulator(simName) && ((addPipe(parentName) &&
	 *           addFilter(childName)) || (addFilter(parentName) &&
	 *           addPipe(childName))) && edgeLabel != null && node named
	 *           parentName has no other outgoing edge labeled edgeLabel 
	 *           && node named childName has no other incoming edge labeled edgeLabel
	 * @modifies simulator named simName
	 * @effects Adds an edge from the node named parentName to the node named
	 *          childName in the simulator named simName. The new edge's label
	 *          is the String edgeLabel.
	 */
	public void addEdge(String simName, String parentName, String childName, String edgeLabel) throws NullPointer {
		simulators.get(simName).addEdge(parentName, childName, edgeLabel);
		}

	/**
	 * @throws NullPointer 
	 * @requires createSimulator(simName) && addChannel(channelName)
	 *           A transaction Transaction != null
	 * @modifies channel named channelName
	 * @effects pushes the Transaction into the channel named channelName in the
	 *          simulator named simName.
	 */
	public void sendTransaction(String simName, String channelName, Transaction tx) throws NullPointer {
		simulators.get(simName).giveTransaction(channelName, tx);
    }
	
	
	/**
	 * @requires addChannel(channelName)
	 * @return a space-separated list of the Transaction values currently in the
	 *         channel named channelName in the simulator named simName.
	 * @throws NullPointer 
	 */
	public String listContents(String simName, String channelName) throws NullPointer {
		return simulators.get(simName).getContent(channelName);
		}


	/**
	 * @requires addParticipant(participantName)
	 * @return The sum of all Transaction amount of stored products that one has in his storage buffer.
	 * @throws NullPointer 
	 */
	public double getParticipantStorageAmount(String simName, String participantName) throws NullPointer {
		if (simulators.get(simName).getSimModule(participantName) instanceof Participant) {
			return ((Participant) (simulators.get(simName).getSimModule(participantName))).getAmount();
			}
		throw new NullPointer("no participant exist");
	}


	/**
	 * @requires addParticipant(participantName)
	 * @return The sum of all Transaction amount of waiting to be recycled products that one has.
	 * @throws NullPointer 
	 */
	public double getParticipantToRecycleAmount(String simName, String participantName) throws NullPointer {
		if (simulators.get(simName).getSimModule(participantName) instanceof Participant) {
			return ((Participant) (simulators.get(simName).getSimModule(participantName))).getRecycleAmount();
			}
		throw new NullPointer("no participant exist");
	}


	
	/**
	 * @throws NullPointer 
	 * @requires createSimulator(simName)
	 * @modifies simulator named simName
	 * @effects runs simulator named simName for a single time slice.
	 */
	public void simulate(String simName) throws NullPointer {
		simulators.get(simName).simulate();
		}

	/**
	 * Prints the all edges.
	 *
	 * @requires simName the sim name
	 * @effects Prints the all edges.
	 */
	public void printAllEdges(String simName) {
		System.out.println(simulators.get(simName).getAllEdges());
		}

}
