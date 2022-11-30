#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;


class AdjacencyList {
private:
    //Map to store the vertices and two maps to take care of ranks
    map<string, vector<pair<string, double>>> graph;
    map<string, double> oldRanks;
    map<string, double> currRanks;

public:
    AdjacencyList(){
        graph.clear();
    }
    //// prints the PageRank of all pages after p powerIterations in
   //ascending alphabetical order of webpages and rounding rank to two
   //decimal places
    void PageRank(int n) {

        //Iterate the amount of times based on the power iterations
        //Set i to 1 so that it will not run at all if p = 1 and will just print original ranks
        for (int i = 1; i < n; ++i) {

            //Loop through whole graph in order to calculate ranks for each website
            for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
                 double sum = 0;
                //Inner for loop to iterate through each vector for each website and calculate its updated rank
                //which is determined by the sum of the old ranks of each vertex pointing to the current website
                //times the outdegree of that given vertex
                for (int i = 0; i < iter->second.size(); ++i) 
                    sum += (iter->second[i].second * oldRanks[iter->second[i].first]);
                //Set current rank to the sum
                currRanks[iter->first] = sum;
            }
            //Align the oldranks map with the newly calculated ranks
            for (auto iter = currRanks.begin(); iter != currRanks.end(); ++iter)
                    oldRanks[iter->first] = iter->second; 
            
        }
        //Print the ranks after all the power iterations have finished
        for (auto iter = currRanks.begin(); iter != currRanks.end(); ++iter) {
            cout << iter->first << " " << fixed << setprecision(2) << iter->second << endl;
        }
    }
    void insertEdge(string to, string from, double outDegree, int size) {

        //set old and current ranks to (1/# of vertices)
        oldRanks[to] = (1 / (double)size);
        currRanks[to] = (1 / (double)size);
        oldRanks[from] = (1 / (double)size);
        currRanks[from] = (1 / (double)size);

        //Add each edge to the graph and if the from vertex does not exist yet 
        //set it to an empty vector to avoid issues
        graph[to].push_back(make_pair(from, outDegree));
        if (graph.find(from) == graph.end()) {
            graph[from] = {};
        }

    }
 
};



int main()
{
    //Initialize variables to take in input and store vertices and outdegrees
	int no_of_lines, power_iterations;
    set<string> uniqueVerts;
	string from, to;
    map<string, int> outDegrees;
    map<string, vector<pair<string, int>>> graph;

    //Intake the number of lines and the amount of power iterations
	cin >> no_of_lines;
	cin >> power_iterations;

    //Initialize a graph object
    AdjacencyList list;

	for (int i = 0; i < no_of_lines; i++)
	{
        //take in the two websites
		std::cin >> from;
		std::cin >> to;
        
        uniqueVerts.insert(from);
        uniqueVerts.insert(to);
		//Set outdegrees of the from website to 1 if it does not exist in map yet
        //otherwise increment it by 1
        if (outDegrees.find(from) == outDegrees.end()) {
            outDegrees[from] = 1;
        }
        else {
            outDegrees[from]++;
        }
        //Add the from and to to a temporary map that has meaningless weights
        //because the outdegree is unknown yet
        graph[to].push_back(make_pair(from, 1));       

	}

    //Add all the websites and vectors in temporary graph to graph
    //in AdjacencyList class with the updated outdegrees
    for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
        for (int i = 0; i < iter->second.size(); ++i) {
            list.insertEdge(iter->first, iter->second[i].first, 1/(double)outDegrees[iter->second[i].first], uniqueVerts.size());
        }
    }
    //Call the pageRank function
    list.PageRank(power_iterations);

}