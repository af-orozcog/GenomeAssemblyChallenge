#include<bits/stdc++.h>
using namespace std;

int position(char see1[],char see2[],char see3[], char see4[]){
    char black[] = "black";
    if(strcmp(see1,black) == 0){
        if(strcmp(see2,black) == 0) return 0;
        else if(strcmp(see4,black) == 0) return 2;
        else return 1;
    }
    else if(strcmp(see3,black) == 0){
        if(strcmp(see2,black) == 0) return 6;
        else if(strcmp(see4,black) == 0) return 7;
        else return 5;
    }
    else{
        if(strcmp(see2,black) == 0) return 3;
        else if(strcmp(see4,black) == 0) return 5;
        else return 4;
    }
}


int main(){
    char ans[9][4][10];
    char see1[10],see2[10],see3[10],see4[10];
    for(int i = 0; i < 10;++i){
        int pos = position(see1,see2,see3,see4);
        strcpy(ans[pos][0],see1);
        strcpy(ans[pos][1],see2);
        strcpy(ans[pos][2],see3);
        strcpy(ans[pos][3],see4);
    }
    for(int i = 0; i < 9;++i){
        if(i % 3 == 0 && i) puts("");
        printf("(");
        for(int j = 0; j < 4;++j){
            printf("%s",ans[i][j]);
            if(j!=3)
                printf(",");
        }
        printf(")");
        if(i%3 != 2) printf(";");
    }
    return 0;
}
