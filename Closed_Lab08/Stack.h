#ifndef STACK
#define STACK 1

template <class Item>
class Stack
{
private:
    
    struct Node
    {
	Item data;
	Node *next;
    };
    
    Node *top;
    int length;

public:
    
    Stack ()
    {
	top = NULL;
	length = 0;
    }
	
    ~Stack ()
    {
	Node *temp;
	temp = top;
	while (temp != NULL)
	{
	    top = top->next;
	    delete temp;
	    temp = top;
	}
    }
	
    void Push (Item& x)
    {
	Node *temp;
	temp = new Node;
	temp->data = x;
	temp->next = top;
	top = temp;
	length++;
    }
	
    void Pop (Item& x)
    {
	Node *temp;
	temp = top;
	x = temp->data;
	top = temp->next;
	delete temp;
	length--;
    }
	
    int Length ()
    {
	return length;
    }
    
};

#endif // STACK
