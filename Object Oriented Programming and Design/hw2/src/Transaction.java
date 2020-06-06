package homework2;

/**
 * This class implements a transaction in a graph of recycling channels.
 * A transaction has a product which is immutable and an amount of it which is mutable.
 */

public class Transaction {
    private int amount;
    private final String product;
   
    
	/**
	 * @requires amount > 0, the product must be a single word, without special characters/number and also in lowercase.
	 * @modifies this
	 * @effects Constructs a new transaction
	 */
    public Transaction(String product, int amount) {
        this.product = product;
        this.amount = amount;
        assert amount > 0;
    }
    
	/**
	 * @effects Returns the amount of the transaction
	 */
    public int getAmount() {
        return amount;
    }
    
	/**
	 * @effects Returns the product of the transaction
	 */
    public String getProduct() {
        return product;
    }
    
    @Override
    public String toString() {
        return "Transaction: " + this.hashCode() + " Product: " + product + " Amount: " + amount;
    }
    
    
}
