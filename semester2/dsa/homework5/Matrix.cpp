#include "Matrix.h"
#include <exception>
using namespace std;

///Theta(this->capacity)
Matrix::Matrix(int nrLines, int nrCols) {
    this->capacity = 5;
    this->nrElements = 0;
    this->nrLine = nrLines;
    this->nrCol = nrCols;
    this->root = -1;
    this->firstEmpty = 0;
    this->SLLANodes = new Node[this->capacity];
    this->SLLANodes[firstEmpty].left = 1;
    this->SLLANodes[firstEmpty].right = -1;
    this->SLLANodes[firstEmpty].parent = -1;
    get<2>(this->SLLANodes[firstEmpty].info) = NULL_TELEM;
    for (int i = 1; i < this->capacity - 1; i++)
    {
        this->SLLANodes[i].left = i + 1;
        this->SLLANodes[i].right = -1;
        this->SLLANodes[i].parent = -1;
        get<2>(this->SLLANodes[i].info) = NULL_TELEM;
    }
    this->SLLANodes[this->capacity - 1].right = -1;
    this->SLLANodes[this->capacity - 1].left = -1;
    this->SLLANodes[this->capacity - 1].parent = -1;
    get<2>(this->SLLANodes[this->capacity - 1].info) = NULL_TELEM;
}


///Theta(1)
int Matrix::nrLines() const {
    return this->nrLine;
}

///Theta(1)
int Matrix::nrColumns() const {
    return this->nrCol;
}

///Best case: Theta(1) -> if the element we search is exactly the root
///Worst case: Theta(this->nrElements) -> if the element we searched is not in the tree
///Total complexity: O(this->nrElements)
TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= this->nrLine)
        throw exception();
    if (j < 0 || j >= this->nrCol)
        throw exception();
    int currentNode = this->root;
    while (currentNode != -1)
    {
        if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) == j) {
            return get<2>(this->SLLANodes[currentNode].info);
        }
        if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) < j) {
            currentNode = this->SLLANodes[currentNode].right;
        }
        else if (get<0>(this->SLLANodes[currentNode].info) < i) {
            currentNode = this->SLLANodes[currentNode].right;
        }
        else if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) > j) {
            currentNode = this->SLLANodes[currentNode].left;
        }
        else if (get<0>(this->SLLANodes[currentNode].info) > i) {
            currentNode = this->SLLANodes[currentNode].left;
        }
    }

    return NULL_TELEM;
}



///Best case: Theta(1)
///Worst case: Theta(this->nrElements)
///Total complexity: O(this->nrElements)
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= this->nrLine)
        throw exception();
    if (j < 0 || j >= this->nrCol)
        throw exception();

    MCell newCell = MCell(i, j, e);
    if (e != 0) ///have to modify the value or insert a new one
    {
        int currentNode = this->root;
        int previousNode = 0;
        while (currentNode != -1) {
            ///have to modify the value of the cell
            if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) == j)
            {
                TElem oldValue = get<2>(this->SLLANodes[currentNode].info); //save old value
                this->SLLANodes[currentNode].info = newCell;    //override
                return oldValue;
            }
            //right part
            if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) < j)
            {
                previousNode = currentNode;
                currentNode = this->SLLANodes[currentNode].right;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) < i)
            {
                previousNode = currentNode;
                currentNode = this->SLLANodes[currentNode].right;
            }
            //left part
            else if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) > j)
            {
                previousNode = currentNode;
                currentNode = this->SLLANodes[currentNode].left;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) > i)
            {
                previousNode = currentNode;
                currentNode = this->SLLANodes[currentNode].left;
            }
        }

        ///add a new element
        ///the BTS is empty so the first added node will become the root
        if (this->root == -1) {
            int position = this->allocate();
            if (position == -1 && this->nrElements == this->capacity)
            {
                this->resize();
                position = this->allocate();
            }
            this->SLLANodes[position].info = newCell;
            this->root = position;
            this->nrElements++;
            return 0;   //old value
        }

        ///found the node for which we add a new "child"
        int position = this->allocate();
        if (position == -1 && this->nrElements == this->capacity)
        {
            this->resize();
            position = this->allocate();
        }
        /// add the new node as the right child
        if ((get<0>(this->SLLANodes[previousNode].info) == i and get<1>(this->SLLANodes[previousNode].info) < j) || get<0>(this->SLLANodes[previousNode].info) < i)
        {
            this->SLLANodes[previousNode].right = position;
            this->SLLANodes[position].info = newCell;
            this->SLLANodes[position].parent = previousNode;
            this->nrElements++;
            return 0;
        }
        ///add the new node as the left child
        else
        {
            this->SLLANodes[previousNode].left = position;
            this->SLLANodes[position].info = newCell;
            this->SLLANodes[position].parent = previousNode;
            this->nrElements++;
            return 0;
        }

    }
    else///remove the value or do nothing
    {
        int currentNodeToBeRemoved = 0;

        int currentNode = this->root;

        bool stop = false;
        //search the node that neads to be removed
        while (currentNode != -1 and !stop) {
            if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) == j)
            {
                currentNodeToBeRemoved = currentNode;
                stop = true;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) < j) {
                currentNode = this->SLLANodes[currentNode].right;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) < i) {
                currentNode = this->SLLANodes[currentNode].right;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) == i and get<1>(this->SLLANodes[currentNode].info) > j) {
                currentNode = this->SLLANodes[currentNode].left;
            }
            else if (get<0>(this->SLLANodes[currentNode].info) > i) {
                currentNode = this->SLLANodes[currentNode].left;
            }
        }

        ///currentValue from that position is 0 and the new value we want to add is also 0 => do nothing
        if (currentNode == -1)
            return 0;
        //find how many descendents it has
        int numberOfDescendants = 0;
        if (this->SLLANodes[currentNodeToBeRemoved].left != -1)
            numberOfDescendants++;
        if (this->SLLANodes[currentNodeToBeRemoved].right != -1)
            numberOfDescendants++;

        ///the node to delete doesn't have a descendent.
        if (numberOfDescendants == 0)
        {
            ///have only one node in the tree which is the root
            if (currentNodeToBeRemoved == this->root) {
                this->root = -1;
                TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                free(currentNodeToBeRemoved);
                this->nrElements--;
                return oldValue;
            }
            ///node to delete is a leaf
            else
            {
                int parent = this->SLLANodes[currentNodeToBeRemoved].parent;
                ///check if it was the left child of the parent
                if (this->SLLANodes[parent].left == currentNodeToBeRemoved) {
                    this->SLLANodes[parent].left = -1;
                }
                ///check if it was the right child of the parent
                else if (this->SLLANodes[parent].right == currentNodeToBeRemoved) {
                    this->SLLANodes[parent].right = -1;
                }
                TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                free(currentNodeToBeRemoved);
                this->nrElements--;
                return oldValue;
            }
        }
        ///one descendent
        else if (numberOfDescendants == 1) {
            ///node = root
            if (currentNodeToBeRemoved == this->root) {
                ///check if the root had a left child
                if (this->SLLANodes[currentNodeToBeRemoved].left != -1) {
                    TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                    this->root = this->SLLANodes[currentNodeToBeRemoved].left;
                    this->SLLANodes[this->root].parent = -1;
                    free(currentNodeToBeRemoved);
                    this->nrElements--;
                    return oldValue;
                }
                ///check if the root had a right child
                else if (this->SLLANodes[currentNodeToBeRemoved].right != -1) {
                    TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                    this->root = this->SLLANodes[currentNodeToBeRemoved].right;
                    this->SLLANodes[this->root].parent = -1;
                    free(currentNodeToBeRemoved);
                    this->nrElements--;
                    return oldValue;
                }
            }
            ///node is inside the three
            else {
                ///check if the node had a left child
                if (this->SLLANodes[currentNodeToBeRemoved].left != -1) {
                    int parent = this->SLLANodes[currentNodeToBeRemoved].parent;
                    if (this->SLLANodes[parent].left == currentNodeToBeRemoved) {

                        ///set the parent for the left child of the node with the parent of the node
                        this->SLLANodes[this->SLLANodes[currentNodeToBeRemoved].left].parent = parent;

                        ///set the left child of the parent of the node with the left child of the node
                        this->SLLANodes[parent].left = this->SLLANodes[currentNodeToBeRemoved].left;

                        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                        free(currentNodeToBeRemoved);
                        this->nrElements--;
                        return oldValue;
                    }
                    else if (this->SLLANodes[parent].right == currentNodeToBeRemoved) {
                        this->SLLANodes[this->SLLANodes[currentNodeToBeRemoved].left].parent = parent;
                        this->SLLANodes[parent].right = this->SLLANodes[currentNodeToBeRemoved].left;

                        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                        free(currentNodeToBeRemoved);
                        this->nrElements--;
                        return oldValue;
                    }
                }
                ///check if the node had a right child
                else if (this->SLLANodes[currentNodeToBeRemoved].right != -1) {

                    ///keep the parent of the node 
                    int parent = this->SLLANodes[currentNodeToBeRemoved].parent;
                    if (this->SLLANodes[parent].left == currentNodeToBeRemoved) {
                        this->SLLANodes[this->SLLANodes[currentNodeToBeRemoved].right].parent = parent;
                        this->SLLANodes[parent].left = this->SLLANodes[currentNodeToBeRemoved].right;

                        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                        free(currentNodeToBeRemoved);
                        this->nrElements--;
                        return oldValue;
                    }
                    else if (this->SLLANodes[parent].right == currentNodeToBeRemoved) {
                        this->SLLANodes[this->SLLANodes[currentNodeToBeRemoved].right].parent = parent;
                        this->SLLANodes[parent].right = this->SLLANodes[currentNodeToBeRemoved].right;

                        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
                        free(currentNodeToBeRemoved);
                        this->nrElements--;
                        return oldValue;
                    }

                }
            }

        }
        ///node we want to remove has 2 descendents
        int rightChild = this->SLLANodes[currentNodeToBeRemoved].right;
        int replacedNode = this->findMinimum(rightChild);

        ///detach the minimum from the tree

        ///minimum is a leaf
        if (this->SLLANodes[replacedNode].right == -1) {
            ///keep the parent of the minimum
            int parent = this->SLLANodes[replacedNode].parent;
            this->SLLANodes[replacedNode].parent = -1;
            if (this->SLLANodes[parent].left == replacedNode) {
                this->SLLANodes[parent].left = -1;
            }
            else if (this->SLLANodes[parent].right == replacedNode) {
                this->SLLANodes[parent].right = -1;
            }

        }

        ///minimum has a right child
         else if (this->SLLANodes[replacedNode].right != -1) {
            int parent = this->SLLANodes[replacedNode].parent;
            if (this->SLLANodes[parent].left == replacedNode) {
                this->SLLANodes[parent].left = this->SLLANodes[replacedNode].right;
            }
            else if (this->SLLANodes[parent].right == replacedNode) {
                this->SLLANodes[parent].right = this->SLLANodes[replacedNode].right;
            }
            int child = this->SLLANodes[replacedNode].right;
            this->SLLANodes[child].parent = parent;
            this->SLLANodes[replacedNode].parent = -1;

        }
        //replece the current node with the minimum
        TElem oldValue = get<2>(this->SLLANodes[currentNodeToBeRemoved].info);
        this->SLLANodes[currentNodeToBeRemoved].info = this->SLLANodes[replacedNode].info;
        free(replacedNode);
        this->nrElements--;
        return oldValue;

    }
}

///Best case: Theta(1)
///Worst case: Theta(this->nrElements)
///Total complexity: O(this->nrElements)
int Matrix::findMinimum(int position) {
    while (this->SLLANodes[position].left != -1) {
        position = this->SLLANodes[position].left;
    }
    return position;
}

///Theta(this->capacity)
void Matrix::resize() {
    this->capacity = 2 * this->capacity;
    Node* NewArray = new Node[this->capacity];
    for (int i = 0; i < this->nrElements; i++)
    {
        NewArray[i] = this->SLLANodes[i];
    }

    this->firstEmpty = this->nrElements;
    NewArray[firstEmpty].left = this->nrElements + 1;
    NewArray[firstEmpty].right = -1;
    NewArray[firstEmpty].parent = -1;
    get<2>(NewArray[firstEmpty].info) = NULL_TELEM;
    for (int i = this->nrElements + 1; i < this->capacity - 1; i++) {
        NewArray[i].left = i + 1;
        NewArray[i].right = -1;
        NewArray[i].parent = -1;
        get<2>(NewArray[i].info) = NULL_TELEM;
    }
    NewArray[this->capacity - 1].right = -1;
    NewArray[this->capacity - 1].left = -1;
    NewArray[this->capacity - 1].parent = -1;
    get<2>(NewArray[this->capacity - 1].info) = NULL_TELEM;

    delete[] this->SLLANodes;
    this->SLLANodes = NewArray;
}

///Theta(1)
int Matrix::allocate() {
    int newElement = this->firstEmpty;
    if (newElement != -1) {
        this->firstEmpty = this->SLLANodes[this->firstEmpty].left;
        this->SLLANodes[newElement].left = -1;
        this->SLLANodes[newElement].right = -1;
        this->SLLANodes[newElement].parent = -1;
    }
    return newElement;
}

///Theta(1)
void Matrix::free(int position) {
    this->SLLANodes[position].left = this->firstEmpty;
    get<2>(this->SLLANodes[position].info) = NULL_TELEM;
    this->SLLANodes[position].right = -1;
    this->SLLANodes[position].parent = -1;
    this->firstEmpty = position;
}


int Matrix::recursiveSearch(int position, TElem value) const {
    if (position == -1 || get<2>(this->SLLANodes[position].info) == value)
        return position;

    int rightPosition = this->recursiveSearch(this->SLLANodes[position].right, value);
    if (rightPosition != -1)
        return rightPosition;

    int leftPosition = this->recursiveSearch(this->SLLANodes[position].left, value);
    if (leftPosition != -1)
        return leftPosition;

    return -1;
}

///Best case: Theta(1) -> if the element we searched is exactly the root
///Worst case: Theta(this->nrOfElements) ->if the element we searched for is not in the tree
///Total complexity: O(this->nrOfElements)
std::pair<int, int> Matrix::positionOf(TElem elem) const {
    int position = this->recursiveSearch(this->root, elem);
    if (position == -1) {
        return std::make_pair(-1, -1);
    }
    int line = get<0>(this->SLLANodes[position].info);
    int column = get<1>(this->SLLANodes[position].info);
    return std::make_pair(line, column);
}

