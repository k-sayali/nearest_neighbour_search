#ifndef TREEINDEX_H
#define TREEINDEX_H

#include "VectorDataset.h"
#include "DataVector.h"
#include<vector>

class TreeIndex{

};
class KDTreeIndex : public TreeIndex{
    public:
    static KDTreeIndex &GetInstance()
}