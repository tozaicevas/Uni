/* Graph implementation with adjacency matrix and DFS traversal
Made for Algorithms and Data Structures course (Spring 2018)
Program solves problem - do you have to take course A before taking course B?
Input format:
1st line is ignored
Course_name: [course names, that have to be taken beforehand, separated with spaces]
AUTHOR: Tomas Zaicevas
DATE: 2018-05-03 */
#include <stdio.h>
#include <string.h>			// strlen
#include <utility>			// pair
#include <vector>
#include <stack>
#include <string>

#define MAX_LINE 256
#define MAX_VERTEX 72		// max length of vertex's key
#define ui unsigned

using namespace std;

class Graph {
private:
	vector< pair<string, vector<bool>> > vertexes;
	int count=0;													// can only be changed in add_vertex, add_edge
	vector<int> get_adjacent(int);
	int find_vertex(string);										// returns vertex with given key or -1 otherwise
public:
	int get_count();
	void add_vertex(string);
	void add_edge(string, string);
	bool DFS(string, string);
};

int Graph::get_count() { return count; }

void Graph::add_vertex(string key) {
	vertexes.push_back(make_pair(key, vector<bool>()));
	for (int i=0; i<count; i++) {									// in all vertexes but our new one, add 1 more bool
		vertexes[i].second.push_back(false);
		vertexes[count].second.push_back(false);					// our new vertex
	}
	vertexes[count++].second.push_back(false);						// one more for our new vertex
}

void Graph::add_edge(string from, string to) {						// add an edge
	int v1=-1, v2=-1;
	for (int i=0; i<count; i++) {									// more efficient than calling find_vertex
		if (vertexes[i].first == from)
			v1 = i;
			else if (vertexes[i].first == to)
				v2 = i;
	}
	if (v1 != -1 && v2 != -1 && v1+v2 < 2*count)					// same as := v1 < count && v2 < count
		vertexes[v1].second[v2] = true;
}

int Graph::find_vertex(string key) {
	for (int i=0; i<count; i++)
		if (vertexes[i].first == key)
			return i;
	return -1;
}

vector<int> Graph::get_adjacent(int a) {							// get adjacent vertexes of vertexes[a]
	vector<int> result;
	for (int i=0; i<count; i++) {
		if (vertexes[a].second[i])
			result.push_back(i);
	}
	return result;
}

bool Graph::DFS(string START, string KEY) {
// true, if we can get to vertex with value KEY from vertex with value START
	stack< pair<string, vector<bool>> > stekas;
	bool visited[count] = {};
	const int i_START = find_vertex(START), i_END = find_vertex(KEY);
	if (i_START == -1 || i_END == -1)		// if there are no such vertexes
		return false;
	visited[i_START] = true;
	stekas.push(vertexes[i_START]);
	while (!stekas.empty()) {
		vector<int> adjacent = get_adjacent(find_vertex(stekas.top().first));
		bool adjacent_visited = true;								// have visited all adjacent vertexes?
		for (ui i=0; i<adjacent.size(); i++) {
			if (!visited[adjacent[i]]) {
				visited[adjacent[i]] = true;
				stekas.push(vertexes[adjacent[i]]);
				adjacent_visited = false;
			}
		}
		if (adjacent_visited)
			stekas.pop();
	}
	return visited[i_END];
}

void analyze_line(char *buffer, Graph &grafas) {					// separate vertexes, edges, add them to graph
	string vertex("");
	ui i=0;
	const ui len = strlen(buffer);
	while (buffer[i] != ':' && i < len)
		vertex += buffer[i++];
	grafas.add_vertex(vertex);
	i++;															// was pointing to ':'
	while (i < len) {
		while (isspace(buffer[i]) && i < len)
			i++;
		string edge("");
		while (!isspace(buffer[i]) && i < len)
			edge += buffer[i++];
		if (edge.length())
			grafas.add_edge(edge, vertex);
	}
}

void build_graph(FILE *input, Graph &grafas) {				// build graph from file
	char buffer[MAX_LINE];
	fgets(buffer, MAX_LINE, input);							// first line is ignored (it's for comments)
	while (fgets(buffer, MAX_LINE, input))
		analyze_line(buffer, grafas);
}

int main() {
	char a[MAX_VERTEX], b[MAX_VERTEX];
	Graph grafas;
	FILE *input;

	input = fopen("input_graph.txt", "r");
	build_graph(input, grafas);

	printf("Enter two course names (A, B)\n");
	printf("Program will print whether you have to take course A before taking course B.\n");
	scanf("%s%s", a, b);
	printf("%s\n", grafas.DFS(string(a), string(b)) ? "Yes" : "No");

	fclose(input);

	return 0;
}
