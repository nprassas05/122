/* problem statement: suppose you are building
   an N node binary search tree with the values 1..N
   How many structurally different unique binary trees
   can you build that store those values. */
#include <iostream>
using namespace std;

int countTrees(int, int);
int countTrees(int);

int main() {
	int n;
	cin >> n;

	while (n != -99) {
		cout << countTrees(n) << endl;
		cin >> n;
	}
	return 0;
}

int countTrees(int numKeys) {
	return countTrees(1, numKeys);
}

int countTrees(int minKeyNum, int maxKeyNum) {
	if (minKeyNum >= maxKeyNum) return 1;

	int pSum = 0;
	for (int i = minKeyNum; i <= maxKeyNum; i++) {
		int left = countTrees(minKeyNum, i - 1);
		int right = countTrees(i + 1, maxKeyNum);
		pSum += (left * right);
	}
	return pSum;
}
