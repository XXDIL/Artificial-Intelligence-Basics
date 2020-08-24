import java.util.*;

import javafx.scene.shape.Path;

public class Agent {
	protected String name;

	public ArrayList<Pair> steps = new ArrayList<>();

	public Agent(String name, int intitialX, int initialY) {
		this.name = name;

		Environment.initializeAgentLocation(this, new Pair(intitialX, initialY));
	}

	public Pair sensor() {
		return Environment.getLocation(this);
	}

	public void moveDown() {
		if (Environment.boundCheck(this, 0, 1)) {
			steps.add(new Pair(0, 1));
			Environment.moveY(this, 1);
		}
	}

	public void moveUp() {
		if (Environment.boundCheck(this, 0, -1)) {
			steps.add(new Pair(0, -1));
			Environment.moveY(this, -1);
		}
	}

	public void moveLeft() {
		if (Environment.boundCheck(this, -1, 0)) {
			steps.add(new Pair(-1, 0));
			Environment.moveX(this, -1);
		}
	}

	public void moveRight() {
		if (Environment.boundCheck(this, 1, 0)) {
			steps.add(new Pair(1, 0));
			Environment.moveX(this, 1);
		}
	}

	public ArrayList<Pair> positions = new ArrayList<>();

	public void travel() {
		while (!Environment.check(this)) {

			int X = Environment.getDestination().x - this.sensor().x;
			int Y = this.sensor().y - Environment.getDestination().y;

			if (Y == 0) // Numerator = 0
			{
				if (X > 0)
					this.moveRight();
				else
					this.moveLeft();
				positions.add(this.sensor());
				continue;
			}

			else if (X == 0) // Denominator = 0
			{
				if (Y > 0)
					this.moveUp();
				else
					this.moveDown();
				positions.add(this.sensor());
				continue;
			}

			double m = ((double) Y) / X;

			if (X > 0) // Quadrant 1 and 4
			{
				if (m >= -1 && m <= 1)
					this.moveRight();

				else if (m > 1)
					this.moveUp();

				else if (m < -1)
					this.moveDown();
				positions.add(this.sensor());
			}

			else // Quadrant 2 and 3
			{
				if (m >= -1 && m <= 1)
					this.moveLeft();

				else if (m > 1)
					this.moveDown();

				else if (m < -1)
					this.moveUp();
				positions.add(this.sensor());
			}

		}

	}

	private void moveWithNumber(int rng) {
		switch (rng) {
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