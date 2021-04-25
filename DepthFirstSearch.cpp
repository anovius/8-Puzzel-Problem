#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
using namespace std;

class State{
public:
    int data[3][3];
    State *parent;
    int depth;
    State(){
        parent = NULL;
        depth = 0;
    }
    void init(int arr[][3]){
         for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                data[i][j] = arr[i][j];
    }
    bool operator==(State s){
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(data[i][j] != s.data[i][j])
                    return false;
        return true;
    }
    void print(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                cout << data[i][j] << ' ';
            cout << '\n';
        }
    }
};

bool isVisited(vector<State> visited, State s){
    for(int i=0; i<visited.size(); i++){
        if(visited[i] == s) return true;
    }
    return false;
}
void findZeroIndex(int arr[][3], int &a, int &b){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(arr[i][j] == 0){
                a = i;
                b = j;
                return;
            }
}
void printPath(State *final){
    vector<State> path;
    while(final != NULL){
        path.push_back(*final);
        final = final->parent;
    }
    reverse(path.begin(), path.end());
    for(int i=0; i<path.size(); i++){
        path[i].print();
        cout <<'\n';
    }
}
int main(){
    int depth;
    cout << "Enter Depth or leave -1 for default depth: ";
    cin >> depth;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    if(depth == -1) depth =10;                                                                                                                                                      
    vector<State> visited;
    stack<State*> remaining;
    int s[3][3] = {{2,8,3},{1,6,4},{7,0,5}};
    int g[3][3] = {{1,2,3},{8,0,4}, {7,6,5}};
    State start, goal;
    start.init(s);
    goal.init(g);
    cout << "Start State\n";
    start.print();
    cout << "Goal State\n";
    goal.print();
    State *final;
    bool isFound = false;
    remaining.push(&start);
    while(!remaining.empty()){
        State *current = remaining.top();
        remaining.pop();
        visited.push_back(*current);
        int a,b; //index of 0 in puzzel
        if(*current == goal){
            final = current;
            isFound = true;
            break;
        }
        else if(!(current->depth == depth)){
            findZeroIndex(current->data, a, b);
            //left move
            if(b-1>=0){
                State *newState = new State(*current);
                newState->parent = current;
                newState->depth = current->depth + 1;
                swap(newState->data[a][b], newState->data[a][b-1]);
                if(!isVisited(visited, *newState)){
                    remaining.push(newState);
                }
            }
            //right move
            if(b+1<3){
                State *newState = new State(*current);
                newState->parent = current;
                newState->depth = current->depth + 1;
                swap(newState->data[a][b], newState->data[a][b+1]);
                if(!isVisited(visited, *newState)){
                    remaining.push(newState);
                }
            }
            //top move
            if(a-1>=0){
                State *newState = new State(*current);
                newState->parent = current;
                newState->depth = current->depth + 1;
                swap(newState->data[a][b], newState->data[a-1][b]);
                if(!isVisited(visited, *newState)){
                    remaining.push(newState);
                }
            }
            //bottom move
            if(a+1<3){
                State *newState = new State(*current);
                newState->parent = current;
                newState->depth = current->depth + 1;
                swap(newState->data[a][b], newState->data[a+1][b]);
                if(!isVisited(visited, *newState)){
                    remaining.push(newState);
                }
            }
        }
    }
    if(isFound){
        cout << "\n\nGoal Found!\nThe path will be following\n\n";
        printPath(final);
    }
    else{
        cout << "\n\nGoal Not Found!\n";
    }
    return 0;
}