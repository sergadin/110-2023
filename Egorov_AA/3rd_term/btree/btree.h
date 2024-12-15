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
            return currentNode != nullptr && (currentIndex < int(currentNode->keys.size()) || !path.empty());
        }

        const std::string& next() {
            if (currentIndex < int(currentNode->keys.size())) {
                return *currentNode->keys[currentIndex++];
            }
            else if (!path.empty()) {
                currentNode = path.back();
                path.pop_back();
                currentIndex = 0;
                return next();
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
    };

    Iterator iteratorFrom(const std::string& value) {
        BTreeNode* node = root;
        int idx = 0;
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

