package homework2;

/**
 * The Simulatable interface is implemented by each of the pipes and filters in
 * a pipe-and-filter simulation.
 */
public interface Simulatable<T> {

	/**
	 * @modifies this, graph
	 * @effects Simulates this pipe or filter in a system modeled by graph
	 */
	public void simulate(BipartiteGraph<T> graph);
}
