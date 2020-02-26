#include <iostream>
#include<bits/stdc++.h>
#define MAX INT_MAX
using namespace std;


typedef struct Edge
{
	int index;
	int weight;
}Edge;

typedef struct Graph
{
	int vertex;
	string city;
	vector<Edge> edges;
}Graph;

typedef struct Solution
{
	int cost;
	vector<int> vertices;
}Solution;

typedef struct MEMO
{
	int weight;
	int prev_vertex;
}MEMO;

class bellFord {
private:
   vector<Graph> G;
   


public:
	bellFord ()
	{}
    bellFord (int n)
    {
		Graph v;
		Edge e;
		for (int i = 0; i < n; i++)
		{
			v.vertex = i;
			cout << "Enter City Name ["<< i << "]:";
			cin>>v.city;
			G.push_back(v);
		}
		int N;
		cout<<"Enter Number of Edges:";
		cin>>N;
		while(N--)
		{
			string source,destination;
			int wt,sourceI,desI;;

			cout<<"Source : ";
			cin>>source;
			cout<<"Destination : ";
			cin>>destination;
			cout<<"Weight : ";
			cin>>wt;

			sourceI = findIndexByCity(source);
			desI = findIndexByCity(destination);
			
			e.index = desI;
			e.weight = wt;

			G[sourceI].edges.push_back(e);
		}
    }
	void display()
	{
		for (vector<Graph> :: iterator i = G.begin() ; i != G.end(); i++)
		{
			cout << "For City "<<i->city<< '\n';
			for(vector<Edge> :: iterator j = i->edges.begin(); j != i->edges.end(); j++)
				cout<<"Neighbor :"<<G[j->index].city<<" Distance :"<<j->weight<<"\n";
			cout<<"\n";
		}
	}
	int findIndexByCity(string city)
	{
		int i = 0;
		for(vector<Graph> :: iterator vertex_iterator = G.begin(); 
		vertex_iterator != G.end(); vertex_iterator++)
		{
			if(!city.compare(vertex_iterator->city))
				return i;
			i++;
		}
		return -1;
	}

	bool findShortest()
	{
		int n = G.size();
		vector<Solution> solution;

		for(int i = 0;i <= n-1;i++)
		{
			Solution sol;
			sol.cost = 0;
			solve(sol,i);
			solution.push_back(sol);
		}
		
		int min = 0;
		for(int i =1;i<solution.size();i++)
			if(solution[min].cost > solution[i].cost)
				min = i;
		
		displayShortest(solution[min]);
	
	}

	void solve(Solution &sol,int start_index)
	{
		int num_cities = G.size();
		MEMO memo[num_cities][num_cities];
		
		for(int i=0;i<num_cities;i++)
			for(int j=0;j<num_cities;j++)
				memo[i][j].weight = MAX;
		
		for(int i = 0; i < num_cities;i++)
			for(int j = 0;j < num_cities;j++)
				if(j != start_index)
				{
					if(i == 0)
					{
						memo[i][j].weight = cost(start_index,j);
						memo[i][j].prev_vertex = -1; //signifies last vertex before cycle 
					}
					else
					{
						int min = MAX;
						int prev_vertex = -1;
						for(int k =0; k < num_cities; k++)
							if(k != start_index && cost(k,j) != MAX && min > cost(k,j) + memo[i-1][j].weight)
							{
								min = cost(k,j) + memo[i-1][k].weight;
								prev_vertex = k;
							}

						memo[i][j].weight = min;
						memo[i][j].prev_vertex = prev_vertex;
					}
				}
			
		

		//Tracing the possible shortest path with start vertex 
		sol.vertices.push_back(start_index);
		int min = MAX;
		int vertex = -1;
		for(int i =0;i<num_cities;i++)
			if(min > memo[num_cities -  1][i].weight + cost(start_index,i))
			{
				sol.cost = memo[num_cities - 1][i].weight + cost(start_index,i);
				vertex = i;
			}
		
		
		for(int i = num_cities -2 ;i >= 0; i--){
			if(vertex == -1)
				break;
			cout<<i<< " "<<vertex<<"\n";
	//         sol.vertices.push_back(memo[i][vertex].prev_vertex);
	//         vertex = memo[i][vertex].prev_vertex;
	}
	cout<<"\n\n\n"<<sol.cost;
    }



    
    
    
};


int main()
{
	int n;
	cout<<"Enter the Number of Cities : ";
	cin>>n;
	bellFord B(n);
	B.display();
	return 0;
}
