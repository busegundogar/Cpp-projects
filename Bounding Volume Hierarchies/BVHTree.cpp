#include "BVHTree.h"
#include <string>

using namespace std;


BVHTree::BVHTree(){
    root = nullptr;
}


BVHTree::~BVHTree(){
    destroy(root);
}

void BVHTree::destroy(BVHTreeNode *node){
     
    if(node != nullptr){
        destroy(node->leftChild);
        destroy(node->rightChild);
        delete node;
    }
}

void BVHTree::printNode(ostream &out, BVHTreeNode *node, int level) {
	if (root == nullptr) return;
	for (int i = 0; i < level; i++) {
		out << "  ";
	}
	if (!node->isLeaf) {
		out << "+ branch || ";
		node->aabb.printAABB(out);
		out << std::endl;
		printNode(out, node->rightChild, level + 1);
		printNode(out, node->leftChild, level + 1);
	}
	else {
		out << "- ";
		if (node->parent) {
			if (node->parent->rightChild == node)
				out << "R ";
			else
				out << "L ";
		}
		out << "- leaf: " << node->name << " || ";
		node->aabb.printAABB(out);
		out << std::endl;
	}
}

void BVHTree::addBVHMember(AABB objectArea, string name){
    
    //If the tree is empty
    if(root == nullptr){

        
        BVHTreeNode *addNode = new BVHTreeNode(objectArea,name,true);
        root = addNode;
        
        map[name] = root;
    }
    
    
    //If the tree has only 1 node
    else if(root->leftChild == nullptr){
        
        BVHTreeNode *tempRightNode = root;
 
        
        BVHTreeNode *addNode = new BVHTreeNode(objectArea,name,true);
        
        AABB newRootAABB = objectArea + tempRightNode->aabb;
        BVHTreeNode *newRoot = new BVHTreeNode(newRootAABB,"branch",false);

        newRoot->leftChild = addNode;
        newRoot->rightChild = tempRightNode;
        
        addNode->parent = newRoot;
        
        tempRightNode->parent = newRoot;
        
        updateParents(addNode);
        updateParents(tempRightNode);
        root = newRoot;
        
        map[name] = addNode;
    }
    
    
    //If the tree has more than 1 node
    else{
        BVHTreeNode *addNode = new BVHTreeNode(objectArea,name,true);
        BVHTreeNode *searchNode = root;
        
        int increaseInRightTreeSize, increaseInLeftTreeSize;
        string last= "";
        
        //Iterating untill finding the leaf with least area
        while(!(searchNode->isLeaf)){
            increaseInRightTreeSize = AABB::unionArea(addNode->aabb, searchNode->rightChild->aabb) - searchNode->rightChild->aabb.getArea();
            increaseInLeftTreeSize = AABB::unionArea(addNode->aabb, searchNode->leftChild->aabb) - searchNode->leftChild->aabb.getArea();
            
            //Continue to search in right
            if(increaseInRightTreeSize < increaseInLeftTreeSize){
                searchNode = searchNode->rightChild;
                last = "right";
            }
            else{ //else, continue with left
                searchNode = searchNode->leftChild;
                last = "left";
            }
        }
        
        //When we find the leaf node:
        AABB newRootAABB = objectArea + searchNode->aabb;
        BVHTreeNode *newBranch = new BVHTreeNode(newRootAABB,"branch",false);
        
        newBranch->parent = searchNode->parent;
        if(last == "right")
            searchNode->parent->rightChild = newBranch;
        else
            searchNode->parent->leftChild = newBranch;
           
        
        newBranch->leftChild = addNode;
        newBranch->rightChild = searchNode;
        
        searchNode->parent = newBranch;
        searchNode->leftChild = nullptr;
        searchNode->rightChild = nullptr;
        searchNode->isLeaf = true;
        
        addNode->parent = newBranch;
        
        updateParents(addNode);
        updateParents(newBranch);

        
        map[name] = addNode;
    }
    
}

void BVHTree::updateParents(BVHTreeNode *&addedNode){
     
    int xMax = addedNode->aabb.maxX;
    int yMax = addedNode->aabb.maxY;
    int xMin = addedNode->aabb.minX;
    int yMin = addedNode->aabb.minY;
    
    BVHTreeNode *search = addedNode;
    
    while(search->parent != nullptr){
        
        if(search->parent->aabb.maxX >= xMax){
            if(search->parent->aabb.maxY >= yMax){
                if(search->parent->aabb.minX <= xMin){
                    if(search->parent->aabb.minY <= yMin){
                        return;
                    }
                    else
                        search->parent->aabb.minY = yMin;
                }
                else{
                    search->parent->aabb.minX = xMin;
                }
            }
            else{
                search->parent->aabb.maxY = yMax;
            }
        }
        else{
            search->parent->aabb.maxX = xMax;
        }
            
    
        search = search->parent;
    }
    
    if(search->aabb.maxX >= xMax){
        if(search->aabb.maxY >= yMax){
            if(search->aabb.minX <= xMin){
                if(search->aabb.minY <= yMin){
                    return;
                }
                else
                    search->aabb.minY = yMin;
            }
            else{
                search->aabb.minX = xMin;
            }
        }
        else{
            search->aabb.maxY = yMax;
        }
    }
    else{
        search->aabb.maxX = xMax;
    }
    
    
}

void BVHTree::updateBranch(BVHTreeNode *branch){
    
    if (!branch->isLeaf) {
        
        branch->aabb.maxX = AABB::getMax(branch->leftChild->aabb.maxX, branch->rightChild->aabb.maxX);
        branch->aabb.maxY = AABB::getMax(branch->leftChild->aabb.maxY, branch->rightChild->aabb.maxY);
        branch->aabb.minX = AABB::getMin(branch->leftChild->aabb.minX, branch->rightChild->aabb.minX);
        branch->aabb.minY = AABB::getMin(branch->leftChild->aabb.minY, branch->rightChild->aabb.minY);

        updateBranch(branch->rightChild);
        updateBranch(branch->leftChild);
    }
}

void BVHTree::moveBVHMember(string name, AABB newLocation){
    BVHTreeNode *moveNode = map[name];
    
    
    if(moveNode == root){
        moveNode->aabb = newLocation;
        map[name] = moveNode;
        return;
    }
    
    //If parent includes the node to be moved
    if(moveNode->parent->aabb.maxX >= newLocation.maxX && moveNode->parent->aabb.maxY >= newLocation.maxY && moveNode->parent->aabb.minX <= newLocation.minX && moveNode->parent->aabb.minY <= newLocation.minY){
        
        moveNode->aabb = newLocation;
        
        updateParents(moveNode);
        map[name] = moveNode;
    }
    else{ //If not
        removeBVHMember(name);
        
        
        addBVHMember(newLocation, name);
        
        updateBranch(moveNode->parent);
        updateBranch(moveNode->parent->parent);
    }
    
    
}

void BVHTree::removeBVHMember(string name){
    
    BVHTreeNode *toRemove = map[name];
    
    BVHTreeNode *branchToDelete = toRemove->parent;
    BVHTreeNode *grandNode = branchToDelete->parent;
    
    BVHTreeNode *siblingNode;
    if(branchToDelete->rightChild == toRemove)
        siblingNode = branchToDelete->leftChild;
    else if(branchToDelete->leftChild == toRemove)
        siblingNode = branchToDelete->rightChild;
        
    
    //Change place of sibling node
    if(grandNode->leftChild == branchToDelete){
        grandNode->leftChild = siblingNode;
        
        updateParents(siblingNode);
        updateParents(grandNode->rightChild);
        
        updateBranch(grandNode);
        
        siblingNode->parent = grandNode;
    }
    else if(grandNode->rightChild == branchToDelete){
        grandNode->rightChild = siblingNode;
        
        updateParents(siblingNode);
        updateParents(grandNode->leftChild);
        
        updateBranch(grandNode);

        siblingNode->parent = grandNode;
    }

    map.erase(name);
    //delete branchToDelete;
    //delete toRemove;
}


vector<string> BVHTree::getCollidingObjects(AABB object){
    
    vector<string> collObj;
    vector<string> result;
    
    BVHTreeNode *searchNode = root;
    searchTree(searchNode,collObj);
    
    for(int i = 0; i < collObj.size(); i++){
        auto itr = map.find(collObj[i]);
        if( (itr->second->aabb).collide(object) ){
            result.push_back(collObj[i]);
        }
    }
    return result;
}

void BVHTree::searchTree(BVHTreeNode *searchNode, vector<string> &vec){
     
    if (root == nullptr)
        return ;
    
    
    if (!searchNode->isLeaf) {
        searchTree(searchNode->rightChild,vec);
        searchTree(searchNode->leftChild,vec);
    }
    else {
        vec.push_back(searchNode->name);
    }
        
}
 

ostream &operator<<(ostream &out, BVHTree &tree) {
	tree.printNode(out, tree.root, 0);
	return out;
}
