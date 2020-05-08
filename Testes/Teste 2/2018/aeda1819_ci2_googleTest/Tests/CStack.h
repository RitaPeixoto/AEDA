// CStack.h - uma Stack simples de inteiros implementada com arrays

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CStack { 
    int top, d_size, *items;
public:
    CStack(int size) { top = -1; d_size = size; items = new int[size]; }
    ~CStack() { delete []items;} 
    bool empty() const { return top==-1; } 
    int size() const { return top+1; } 
    void push(int elem) { 
        if(size()==d_size) cerr << "Stack Full!\n";
        else { top++; items[top] = elem; }
    }
    void pop() { 
        if(this->empty()) cerr << "Empty stack\n";
        else top--;
    }
    int peek() const { 
        if(this->empty()) cerr << "Empty stack\n";
        else return items[top];
        return 0;
    }
    string toStr() const {
        stringstream oss;
        for(int i = size()-1; i>=0; i--)
        	oss << items[i] << " ";
        return oss.str();
    }
    void print() const { 
        cout << "Stack with " << size() << " elements: ";
        for(int i = size()-1; i>=0; i--)
            cout << items[i] << " ";
        cout << endl;
    }
    void adicionaN(int n)
	{
        int v=peek();
        while(n!=0){
            v++;
            push(v);
            n--;
        }
    	
	}
	bool inverte4() 
	{   //Grupo 2 b)
        int i=size(),v,k,counter=4;
        vector<int> n;
        if(i<4) return false;
        else{
            while(counter!=0){
                v=peek();
                n.push_back(v);
                pop();
                counter--;
            }
            while(counter!=4){
                push(n[0+counter]);
                counter ++;
            }
            return true;
        }
	}


};

