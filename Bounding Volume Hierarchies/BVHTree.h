#include "AABB.h"
#include "BVHTreeNode.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#ifndef _BVH_TREE
#define _BVH_TREE

using namespace std;

class BVHTree {
private:
	BVHTreeNode *root;
	std::unordered_map<string, BVHTreeNode *> map;
public:
	BVHTree();
	~BVHTree();
    void destroy(BVHTreeNode *);
	void printNode(ostream &out, BVHTreeNode *, int level);
	void addBVHMember(AABB objectArea, string name);
    void updateParents(BVHTreeNode *&);
    void updateBranch(BVHTreeNode *);
	void moveBVHMember(string name, AABB newLocation);
	void removeBVHMember(string name);
    void searchTree(BVHTreeNode *,vector<string> &vec);
	vector<string> getCollidingObjects(AABB object);
	friend std::ostream &operator<<(ostream &out, BVHTree &tree);
};

#endif
