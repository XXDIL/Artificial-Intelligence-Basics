import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.lang.Comparable;

import javafx.animation.SequentialTransition;
import javafx.animation.TranslateTransition;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;
import javafx.util.Duration;

public class Main extends Application 
{
	private static Scanner scan = new Scanner(System.in);
	private static List<Pair> path;
	private static Agent A1;

	private static final int W_WIDTH = 800;	
	private static final int W_HEIGHT = 600;
	private static final Random rand = new Random();
	
	public static void main(String[] args) 
	{
		// creating an agent with name "Agent1" and initial coords as (0, 0)
		initializeEnvironment(); // getting input from user and setting up environment
		launch(args);

		scan.close();
	}


	@Override
	public void start(Stage primaryStage) throws Exception 
	{
		Pane root = new Pane();
		Label intro = new Label("Click anywhere to set the destination point");	
		intro.setStyle("-fx-font-size: 25px;"
				+ "-fx-font-smoothing-type: gray;");
		intro.relocate(W_WIDTH/2-235, W_HEIGHT/2-50);		
		root.getChildren().add(intro);
		Scene scene = new Scene(root, W_WIDTH, W_HEIGHT);
		scene.setOnMouseClicked(new EventHandler<MouseEvent>() 
		{

			@Override
			public void handle(MouseEvent event) 
			{
				scene.setOnMouseClicked(null);
				intro.setVisible(false);
				
				// Setting destination positions and the destination circle
				Environment.setDestination(new Pair((int) event.getSceneX()/20, (int) event.getSceneY()/20)); // Setting destination based on mouse click
				Circle destination = new Circle(Environment.getDestination().x * 20, Environment.getDestination().y * 20, 10, Color.RED);

				// setting up agents
				int x = rand.nextInt(W_WIDTH)/20, y = rand.nextInt(W_HEIGHT)/20; // initial (random) coordinates for our agent
				A1 = new Agent("Agent1", x, y);
				// TODO, add multiple agents
				
				A1.travel();
				path = A1.steps;

				
				Circle agent = new Circle(x * 20, y * 20, 10, Color.DARKOLIVEGREEN);
				SequentialTransition st = setMovementTransition(path, agent);			
				st.play();
								
				root.getChildren().addAll(agent, destination);

			}

		});

		primaryStage.setScene(scene);
		primaryStage.setResizable(false);

		primaryStage.show();
	}

	
	private SequentialTransition setMovementTransition(List<Pair> path, Node agentShape) 
	{
		SequentialTransition st = new SequentialTransition(agentShape);				
		
		for (int i = 1; i < path.size(); i++) 
		{
			TranslateTransition tt = new TranslateTransition(Duration.millis(250), agentShape);
			tt.setByX((path.get(i).x) * 20);
			tt.setByY((path.get(i).y) * 20);
			System.out.println("Transition " + i);
			System.out.println("byX - " + (path.get(i).x) * 20 + " byY - " + (path.get(i).y) * 20);
			st.getChildren().add(tt);
		}		
		return st;
	}

	private static void initializeEnvironment() 
	{
		int m = W_WIDTH/20;
		int n = W_HEIGHT/20;

		Environment.setMN(m, n);
	}

}

class Pair implements Comparable<Pair>
{
	int x;
	int y;

	protected Pair(int X, int Y) 
	{
		x = X;
		y = Y;
	}

	@Override
	public boolean equals(Object obj) 
	{
		return (((Pair) obj).x == this.x) && (((Pair) obj).y == this.y);
	}

	@Override
	public String toString() 
	{
		return "(" + x + ", " + y + ")";
	}

	@Override
	public int compareTo(Pair P)
	{
		double dist = Math.hypot(Environment.getDestination().x - x, Environment.getDestination().y - y);
		double distP = Math.hypot(Environment.getDestination().x - P.x, Environment.getDestination().y - P.y);

		return(dist > distP ? 1 : (dist == distP ? 0 : -1));
	}
}