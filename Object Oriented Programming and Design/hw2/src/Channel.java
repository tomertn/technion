
package homework2;


public class Channel extends Pipe<String, Transaction> {
    /**
     * Abstraction function:
     * Channel represents a simulatable object of type pipe.
     * this.capacity represents the pipe capacity of objects.
     * Channel transfer objects to Participant.
     *
     * Representation invariant:
     * this.capacity > 0
     * this.getCapacity() >= capacity;
     *
     *
     */

	private int capacity;
	/**
     * @requires label != null, capacity > 0
     * @modifies this
     * @effects creates new Channel with label and capacity. 
     * @throws NullPointer 
     */
    public Channel(String label, int capacity_) throws NullPointer
    {
        super(label, capacity_, true);
        this.capacity =0;
        checkRep();
    }
    
    /**
     * @requires rec != null
     * @modifies this and rec. 
     * @effects store data stored in channel to rec.
     */
    @Override
    public boolean giveProducts(SimModule<String, Transaction> rec) throws NullPointer{
        checkRep();
        if (!this.Queue.isEmpty())
        {
             	rec.addProducts(this.Queue.element());
                this.capacity -= ((Transaction)Queue.element()).getAmount();
                Queue.remove();
        }
        checkRep();
        return true;
    }
    
    /**
     * @throws NullPointer 
     * @requires trec != null
     * @modifies this 
     * @effects store trec in this.
     */
    public boolean addProducts(Transaction trac) throws NullPointer{
        checkRep();
        if (this.capacity >= this.getCapacity())
        	return false;
        if (trac.getAmount() + this.capacity > this.getCapacity()) {
        	Transaction newTrac = new Transaction(trac.getProduct(), (int)(this.getCapacity() -this.capacity) );
        	this.Queue.add(newTrac);
        	this.capacity +=  newTrac.getAmount();
        }
        else 
        {
        	this.Queue.add(trac);
        	this.capacity +=  trac.getAmount();
        }
        checkRep();
        return true;
    }

    
    private void checkRep()
    {
    	assert capacity >= 0;
        assert this.getCapacity() >= capacity;
    }

}
