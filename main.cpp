#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<vector>
#include"node.h"
#include"Path.cpp"
#include<string>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include"bitChar.cpp"


using namespace std;


string encode(node<double>* root, string c);
void Decode(node<double>* root, string encoded);
node<double>* weightsFileToTree(string fileName);
void readPath(string fileName, vector<Path> *path_vec);
void sortVector(vector<node<double> > &weights);
void sortNodeVector(vector<node<double>* > &nodes);
void printWeightsFile(node<double>* root, int &position);
void printPath(node<double>* root,string letter);
void printCodes(struct node<double>* root, int arr[], int top);
string getPath(int arr[], int n);
node<double>* buildHuffmanTree(vector<node<double>* > &nodeVector);
bool charAlreadyEncountered(vector<node<double>* > nodes, string s);
int nodeIndexOf(vector<node<double>* > nodes, string c);
node<double>* treeFromTextFile(string filename, vector<node<double>* > &nodes);
void treeSize(node<double>* root, int &size);
void compressToFile(node<double>* root, ofstream &outf);
vector <char> generatePathFile();
void compressMethod(node<double> * root, vector<char> v,string fileName);
void decompressMethod(string fileName);
void printHCodeFile(node<double>* root, int &position,node<double>* staticRoot, string fileName);
double compressionRatio(string normal, string compressed);

int main(){

	/*string path = encode(test,"a");
	string path = encode(textFileRoot," ");

	FILE * dat = fopen ("data.dat", "wb");
	fwrite (&path, sizeof(unsigned char), 1, dat);
	fclose(dat);

	dat = fopen("data.dat", "rb");
	fread (&path, sizeof(unsigned char), 1, dat);
	cout << "this is the path after decoding "<<path << endl;
	/*string temp;
	while (!dat.eof()){
		getline(dat, temp);
		cout <<temp<<endl;
	}*
	fclose(dat);*/

//	printCodes(root, arr, top1);
	//#1 + 6
	vector<char> charVector;
	cout << "Enter 1 to compress a file." << endl;
	cout << "Enter 2 to decompress an hzip file using an hcode file." << endl;
	cout << "Enter q to quit." << endl;
	string option;
	getline(cin,option);

	if(option == "1"){
		//compress file
		//prompt for compress file name
		string compressFile;
		cout << "Enter text file to compress" << endl;
		cin >> compressFile;
		vector<node<double>*> textFileNodes = vector<node<double>* >();
		node<double>* textFileRoot = treeFromTextFile(compressFile, textFileNodes);

		int position = 0;
		printWeightsFile(textFileRoot,position);
		position = 0;
		string hcodeFileName = compressFile + ".hcode";
		printHCodeFile(textFileRoot,position,textFileRoot,hcodeFileName);
		int textTreeSize = 0;
		treeSize(textFileRoot, textTreeSize);
	
		int array[textTreeSize];
		int top = 0;

		printCodes(textFileRoot, array, top);

		string compressedFile = compressFile + ".hzip";
/*		ofstream outf(compressedFile.c_str());
		compressToFile(textFileRoot,outf);
*/
//		outf.close();
		charVector = generatePathFile();
		cout << charVector.at(0)<< " the char in the vector" << endl;
		compressMethod(textFileRoot, charVector,compressedFile);

		cout << compressFile << " was compressed at a " 
			 << setprecision(2)
			 << compressionRatio(compressFile,compressedFile) 
			 << "% rate" << endl;
//		decompressMethod("");


	}
	else if(option == "2"){
		//prompt for hzip file
		//prompt for hcode file
	}
	else if(option == "q"){
		//quit file
	}
	else{
		cout << "Invalid input." << endl;
		cout << "Please enter 1 or 2 to select an option." << endl;
		getline(cin,option);
	}
	
	//get user input for filename
	//create huffman tree
	//read the file again and encode it using the codes from the huffman tree
		//output as filename.hzip
	//create file with lists of characters and binary encodings
		//output as filename.hcodes
	//print compression rations
		//number of bits in compressed file divided by bits in original file (8x the number of characters)
	//take .hzip file and .hcodes file
		//decompress as filename.txt	

	//node<double>* root = buildHuffmanTree(nodes,totalWeight);
	//printTree(root);

	
	cout << "End!" << endl;	
	return 0;
}

void printCodes(node<double>* root, int arr[], int top){
    // Assign 0 to left edge and recur
    if (root->left_child()){
        arr[top] = 0;
        printCodes(root->left_child(), arr, top + 1);
    }
    // Assign 1 to right edge and recur
    if (root->right_child()){
        arr[top] = 1;
        printCodes(root->right_child(), arr, top + 1);
    }
    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (root->isLeaf()){
        cout << root->get_char() <<endl;
        string temp;
        temp = getPath(arr, top);
    }
}

string getPath(int arr[], int n)
{
    int i;
    string stringPath = "";
    string text;
    for (i = 0; i < n; ++i){
    	int number = arr[i];
    	string Result;
    	ostringstream convert;
    	convert << number;
    	text = convert.str();
    	stringPath += text;
    }
    cout << stringPath << endl;
    return stringPath;

}

string encode(node<double>* root, string c){
	string path = "";
	node<double>* lastRoot = root;
	while(lastRoot->get_char().length() != 1){				//while looking through the tree
		if(lastRoot->right_child()->get_char().find(c) != string::npos){		//if the right child contains the letter
			path += "1";
			if(lastRoot->right_child()){						
				lastRoot = lastRoot->right_child();
			}
		}
		else if(lastRoot->left_child()->get_char().find(c) != string::npos){	//if the left child contains the letter
			path += "0";
			if(lastRoot->left_child()){
				lastRoot = lastRoot->left_child();
			}
		}
	}
	return path;	
}

node<double>* weightsFileToTree(string fileName){
	vector<node<double> > weights;
	ifstream infile;
	string key;  			//first character is the data for node
	double weight;
	//second string is weight of character 
	infile.open(fileName.c_str());
	while(!infile.eof()){
		string temp;			
		getline(infile, temp);
		if(temp != ""){
			key = temp[0];
			weight = atof(temp.substr(2,temp.size()-1).c_str());
			node<double> tempnode = node<double>(weight, key);
			weights.push_back(tempnode);
		}
	}
	sortVector(weights);
 	
 	vector<node<double>* > nodes;
	for(int i = 0; i < weights.size(); i++){
		nodes.push_back(new node<double>(weights[i].get_weight(),weights[i].get_char(),NULL,NULL));
	}
	//cout << "Weights size: " << weights.size() << endl;
	return buildHuffmanTree(nodes);
}

void readPath(string fileName, vector<Path> *path_vec, int pathSize){
	//for line in file
	ifstream infile;
	//sting key;		//first character is the data for node
	double 	pathBinary = 0;		//second string is path of character 
	infile.open(fileName.c_str());
	while(infile.get() != infile.eof()){
		string temp;			
		getline(infile, temp);
		if(temp != ""){
			string key = temp.substr(0, 1);
			pathBinary= atof(temp.substr(1).c_str());
			Path tempPath = Path(key, pathBinary);
			path_vec->push_back(tempPath);
			pathSize ++;
		}
	}	
}

void sortVector(vector<node<double> > &weights){
	int i, j;
	node<double> temp;
	for(i = weights.size() ; i > 0; i--){
		for(j = 1; j < i; j++){
			if(weights[j-1].get_weight() > weights[j].get_weight()){
				temp = weights[j-1];
				weights[j-1] = weights[j];
				weights[j] = temp;
			}
		}
	}
}

void sortNodeVector(vector<node<double>* > &nodes){
	int i, j;
	node<double>* temp;
	for(i = nodes.size() ; i > 0; i--){
		for(j = 1; j < i; j++){
			if(nodes[j-1]->get_weight() > nodes[j]->get_weight()){
				temp = nodes[j-1];
				nodes[j-1] = nodes[j];
				nodes[j] = temp;
			}
		}
	}
}

void printWeightsFile(node<double>* root, int &position){
	fstream ofs("output.txt");
	ofs.seekp(position);
	if(root){
		if(root->isLeaf()){
			cout << (int) root->get_char()[0] << endl;
			ofs << (int) root->get_char()[0];
			ofs << " ";
			ofs << root->get_weight();
			cout <<root->get_weight() << endl;
			ofs << "\n";
			position = ofs.tellp();
			ofs.close();
		}
		if(root->left_child()){ 
			printWeightsFile(root->left_child(), position);
		}
		if(root->right_child()){
			printWeightsFile(root->right_child(), position);
		}	
	}
}

void Decode(node<double>* root, string encoded){
	 node<double>* ptrRoot = root;
	 string finalCharacter; 

	 for (int i = 0; i < encoded.size(); i ++){
	 	if (encoded[i] == '0'){
	 		if(ptrRoot->left_child())
	 			ptrRoot = ptrRoot->left_child();
	 	}
 		else if(encoded[i] == '1'){
 			if(ptrRoot->right_child())
 				ptrRoot = ptrRoot->right_child(); 	
	 	}
	 }
	 finalCharacter = ptrRoot->get_char();
}

//build a tree, given a vector of node pointers
node<double>* buildHuffmanTree(vector<node<double>* > &nodeVector){
	node<double>* newNode;
	while(nodeVector.size() > 1){
		sortNodeVector(nodeVector);					//sort the vector
		node<double>* smallest = nodeVector[0]; 		//the last item is smallest
		node<double>* nextSmallest = nodeVector[1];	//the second to last item is next smallest
		newNode = new node<double>(smallest->get_weight()+nextSmallest->get_weight(),
					smallest->get_char()+nextSmallest->get_char(), smallest,nextSmallest);	//make a new node
		nodeVector.erase(nodeVector.begin());						//we used smallest already
		nodeVector.erase(nodeVector.begin());						//we used nextSmallest, too
		nodeVector.push_back(newNode);				//add new node into the vector
		//cout << "Added node with weight " << nodes.back()->get_weight() << endl;
	}
	return nodeVector[0];
}

//determines if character is already in vector
bool charAlreadyEncountered(vector<node<double>* > nodes, string s){
	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i]->get_char().compare(s) == 0){
			return true;
		}
	}
	return false;
}

//returns index of character in vector
int nodeIndexOf(vector<node<double>* > nodes, string c){
	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i]->get_char().compare(c) == 0){
			return i;
		}
	}
	return -1;
}

void treeSize(node<double>* root, int &size){
	if(root->isLeaf()){
		size++;
	}
	else{
		treeSize(root->left_child(), size);
		treeSize(root->right_child(), size);
	}
}

node<double>* treeFromTextFile(string filename, vector<node<double>* > &nodes){
	ifstream infile;
	infile.open(filename.c_str());
	char nextChar;
	infile >> noskipws;
	while(infile.get(nextChar) && nextChar != infile.eof()){
		string thisChar;
		thisChar += nextChar;
		if(!charAlreadyEncountered(nodes, thisChar)){
			node<double>* temp = new node<double>(1,thisChar);
			nodes.push_back(temp);
		}
		else if(charAlreadyEncountered){
			nodes[nodeIndexOf(nodes, thisChar)]->inc_Weight();
		}
	}
	return buildHuffmanTree(nodes);
}
vector <char> generatePathFile(){
	vector<char> v;
	ifstream infile;
	infile.open("frequency.txt");
	while(!infile.eof()){
		string temp;
		getline(infile, temp);
		if(temp != ""){
			for (int i = 0; i < temp.length(); i ++){
				v.push_back(temp[i]);

				//cout << v.at(i)<< " the char in the vector" << endl;
			}

		}

	}
	return v;

}
void compressMethod(node<double> * root, vector<char> v, string fileName){
	ofstream outf(fileName.c_str());
	bitChar bchar;
	string tempPath;
	string temp;
	for (int i = 0; i<v.size(); i++){
		temp = v.at(i);

		tempPath += encode(root, temp);
		tempPath += "\n";
		//bchar.setBITS(tempPath);
		//bchar.writeBits(outf);
		//bchar.insertBits(outf);

		//cout <<"this is the path for " << v.at(i)<<" "<<tempPath<<endl;
	}
		bchar.setBITS(tempPath);
		//bchar.writeBits(outf);
		bchar.insertBits(outf);
		outf.close();
		cout <<"this is the path for " << v.at(1)<<" "<<tempPath<<endl;
}

void decompressMethod(string fileName){
	ifstream inf("compressfile.txt", ios::binary);
	bitChar bChar;
	string wat = bChar.readByBits(inf);
	cout << "Decompression: " << endl << wat;
}


void compressToFile(node<double>* root, ofstream &outf){
	node<double>* tempRoot = root;
	if(tempRoot->isLeaf()){
		string path = encode(tempRoot,tempRoot->get_char());
		//cout << "Attempting to write " << tempRoot->get_char() << endl;
		//ifstream inf("data.dat");
		bitChar bit;
		bit.setBITS(path);
		bit.insertBits(outf);
	}
	else{
		if(tempRoot->left_child()){
			compressToFile(tempRoot->left_child(), outf);
		}
		if(tempRoot->right_child()){
			compressToFile(tempRoot->right_child(), outf);
		}
	}
}

void printHCodeFile(node<double>* root, int &position, node<double>* staticRoot, string fileName){
	fstream ofs(fileName.c_str());
	ofs.seekp(position);
	node<double>* tempRoot = root;
	if(root->isLeaf()){
			cout << (int) root->get_char()[0] << " ";
			ofs << (int) root->get_char()[0];
			ofs << " ";
			ofs << encode(staticRoot,root->get_char());
			cout << encode(staticRoot,root->get_char()) << endl;
			ofs << "\n";
			position = ofs.tellp();
			ofs.close();
	}
	if(root->left_child()){ 
		printHCodeFile(root->left_child(), position,staticRoot,fileName);
	}
	if(root->right_child()){
		printHCodeFile(root->right_child(), position,staticRoot,fileName);
	}	
}

double compressionRatio(string normal, string compressed){
	double normalFileSize = 0.0;
	fstream nofs(normal.c_str(), fstream::in);
	char dummyChar;
	while(nofs >> noskipws >> dummyChar){
		normalFileSize+=1;
	}
	nofs.close();
	normalFileSize = normalFileSize * 8;

	double compressedFileSize = 0.0;
	fstream cofs(compressed.c_str(),fstream::in);
	while(cofs >> noskipws >> dummyChar){
		compressedFileSize +=1;
	}
	cofs.close();
	compressedFileSize =compressedFileSize * 8;

	return compressedFileSize / normalFileSize;

}