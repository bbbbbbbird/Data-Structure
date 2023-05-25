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
    Team(int id, string work_name, string school, string match_sort, string player, string teacher) {}
};
struct BSTNode {
    Team data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Team data) : data(data), left(nullptr), right(nullptr) {}
};
int main() {
    ifstream file("team.txt"); // 打开team.txt
    if (!file) { // 判断文件是否打开成功
        cout << "Error: Could not open the file." << endl;
        return 1;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line); // 定义字符串流并将读入的字符串传入
        string temp;
        while (ss >> temp) { // 从字符串流中逐个读出去掉空格的字符串
            cout << temp;
        }
        cout << endl;
    }

    file.close(); // 关闭文件
    system("pause");
    return 0;
}
