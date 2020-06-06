package homework2;

import java.util.LinkedList;
import java.util.*;

public class Participant extends Filter<String, Transaction>{
	/**
     * Abstraction function:
     * Participant represents a simulatable object of type filter.
     * this.needProd represents the needed product.
     * this.amount represents the needed amount ofproduct.
     * Participant "process" Transaction.
     *
     * Representation invariant:
     * amount >= 0;
     *
     */

	private String needProd;
	private int amountBegin;
	private int needAmount;

	/**
     * @requires label != null, needProd !=null;
     * @effects creates new Participant with the label and products needs.
     * @throws NullPointer 
     */
	public Participant(String label, String needProd, int amount ) throws NullPointer {
		super(label);
		this.needProd = needProd;	
		this.needAmount=amount;
		this.amountBegin=amount;
		checkRep();
	}
	 
	 /**
     * @requires rec != null
     * @modifies this and rec. 
     * @effects store data stored in Participant to rec channel.
     */
    @Override
    public boolean giveProducts(SimModule<String, Transaction> rec) throws NullPointer{
        checkRep();
        Queue<Transaction> tempQ =  new LinkedList<>();
        Transaction tempTran =this.objects.poll();
        while (tempTran != null)
        {
             	if (rec.addProducts(tempTran)) {
             		break;
             	}
             	tempQ.add(tempTran);
             	tempTran =this.objects.poll();
        }
        tempTran =this.objects.poll();
        while (tempTran != null)
        {
             	tempQ.add(tempTran);
             	tempTran =this.objects.poll();
        }
        this.objects = tempQ;
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
        if (trac.getProduct().equals(this.needProd)) {
        	this.needAmount -= trac.getAmount();
        	if (this.needAmount <=0) { 
        		if (this.needAmount !=0) {
        			this.objects.add(new Transaction(trac.getProduct(),this.needAmount*(-1)));
        		}
        		this.needAmount =0;
        	}
		} else {
			this.objects.add(trac);
        }
        checkRep();
        return true;
    }

    /**
     * @return this.amount
     */
    public double getAmount() {
        checkRep();
        return this.amountBegin-this.needAmount;
    }
    
    /**
     * @return the total amount of products in
     */
    public double getRecycleAmount() {
        checkRep();
        Queue<Transaction> tempQ =  new LinkedList<>();
        Transaction tempTran =this.objects.poll();
        double sum =0;
        while (tempTran != null)
        {
             	sum += tempTran.getAmount();
             	tempQ.add(tempTran);
             	tempTran =this.objects.poll();

        }
        return sum;
    }
    
    private void checkRep()
    {
    	assert needAmount >= 0;
    	assert amountBegin >= 0;
    }

}