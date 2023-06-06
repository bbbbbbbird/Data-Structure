#include"map.h"

void Graph::addNode(string name, int x, int y) {
        nodes.push_back({ name, x, y });
    }

    // 添加边（无向图）
void Graph::addEdge(int u, int v, int w) {
        adj_[u].push_back({ v, w });
        adj_[v].push_back({ u, w });
    }

    // 查询任意两点最短路径
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

    // 获取节点信息
MapNode Graph::getNode(int idx) {
        return nodes[idx];
    }
void guide() {
    Graph g;

    // 添加节点
    g.addNode("北苑餐厅", 1000, 500);
    g.addNode("能动学院楼", 800, 540);
    g.addNode("计算机学院楼", 620, 475);
    g.addNode("经管学院楼", 650, 450);
    g.addNode("文理大楼", 580, 420);
    g.addNode("图书馆", 610, 330);
    g.addNode("蚕研所/生物技术学院楼", 450, 300);
    g.addNode("材料学院楼", 310, 190);
    g.addNode("文体中心", 280, 340);
    g.addNode("明德楼", 460, 420);

    // 添加边
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

    // 查询最短路径
    cout << "建筑列表: 1.北苑餐厅2.能动学院楼3.计算机学院楼4.经管学院楼5.文理大楼" << endl;
    cout<<'\t'<<"  6.图书馆7.蚕研所 / 生物技术学院楼8.材料学院楼9.文体中心10.明德楼"<<endl;
    cout << "输入你想要查询的两地: ";
    int u, v;
    cin >> u >> v;
    int dist = g.shortestPath(u, v);
    if (dist == -1) {
        cout << "无法到达目标地点" << endl;
    }
    else {
        cout << "从 " << g.getNode(u).name << " 到 " << g.getNode(v).name << " 的最短路径长度为：" << dist << endl;
    }
}
