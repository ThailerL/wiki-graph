/**
 * @file kdtree.h
 * KDTree implementation using Points in k-dimensional space.
 *
 * @author Zesheng Wang
 * @author Wade Fagen-Ulmschneider
 * @author Cinda Heeren
 * @author Jack Toole
 * @author Sean Massung
 */

#pragma once

#include <vector>

#include "point.h"

using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::endl;

namespace wikigraph {
namespace core {

/**
 * KDTree class: implemented using Points in Dim dimensional space (given
 * by the template parameter).
 */
template<int Dim, typename V>
class KDTree {
private:
    /**
     * Internal structure for a node of KDTree.
     * Contains left, right children pointers and a K-dimensional point
     */
    struct KDTreeNode {
        Point<Dim, V> point;
        KDTreeNode* left, * right;

        KDTreeNode() : point(), left(NULL), right(NULL) {}

        KDTreeNode(const Point<Dim, V>& point) : point(point), left(NULL), right(NULL) {}

        bool isLeaf() const { return !left && !right; }
    };

public:
    /**
     * Determines if Point a is smaller than Point b in a given dimension d.
     * If there is a tie, break it with Point::operator<().
     *
     * For example:
     *
     *     Point<3> a(1, 2, 3);
     *     Point<3> b(3, 2, 1);
     *     cout << smallerDimVal(a, b, 0) << endl; // should print true
     *     cout << smallerDimVal(a, b, 2) << endl; // should print false
     *     cout << smallerDimVal(a, b, 1) << endl; // based on operator<, this should be true
     *
     * @param first Point to compare.
     * @param second Second point to compare.
     * @param curDim Dimension these points are being compared in.
     * @return A boolean value indicating whether the first Point is smaller
     *  than the second Point in the curDim dimension.
     */
    bool smallerDimVal(const Point<Dim, V>& first, const Point<Dim, V>& second,
                       int curDim) const;

    /**
     * Determines if a Point is closer to the target Point than another
     * reference Point. Takes three points: target, currentBest, and
     * potential, and returns whether or not potential is closer to
     * target than currentBest.
     *
     * We are using Euclidean distance to compare k-dimensional
     * points: \f$\sqrt{(p_1-q_1)^2+(p_2-q_2)^2+\ldots+(p_n-q_n)^2} =
     * \sqrt{\sum_{i=1}^n (p_i-q_i)^2}\f$. Note, however, that
     * **minimizing distance is the same as minimizing squared
     * distance**, so you can **avoid invoking the square root** and
     * just compare squared distances in your code.
     *
     * For example:
     *
     *     Point<3> target(1, 3, 5);
     *     Point<3> currentBest1(1, 3, 2);
     *     Point<3> possibleBest1(2, 4, 4);
     *     Point<3> currentBest2(1, 3, 6);
     *     Point<3> possibleBest2(2, 4, 4);
     *     Point<3> currentBest3(0, 2, 4);
     *     Point<3> possibleBest3(2, 4, 6);
     *     cout << shouldReplace(target, currentBest1, possibleBest1) << endl; // true
     *     cout << shouldReplace(target, currentBest2, possibleBest2) << endl; // false
     *     cout << shouldReplace(target, currentBest3, possibleBest3) << endl;
     *      // based on operator<, this should be false
     *
     * @param target The Point we want to be close to.
     * @param currentBest The Point that is currently our closest Point
     *    to target.
     * @param potential Our Point that is a candidate to replace
     *    currentBest (that is, it may be closer to target than
     *    currentBest).
     * @return A boolean value indicating whether potential is closer
     *  to target than currentBest. Ties should be broken with
     *  Point::operator<().
     */
    bool shouldReplace(const Point<Dim, V>& target, const Point<Dim, V>& currentBest,
                       const Point<Dim, V>& potential) const;

    /**
     * Constructs a KDTree from a vector of Points, each having dimension Dim.
     *
     * You need to handle the case that the vector has no Point in it. It should
     * build the tree using recursive helper functions.
     *
     * Since we know the size of the KDTree at construction, we can
     * represent the tree as a linear structure and building the tree nodes
     * based off this structure efficiently. For testing, we **require**
     * the following:
     *
     * 1.  The median node of n nodes is calculated as the cell
     *     \f$\left\lfloor\frac{n-1}{2}\right\rfloor\f$. That is, the
     *     middle node is selected if there are an odd number, and the
     *     item before the middle if there are an even number. **If there
     *     are ties (two points have equal value along a dimension), they
     *     must be decided using Point::operator<().** Although this is
     *     arbitrary and doesn't affect the functionality of the KDTree,
     *     it is required to be able to grade your code.
     *
     * KD-trees are created recursively; at any stage of the construction,
     * the median value in the current dimension is selected and a node is
     * created based on it. Then, all the elements in the current subtree are divided
     * up into elements which are less than the median, or greater than
     * the median, and then the subtrees are created recursively.
     * The children pick the median in the next dimension, and repeat
     * until the entire set of inputs has been processed. Successive
     * levels of the tree split on increasing dimensions, modulo the
     * total number: a 3D tree will have levels split by dimension 0, 1, 2,
     * 0, 1, 2, etc.
     *
     * You will probably want to write a helper function which performs the
     * median selection and partitioning. Maybe you can use a function you
     * already wrote...
     *
     * @see Here is a reference that should help you create concise,
     * efficient code: [Partition-based General Selection
     * Algorithm](http://en.wikipedia.org/wiki/Selection_algorithm). Note
     * that "select pivotIndex between left and right" means that you
     * should choose a midpoint between the left and right indices.
     *
     * @param newPoints The vector of points to build your KDTree off of.
     */
    KDTree(const vector<Point<Dim, V>>& newPoints);

    /**
     * Copy constructor for KDTree.
     *
     * @param other The KDTree to copy.
     */
    KDTree(const KDTree<Dim, V>& other);

    /**
     * Assignment operator for KDTree.
     *
     * @param rhs The right hand side of the assignment statement.
     * @return A reference for performing chained assignments.
     */
    KDTree const& operator=(const KDTree<Dim, V>& rhs);

    /**
     * Gets all points within a taxicab distance r2 of p.
     * @param p the center point
     * @param r2 the squared radius around the point to query
     * @return vector with the data of the found points
     */
    vector<V> rangeQuery(const Point<Dim, V>& p, double r2);

    /**
     * Destructor for KDTree.
     */
    ~KDTree();

private:

    /** Internal representation, root and size **/
    KDTreeNode* root;
    size_t size;

    /**
     * Recursively deep copies a k-d tree.
     * @param subroot node to start at
     * @return pointer to head of new tree
     */
    KDTreeNode* copyTree(KDTreeNode* subroot) const;

    /**
     * Recursively deletes a node and all children.
     */
    void clear(KDTreeNode* node);

    /**
     * Swaps index i and j of a vector of points.
     */
    void swap(vector<Point<Dim, V>>& points, int i, int j);

    /**
     * Lomuto partition scheme for a vector of points.
     * @return index of pivot in partitioned list
     */
    int partition(vector<Point<Dim, V>>& points, int left, int right, int pivotIndex, int d);

    /**
     * Gets median of list and partitions it along the median.
     * @return median point of list
     */
    Point<Dim, V> quickSelect(vector<Point<Dim, V>>& points, int left, int right, int k, int d);

    /**
     * Recursively builds a k-d tree from a list of points.
     * @param d splitting dimension
     * @return head of built k-d tree
     */
    KDTreeNode* buildTree(vector<Point<Dim, V>> points, int d);

    /**
     * Recursive helper function for rangeQuery
     * @param p the center point
     * @param r2 the squared radius around the point to query
     * @param n current splitting dimension
     * @param subroot current node
     * @return vector with the data of the found points
     */
    vector<V> rangeQuery(const Point<Dim, V>& p, double r2, int n, KDTree::KDTreeNode* subroot);
};

}
}

#include "kdtree.hpp"
