import java.util.*;

public class Environment {
	private static Pair destination;
	
	private static int m, n;
	
	private static HashMap<Agent, Pair> location = new HashMap<>();

	public static ArrayList<ArrayList<Pair>> pathsOfAgents = new ArrayList<>(); // stores path taken by each agent
	
	
	public static void initializeAgentLocation (Agent a, Pair initialCoordinates) {
		location.put(a, initialCoordinates);
	}
	
	protected static Pair getDestination() {
		return destination;
	}
	
	public static int getX(Agent agent) {
		return location.get(agent).x;
	}

	public static int getY(Agent agent) {
		return location.get(agent).y;
	}

	public static Pair getLocation(Agent a) {
		return location.get(a);
	}
	
	public static void moveX(Agent agent, int by) {
		Pair temp = new Pair(Environment.location.get(agent).x + by, Environment.location.get(agent).y);
		location.put(agent, temp);
	}

	public static void moveY(Agent agent, int by) {
		Pair temp = new Pair(Environment.location.get(agent).x, Environment.location.get(agent).y + by);
		location.put(agent, temp);
	}

	public static void setMN(int M, int N) {
		m = M;
		n = N;
	}

	public static double distance(Agent agent) {
		Pair loc = location.get(agent);
		double dist = Math.hypot((destination.x - loc.x), (destination.y - loc.y));

		return dist;
	}

	public static boolean check(Agent agent) { // check if reached destination
		Pair pos = location.get(agent);
		return destination.equals(pos);
	}

	public static void setDestination(Pair D) {
		destination = D;
	}

	public static boolean XYCheck(int currx, int curry) {
		if (!(currx >= 0 && currx <= m) || !(curry >= 0 && curry <= n)) {
			return false;
		}
		return true;
	}

	public static boolean boundCheck(Agent agent, int x, int y) {
		return XYCheck(location.get(agent).x + x, location.get(agent).y + y);
	}
	
}

