#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    string to;
    int cost;
};

// Heuristic values
unordered_map<string, int> heuristic = {
    {"Pune", 150},
    {"Expressway", 100},
    {"OldHighway", 120},
    {"CoastalRoad", 180},
    {"Mumbai", 0}};

// Graph definition
unordered_map<string, vector<Edge>> graph = {
    {"Pune", {{"Expressway", 50}, {"OldHighway", 30}, {"CoastalRoad", 20}}},
    {"Expressway", {{"Mumbai", 100}}},
    {"OldHighway", {{"Mumbai", 120}}},
    {"CoastalRoad", {{"Mumbai", 180}}},
    {"Mumbai", {}}};

struct Node
{
    string name;
    int g; // cost so far
    int f; // g + h
    bool operator>(const Node &other) const
    {
        return f > other.f;
    }
};

// Function to print Open List
void printOpenList(priority_queue<Node, vector<Node>, greater<Node>>
                       openList)
{
    vector<Node> temp;
    cout << "Open List: [";
    while (!openList.empty())
    {
        Node n = openList.top();
        openList.pop();
        temp.push_back(n);
        cout << n.name << "(g=" << n.g << ", h=" << heuristic[n.name]
             << ", f=" << n.f << ")";
        if (!openList.empty())
            cout << ", ";
    }
    cout << "]\n";
    // Restore nodes (since we passed by value, the original queue is unchanged)
}

// A* Algorithm with Logging

vector<string> aStar(string start, string goal)
{
    priority_queue<Node, vector<Node>, greater<Node>> openList;
    unordered_map<string, int> gScore;
    unordered_map<string, string> parent;
    unordered_set<string> closed;

    gScore[start] = 0;
    openList.push({start, 0, heuristic[start]});

    int step = 0;
    while (!openList.empty())
    {
        cout << "\n--- Step " << ++step << " ---\n";
        printOpenList(openList);

        Node current = openList.top();
        openList.pop();
        cout << "Expanding: " << current.name
             << " (g=" << current.g
             << ", h=" << heuristic[current.name]
             << ", f=" << current.f << ")\n";

        if (current.name == goal)
        {
            cout << "Goal reached!\n";
            vector<string> path;
            string node = goal;
            while (!node.empty())
            {
                path.push_back(node);

                node = parent[node];
            }
            reverse(path.begin(), path.end());
            cout << "Total cost = " << gScore[goal] << " km\n";
            return path;
        }

        closed.insert(current.name);
        cout << "Closed List: {";
        for (auto &c : closed)
            cout << c << " ";
        cout << "}\n";

        // Explore neighbors
        for (auto &edge : graph[current.name])
        {
            int tentative_g = gScore[current.name] + edge.cost;
            if (!gScore.count(edge.to) || tentative_g < gScore[edge.to])
            {
                gScore[edge.to] = tentative_g;
                parent[edge.to] = current.name;
                int f = tentative_g + heuristic[edge.to];
                openList.push({edge.to, tentative_g, f});
            }
        }
    }

    return {}; // No path found
}

int main()
{
    string start = "Pune";
    string goal = "Mumbai";
    vector<string> path = aStar(start, goal);

    if (!path.empty())
    {
        cout << "\nOptimal Path: ";
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i];
            if (i != path.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found.\n";
    }

    return 0;
}
