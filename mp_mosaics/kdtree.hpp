/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]){
      return true;
    }
    else if (first[curDim] == second[curDim]){
      return first < second;
    }
    else{
      return false;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double ptdiff = 0;
    double ctdiff = 0;
    for(int i = 0; i< Dim; i++){
      ptdiff += pow(target[i]-potential[i],2);
      ctdiff += pow(target[i]-currentBest[i],2);
    }

    if(ptdiff< ctdiff){
      return true;
    }
    else if(ptdiff == ctdiff){
      return potential < currentBest;
    }
    else{
      return false;
    }
}

template <int Dim>
int KDTree<Dim>::Partition(vector<Point<Dim>>& vector, int start, int end, int dimension){
  Point<Dim> pivot = vector[end];
  int i = start - 1;
  for(int j = start; j < end; j++){
    if(smallerDimVal(vector[j],pivot,dimension)){
      i++;
      Point<Dim> temp =vector[i];
      vector[i] = vector[j];
      vector[j] = temp;
    }
  }
  //std::cout<<"end is "<<end<<std::endl;
  //std::cout<<"i is "<<i<<std::endl;
  Point<Dim> temp2 =vector[i+1];
  vector[i+1] = vector[end];
  vector[end] = temp2;

  return i+1;
}

template <int Dim>
Point<Dim> KDTree<Dim>::QuickSelect(vector<Point<Dim>>& vector, int start, int end, int rank, int dimension){
  if(start == end){
    return vector[start];
  }
  int pivotIndex = Partition(vector,start,end,dimension);
  // for(auto it = vector.begin();it != vector.end(); ++it){
  //     std::cout<<*it<<std::endl;
  //   }
  // std::cout<<"--------"<<std::endl;
  //std::cout<<"rank is " <<rank<<std::endl;
  //std::cout<<"pivotIndex is " <<pivotIndex<<std::endl;
  if(pivotIndex == rank){
    return vector[pivotIndex];
  }
  else if(pivotIndex < rank){
    return QuickSelect(vector,pivotIndex+1,end,rank,dimension);
  }
  else{
    return QuickSelect(vector,start,pivotIndex-1,rank,dimension);
  }
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::construct(vector<Point<Dim>>& vector, int start, int end, int dimension){
  if(start > end){
    return NULL;
  }
  KDTreeNode* temp = new KDTreeNode(QuickSelect(vector,start, end, (start + end)/2, dimension));
  size++;
  temp->left = construct(vector, start, (start + end)/2 - 1, (dimension + 1) % Dim);
  temp->right = construct(vector, (start + end)/2 + 1, end, (dimension + 1) % Dim);
  //std::cout<<"rank is " <<(start + end)/2<<std::endl;
  //std::cout<<"pivot is " <<temp<<std::endl;

  return temp;

}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = 0;
    vector<Point<Dim>> KDTree = newPoints;
    // for(auto it = KDTree.begin();it != KDTree.end(); ++it){
    //   std::cout<<*it<<std::endl;
    // }
    // std::cout<<"------------------"<<std::endl;
    //std::cout<<"curr line is "<<__LINE__<<std::endl;
    if(!KDTree.empty()){
      root = construct(KDTree,0,KDTree.size()-1,0);
    }
    else{
      root = NULL;
    }
    //std::cout<<"curr line is "<<__LINE__<<std::endl;
    
    // for(auto it = KDTree.begin();it != KDTree.end(); ++it){
    //   std::cout<<*it<<std::endl;
    // }


}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode * subroot){
  if(subroot == NULL){
    return;
  }
  clear(subroot->left);
  clear(subroot->right);
  delete subroot;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode *& subroot,KDTreeNode * other){
  if(other == NULL){
    return;
  }
  subroot = new KDTreeNode(other->point);
  copy(subroot->left, other->left);
  copy(subroot->right, other->right);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = other.size;
  
  copy(root,other.root);
  //std::cout<<"curr is"<<__LINE__<<std::endl;


}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  size = rhs.size;
  clear(root);
  copy(root,rhs.root);

  

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::find(const Point<Dim>& query, int dimension, KDTreeNode* curRoot) const{
  //std::cout<<curRoot->point<<std::endl;
  if(curRoot->left == NULL && curRoot->right == NULL){
    return curRoot;
  }

  KDTreeNode* nearest = curRoot;
  if(smallerDimVal(query,curRoot->point,dimension)){
    if(curRoot->left != NULL){
      nearest = find(query,(dimension+1) % Dim,curRoot->left);
    }
  }
  else{
    if(curRoot->right != NULL){
      nearest = find(query,(dimension+1) % Dim,curRoot->right);
    }
  }

  if(shouldReplace(query, nearest->point, curRoot->point)){
    nearest = curRoot;
  }

  int radius = 0;
  for (int i = 0; i < Dim; i++){
    radius += pow((query[i] - nearest->point[i]),2);
  }
  int splitDist = pow(curRoot->point[dimension]-query[dimension],2);

  KDTreeNode* tempNearest = nearest;
  if(radius >= splitDist){
    if(smallerDimVal(query,curRoot->point,dimension) && curRoot->right != NULL){
      tempNearest = find(query,(dimension+1) % Dim,curRoot->right);
    }
    else if (!smallerDimVal(query,curRoot->point,dimension) && curRoot->left != NULL) {
      tempNearest = find(query,(dimension+1) % Dim,curRoot->left);
  
    }
    if(shouldReplace(query, nearest->point, tempNearest->point)){
      nearest = tempNearest;
    }
  }
  

  return nearest;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return find(query,0,root)->point;
}

