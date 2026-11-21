#include <iostream>
#include <Windows.h>

using namespace std;

struct Edge {
    int u, v, weight;
};

void bubbleSort(Edge* edges, int m) {
    for (int i = 0; i < m - 1; ++i) {
        for (int j = 0; j < m - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                swap(edges[j], edges[j + 1]);
            }
        }
    }
}

struct DSU {
    int* parent;
    int* rank;

    DSU(int n) {
        parent = new int[n];
        rank = new int[n] {};
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    ~DSU() {
        delete[] parent;
        delete[] rank;
    }

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
        return true;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Вітаємо у програмі пошуку мінімального остовного дерева!" << endl;
    int n, m;
    cout << "\nВведіть кількість вершин та ребер: ";
    cin >> n >> m;

    Edge* edges = new Edge[m];

    cout << "\nВведіть ребра у форматі: вершина1 вершина2 вага" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
        edges[i].u--; // переводим к 0-индексации
        edges[i].v--;
    }

    bubbleSort(edges, m);

    DSU dsu(n);
    Edge* mst = new Edge[n - 1];
    int totalWeight = 0;
    int mstSize = 0;

    cout << "\nПочинаємо пошук мінімального остовного дерева..." << endl;

    for (int i = 0; i < m; ++i) {
        Edge e = edges[i];
        cout << "Розглядаємо ребро: (" << e.u + 1 << ", " << e.v + 1 << ") з вагою " << e.weight << endl;
        if (dsu.unite(e.u, e.v)) {
            mst[mstSize++] = e;
            totalWeight += e.weight;
            cout << "  Додаємо до дерева." << endl;

            if (mstSize == n - 1)
                break;
        }
        else {
            cout << "  Це створює цикл. Пропускаємо." << endl;
        }
    }

    cout << "\nЗагальна вага остовного дерева: " << totalWeight << endl;
    cout << "Ребра остовного дерева:" << endl;
    for (int i = 0; i < mstSize; ++i) {
        cout << mst[i].u + 1 << " - " << mst[i].v + 1 << " (" << mst[i].weight << ")" << endl;
    }

    delete[] edges;
    delete[] mst;

    cout << "\nВага мінімального остовного дерева дорівнює: " << totalWeight << endl;

    return 0
        ;