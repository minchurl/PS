#include<bits/stdc++.h>
using namespace std;
class node{

private:
    int x = 2;
public:
    node(int xx){
        this->x = xx;
    }
    int get_x(){
        return x;
    }


};

int main(){
    int y;
    scanf("%d",&y);
    node *x = new node(y);
    printf("%d\n",x->get_x());
    return 0;
}