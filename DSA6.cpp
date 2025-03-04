
#include <iostream>
#include<queue>
using namespace std;
class Node{
public:
	int data;
	Node*next;
	Node(int x)
	{
		data=x;
		next=NULL;
	}
};

class Graph{
public:
	Node* G[20];
	bool visited[20];
	Graph(int n)
	{
		for(int i=0;i<n;i++)
		{
			G[i]=new Node(i);
		    visited[i]=false;
		}
	}

	void create(int n)
	{
		int s,d;
		for(int i=0;i<n;i++)
		{
			cout<<"enter Source and dESTINATION:";
			cin>>s>>d;


		Node* temp=G[s];
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=new Node(d);



		temp=G[d];
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=new Node(s);

		}
	}

	void DFS(int v)
	{
		cout<<v<<" ";
		visited[v]=true;
		Node* temp=G[v]->next;
		while(temp!=NULL){
			if(!visited[temp->data])
				DFS(temp->data);
		temp=temp->next;
	}

	}


};
int main()
{
	int n,edges,start;
	cout<<"Enter the no.of vertices:"<<endl;
	cin>>n;
	cout<<"Enter the no. of edges:"<<endl;
	cin>>edges;

	Graph g(n);
	g.create(edges);

	cout<<"Enter Starting Node for DFS:"<<endl;
	cin>>start;
	cout<<"DFS Traversal:"<<endl;
	g.DFS(start);
	cout<<endl;
	return 0;
}
