#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include<vector>
using namespace std;
// 队伍数据结构
struct Team {
    int id;               // 参赛队编号
    string work_name;     // 参赛作品名称
    string school;        // 参赛学校
    string match_sort;    // 赛事类别
    string player;        // 参赛者
    string teacher;       // 指导老师

    // 构造函数
    Team() {}
    Team(int id, string work_name, string school, string match_sort, string player, string teacher) :
        id(id), work_name(work_name), school(school), match_sort(match_sort), player(player), teacher(teacher) {}

};

struct Node {
    //string name;
    string category; // 赛事类别
    Node* left;
    Node* right;
};
// 二叉排序树节点
struct BSTNode {
    Team data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Team data) : data(data), left(nullptr), right(nullptr) {}
};

// 二叉排序树
class BST {
public:
    BSTNode* root;
    vector<BSTNode*> nodes; // 存储所有结点的指针
    // 构造函数和析构函数
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    // 插入结点
    bool insert(Team data) {
        if (find(data.id) != nullptr) {
            return false; // 结点已存在，插入失败
        }
        BSTNode* node = new BSTNode(data);
        nodes.push_back(node);
        if (root == nullptr) {
            root = node;
            return true;
        }
        else {
            BSTNode* p = root;
            while (true) {
                if (data.id < p->data.id) {
                    if (p->left == nullptr) {
                        p->left = node;
                        return true;
                    }
                    else {
                        p = p->left;
                    }
                }
                else {
                    if (p->right == nullptr) {
                        p->right = node;
                        return true;
                    }
                    else {
                        p = p->right;
                    }
                }
            }
        }
    }

    // 删除结点
    bool remove(int id) { return remove(root, id); }

    // 查找结点
    Team* find(int id) {
        BSTNode* p = root;
        while (p != nullptr) {
            if (p->data.id == id) {
                return &p->data;
            }
            else if (p->data.id > id) {
                p = p->left;
            }
            else {
                p = p->right;
            }
        }
        return nullptr;
    }
    // 中序遍历输出
    void inorderTraversal() { inorderTraversal(root); }

    // 归并排序
    void mergeSort() { mergeSort(root); }

private:
    // 销毁二叉排序树
    void destroy(BSTNode* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            node = nullptr;
        }
    }

    // 插入结点
    bool insert(BSTNode*& node, Team data) {
        if (node == nullptr) {
            node = new BSTNode(data);
            return true;
        }
        else if (node->data.id > data.id) {
            return insert(node->left, data);
        }
        else if (node->data.id < data.id) {
            return insert(node->right, data);
        }
        else {
            return false;
        }
    }

    // 删除结点
    bool remove(BSTNode*& node, int id) {
        if (node == nullptr) {
            return false;
        }
        else if (node->data.id > id) {
            return remove(node->left, id);
        }
        else if (node->data.id < id) {
            return remove(node->right, id);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) { // 叶子结点
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr) { // 只有右子树
                BSTNode* temp = node;
                node = node->right;
                delete temp;
                temp = nullptr;
            }
            else if (node->right == nullptr) { // 只有左子树
                BSTNode* temp = node;
                node = node->left;
                delete temp;
                temp = nullptr;
            }
            else { // 左右子树都存在
                BSTNode* min_right = node->right; // 找到右子树最小结点
                while (min_right->left != nullptr) {
                    min_right = min_right->left;
                }
                node->data = min_right->data; // 用右子树最小值替换要删除的结点
                remove(node->right, min_right->data.id); // 删除右子树最小结点
            }
            return true;
        }
    }

    // 查找结点
    Team* find(BSTNode* node, int id) {
        if (node == nullptr) {
            return nullptr;
        }
        else if (node->data.id > id) {
            return find(node->left, id);
        }
        else if (node->data.id < id) {
            return find(node->right, id);
        }
        else {
            return &node->data;
        }
    }

    // 中序遍历输出
    void inorderTraversal(BSTNode* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data.id << " " << node->data.work_name << " " << node->data.school << " " << node->data.match_sort << " " << node->data.player << " " << node->data.teacher << endl;
            inorderTraversal(node->right);
        }
    }

    // 归并排序
    void mergeSort(BSTNode*& node) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
            return;
        }
        BSTNode* left = node->left;
        BSTNode* right = node->right;
        mergeSort(left);
        mergeSort(right);
        node->left = nullptr;
        node->right = nullptr;
        node = merge(node, left, right);
    }

    // 合并两个已排好序的二叉树
    BSTNode* merge(BSTNode* parent, BSTNode* left, BSTNode* right) {
        if (left == nullptr) {
            return right;
        }
        else if (right == nullptr) {
            return left;
        }
        else if (left->data.match_sort <= right->data.match_sort) {
            left->right = merge(parent, left->right, right);
            return left;
        }
        else {
            right->left = merge(parent, left, right->left);
            return right;
        }
    }

};

// 根据赛事类别查询参赛团队
vector<Team> searchByCategory(BST& bst, string category) {
    vector<Team> result;
    for (int i = 0; i < bst.nodes.size(); i++) {
        if (bst.nodes[i]->data.match_sort == category) {
            result.push_back(bst.nodes[i]->data);
        }
    }
    return result;
}
// 查找结果结构体
struct SearchResult {
    Team* data;
    int depth; // 结点深度
    int path_length; // 到达该结点的路径长度
    double asl; // 平均查找长度ASL
};

// 查找类
class Search {
public:
    Search(BSTNode* root) : root(root), total_nodes(0), sum_depth(0) {
        countNodes(root);
        asl = (double)sum_depth / total_nodes;
    }

    // 查找操作
    SearchResult search(int id) {
        SearchResult result = { nullptr, 0, 0, asl };
        BSTNode* node = root;
        int depth = 1;
        int path_length = 0;
        while (node != nullptr) {
            if (node->data.id == id) {
                result.data = &node->data;
                result.depth = depth;
                result.path_length = path_length;
                break;
            }
            else if (node->data.id > id) {
                node = node->left;
                depth++;
                path_length++;
            }
            else {
                node = node->right;
                depth++;
                path_length++;
            }
        }
        return result;
    }

private:
    BSTNode* root;
    int total_nodes; // 总结点数
    int sum_depth; // 所有结点深度之和
    double asl; // 平均查找长度ASL

    // 计算总结点数和所有结点深度之和
    void countNodes(BSTNode* node) {
        if (node != nullptr) {
            countNodes(node->left);
            total_nodes++;
            sum_depth += getDepth(root, node->data.id);
            countNodes(node->right);
        }
    }

    // 计算结点深度
    int getDepth(BSTNode* node, int id) {
        if (node == nullptr) {
            return 0;
        }
        else if (node->data.id > id) {
            return getDepth(node->left, id) + 1;
        }
        else if (node->data.id < id) {
            return getDepth(node->right, id) + 1;
        }
        else {
            return 1;
        }
    }
};

// 从文件中读取参赛队伍信息并构建二叉排序树

void buildBST(BST& bst) {
    ifstream fin("team.txt");
    if (!fin.is_open()) {
        cout << "文件打开失败！" << endl;
        return;
    }
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        int id;
        string work_name;
        string school;
        string match_sort;
        string player;
        string teacher;
        stringstream ss(line);
        ss >> id;
        getline(ss, work_name, '#');
        getline(ss, work_name, '#');
        getline(ss, school, '#');
        getline(ss, match_sort, '#');
        getline(ss, player, '#');
        getline(ss, teacher, '#');
        Team team(id, work_name, school, match_sort, player, teacher);
        bst.insert(team);
    }
    fin.close();
}

// 将参赛队伍信息写入文件
void writeToFile(BSTNode* node, ofstream& fout) {
    if (node != nullptr) {
        fout << node->data.id << '#' << node->data.work_name << '#' << node->data.school << '#'
            << node->data.match_sort << '#' << node->data.player << '#' << node->data.teacher << '\n';
        writeToFile(node->left, fout);
        writeToFile(node->right, fout);
    }
}
int operate() {
    BST bst;
    buildBST(bst);
    int choice = 0;
    while (true) {
        cout << "请输入您的选择（1:插入；2:删除；3:搜索；4:退出）: ";
        cin >> choice;
        if (choice == 1) { // 插入队伍
            string work_name;
            string school;
            string match_sort;
            string player;
            string teacher;
            cout << "请输入你想要插入的队伍编号: ";
            int id;
            cin >> id;
            if (bst.find(id) != nullptr) {
                cout << "队伍已存在！" << endl;
            }
            else {
                cout << "请输入赛事作品名称: ";
                cin >> work_name;
                cout << "请输入参赛学校: ";
                cin >> school;
                cout << "请输入赛事类别: ";
                cin >> match_sort;
                cout << "请输入参赛者: ";
                cin >> player;
                cout << "请输入指导教师: ";
                cin >> teacher;
                Team team(id, work_name, school, match_sort, player, teacher);
                bst.insert(team);

                // 将新增的队伍信息写入到文件末尾
                ofstream fout("team.txt", ios::app);
                if (!fout.is_open()) {
                    cout << "打开文件失败！" << endl;
                    return 0;
                }
                fout << id << '#' << work_name << '#' << school << '#' << match_sort << '#' << player << '#' << teacher << '\n';
                fout.close();

                cout << "插入成功！" << endl;
            }
        }

        else if (choice == 2) { // 删除队伍
            cout << "请输入你想要删除的队伍编号: ";
            int id;
            cin >> id;
            if (bst.remove(id)) {

                // 将修改后的队伍信息写回到文件中
                ofstream fout("team.txt");
                if (!fout.is_open()) {
                    cout << "打开文件失败！" << endl;
                    return 0;
                }
                writeToFile(bst.root, fout);
                fout.close();

                cout << "删除成功！" << endl;
            }
            else {
                cout << "未找到队伍！" << endl;
            }
        }
        else if (choice == 3) { // 查询队伍
            cout << "请输入你要查找的队伍编号: ";
            int id;
            cin >> id;
            SearchResult result = Search(bst.root).search(id);
            if (result.data == nullptr) {
                cout << "未找到队伍！" << endl;
            }
            else {
                cout << "---------------------------------------------------------------------" << endl;
                cout << "参赛作品名称: " << result.data->work_name << endl;
                cout << "参赛学校: " << result.data->school << endl;
                cout << "赛事类别: " << result.data->match_sort << endl;
                cout << "参赛者: " << result.data->player << endl << "指导教师: " << result.data->teacher << endl;

                cout << "Average Search Length: " << result.asl << endl;
                cout << "---------------------------------------------------------------------" << endl;
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "无效选项！" << endl;
        }
    }
}

int category_search() {
    // 构建二叉排序树
    BST bst;
    buildBST(bst);

    // 归并排序并输出结果
    bst.mergeSort();

    while (true) {
        string category;
        cout << "请输入要查询的赛事类别(输入quit退出)：";
        cin >> category;
        vector<Team> result = searchByCategory(bst, category);
        if (category == "quit") {
            return 0;
        }
        if (result.empty()) {
            cout << "没有找到符合条件的参赛团队！";
        }
        else{
            cout << "符合条件的参赛团队如下：" << endl;
            for (int i = 0; i < result.size(); i++) {
                cout << "---------------------------------------------------------------------" << endl;
                cout << "参赛作品名称: " << result[i].work_name << endl;
                cout << "参赛学校: " << result[i].school << endl;
                cout << "赛事类别: " << result[i].match_sort << endl;
                cout << "参赛者: " << result[i].player << endl << "指导教师: " << result[i].teacher << endl;
                cout << "---------------------------------------------------------------------" << endl;
            }
        }
    }
}

int main() {
    int choice;
    cout << "请输入想要实现的功能(1:参赛队伍管理 2:按赛事类别查找队伍):";
    cin >> choice;
    if (choice == 1) {
        operate();
    }
    else if (choice == 2) {
        category_search();
    }
    else {
        cout << "输入无效!";
    }
    system("pause");
    return 0;
}