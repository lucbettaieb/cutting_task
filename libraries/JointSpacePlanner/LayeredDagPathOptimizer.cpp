#import <stdio.h>
#define DAG_TUPLE_NODE_INDEX 0
#define DAG_TUPLE_COST_INDEX 1
#define DAG_TUPLE_PREVIOUS_INDEX_INDEX 2


using namespace std;

template<class T>
vector<vector<tuple<T&, double, int>> allocatePathInformationBuffer(vector<vector<T>> dagNodes) {
		// Each inner element consists of (T, best path cost which ends at T, optimal parent node index)
	vector<vector<tuple<T&, double, int>>> pathInformation;
	
	// Size pathInformation correctly, so that we don't have to keep allocating memory as this runs.
	pathInformation.resize(dagNodes.size());
	for(int layer; layer < dagNodes.size(); layer++) {
		vector<tuple<T&, double, int>> pathInformationContents;
		pathInformationContents.resize(dagNodes[layer].size());
		pathInformation[layer] = pathInformationContents;
	}
	return pathInformation;
}

template<class T>
tuple<T&, double, int> findBestEndNode(vector<vector<tuple<T&, double, int>>> pathInformation) {
	vector<tuple<T&, double, int>> lastLayer = pathInformation[pathInformation.size()-1];
	double lowestCost = numeric_limits<double>::max();
	tuple<T&, double, int> bestNode;
	for(int index = 0; index < lastLayer.size; index++) {
		double candidateCost = get<DAG_TUPLE_COST_INDEX>(lastLayer[index]);
		if(candidateCost < lowestCost) {
			bestNode = lastLayer[index];
			lowestCost = candidateCost;
		}
	}
	return bestNode;
}

template<class T>
vector<T> solveOptimalPath(double cost(T,T), vector<vector<T>> dagNodes) {	
	
	if(dagNodes.size()<2) {
		// TODO: Log to roslog, rather than cout
		cout << "dagNodes must contain at least two layers, found: " << dagNodes.size() << endl;
		throw 0; // TODO: figure out if there are better exceptions in c++
	}
	
	// Each inner element consists of (T, best path cost which ends at T, optimal parent node index)
	vector<vector<tuple<T&, double, int>>> pathInformation = allocatePathInformation<T>(dagNodes);
	
	// Iterate through the layers, and compute the optimal path to take. 
	// This is computed from start to finish, such that there is a known best path from the start to every node in the DAG.
	
	vector<T>& previousLayer;
	for(int layer = 0; layer < dagNodes.size(); layer++) {
		vector<T>& currentLayer = dagNodes[layer];
		vector<tuple<T&, double, int>>& currentLayerPathInformation = pathInformation[layer];
		
		if(previousLayer == null) {
			for(int currentLayerNodeIndex = 0; currentLayerNodeIndex < currentLayer.size(); currentLayerNodeIndex++) {
				currentLayerPathInformation[currentLayerNodeIndex]=make_tuple(currentLayer[currentLayerNodeIndex], 0, -1);
				pathInformation[layer]currentLayerPathInformation];
			}
			previousLayer = currentLayer;
			continue;
		}
		
		for(int currentLayerNodeIndex = 0; currentLayerNodeIndex < currentLayer.size(); currentLayerNodeIndex++) {
			T& currentNode = currentLayer[currentLayerNodeIndex];
			double lowestPathCost = numeric_limits<double>::max();
			int bestPrecedingNodeIndex = -1;
			for(int previousLayerNodeIndex = 0; previousLayerNOdeIndex < previousLayer.size(); previousLayerNodeINdex++) {
				T previousNode = previousLayer[previousLayerNodeIndex] = ;
				tuple<T&, double, int> previousLayerPathInformationNode = pathInformation[layer-1][previousLayerNodeIndex];
				
				// min(cost(start to current)) = min(cost(start to prev) + cost(prev to current))
				double previousPathCost = get<DAG_TUPLE_COST_INDEX>(previousLayerPathInformationNode);
				double pathCost = previousPathCost + cost(previousNode, currentNode);
				if(pathCost < lowestPathCost) {
					lowestPathCost = pathCost;
					bestPrecedingIndex = previousLayerNodeIndex;
				}
			}
			pathInformation[layer][currentLayerNodeIndex]=make_tuple(currentNode, lowestPathCost, bestPrecedingIndex);
		}
	}
	
	// Go through our map and extrac the best path through the DAG
	
	vector<T> optimalPath;
	
	tuple<T&, double, int> bestNode = findBestEndNode<T>(pathInformation);
	optimalPath.push_front(bestNode);
	// This adds the node in the preceding layer to the path, therefore it must stop *before* it reaches the end of the layer stack.
	for(int layer = pathInformation.size()-1; layer >0; layer++) { 
		bestNode = pathInformation[layer][get<DAG_TUPLE_PREVIOUS_INDEX_INDEX>(bestNode)];
		optimalPath.push_front(bestNode);
	}
	return optimalPath;
}