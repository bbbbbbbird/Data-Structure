#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include<vector>
using namespace std;
// �������ݽṹ
struct Team {
    int id;               // �����ӱ��
    string work_name;     // ������Ʒ����
    string school;        // ����ѧУ
    string match_sort;    // �������
    string player;        // ������
    string teacher;       // ָ����ʦ

    // ���캯��
    Team() {}
    Team(int id, string work_name, string school, string match_sort, string player, string teacher) :
        id(id), work_name(work_name), school(school), match_sort(match_sort), player(player), teacher(teacher) {}

};

struct Node {
    //string name;
    string category; // �������
    Node* left;
    Node* right;
};
// �����������ڵ�
struct BSTNode {
    Team data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Team data) : data(data), left(nullptr), right(nullptr) {}
};

// ����������
class BST {
public:
    BSTNode* root;
    vector<BSTNode*> nodes; // �洢���н���ָ��
    // ���캯������������
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    // ������
    bool insert(Team data) {
        if (find(data.id) != nullptr) {
            return false; // ����Ѵ��ڣ�����ʧ��
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

    // ɾ�����
    bool remove(int id) { return remove(root, id); }

    // ���ҽ��
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
    // ����������
    void inorderTraversal() { inorderTraversal(root); }

    // �鲢����
    void mergeSort() { mergeSort(root); }

private:
    // ���ٶ���������
    void destroy(BSTNode* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
            node = nullptr;
        }
    }

    // ������
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

    // ɾ�����
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
            if (node->left == nullptr && node->right == nullptr) { // Ҷ�ӽ��
                delete node;
                node = nullptr;
            }
            else if (node->left == nullptr) { // ֻ��������
                BSTNode* temp = node;
                node = node->right;
                delete temp;
                temp = nullptr;
            }
            else if (node->right == nullptr) { // ֻ��������
                BSTNode* temp = node;
                node = node->left;
                delete temp;
                temp = nullptr;
            }
            else { // ��������������
                BSTNode* min_right = node->right; // �ҵ���������С���
                while (min_right->left != nullptr) {
                    min_right = min_right->left;
                }
                node->data = min_right->data; // ����������Сֵ�滻Ҫɾ���Ľ��
                remove(node->right, min_right->data.id); // ɾ����������С���
            }
            return true;
        }
    }

    // ���ҽ��
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

    // ����������
    void inorderTraversal(BSTNode* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data.id << " " << node->data.work_name << " " << node->data.school << " " << node->data.match_sort << " " << node->data.player << " " << node->data.teacher << endl;
            inorderTraversal(node->right);
        }
    }

    // �鲢����
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

    // �ϲ��������ź���Ķ�����
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

// ������������ѯ�����Ŷ�
vector<Team> searchByCategory(BST& bst, string category) {
    vector<Team> result;
    for (int i = 0; i < bst.nodes.size(); i++) {
        if (bst.nodes[i]->data.match_sort == category) {
            result.push_back(bst.nodes[i]->data);
        }
    }
    return result;
}
// ���ҽ���ṹ��
struct SearchResult {
    Team* data;
    int depth; // ������
    int path_length; // ����ý���·������
    double asl; // ƽ�����ҳ���ASL
};

// ������
class Search {
public:
    Search(BSTNode* root) : root(root), total_nodes(0), sum_depth(0) {
        countNodes(root);
        asl = (double)sum_depth / total_nodes;
    }

    // ���Ҳ���
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
    int total_nodes; // �ܽ����
    int sum_depth; // ���н�����֮��
    double asl; // ƽ�����ҳ���ASL

    // �����ܽ���������н�����֮��
    void countNodes(BSTNode* node) {
        if (node != nullptr) {
            countNodes(node->left);
            total_nodes++;
            sum_depth += getDepth(root, node->data.id);
            countNodes(node->right);
        }
    }

    // ���������
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

// ���ļ��ж�ȡ����������Ϣ����������������

void buildBST(BST& bst) {
    ifstream fin("team.txt");
    if (!fin.is_open()) {
        cout << "�ļ���ʧ�ܣ�" << endl;
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

// ������������Ϣд���ļ�
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
        cout << "����������ѡ��1:���룻2:ɾ����3:������4:�˳���: ";
        cin >> choice;
        if (choice == 1) { // �������
            string work_name;
            string school;
            string match_sort;
            string player;
            string teacher;
            cout << "����������Ҫ����Ķ�����: ";
            int id;
            cin >> id;
            if (bst.find(id) != nullptr) {
                cout << "�����Ѵ��ڣ�" << endl;
            }
            else {
                cout << "������������Ʒ����: ";
                cin >> work_name;
                cout << "���������ѧУ: ";
                cin >> school;
                cout << "�������������: ";
                cin >> match_sort;
                cout << "�����������: ";
                cin >> player;
                cout << "������ָ����ʦ: ";
                cin >> teacher;
                Team team(id, work_name, school, match_sort, player, teacher);
                bst.insert(team);

                // �������Ķ�����Ϣд�뵽�ļ�ĩβ
                ofstream fout("team.txt", ios::app);
                if (!fout.is_open()) {
                    cout << "���ļ�ʧ�ܣ�" << endl;
                    return 0;
                }
                fout << id << '#' << work_name << '#' << school << '#' << match_sort << '#' << player << '#' << teacher << '\n';
                fout.close();

                cout << "����ɹ���" << endl;
            }
        }

        else if (choice == 2) { // ɾ������
            cout << "����������Ҫɾ���Ķ�����: ";
            int id;
            cin >> id;
            if (bst.remove(id)) {

                // ���޸ĺ�Ķ�����Ϣд�ص��ļ���
                ofstream fout("team.txt");
                if (!fout.is_open()) {
                    cout << "���ļ�ʧ�ܣ�" << endl;
                    return 0;
                }
                writeToFile(bst.root, fout);
                fout.close();

                cout << "ɾ���ɹ���" << endl;
            }
            else {
                cout << "δ�ҵ����飡" << endl;
            }
        }
        else if (choice == 3) { // ��ѯ����
            cout << "��������Ҫ���ҵĶ�����: ";
            int id;
            cin >> id;
            SearchResult result = Search(bst.root).search(id);
            if (result.data == nullptr) {
                cout << "δ�ҵ����飡" << endl;
            }
            else {
                cout << "---------------------------------------------------------------------" << endl;
                cout << "������Ʒ����: " << result.data->work_name << endl;
                cout << "����ѧУ: " << result.data->school << endl;
                cout << "�������: " << result.data->match_sort << endl;
                cout << "������: " << result.data->player << endl << "ָ����ʦ: " << result.data->teacher << endl;

                cout << "Average Search Length: " << result.asl << endl;
                cout << "---------------------------------------------------------------------" << endl;
            }
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "��Чѡ�" << endl;
        }
    }
}

int category_search() {
    // ��������������
    BST bst;
    buildBST(bst);

    // �鲢����������
    bst.mergeSort();

    while (true) {
        string category;
        cout << "������Ҫ��ѯ���������(����quit�˳�)��";
        cin >> category;
        vector<Team> result = searchByCategory(bst, category);
        if (category == "quit") {
            return 0;
        }
        if (result.empty()) {
            cout << "û���ҵ����������Ĳ����Ŷӣ�";
        }
        else{
            cout << "���������Ĳ����Ŷ����£�" << endl;
            for (int i = 0; i < result.size(); i++) {
                cout << "---------------------------------------------------------------------" << endl;
                cout << "������Ʒ����: " << result[i].work_name << endl;
                cout << "����ѧУ: " << result[i].school << endl;
                cout << "�������: " << result[i].match_sort << endl;
                cout << "������: " << result[i].player << endl << "ָ����ʦ: " << result[i].teacher << endl;
                cout << "---------------------------------------------------------------------" << endl;
            }
        }
    }
}

int main() {
    int choice;
    cout << "��������Ҫʵ�ֵĹ���(1:����������� 2:�����������Ҷ���):";
    cin >> choice;
    if (choice == 1) {
        operate();
    }
    else if (choice == 2) {
        category_search();
    }
    else {
        cout << "������Ч!";
    }
    system("pause");
    return 0;
}