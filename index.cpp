#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits> 

struct Node
{
    int id;
    float x;
    float y;
    Node* left;
    Node* right;

    Node(int _id, float _x, float _y)
        : id(_id), x(_x), y(_y), left(nullptr), right(nullptr) {
    }
};

class CompositeIndex
{
public:
    CompositeIndex() : root(nullptr) {}

    ~CompositeIndex()
    {
        destroy(root);
    }

    void parseIndex(std::istringstream& iss)
    {
        destroy(root);
        root = parseNode(iss);
    }

    int totalNodes() const
    {
        return countNodes(root);
    }

    int height() const
    {
        return treeHeight(root);
    }

    int leaves() const
    {
        return countLeaves(root);
    }

    bool isValid() const
    {
        if (!root) return true; 

        std::vector<int> ids;
        getInorder(root, ids);

        for (size_t i = 1; i < ids.size(); ++i) {
            if (ids[i] <= ids[i - 1]) {
                return false;
            }
        }
        return true;
    }

    int minID() const
    {
        if (!root) throw std::runtime_error("Tree is empty");
        return findMin(root);
    }

    int maxID() const
    {
        if (!root) throw std::runtime_error("Tree is empty");
        return findMax(root);
    }

private:
    Node* root;

    Node* parseNode(std::istringstream& iss)
    {
        std::string token;
        if (!(iss >> token)) return nullptr; 

        if (token == "#") {
            return nullptr;
        }

        int id = std::stoi(token);
        float x, y;
        iss >> x >> y;

        Node* node = new Node(id, x, y);
        node->left = parseNode(iss);  
        node->right = parseNode(iss); 
        return node;
    }

    int countNodes(Node* node) const
    {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int treeHeight(Node* node) const
    {
        if (!node) return 0;
        return 1 + std::max(treeHeight(node->left), treeHeight(node->right));
    }

    int countLeaves(Node* node) const
    {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

    void getInorder(Node* node, std::vector<int>& arr) const
    {
        if (!node) return;
        getInorder(node->left, arr);  
        arr.push_back(node->id);      
        getInorder(node->right, arr); 
    }

    // Вспомогательная функция поиска минимума во всем дереве
    int findMin(Node* node) const {
        if (!node) return std::numeric_limits<int>::max();
        int res = node->id;
        int lres = findMin(node->left);
        int rres = findMin(node->right);
        return std::min(res, std::min(lres, rres));
    }

    // Вспомогательная функция поиска максимума во всем дереве
    int findMax(Node* node) const {
        if (!node) return std::numeric_limits<int>::min();
        int res = node->id;
        int lres = findMax(node->left);
        int rres = findMax(node->right);
        return std::max(res, std::max(lres, rres));
    }

    void destroy(Node* node)
    {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};