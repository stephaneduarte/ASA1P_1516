#include <iostream>
#include <stdio.h>
#include <list>
#include <vector>

#define NIL -1

using namespace std;

//Undirected Graph
class Graph{

		int NVertices;

		list<int> *linked; //Dinamic array of adjacency lists

		void SearchFundamentals(int u, bool visited[], int visittime[], int lowtime[], int parent[], bool fpoint[]){
			// u -> The vertex that will be visited

			static int time = 0;
			//static variable simplifies its use

			int children = 0;
			//number of children

			visited[u] = true;
			//changes the boolean in the visited array

			visittime[u] = lowtime[u] = ++time;
			//sets the visit time and the lowest time

			list<int>::iterator i;

			for (i = linked[u].begin() ; i != linked[u].end() ; ++i){
				//goes to every children of u

				int v = *i;

				//if it has not been visited
				if (!visited[v]){
					children++;
					parent[v] = u; //sets the parent
					SearchFundamentals(v, visited, visittime, lowtime, parent, fpoint); //make the same for the child

					lowtime[u] = min(lowtime[u], lowtime[v]);
					//the lowest time is mininum between itself and its father

					//CASE 1: If it has no parents (is the roof) and has more than 1 children, it is a fundamental point.
					if (parent[u] == NIL && children > 1){
						fpoint[u] = true;
					}

					//CASE 2: If it has parents but the lowest time of his child is >= than itself, it is a fundamental point.
					if (parent[u] != NIL && lowtime[v] >= visittime[u]){
						fpoint[u] = true;
					}
				}

				//if it has already been visited, it just actualizes the lowest time needed
				else if (v != parent[u]){
					lowtime[u] = min(lowtime[u], visittime[v]);
				}
			}
		};
		

	public:

		Graph(int NVertices){ //Constructor
			this->NVertices = NVertices;
			linked = new list<int>[NVertices+1];
			//We will ignore the 0 position because we will associate the vertex from the input to the
			//position in the array. The input goes from 1 to NVertices and not from 0 to NVertices-1.
		} 

		void addEdge(int v, int w){
			//V linked with W means that W is linked with V too.
			linked[w].push_back(v);
			linked[v].push_back(w);
		};

		void printFundamentals(){
			// visited is an array of booleans. TRUE in case the point was already visited, FALSE in case it wasn't.
			// visittime is an array that stores the discovery times of visited vertices
			// lowtime is an array that stores the lowest discovery time needed of visited vertices
			// parent is an array that stores the parent vertices
			// fpoint is an array of booleans. TRUE in case the point is a Fundamental Point, FALSE in case it isn't.
			bool *visited = new bool[NVertices+1];
			int *visittime = new int[NVertices+1];
			int *lowtime = new int[NVertices+1];
			int *parent = new int[NVertices+1];
			bool *fpoint = new bool[NVertices+1];

			int count = 0; //Counter for the number of Fundamental Points
			int min = -1; //Fundamental Points' minimum value (if there's no fundamental points, must print -1)
			int max = -1; //Fundamental Points' maximum value (if there's no fundamental points, must print -1)

			//The following for function will iniciate the arrays' values.
			for (int i = 1 ; i < NVertices + 1; i++){
				parent[i] = NIL;
				visited[i] = false;
				fpoint[i] = false;
			}

			//The following for function will visite every Point of the graph.
			for (int i = 1 ; i < NVertices + 1; i++){
				if (visited[i] == false){
					SearchFundamentals(i, visited, visittime, lowtime, parent, fpoint);
				}
			}

			//The following for function will update the min and max values and the counter.
			for (int i = 1 ; i < NVertices + 1; i ++){
				if (fpoint[i] == true){
					if (min == -1){
						min = i;
					}
					if (i < min){
						min = i;
					}
					if (i > max){
						max = i;
					}
					count++;
				}
			}

			//Prints the standart output:
			//count
			//min max
			cout << count << "\n" << min << " " << max << "\n";
		};
};

int main(){
	int numVertices;
	int numEdges;

	//Save the values from the first line of the input (numVertices nEdges)
	cin >> numVertices;
	cin >> numEdges;

	//Creates the graph
	Graph g(numVertices);

	//Read the edges from the input
	for (int i = 0 ; i < numEdges ; i++){

		int v1;
		cin >> v1; //First Component
		int v2;
		cin >> v2; //Second Component

		g.addEdge(v1, v2); //Add the edge on the graph
	}

	g.printFundamentals(); //Print the fundamental components
}