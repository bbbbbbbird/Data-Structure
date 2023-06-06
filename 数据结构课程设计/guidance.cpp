#include"map.h"

void Graph::addNode(string name, int x, int y) {
        nodes.push_back({ name, x, y });
    }

    // ��ӱߣ�����ͼ��
void Graph::addEdge(int u, int v, int w) {
        adj_[u].push_back({ v, w });
        adj_[v].push_back({ u, w });
    }

    // ��ѯ�����������·��
int Graph::shortestPath(int u, int v) {
        vector<int> dist(nodes.size(), 1000);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[u] = 0;
        pq.push({ 0, u });
        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();
            int d = cur.first;
            int node = cur.second;
            if (node == v) 
                return d;
            if (d > dist[node]) 
                continue;
            for (auto& next : adj_[node]) {
                int n = next.first;
                int w = next.second;
                if (dist[node] + w < dist[n]) {
                    dist[n] = dist[node] + w;
                    pq.push({ dist[n], n });
                }
            }
        }
        return -1;
    }

    // ��ȡ�ڵ���Ϣ
MapNode Graph::getNode(int idx) {
        return nodes[idx];
    }
void guide() {
    Graph g;

    // ��ӽڵ�
    g.addNode("��Է����", 1000, 500);
    g.addNode("�ܶ�ѧԺ¥", 800, 540);
    g.addNode("�����ѧԺ¥", 620, 475);
    g.addNode("����ѧԺ¥", 650, 450);
    g.addNode("�����¥", 580, 420);
    g.addNode("ͼ���", 610, 330);
    g.addNode("������/���＼��ѧԺ¥", 450, 300);
    g.addNode("����ѧԺ¥", 310, 190);
    g.addNode("��������", 280, 340);
    g.addNode("����¥", 460, 420);

    // ��ӱ�
    g.addEdge(0, 1, 260);
    g.addEdge(0, 2, 400);
    g.addEdge(1, 3, 150);
    g.addEdge(1, 4, 180);
    g.addEdge(2, 4, 130);
    g.addEdge(2, 5, 145);
    g.addEdge(3, 4, 120);
    g.addEdge(3, 6, 200);
    g.addEdge(4, 5, 90);
    g.addEdge(4, 6, 350);
    g.addEdge(4, 9, 120);
    g.addEdge(5, 7, 170);
    g.addEdge(5, 6, 200);
    g.addEdge(8, 9, 140);

    // ��ѯ���·��
    cout << "�����б�: 1.��Է����2.�ܶ�ѧԺ¥3.�����ѧԺ¥4.����ѧԺ¥5.�����¥" << endl;
    cout<<'\t'<<"  6.ͼ���7.������ / ���＼��ѧԺ¥8.����ѧԺ¥9.��������10.����¥"<<endl;
    cout << "��������Ҫ��ѯ������: ";
    int u, v;
    cin >> u >> v;
    int dist = g.shortestPath(u, v);
    if (dist == -1) {
        cout << "�޷�����Ŀ��ص�" << endl;
    }
    else {
        cout << "�� " << g.getNode(u).name << " �� " << g.getNode(v).name << " �����·������Ϊ��" << dist << endl;
    }
}
