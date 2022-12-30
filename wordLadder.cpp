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
  //opems file
  ifstream file("wordlist05.txt");
  string word;

  //goes through files and puts every word in V vector
  while(getline(file, word)){
    V.push_back(word);
    strs[word] = vector<string>();
  }

  //goes through each word in V
  for(string w: V){
    //changes each letter of each word one at a time and checks if it exists
    for(int i = 0; i < 5; i++){
      for(int a = 97; a < 97 + 26; a++){
        if(w[i] == a){
          continue;
        }

        string curr = w;
        curr[i] = (char)a;
        //if word is in strs map then add it to the strs map under word
        if(strs.find(w) != strs.end()){
            strs[w].push_back(curr);
        }
      }
    }
  }
}

int findSteps(string s, string t, vector<string> &p){
  //starts with 0 steps
  int steps = 0;

  //if theres nothing behind t return 0
  if(pred.find(t) == pred.end()){
    p.push_back(t);
    return 0;
  //if t isnt s add one to steps and go through find steps up to the one before t
  }else if(t != s){
    steps = 1 + findSteps(s, pred[t], p);
    p.push_back(t);
    return steps;
  }else{
    //if nothing else add t to p and return steps
    p.push_back(t);
    return steps;
  }
}

void wordLadder(string s, string t, int &steps, vector<string> &p){
  //builds graphs searches through s and find the number of steps
  buildGraph();
  search(s);
  steps = findSteps(s, t, p);
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

