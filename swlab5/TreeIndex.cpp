// TreeIndex.cpp

#include "TreeIndex.h"
#include <bits/stdc++.h>

// TreeNode constructor
TreeNode::TreeNode()
{
    left = NULL;
    right = NULL;
    axis.AssignVector({0});
    median = 0;
}

// TreeNode destructor
TreeNode::~TreeNode()
{
    if (left != NULL)
        delete left;
    if (right != NULL)
        delete right;
}

// TreeIndex Constructor function
TreeIndex::TreeIndex()
{
    root = NULL;
}
// TreeIndex Destructor function
TreeIndex::~TreeIndex()
{
    if (root != NULL)
        delete root;
}

// TreeIndex GetInstance function
TreeIndex &TreeIndex::GetInstance()
{
    static TreeIndex treeIndex;
    return treeIndex;
}

// AddData function

void TreeIndex::AddDataHelper(const DataVector &data)
{
    TreeIndex::Space.getDataset().push_back(data);
}

// RemoveData function
void TreeIndex::RemoveDataHelper(const DataVector &data)
{
    for (int i = 0; i < TreeIndex::GetDatasetSize(); i++)
    {
        if (TreeIndex::Space.getDatavector(i) == data)
        {
            TreeIndex::Space.getDataset().erase(TreeIndex::Space.getDataset().begin() + i);
            break;
        }
    }
}

// AssignDataset function
void TreeIndex::AssignDataset(VectorDataset &dataset)
{
    TreeIndex::Space = dataset;
}

// AssignIndexes function
void TreeNode::AssignIndexes()
{
    indexes.resize(TreeIndex::GetDatasetSize());
    for (int i = 0; i < TreeIndex::GetDatasetSize(); i++)
    {
        indexes[i] = i;
    }
}

// GetDataset function
VectorDataset &TreeIndex::GetDataset()
{
    return TreeIndex::Space;
}

// GetDatasetSize function
int TreeIndex::GetDatasetSize()
{
    return TreeIndex::Space.getDataset().size();
}

// GetDatasetDimension function
int TreeIndex::GetDatasetDimension()
{
    return TreeIndex::Space.getDataset()[0].getDimension();
}
// KDTreeIndex GetInstance function
KDTreeIndex &KDTreeIndex::GetInstance()
{
    static KDTreeIndex kdTreeIndex;
    return kdTreeIndex;
}

// KDTreeIndex constructor function
KDTreeIndex::KDTreeIndex()
{
    root = new TreeNode();
    root->AssignIndexes();
    cout << "Making Tree\n";
    root = MakeTree(root);
}

// KDTreeIndex destructor function
KDTreeIndex::~KDTreeIndex()
{
}

// AddDate for KDTree
void KDTreeIndex::AddDate(const DataVector &data)
{
    TreeIndex::AddDataHelper(data);
    AssignDataset(GetDataset());
    root = MakeTree(root);
}
// RemoveDate for KDTree
void KDTreeIndex::RemoveDate(const DataVector &data)
{
    TreeIndex::RemoveDataHelper(data);
    root = MakeTree(root);
}
// RPTreeIndex GetInstance function
RPTreeIndex &RPTreeIndex::GetInstance()
{
    static RPTreeIndex rpTreeIndex;
    return rpTreeIndex;
}

// RPTreeIndex constructor function
RPTreeIndex::RPTreeIndex()
{
    root = new TreeNode();
    root->AssignIndexes();
    cout << "Making Tree\n";
    root = MakeTree(root);
}

// RPTreeIndex destructor function
RPTreeIndex::~RPTreeIndex()
{
}

// AddDate for RPTree
void RPTreeIndex::AddDate(const DataVector &data)
{
    TreeIndex::AddDataHelper(data);
    AssignDataset(GetDataset());
    root = MakeTree(root);
}

// RemoveDate for RPTree
void RPTreeIndex::RemoveDate(const DataVector &data)
{
    TreeIndex::RemoveDataHelper(data);
    root = MakeTree(root);
}

// ChooseRule function for KDTreeIndex
vector<vector<int>> KDTreeIndex::ChooseRule(TreeNode *root)
{
    vector<pair<double, int>> temp;

    for (auto ind : root->indexes)
    {
        temp.push_back({TreeIndex::Space.getDatavector(ind).getVector()[root->axis.getVector()[0]], ind});
    }
    // sort temp vector in the ascending order of the first element
    sort(temp.begin(), temp.end());
    // median is the middle element of the sorted vector
    root->median = temp[temp.size() / 2].first;
    // left and right vector dataset
    vector<int> left, right;
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i].first <= root->median)
        {
            left.push_back(temp[i].second);
        }
        else
        {
            right.push_back(temp[i].second);
        }
    }
    return {left, right};
}
// MakeTree function for KDTreeIndex
TreeNode *KDTreeIndex::MakeTree(TreeNode *root)
{
    if (root->indexes.size() <= 50)
    {
        return root;
    }

    vector<vector<int>> left_right = KDTreeIndex::ChooseRule(root);
    TreeNode *_right = new TreeNode();
    TreeNode *_left = new TreeNode();

    _left->indexes = left_right[0];
    _right->indexes = left_right[1];

    double right_axis = (static_cast<int>(root->axis.getVector()[0]) + 1) % TreeIndex::GetDatasetDimension();
    double left_axis = (static_cast<int>(root->axis.getVector()[0]) + 1) % TreeIndex::GetDatasetDimension();

    _left->axis.AssignVector({left_axis});
    _right->axis.AssignVector({right_axis});

    root->left = MakeTree(_left);
    root->right = MakeTree(_right);

    return root;
}

// Print function for KDTreeIndex
void KDTreeIndex::printKDTreeIndex(TreeNode *root)
{
    cout << "Printing TreeIndex\n";

    for (int i = 0; i < root->indexes.size(); i++)
    {
        cout << TreeIndex::Space.getDatavector(root->indexes[i]);
        cout << endl;
    }
    cout << "Median " << root->median << endl;
    cout << "Axis " << root->axis << endl;
    if (root->left != NULL)
    {
        printKDTreeIndex(root->left);
    }
    if (root->right != NULL)
    {
        printKDTreeIndex(root->right);
    }
}
// SearchHelper function for TreeIndex
void TreeIndex::SearchHelper(int k, DataVector &query, TreeNode *root, vector<pair<double, int>> &result)
{
    priority_queue<pair<double, int>> pq(result.begin(), result.end());
    for (auto index : root->indexes)
    {
        if (query == TreeIndex::Space.getDatavector(index))
            continue;
        double dist = query.dist(TreeIndex::Space.getDatavector(index));
        if (pq.size() < k)
        {
            pq.push({dist, index});
        }
        else
        {
            if (pq.top().first > dist)
            {
                pq.pop();
                pq.push({dist, index});
            }
        }
    }
    result.clear();
    while (!pq.empty())
    {
        result.push_back(pq.top());
        pq.pop();
    }
    // Successfully populated the result vector
}

// Search function for KDTreeIndex
bool KDTreeIndex::Search(DataVector &query, int k, TreeNode *root, vector<pair<double, int>> &result)
{
    if (root == NULL)
        return false;
    if (root->indexes.size() <= 50)
    {
        this->TreeIndex::SearchHelper(k, query, root, result);
        return false;
    }
    else
    {
        if (query.getVector()[root->axis.getVector()[0]] <= root->median)
        {
            if (Search(query, k, root->left, result))
                return true;
            if (result.size() == k && abs(query.getVector()[root->axis.getVector()[0]] - root->median) > result[0].first)
            {
                return true;
            }
            else
            {
                TreeIndex::SearchHelper(k, query, root->right, result);
                return false;
            }
        }
        else
        {
            if (Search(query, k, root->right, result))
                return true;
            if (result.size() == k && abs(query.getVector()[root->axis.getVector()[0]] - root->median) > result[0].first)
            {
                return true;
            }
            else
            {
                TreeIndex::SearchHelper(k, query, root->left, result);
                return false;
            }
        }
    }
}

// ChooseRule function for RPTreeIndex
vector<vector<int>> RPTreeIndex::ChooseRule(TreeNode *root)
{
    // random unit vector
    vector<double> unit_;
    for (int i = 0; i < GetDatasetDimension(); i++)
    {
        double index = rand();
        unit_.push_back(index);
    }

    DataVector unit_vector(0);
    unit_vector.AssignVector(unit_);

    double norm = unit_vector.norm();
    for (int i = 0; i < unit_.size(); i++)
    {
        unit_[i] /= norm;
    }
    root->axis.AssignVector(unit_);

    int t = rand() % root->indexes.size();
    int random_data_vector_index = root->indexes[t];
    DataVector random_vector = TreeIndex::Space.getDatavector(random_data_vector_index);

    // find the farthest DataVector from the random_vector in the dataset
    double max_dist = 0;
    int farthest_index = 0;
    for (int i = 0; i < root->indexes.size(); i++)
    {
        double dist = random_vector.dist(TreeIndex::Space.getDatavector(root->indexes[i]));
        if (dist > max_dist)
        {
            max_dist = dist;
            farthest_index = i;
        }
    }


    static std::random_device rd;
    static std::mt19937 rng(rd()); // Mersenne Twister engine
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    double delta = distribution(rng);
    delta *= (0.06) * max_dist / sqrt(TreeIndex::GetDatasetDimension());

    vector<pair<double, int>> temp;
    for (int i = 0; i < root->indexes.size(); i++)
    {
        temp.push_back({TreeIndex::Space.getDatavector(root->indexes[i]) * root->axis, root->indexes[i]});
    }

    sort(temp.begin(), temp.end());
    root->median = temp[temp.size() / 2].first + delta;
    vector<int> left, right;
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i].first <= root->median)
        {
            left.push_back({temp[i].second});
        }
        else
        {
            right.push_back({temp[i].second});
        }
    }
    return {left, right};
}

// MakeTree function for RPTreeIndex
TreeNode *RPTreeIndex::MakeTree(TreeNode *root)
{
    if (root->indexes.size() <= 50)
    {
        return root;
    }
    vector<vector<int>> left_right = RPTreeIndex::ChooseRule(root);

    TreeNode *_right = new TreeNode();
    TreeNode *_left = new TreeNode();

    _left->indexes = left_right[0];
    _right->indexes = left_right[1];

    root->left = MakeTree(_left);
    root->right = MakeTree(_right);
    return root;
}

// Print function for RPTreeIndex
void RPTreeIndex::printRPTreeIndex(TreeNode *root)
{
    cout << "Printing TreeIndex\n";
    for (auto ind : root->indexes)
    {
        cout << TreeIndex::Space.getDatavector(ind);
        cout << endl;
    }
    cout << "Median " << root->median << endl;
    cout << "Axis " << root->axis << endl;
    if (root->left != NULL)
    {
        printRPTreeIndex(root->left);
    }
    if (root->right != NULL)
    {
        printRPTreeIndex(root->right);
    }
}

// Search function for RPTreeIndex
bool RPTreeIndex::Search(DataVector &query, int k, TreeNode *root, vector<pair<double, int>> &result)
{

    if (root == NULL)
        return false;
    if (root->indexes.size() <= 50)
    {
        this->TreeIndex::SearchHelper(k, query, root, result);
        return false;
    }
    else
    {

        if (query * root->axis <= root->median)
        {
            if (Search(query, k, root->left, result))
                return true;
            if (result.size() == k && abs(query * root->axis - root->median) > result[0].first)
            {
                return true;
            }
            else
            {
                TreeIndex::SearchHelper(k, query, root->right, result);
                return false;
            }
        }
        else
        {
            if (Search(query, k, root->right, result))
                return true;
            if (result.size() == k && abs(query * root->axis - root->median) > result[0].first)
            {
                return true;
            }
            else
            {
                TreeIndex::SearchHelper(k, query, root->left, result);
                return false;
            }
        }
    }
}