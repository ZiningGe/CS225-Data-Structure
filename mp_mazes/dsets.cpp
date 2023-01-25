/* Your code here! */
#include "dsets.h"
#include <iostream>

void DisjointSets::addelements(int num){
    for(int i = 0; i < num; i++){
        v.push_back(-1);
    }
}

int DisjointSets::find(int elem){
    if(v[elem] < 0){
        return elem;
    }
    else{
        v[elem] = find(v[elem]);
        return v[elem];
    }
}

void DisjointSets::setunion(int a, int b){
    int newsize = -1 * (size(a)+size(b));
    if(find(a) == find(b)){
        return;
    }
    if(size(a) >= size(b)){
        v[find(b)] = find(a);
        v[find(a)] = newsize;
    }
    else{
        v[find(a)] = find(b);
        v[find(b)] = newsize;
    }
}

int DisjointSets::size(int elem){
    //std::cout<<-1 * v[find(elem)]<<std::endl;
    return -1 * v[find(elem)];
}

void DisjointSets::print(){
    for(auto it = v.begin(); it != v.end(); it++){
        std::cout<<*it<<std::endl;
    }
}