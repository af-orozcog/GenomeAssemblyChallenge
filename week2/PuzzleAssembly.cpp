#include<bits/stdc++.h>
using namespace std;

struct square{
    string vals[4];
    string top(){
        return vals[0];
    }
    string left(){
        return vals[1];
    }
    string bottom(){
        return vals[2];
    }
    string right(){
        return vals[3];
    }
};


string answer[5][5][4];
bool found = 0;

int top = 0;
int left1 = 1;
int bottom = 2;
int right1 = 3;

void getAns(int positionX, int positionY, vector<int> &used, vector<square*> &possible){
    if(found) return;
    if(positionX == 5){
        found = 1;
        return;
    }
    for(int i = 0; i < 25 && !found;++i){
        if(used[i])continue;
        if(positionX == 0 && possible[i]->top() != "black")continue;
        if(positionY == 0 && possible[i]->left() != "black")continue;
        if(positionY == 4 && possible[i]->right() != "black")continue;
        if(positionX == 4 && possible[i]->bottom() != "black") continue;
        if(positionX > 0 && possible[i]->top() != answer[positionX-1][positionY][bottom]) continue;
        if(positionY > 0 && possible[i]->left() != answer[positionX][positionY-1][right1]) continue;
        answer[positionX][positionY][bottom] = possible[i]->bottom();
        answer[positionX][positionY][left1] = possible[i]->left();
        answer[positionX][positionY][right1] = possible[i]->right();
        answer[positionX][positionY][top] = possible[i]->top();
        used[i] = 1;
        if(positionY == 4)
            getAns(positionX+1,0,used,possible);
        else
            getAns(positionX,positionY+1,used,possible);
        used[i] = 0;
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<square*> use(25);
    for(int i = 0; i < 25;++i){
        string line;
        getline(cin,line);
        square *append = new square();
        for(int i = 0; i < line.size();++i)
            if(line[i] == '(' || line[i] == ',' || line[i] == ')')
                line[i] = ' ';
        stringstream ss(line);
        string temp;
        int who = 0;
        while(ss >> temp){
            append->vals[who] = temp;
            ++who;
        }
        use[i] = append;
    }
    vector<int> used(25,0);
    getAns(0,0,used,use);
    for(int i = 0; i < 5;++i){
        for(int j = 0; j < 5;++j){
            cout << "(";
            for(int k = 0; k < 4;++k){
                cout << answer[i][j][k];
                if(k != 3) cout << ",";
            }
            cout << ")";
            if(j != 4) cout << ";";
        }
        cout << "\n";
    }
    return 0;
}
