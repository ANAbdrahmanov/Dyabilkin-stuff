#include <iostream>
#include <math.h>
#include <map>

#ifdef _DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x) 
#endif // DEBUG

void lastBlockSize(int currentDepth, long long currentBlockSize, std::map<long long,int>& blocks) {
	if (currentDepth == 0) { 
		blocks[currentBlockSize]++;
		return;
	}
	//LOG(currentBlockSize);
	int center = currentBlockSize / 2 + (currentBlockSize & 1) - 1;
	lastBlockSize(currentDepth - 1, center, blocks);
	lastBlockSize(currentDepth - 1, currentBlockSize - center - 1, blocks);
}

int main(){
	long long x, y;
	std::cin >> x >> y;
	int treeDepth = -1; //"bfs" helpers
	long long controlSum = 0; 
	//closest 2^treeDepth to y
	for (long long power = 1; controlSum < y; treeDepth++) {
		controlSum += power;
		power *= 2;
	}
	LOG(treeDepth);
	//diffence between 2^... and y = left to fill the layer
	int leftToFill = controlSum - y;
	//finding all solutions on needed level
	std::map<long long, int> lastLayerBlockCounters;
	lastBlockSize(treeDepth, x, lastLayerBlockCounters);
	//what's the solution size
	int solutionSize;
	if (lastLayerBlockCounters.size() == 1) {
		solutionSize = lastLayerBlockCounters.begin()->first;
	}
	else {
		int smaller = lastLayerBlockCounters.begin()->first;
		int bigger = (++lastLayerBlockCounters.begin())->first;
		if (smaller > bigger) std::swap(smaller, bigger);
		solutionSize = lastLayerBlockCounters[smaller] <= leftToFill ? bigger : smaller;
	}
	//make answer out of size
	LOG(solutionSize);
	if (solutionSize < 2) {
		std::cout << 0 << " " << 0 << std::endl;
	}
	else {
		int center = solutionSize / 2 + (solutionSize & 1) - 1;
		std::cout << center << " " << solutionSize - center - 1 << std::endl;
	}
	system("pause");
	return 0;
}