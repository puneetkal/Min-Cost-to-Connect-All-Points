class Unionfind{
public:
    vector<int> parent;
    vector<int> rank;

    Unionfind(int n){
        rank.resize(n,1);
        parent.resize(n,1);
        for(int i=0; i<n; i++){
            parent[i]=i;
        }
    }

    int find(int x){
        if(parent[x]==x) return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y){
        int px = find(x);
        int py = find(y);

        if(rank[px]>rank[py]){
            parent[py]=px;
        }
        else if(rank[py]>rank[px]){
            parent[px]=py;
        }
        else{
            parent[py]=px;
            rank[px]++;
        }
    }
};


class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {

        int dots = points.size();
        vector<pair<int, pair<int,int>>> pairs;
        // cost = point1, point2

        for(int i=0; i<dots; i++){
            int x1 = points[i][0];
            int y1 = points[i][1];
            for(int j=i+1; j<dots; j++){
                int x2 = points[j][0];
                int y2 = points[j][1];
                int cost = abs(x2-x1)+abs(y2-y1);
                pairs.push_back({cost,{i,j}});
            }
        }
        sort(pairs.begin(), pairs.end());

        int edges_used=0;
        int total_cost=0;

        Unionfind uf(dots);

        for(auto j: pairs){
            int cost   =j.first;
            int point1 =j.second.first;
            int point2 =j.second.second;

            if(uf.find(point1)!=uf.find(point2)){
                uf.unite(point1, point2);
                total_cost+=cost;
                edges_used+=1;
            }
            if(edges_used==dots-1) break;
        }
        return total_cost;
    }
};