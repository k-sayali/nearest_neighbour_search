#include <bits/stdc++.h>
#include "TreeIndex.h"
using namespace std;

VectorDataset TreeIndex::Space = VectorDataset(0);
int main()
{

    string filename = "fmnist-train.csv";
    // cout << "Enter the dataset file name: ";
    // cin >> filename;

    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "File not found!" << endl;
        return 0;
    }

    int dataSize;
    cout << "Enter the dataset size: ";
    cin >> dataSize;

    VectorDataset Dataset(dataSize);
    Dataset.ReadDataset(filename);
    TreeIndex::AssignDataset(Dataset);
    // close file
    file.close();

    filename = "fmnist-test.csv";

    ifstream file2(filename);
    if (!file2.is_open())
    {
        cout << "File not found!" << endl;
        return 0;
    }
    VectorDataset QueryDataset(10000);
    QueryDataset.ReadDataset(filename);
    // close fileQueryDataset
    file2.close();

    while (1)
    {
        int choice;
        cout << "Enter 1 to search : ";
        cin >> choice;
        if (choice == 1)
        {
            int n;
            cout << "Enter 1 for KDTreeIndex and 2 for RPTreeIndex: ";
            cin >> n;
            if (n == 1)
            {
                KDTreeIndex &kdtree = KDTreeIndex::GetInstance();
                // take index for seach
                int index;
                cout << "Enter the index for search: ";
                cin >> index;
                DataVector query = QueryDataset.getDatavector(index);
                int k;
                cout << "Enter the value of k: ";
                cin >> k;
                vector<pair<double, int>> result;
                kdtree.Search(query, k, kdtree.root, result);
                cout << "The " << k << " nearest neighbours are: " << endl;
                for (int i = k - 1; i >= 0; i--)
                {
                    cout << "Index: " << result[i].second << " Distance: " << result[i].first << endl;
                }
            }
            else if (n == 2)
            {
                RPTreeIndex &rptree = RPTreeIndex::GetInstance();
                // take index for seach
                int index;
                cout << "Enter the index for search: ";
                cin >> index;
                DataVector query = QueryDataset.getDatavector(index);
                int k;
                cout << "Enter the value of k: ";
                cin >> k;
                vector<pair<double, int>> result;
                rptree.Search(query, k, rptree.root, result);
                cout << "The " << k << " nearest neighbours are: " << endl;
                for (int i = k - 1; i >= 0; i--)
                {
                    cout << "Index: " << result[i].second << " Distance: " << result[i].first << endl;
                }
            }
            else
            {
                cout << "Invalid choice" << endl;
            }
        }
        else
        {
            break;
        }
    }

    cout << "Exiting..." << endl;

    exit(0);
}