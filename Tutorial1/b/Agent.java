import java.util.*;

public class Agent 
{
	protected String name;

	public ArrayList<Pair> steps = new ArrayList<>();
	
	public Agent(String name, int intitialX, int initialY) 
	{
		this.name = name;

		Environment.initializeAgentLocation(this, new Pair(intitialX, initialY));
		steps.add(new Pair(intitialX, initialY));
	}

	public double sensor() 
	{
		return Environment.distance(this);
	}

	public void moveDown() 
	{
		if (Environment.boundCheck(this, 0, 1)) 
		{
			steps.add(new Pair(0, 1));
			Environment.moveY(this, 1);
		}
	}

	public void moveUp() 
	{
		if (Environment.boundCheck(this, 0, -1)) 
		{
			steps.add(new Pair(0, -1));			
			Environment.moveY(this, -1);
		}
	}

	public void moveLeft() {
		if (Environment.boundCheck(this, -1, 0)) 
		{
			steps.add(new Pair(-1, 0));
			Environment.moveX(this, -1);
		}
	}

	public void moveRight() 
	{
		if (Environment.boundCheck(this, 1, 0)) 
		{
			steps.add(new Pair(1, 0));
			Environment.moveX(this, 1);
		}
	}

	public void travel() 
	{
		Random rand = new Random();
		while (!Environment.check(this)) 
		{
			int r = rand.nextInt(4);
			double initial = this.sensor();

			moveWithNumber(r); // completely random movement
						
			if (this.sensor() >= initial)
			{ // made a mistake
				moveWithNumber(3-r); // undoing the mistake
			} 
			else continue;
			
			// at this point, we know r corresponds to a bad direction. so we generate another random integer that can't be equal to r
			int u;
			do 
			{
				u = rand.nextInt(4);
			} while(u == r);
			
			moveWithNumber(u);
			
			if (this.sensor() >= initial){ // if still a mistake
				moveWithNumber(3 - u);
			} 
			else continue;

			// u & r are both bad
			int v;
			do 
			{
				v = rand.nextInt(4);
			} while(v == r || v == u);
			
			moveWithNumber(v);
			
			if(this.sensor() >= initial) 
			{
				 // absolutely worst case scenario, wrong for the 3rd time
				moveWithNumber(3 - v);
				// let w be the number corresponding to the correct move, since its the worst case, r, u and v are all bad and unique
				// we know r + u + v + w must be 6, so w has to be 6 -r -u -v
				moveWithNumber(6-r-u-v);
			}
			
		}
	}
	
	private void moveWithNumber(int rng) 
	{
		switch (rng) 
		{
			case 0:
				moveRight();
				break;
			case 1:
				moveUp();
				break;
			case 2:
				moveDown();
				break;
			case 3:
				moveLeft();	
		}
	}
}