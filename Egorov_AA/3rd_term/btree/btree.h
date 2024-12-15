#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

const int T = 3; // Минимальная степень B-дерева

struct BTreeNode {
    bool isLeaf;
    std::vector<std::string*> keys;
    std::vector<BTreeNode*> children;

    BTreeNode(bool leaf) : isLeaf(leaf) {}
};

class BTree {
public:
    BTree() : root(new BTreeNode(true)), size(0) {}

    ~BTree() {clear(root);}

    void insert(const std::string& value);

    bool remove(const std::string& value);

    bool contains(const std::string& value);

    size_t count() const;

    class Iterator {
    public:
        Iterator(BTreeNode* node, int idx) : currentNode(node), currentIndex(idx) {}

        bool hasNext() const {
            return currentNode != nullptr;;
        }

        const std::string& next() {
            if (currentIndex < int(currentNode->keys.size())) {
                return *currentNode->keys[currentIndex++];
            }
            else {
                moveToNextNode();
                if (currentNode != nullptr && currentIndex < currentNode->keys.size()) {
                    return *currentNode->keys[currentIndex++];
                }
            }
            throw std::out_of_range("Iterator reached the end");
        }

        void pushChild(BTreeNode* child) {
            path.push_back(child);
        }

    private:
        BTreeNode* currentNode;
        int currentIndex;
        std::vector<BTreeNode*> path;

        void moveToNextNode() {
            while (!path.empty()) {
                BTreeNode* parent = path.back();
                path.pop_back();
                int childIndex = std::find(parent->children.begin(), parent->children.end(), currentNode)
                    - parent->children.begin();

                if (childIndex + 1 < int(parent->children.size())) {
                    currentNode = parent->children[childIndex + 1];
                    while (!currentNode->isLeaf) {
                        path.push_back(currentNode);
                        currentNode = currentNode->children[0];
                    }
                    currentIndex = 0;
                    return;
                }

                currentNode = parent;
            }
            currentNode = nullptr;
        }
    };

    Iterator iteratorFrom(const std::string& value) {
        BTreeNode* node = root;
        int idx = 0;
        std::vector<BTreeNode*> path;
        while (node != nullptr) {
            auto it = std::lower_bound(node->keys.begin(), node->keys.end(), &value, comparePointers);
            idx = it - node->keys.begin();
            if (idx < int(node->keys.size()) && *node->keys[idx] == value) {
                return Iterator(node, idx);
            }
            if (node->isLeaf) {
                return Iterator(nullptr, 0);
            }
            else {
                node = node->children[idx];
            }
        }
        return Iterator(nullptr, 0);
    }

private:
    BTreeNode* root;
    size_t size;

    static bool comparePointers(const std::string* a, const std::string* b) {
        return *a < *b;
    }
    void splitChild(BTreeNode* parent, int idx);

    void insertNonFull(BTreeNode* node, std::string* value);

    void removeFromNode(BTreeNode* node, const std::string& value);

    int findKey(BTreeNode* node, const std::string& value);

    std::string* getPredecessor(BTreeNode* node, int idx);

    std::string* getSuccessor(BTreeNode* node, int idx);

    void merge(BTreeNode* node, int idx);

    void fill(BTreeNode* node, int idx);

    void borrowFromPrev(BTreeNode* node, int idx);

    void borrowFromNext(BTreeNode* node, int idx);

    std::string* search(BTreeNode* node, const std::string& value);

    void clear(BTreeNode* node);
};

