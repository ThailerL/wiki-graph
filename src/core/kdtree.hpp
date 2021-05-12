/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include "kdtree.h"

using namespace std;

template<int Dim, typename V>
bool KDTree<Dim, V>::smallerDimVal(const Point<Dim, V>& first,
                                   const Point<Dim, V>& second, int curDim) const {
    if (first[curDim] == second[curDim]) return first < second;
    return first[curDim] < second[curDim];
}

template<int Dim, typename V>
bool KDTree<Dim, V>::shouldReplace(const Point<Dim, V>& target,
                                   const Point<Dim, V>& currentBest,
                                   const Point<Dim, V>& potential) const {
    double currentBestDist = 0;
    double potentialDist = 0;
    for (int i = 0; i < Dim; i++) {
        currentBestDist += std::pow(currentBest[i] - target[i], 2);
        potentialDist += std::pow(potential[i] - target[i], 2);
    }
    return (potentialDist < currentBestDist) || (potentialDist == currentBestDist && potential < currentBest);
}

template<int Dim, typename V>
KDTree<Dim, V>::KDTree(const vector<Point<Dim, V>>& newPoints) {
    root = buildTree(newPoints, 0);
    size = newPoints.size();
}

template<int Dim, typename V>
KDTree<Dim, V>::KDTree(const KDTree<Dim, V>& other) {
    size = other.size;
    root = copyTree(other.root);
}

template<int Dim, typename V>
const KDTree<Dim, V>& KDTree<Dim, V>::operator=(const KDTree<Dim, V>& rhs) {
    if (this != &rhs) {
        size = rhs.size;
        root = copyTree(rhs.root);
    }
    return *this;
}

template<int Dim, typename V>
KDTree<Dim, V>::~KDTree() {
    clear(root);
}

template<int Dim, typename V>
typename KDTree<Dim, V>::KDTreeNode* KDTree<Dim, V>::copyTree(KDTree::KDTreeNode* subroot) const {
    KDTreeNode* copyHead = new KDTreeNode(subroot->point);
    if (subroot->left) copyHead->left = copyTree(subroot->left);
    if (subroot->right) copyHead->right = copyTree(subroot->right);
    return copyHead;
}

template<int Dim, typename V>
void KDTree<Dim, V>::clear(KDTree::KDTreeNode* node) {
    if (node) {
        if (node->left) clear(node->left);
        if (node->right) clear(node->right);
        delete node;
    }
}

template<int Dim, typename V>
void KDTree<Dim, V>::swap(vector<Point<Dim, V>>& points, int i, int j) {
    std::iter_swap(points.begin() + i, points.begin() + j);
}

template<int Dim, typename V>
int KDTree<Dim, V>::partition(vector<Point<Dim, V>>& points, int left, int right, int pivotIndex, int d) {
    Point<Dim, V> pivotValue = points[pivotIndex];
    swap(points, pivotIndex, right);
    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (smallerDimVal(points[i], pivotValue, d)) {
            swap(points, storeIndex, i);
            storeIndex++;
        }
    }
    swap(points, right, storeIndex);
    return storeIndex;
}

template<int Dim, typename V>
Point<Dim, V> KDTree<Dim, V>::quickSelect(vector<Point<Dim, V>>& points, int left, int right, int k, int d) {
    if (left == right) return points[left];
    int pivotIndex = left;
    pivotIndex = partition(points, left, right, pivotIndex, d);
    if (k == pivotIndex) return points[k];
    else if (k < pivotIndex) return quickSelect(points, left, pivotIndex - 1, k, d);
    else return quickSelect(points, pivotIndex + 1, right, k, d);
}

template<int Dim, typename V>
typename KDTree<Dim, V>::KDTreeNode* KDTree<Dim, V>::buildTree(vector<Point<Dim, V>> points, int d) {
    if (points.size() == 0) return nullptr;
    // median index
    int k = (points.size() - 1) / 2;
    Point<Dim, V> mid = quickSelect(points, 0, points.size() - 1, k, d);
    KDTreeNode* subroot = new KDTreeNode(mid);
    subroot->left = buildTree(vector<Point<Dim, V>>(points.begin(), points.begin() + k), (d + 1) % Dim);
    subroot->right = buildTree(vector<Point<Dim, V>>(points.begin() + k + 1, points.end()), (d + 1) % Dim);
    return subroot;
}
