#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type

//Implement breadth-first search, refer to Lab 10

map<string, bool> visited;         // have we queued up this state for visitation?
map<string, string> pred;           // predecessor state we came from
map<string, int> dist;             // distance (# of hops) from source node
map<string, vector<string> > strs;   // vector of neighboring states

map<pair<string,string>, string> edge_label;

// GENERIC (breadth-first search, outward from curnode)
void search(string source_node){
  queue<string> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    string curnode = to_visit.front();
    to_visit.pop();
    for (string n : strs[curnode])
      if (!visited[n]) {
        pred[n] = curnode;
        dist[n] = 1 + dist[curnode];
        visited[n] = true;
        to_visit.push(n);
      }
  }
}

void buildGraph(){
  ifstream file("wordlist05.txt");
  string word;

  while(getline(file, word)){
    V.push_back(word);
    strs[word] = vector<string>();
  }

  for(string w: V){
    for(int i = 0; i < 5; i++){
      for(int a = 97; a < 97 + 26; a++){
        if(w[i] == a){
          continue;
        }

        string curr = w;
        curr[i] = (char)a;

        if(strs.find(w) != strs.end()){
            strs[w].push_back(curr);
        }
      }
    }
  }
}

int findSteps(string s, string t, vector<string> &p){
  int steps = 0;
  if(pred.find(t) == pred.end()){
    p.push_back(t);
    return 0;
  }else if(t != s){
    steps = 1 + findSteps(s, pred[t], p);
    p.push_back(t);
    return steps;
  }else{
    p.push_back(t);
    return steps;
  }
}

void wordLadder(string s, string t, int &steps, vector<string> &p){
  buildGraph();
  search(s);
  steps = findSteps(s, t, p);
  reverse(p.begin(), p.end());
}

int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
