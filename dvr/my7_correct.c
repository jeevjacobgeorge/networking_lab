#include <stdio.h>
#include <limits.h> //for inf
#define INF INT_MAX 
#define NODES 7

char *nodes[] = {"A", "B", "C", "D", "E", "F", "G"};
void print_routing_table(int dist[NODES],int next_hop[NODES],int src){
      printf("Routing Table for node %s \n",nodes[src]);
      for (int i = 0; i <NODES; i++){
            if(i!=src){
                  printf("Shortest path to node %s: the next hop is %s and the cost is %d\n", nodes[i], nodes[next_hop[i]], (dist[i] == INF ? -1 : dist[i]));
            }
      }
}
void distance_vector_routing(int graph[NODES][NODES],int src){
      int dist[NODES];
      int next_hop[NODES] = {-1};

      for(int i = 0; i < NODES; i++ ){
            dist[i] = graph[src][i];
            if (graph[src][i] != INF && graph[src][i] != 0){
                  next_hop[i] = i;
            } 
      }
      dist[src] = 0;
      next_hop[src] = src;
      //Bellman Ford Algorithm
      for (int k = 0; k < NODES-1;k++){
            for (int u = 0; u < NODES;u++){
                  for (int v = 0; v < NODES; v++){
                        if (graph[u][v]!=INF && dist[u]!=INF &&  dist[u]+ graph[u][v] < dist[v]){
                               dist[v] = dist[u] + graph[u][v];
                               //next_hop[i] is where should you go from src node to reach i
                               next_hop[v] = next_hop[u];
                        }
                  }
            }
      }
      print_routing_table(dist,next_hop,src);
}
int main(){
      int graph[NODES][NODES] = {
       {0, 1, 1, INF, 1, 1, INF},  // A
        {1, 0, 1, INF, INF, INF, INF},  // B
        {1, 1, 0, 1, INF, INF, INF},  // C
        {INF, INF, 1, 0, INF, INF, 1},  // D
        {1, INF, INF, INF, 0, INF, INF},  // E
        {1, INF, INF, INF, INF, 0, 1},  // F
        {INF, INF, INF, 1, INF, 1, 0}   // G
      };

      distance_vector_routing(graph,1);

}