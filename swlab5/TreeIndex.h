// TreeIndex.h

#ifndef TREEINDEX_H
#define TREEINDEX_H

#include "VectorDataset.h"
#include "DataVector.h"
#include <vector>

class TreeNode
{
public:
    vector<int> indexes;
    TreeNode *left;
    TreeNode *right;
    DataVector axis;
    double median;
    TreeNode();
    TreeNode(vector<int> indexes);
    ~TreeNode();
    void AssignIndexes();
};
class TreeIndex
{
protected:
    TreeIndex();
    static VectorDataset Space;
    virtual ~TreeIndex();

public:
    TreeNode *root;
    static VectorDataset &GetDataset();
    static int GetDatasetSize();
    static int GetDatasetDimension();
    static void AssignDataset(VectorDataset &dataset);
    static TreeIndex &GetInstance();
    void AddDataHelper(const DataVector &data);
    void RemoveDataHelper(const DataVector &data);
    void SearchHelper(int k, DataVector &query, TreeNode *root, vector<pair<double, int>> &result);
};

class KDTreeIndex : public TreeIndex
{
public:
    static KDTreeIndex &GetInstance();
    void printKDTreeIndex();
    TreeNode *MakeTree(TreeNode *root);
    vector<vector<int>> ChooseRule(TreeNode *root);
    bool Search(DataVector &query, int k, TreeNode *root, vector<pair<double, int>> &result);
    ~KDTreeIndex();
    // function to print KDTreeINdex
    void printKDTreeIndex(TreeNode *root);
    void AddDate(const DataVector &data);
    void RemoveDate(const DataVector &data);

private:
    KDTreeIndex();
};

class RPTreeIndex : public TreeIndex
{
public:
    static RPTreeIndex &GetInstance();
    void printRPTreeIndex();
    TreeNode *MakeTree(TreeNode *root);
    bool Search(DataVector &query, int k, TreeNode *root, vector<pair<double, int>> &result);
    ~RPTreeIndex();
    vector<vector<int>> ChooseRule(TreeNode *root);
    // function to print RPTreeIndex
    void printRPTreeIndex(TreeNode *root);
    void AddDate(const DataVector &data);
    void RemoveDate(const DataVector &data);

private:
    RPTreeIndex();
};

#endif // TREEINDEX_H