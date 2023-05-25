#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<sstream>
using namespace std;

struct Team {
    int id;
    string work_name;
    string school;
    string match_sort;
    string player;
    string teacher;
    Team(int id, string work_name, string school, string match_sort, string player, string teacher) :id(id),work_name(work_name),school(school),match_sort(match_sort),player(player),teacher(teacher){}
};

struct BSTNode {
    Team data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Team data) : data(data), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST() : root(nullptr) {}

    void insert(Team data) {
        root = insertNode(root, data);
    }

    void remove(Team data) {
        root = removeNode(root, data);
    }

    bool search(Team data) {
        return searchNode(root, data);
    }

private:
    BSTNode* root;

    BSTNode* insertNode(BSTNode* node, Team data) {
        if (node == nullptr) {
            node = new BSTNode(data);
        }
        else if (data.id < node->data.id) {
            node->left = insertNode(node->left, data);
        }
        else if (data.id > node->data.id) {
            node->right = insertNode(node->right, data);
        }
        return node;
    }

    BSTNode* removeNode(BSTNode* node, Team data) {
        if (node == nullptr) {
            return node;
        }
        if (data.id < node->data.id) {
            node->left = removeNode(node->left, data);
        }
        else if (data.id > node->data.id) {
            node->right = removeNode(node->right, data);
        }
        else {
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            BSTNode* temp = findMinNode(node->right);
            node->data = temp->data;
            node->right = removeNode(node->right, temp->data);
        }
        return node;
    }

    bool searchNode(BSTNode* node, Team data) {
        if (node == nullptr) {
            return false;
        }
        if (data.id < node->data.id) {
            return searchNode(node->left, data);
        }
        else if (data.id > node->data.id) {
            return searchNode(node->right, data);
        }
        else {
            return true;
        }
    }

    BSTNode* findMinNode(BSTNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};

int main() {
    ifstream file("team.txt"); // 打开team.txt
    if (!file) { // 判断文件是否打开成功
        cout << "Error: Could not open the file." << endl;
        return 1;
    }

    // 建立二叉排序树，并从文件中读取信息来初始化树
    BST bst;
    string line;
    while (getline(file, line)) {
        stringstream ss(line); // 定义字符串流，将读入的字符串输入
        int id;
        string work_name, school, match_sort, player, teacher;
        ss >> id >> work_name >> school >> match_sort >> player >> teacher; // 将读入的字符串分别赋值给不同的变量
        Team team(id, work_name, school, match_sort, player, teacher); // 将变量组合成Team对象
        bst.insert(team); // 将Team对象插入二叉排序树中
    }

    file.close(); // 关闭文件

    // 测试插入、删除、查找操作
    Team team1(1, "work_name1", "school1", "match_sort1", "player1", "teacher1");
    bst.insert(team1);
    Team team2(2, "work_name2", "school2", "match_sort2", "player2", "teacher2");
    bst.insert(team2);
    Team team3(3, "work_name3", "school3", "match_sort3", "player3", "teacher3");
    bst.insert(team3);
    bst.remove(team2);
    bool isExist = bst.search(team1);

    system("pause");
    return 0;
}
