#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
//template <class T>
class Path{
private:
	double path;
	string data;
public:
	Path (string d, double p){
		data = d;
		path = p;
	} 
	double get_path(){
		return path;
	}
	string get_data(){
		return data;
	}

};