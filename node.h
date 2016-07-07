#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

template<typename T> class node{
	private:
		string data;
		T weight;
		node* left;
		node* right;
		int biNum;
	public:
		node();
		node(string d, T w = 0, node* L =NULL, node* R=NULL);
		node(T w, node* L=NULL, node* R=NULL);
		node(T w, string d, node* L=NULL, node* R=NULL);
		string get_char();
		T get_weight();
		void set_weight(T w);
		void inc_Weight(){ weight++; }
		node* left_child();
		node* right_child();
		void set_left(node* L);
		void set_right(node* R);
		bool isLeaf();
		void setBiNum(T x);
		int getBiNum();
};

template <typename T>
void node<T>::setBiNum(T x){
	biNum = x;
}

template <typename T>
int node<T>:: getBiNum(){
	return biNum;
}

template <typename T>
node<T>::node(){
	left,right = NULL;

}

template<typename T>
node<T>::node(string d, T w, node* L, node* R){
	data = d; weight = w; left = L; right = R;
}

template<typename T>
node<T>::node (T w,node* L,node* R){
	weight = w; left = L; right = R;
}

template<typename T>
node<T>::node(T w, string d, node* L, node* R){
	weight = w;	left = L; right = R; data = d;
}

template<typename T> 
string node<T>::get_char(){
	return data;
}

template<typename T>
T node<T>::get_weight(){
	return weight;
}

template<typename T> 
void node<T>::set_weight(T w){
	weight = w;
}

template<typename T> 
node<T>* node<T>::left_child(){
	return left;
}

template<typename T>
node<T>* node<T>::right_child(){
	return right;
}

template<typename T> 
void node<T>::set_left(node *L){
	left = L;
}

template<typename T> 
void node<T>::set_right(node *R){
	right = R;
}

template<typename T> 
bool node<T>::isLeaf(){
	if((left == NULL) && (right == NULL)){
		return true;
	}
	else{
		return false;
	}
}