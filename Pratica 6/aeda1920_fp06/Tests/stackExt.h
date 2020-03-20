# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
    stack<T> valores;
    stack<T> minimos;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

template <class T> 
bool StackExt<T>::empty() const
{
    if(valores.size()!=0) return false;
    return true;
}

template <class T>
T& StackExt<T>::top()
{
    return valores.top();
}


template <class T> 
void StackExt<T>::pop()
{
    if (valores.top() == minimos.top()){
        minimos.pop();
    }

    valores.pop();

}


template <class T> 
void StackExt<T>::push(const T & val)
{
    valores.push(val);
    if(minimos.empty())
        minimos.push(val);
    else if(minimos.top()>=val){
        minimos.push(val);
    }
}

template <class T> 
T& StackExt<T>::findMin()
{
    return minimos.top();
}

