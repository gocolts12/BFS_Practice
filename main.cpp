#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <utility>
#include <list>
#include <algorithm>


class SpaceGraph {
private:
	std::map < std::string, std::vector<std::string>> spaceGraph;

	//Below are all helper functions for the class and therefore should be 
	//kept private
	 
	//Function for checking if a node exists in the graph
	bool existsInGraph(std::string& node)
	{
		if (spaceGraph.find(node) == spaceGraph.end())
			return false;
		return true;

	}

	//Function for checking if endNode exists in startNode's adjacency list
	bool existsInVector(std::string startNode, std::string endNode)
	{
		auto it = std::find(spaceGraph[startNode].begin(), spaceGraph[startNode].end(), endNode);
		if (it == spaceGraph[startNode].end())
		{
			return false;
		}
		return true;
	}
	//Function that inserts a new node pair into the graph and
	//inserts the inverse if it doesn't exist in the graph either
	//For example, if the pair a->b is entered into the map, it will check
	//if b exists in the map. If it exists, it will add a as a connection to b
	void insertIntoGraph(std::string& startNode, std::string& endNode)
	{
		//Insert the new key-value pair into the map
		std::pair<std::string, std::vector<std::string>> insertionPair;
		insertionPair.first = startNode;
		insertionPair.second.push_back(endNode);
		spaceGraph.emplace(insertionPair);
		//Check if we need to reciprocate the insertion for endNode
		if (!existsInGraph(endNode))
		{
			insertIntoGraph(endNode, startNode);
		}
		//If endNode was in the map, it necessarily must add startNode as a 
		//connection to it
		else
		{
			if (!existsInVector(endNode, startNode))
			insertIntoVector(endNode, startNode);
		}
	}

	//Function for linking an endNode to a pre-existing startNode and 
	//reciprocating if necessary
	void insertIntoVector(std::string startNode, std::string endNode)
	{
		spaceGraph[startNode].push_back(endNode);
		
		//Need to reciprocate insertion if the startNode isn't in startNode's
		//adjacency list
		if (!existsInVector(endNode, startNode))
		{
			insertIntoVector(endNode, startNode);
		}
	}

public:
	SpaceGraph(std::string file)
	{
		populateGraph(file);
	}

	void populateGraph(std::string file)
	{
		std::ifstream newFile;
		newFile.open(file);

		std::string line;
		std::string delimiter = ",";

		while (std::getline(newFile, line))
		{
			int delimiterIndex = line.find(delimiter);
			std::string startNode = line.substr(0, delimiterIndex);
			std::string endNode = line.substr(delimiterIndex + 1, line.length() - 1);

			//Check if the map doesn't contain that starting node yet
			//If it doesn't, add it and its first adjacent node. Also check
			//the re
			if (!existsInGraph(startNode))
			{
				//Insert the new key-value pair into the map
				insertIntoGraph(startNode, endNode);
			}
			//Otherwise the node exists in the map, and we need to verify 
			//that the pair doesn't already exist
			else
			{
				//Verify that the adjacent node isn't in the adjacency list already
				//and insert it if not. We also need to check that the reverse connection
				//exists in the map, i.e. startNode connects to endNode and endNode connects to startNode
				if(!existsInVector(startNode, endNode))
				{
					//spaceGraph[startNode].push_back(endNode);
					insertIntoVector(startNode, endNode);
				}
			}
		}
	}

	std::string areConnected(std::string startNode, std::string const &endNode)
	{
		if (startNode == endNode) return "yes\n";

		std::map<std::string, bool> visited;

		for (auto& i : spaceGraph)
		{
			visited.emplace(i.first, false);
		}
	
		std::list<std::string> queue;
		visited[startNode] = true;
		queue.push_back(startNode);

		while (!queue.empty())
		{
			// Dequeue a vertex from queue and print it
			startNode = queue.front();
			queue.pop_front();

			//Iterate through all adjacent nodes of the dequeued node and if 
			//it hasn't been visited, queue it and mark visited
			for (auto adjacentNode = spaceGraph[startNode].begin(); adjacentNode != spaceGraph[startNode].end(); ++adjacentNode)
			{
				//Check if we've found the end node
				if (*adjacentNode == endNode)
					return "yes\n";

				//Otherwise continue searching
				if (!visited[*adjacentNode])
				{
					queue.push_back(*adjacentNode);
					visited[*adjacentNode] = true;
				}
			}
		}
		return "no\n";
	}

	//Print function for testing purposes
	friend std::ostream &operator<<(std::ostream &output, const SpaceGraph& spaceGraph)
	{
		for (auto& it : spaceGraph.spaceGraph)
		{
			output << "starting node: " << it.first << " " << "adjacent nodes: ";
			for (auto& i : it.second)
			{
				output << i << "| ";
			}
			output << std::endl;
		}
		return output;
	}
};

int main(int argc, char* argv[])
{
	SpaceGraph graph("spacebusroutes.txt");
	std::cout << graph << std::endl;

	std::cout << graph.areConnected(argv[2], argv[3]);

}