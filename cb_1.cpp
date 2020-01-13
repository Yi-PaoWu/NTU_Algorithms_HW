#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
//#include "disjoint_sets.h"
#include "util.h"

using namespace std;

bool Same_Component(Node_Disjoint*, Node_Disjoint*);
int Union(Disjoint_Sets*, Disjoint_Sets*,int ,int );
void QuickSort(vector<Edge>& );
void QuickSortSubVector(vector<Edge>& , int , int );
int Partition(vector<Edge>& , int , int ); 
bool Compare_Edges(Edge ,Edge );
int Has_Cycle(Graph ,int , vector<int>& , vector<Weight_Parent>& );
Cut_Directed Find_Edge(vector<Weight_Parent>& ,int , Graph );


int main(int argc,char* argv[]){

	// ======= READ FILE ======== //
	cout<<" ===== READ FILE =====  "<<endl;
	ifstream file_in;
	file_in.open(argv[1],ios::in);
	vector<int> data;
	char letter;
	int num=0;
	int num_vertices=0;
	long num_edges=0;
	if(file_in.is_open()){
		file_in>>letter;
		file_in>>num_vertices;
		file_in>>num_edges;
		while(file_in >> num) data.push_back(num);
	}

	vector<int> ans;
	int total_weight=0;
	// ======= disjoints sets ======= //

	//int num_vertices = data[0];
	//int num_edges = data[1];

	//=================================================================
	//********************   UNDIRECTED    ****************************
	//=================================================================
	
	if(letter == 'u'){
		vector<Disjoint_Sets> Sets;
		vector<Disjoint_Sets*> Mem_Sets;
		
		// ==== INITIALIZE ===== //
		cout<<"===== state iniatial ===="<<endl;

		
		for(int i=0;i<=num_vertices;i++){
			Node_Disjoint* a = new Node_Disjoint(i);
			//Vertices.push_back(*a);
			Disjoint_Sets set(a);
			//Mem_Sets.push_back(&set);
			Sets.push_back(set);
			//delete a;
		}



		for(int i=0;i<=num_vertices;i++){
			Mem_Sets.push_back(&Sets[i]);
		}
		/*for(int i=0;i<Sets.size();i++){
			cout<<i<<" : " ;
			Sets.at(i).PrintAll();
		}*/
		cout<<"===== finish iniatial ==== "<<endl;
		//cout<<"Sets[0].firstNode = "<<Sets[0].firstNode<<"   NodeSets[0].firstNode->repreNode = "<<Sets[0].firstNode->repreNode<<endl;
		//cout<<"Sets[0].firstNode->data = "<<Sets[0].firstNode->data<<"   NodeSets[0].firstNode->repreNode->data = "<<Sets[0].firstNode->repreNode->data<<endl;
		
		// ==== SORT WEIGHT ==== //
		vector<Edge> Edges;
		cout<<"num_edges = "<<num_edges<<endl;
		//vector<Edge> Ans_Edges;
		for(int i=0;i<num_edges;i++){
			//Edge* b = new Edge(Sets[data[3*i]].firstNode,Sets[data[3*i+1]].firstNode,data[3*i+2]);
			Edge b(Sets[data[3*i]].firstNode,Sets[data[3*i+1]].firstNode,data[3*i+2]);
			Edges.push_back(b);
			//cout<<"i = "<<i<<endl;
		}
		
		/*for(int i=0;i<num_edges;i++){
			cout<<"Edge[ "<<i<<" ] : vertex_1 = "<<Edges[i].vertex_1->data<<" vertex_2 = "<<Edges[i].vertex_2->data<<" weight = "<<Edges[i].weight<<endl;
		}
		*/
		cout<<"========= QUICKSORT =========="<<endl;
		
		//QuickSort(Edges);
		sort(Edges.begin(),Edges.end(),Compare_Edges);
		/*for(int i=0;i<num_edges;i++){
			cout<<"Edge[ "<<i<<" ] : vertex_1 = "<<Edges[i].vertex_1->data<<" vertex_2 = "<<Edges[i].vertex_2->data<<" weight = "<<Edges[i].weight<<endl;
		}*/

		
		cout<<" ======= START ====== "<<endl;
		for(int j=0;j<num_edges;j++){
			//cout<<"-----QQ----"<<endl;
			if(!Same_Component(Edges[j].vertex_1,Edges[j].vertex_2)){

				//cout<<"==== NOT same set ==== "<<endl;
				//Ans_Edges.push_back(Edges[j]);

				//temp = Union(&Sets[Edges[j].vertex_1->data],&Sets[Edges[j].vertex_2->data],mem[Edges[j].vertex_1->data],mem[Edges[j].vertex_2->data]);
				

				// ==== UNION ===== //
				int  x =  Edges[j].vertex_1->data; // NOW Edge vertex1
				int  y =  Edges[j].vertex_2->data; // NOW Edge vertex2
				//cout<<"x = "<<x<<" y = "<<y<<endl;
				if(Mem_Sets[x]->weight >= Mem_Sets[y]->weight){
					//cout<<"case 1!"<<endl;
					Mem_Sets[x]->lastNode->NextNode = Mem_Sets[y]->firstNode;
					//cout<<"Sets[x].lastNode->data = "<<Sets[x].lastNode->data<<endl;
					//cout<<"Sets[x].lastNode->NextNode = "<<Sets[x].lastNode->NextNode->data<<endl;
					Mem_Sets[x]->lastNode = Mem_Sets[y]->lastNode;
					Mem_Sets[x]->weight = Mem_Sets[y]->weight+Mem_Sets[x]->weight;
					//cout<<"Sets[x].lastNode = "<<Sets[x].lastNode->data<<endl;
					Node_Disjoint* node;
					Node_Disjoint* current;
					node = Mem_Sets[x]->firstNode->repreNode;
					current = Mem_Sets[y]->firstNode;
					while(current !=0){
						//cout<<"current->data = "<<current->data<<endl;
						Mem_Sets[current->data] = Mem_Sets[x];
						//Sets[current->data].firstNode = Sets[x].firstNode;
						//Sets[current->data].lastNode = Sets[x].lastNode;
						//Sets[current->data].PrintAll();
						current->repreNode = node;
						current = current->NextNode;
					}
				}
				else{
					//cout<<"case 2!"<<endl;
					Mem_Sets[y]->lastNode->NextNode = Mem_Sets[x]->firstNode;
					//cout<<"Sets[y].lastNode->data = "<<Sets[y].lastNode->data<<endl;
					//cout<<"Sets[y].lastNode->NextNode = "<<Sets[y].lastNode->NextNode->data<<endl;
					Mem_Sets[y]->lastNode = Mem_Sets[x]->lastNode;
					Mem_Sets[y]->weight = Mem_Sets[y]->weight+Mem_Sets[x]->weight;

					Node_Disjoint* node;
					Node_Disjoint* current;
					node = Mem_Sets[y]->firstNode->repreNode;
					current = Mem_Sets[x]->firstNode;
					while(current !=0){
						//cout<<"current->data = "<<current->data<<endl;
						Mem_Sets[current->data] = Mem_Sets[y];
						//Sets[current->data].firstNode = Sets[y].firstNode;
						//Sets[current->data].lastNode = Sets[y].lastNode;
						//Sets[current->data].PrintAll();
						current->repreNode = node;
						current = current->NextNode;
					}
				}

				/*for(int i=0;i<num_vertices;i++){
					cout<<"Set[ "<<i<<" ] : ";
					Sets[i].PrintAll();
				}*/
			}
			else{
				//cout<<" ==== Same Set ==== "<<endl;
				//cout<<Edges[j].vertex_1->data<<"  "<<Edges[j].vertex_2->data<<"  "<<Edges[j].weight<<endl;
				ans.push_back(Edges[j].vertex_1->data);
				ans.push_back(Edges[j].vertex_2->data);
				ans.push_back(Edges[j].weight);
			}
		}
		cout<<" ==== FINISH ====="<<endl;
		
		/*for(int i=0;i<ans.size();i++){
			cout<<ans[i]<<endl;
		}*/
		for(int i=0;i<ans.size();i+=3){
			total_weight += ans[i+2];
		}
		cout<<"total_weight = "<<total_weight;
	}

	//===============================================================================================================
	//*************************************         DIRECTED         ************************************************
	//================================================================================================================

	else if(letter == 'd'){

		cout<<"num_edges = "<<num_edges<<endl;
		Graph g(num_vertices);
		vector<int> color;// 0 : white 1 : grey 2 : black 
		vector<int> temp;
		vector<Weight_Parent> wp;
		vector<Cut_Directed> ans_list;
		for(int i=0;i<num_edges;i++){
			color.push_back(0);
			Weight_Parent a(0,0);
			wp.push_back(a);
		}
		/*for(int i=0;i<num_vertices;i++){
			g.list[i].InsertFront(i,0);
		}*/
		for(int i=0;i<num_edges;i++){
			g.list[data[3*i]].InsertBack(data[3*i+1],data[3*i+2]);
			
		}

		for(int i=0;i<num_vertices;i++){
			cout<<"list "<<i<<" : ";
			g.list[i].PrintAll();
		}
		int x=0;
		for(int i=0;i<num_vertices;i++){
			//cout<<" ------------  i =  "<<i<<"  ---------------"<<endl;
			temp = color;
			x = Has_Cycle(g,i,temp,wp);
			//cout<< x<<endl;
			while(x != -99999){
				//cout<<" ------  CYCLE!!!  ------"<<endl;
				Cut_Directed a(0,0,0);
				a = Find_Edge(wp,x,g);
				ans_list.push_back(a);
				//cout<<"Cut Edge : "<<a.vertex_1<<" "<<a.vertex_2<<" "<<a.weight<<endl;
				g.list[a.vertex_1].Delete(a.vertex_2);
				/*for(int i=0;i<num_vertices;i++){
					cout<<"list "<<i<<" : ";
					g.list[i].PrintAll();
				}*/
				temp = color;
				x = Has_Cycle(g,i,temp,wp);
			}
			color = temp;
		}
		cout<<"===================== ANS!!! ================= :(((((("<<endl;
		for(int i=0;i<ans_list.size();i++){
			cout<<"Cut Edge : "<<ans_list[i].vertex_1<<" "<<ans_list[i].vertex_2<<" "<<ans_list[i].weight<<endl;
			ans.push_back(ans_list[i].vertex_1);
			ans.push_back(ans_list[i].vertex_2);
			ans.push_back(ans_list[i].weight);

			total_weight += ans_list[i].weight;
		}


		cout<<"total_weight = "<<total_weight;

	}


	// ==== OUTPUT FILE ==== // 

	ofstream file_out;
	file_out.open(argv[2],ios::out);
	if (file_out.is_open()){
		file_out<<total_weight<<endl;
		for (int i=0;i<ans.size();i+=3){
			file_out<<ans[i]<<" "<<ans[i+1]<<" "<<ans[i+2]<<endl;
		}
	}
	file_out.close();

	return 0 ;
}






bool Same_Component(Node_Disjoint* node1, Node_Disjoint* node2){
	//cout<<" ==== Same_Component?!?! ====="<<endl;
	//cout<<node1->Find_Set()<<"  "<<node2->Find_Set()<<endl;
	if (node1->Find_Set() == node2->Find_Set()){
		return true;
	}
	else return false;
}

void QuickSort(vector<Edge>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void QuickSortSubVector(vector<Edge>& data, int low, int high) {
    int pivot =0;
    if(low<high){
    pivot =  Partition(data, low , high);
    QuickSortSubVector(data, low,pivot-1);
    QuickSortSubVector(data, pivot+1,high);  
    }
}

bool Compare_Edges(Edge x,Edge y){
	return x.weight > y.weight;
}

int Partition(vector<Edge>& data, int low, int high) {
    int x = data[high].weight;
    int i = low-1;
    for( int j = low; j<=high-1 ; j++){
		if ( data[j].weight >= x){
		    i =i+1;
	  	    swap(data[i],data[j]);
	        }    
    }
    swap(data[i+1],data[high]);
    return i+1;
}


int Has_Cycle(Graph g,int x, vector<int>& color, vector<Weight_Parent>& parent){
	//cout<<" IN Has_Cycle :   x = "<<x<<endl;
	color[x] = 1;
	Node* cur = g.list[x].firstNode;
	int temp =0;
	for(int i=0;i<g.list[x].size;i++){
		//cout<<" ==============================="<<endl;
		//cout<<"i = "<<i<<"   cur->data = "<<cur->data<<endl;
		/*for(int j=0;j<color.size();j++){
			cout<<"COLOR : "<<j<<" "<<color[j]<<"  ";
		}*/
		parent[cur->data].parent= x;
		parent[cur->data].weight= cur->weight;
		if(color[cur->data] == 0){
			temp = Has_Cycle(g,cur->data,color,parent);
			if(temp != -99999) return temp;	
		}
		else if (color[cur->data] == 1) return cur->data;
		cur = cur->NextNode;
		//cout<<"================  FIN   ========"<<endl;
	}
	color[x] = 2;
	return -99999;
}

Cut_Directed Find_Edge(vector<Weight_Parent>& wp,int start, Graph g){
	Cut_Directed ans(0,0,0);
	int current = wp[start].parent;
	int minimum  = 0;
	if(wp[start].weight>0) minimum = wp[start].weight/g.list[start].size;
	else minimum = wp[start].weight*g.list[start].size;
	ans.vertex_1 = wp[start].parent;
	ans.vertex_2 = start;
	ans.weight   = wp[start].weight;
	cout<<"--------------------------"<<endl;
	while(current!=start){
		//int temp =0;
		//if(wp[current].weight>0) temp = wp[current].weight/g.list[current].size;
		//else temp = wp[current].weight*g.list[current].size;
		if(minimum >wp[current].weight/g.list[current].size){
			minimum =  wp[current].weight/g.list[current].size;
			//cout<<"current : "<<current<<" minimum : "<<minimum<<endl;
		//if(minimum > wp[current].weight){
		//	minimum =  wp[current].weight;
			ans.vertex_1 = wp[current].parent;
			ans.vertex_2 = current;
			ans.weight   = wp[current].weight;
		}
		current = wp[current].parent;
	}
	cout<<"CUT : "<<ans.vertex_1<<"  "<<ans.vertex_2<<"  weight : "<<ans.weight<<endl;
	return ans;
}











































/*int Union(Disjoint_Sets* set1, Disjoint_Sets* set2,int a,int b){
	if(set1->weight >= set2->weight){
		set1->lastNode->NextNode = set2->firstNode;
		Node_Disjoint* node;
		Node_Disjoint* current;
		node = set1->firstNode->repreNode;
		cout<<"node : "<<node<<endl;
		current = set2->firstNode;
		while(current !=0){
			cout<<"current :"<<current<<endl;
			current->repreNode = node;
			cout<<"current->repre:"<<current->repreNode<<endl;
			current = current->NextNode;
		}
		cout<<"set2->repre:"<<set2->firstNode->repreNode<<endl;
		set1->lastNode = set2->lastNode;
		set2 = set1;
		set1->weight = set2->weight+set1->weight;
		return a;
	}
	else{
		set2->lastNode->NextNode = set1->firstNode;
		Node_Disjoint* node;
		Node_Disjoint* current;
		node = set2->firstNode->repreNode;
		cout<<"node : "<<node<<endl;
		current = set1->firstNode;
		while(current !=0){
			cout<<"current :"<<current<<endl;
			current->repreNode = node;
			cout<<"current->repre:"<<current->repreNode<<endl;
			current = current->NextNode;
		}
		cout<<"set1->repre:"<<set1->firstNode->repreNode<<endl;
		set2->lastNode = set1->lastNode;
		set1 = set2;
		set2->weight = set2->weight+set1->weight;
		return b;
	}
	/*if(set1.weight >= set2.weight){
		set1.lastNode->NextNode = set2.firstNode;
		Node_Disjoint* node;
		Node_Disjoint* current;
		node = set1.firstNode->repreNode;
		cout<<"node : "<<node<<endl;
		current = set2.firstNode;
		while(current !=0){
			cout<<"current :"<<current<<endl;
			current->repreNode = node;
			cout<<"current->repre:"<<current->repreNode<<endl;
			current = current->NextNode;
		}
		cout<<"set2->repre:"<<set2.firstNode->repreNode<<endl;
		set1.lastNode = set2.lastNode;
		set2 = set1;
		set1.weight = set2.weight+set1.weight;
		return a;
	}
	else{
		set2.lastNode->NextNode = set1.firstNode;
		Node_Disjoint* node;
		Node_Disjoint* current;
		node = set2.firstNode->repreNode;
		cout<<"node : "<<node<<endl;
		current = set1.firstNode;
		while(current !=0){
			cout<<"current :"<<current<<endl;
			current->repreNode = node;
			cout<<"current->repre:"<<current->repreNode<<endl;
			current = current->NextNode;
		}
		cout<<"set1->repre:"<<set1.firstNode->repreNode<<endl;
		set2.lastNode = set1.lastNode;
		set1 = set2;
		set2.weight = set2.weight+set1.weight;
		return b;
	}
}*/



			/*if(Sets[sets_mem[data[j]]].weight >= Sets[sets_mem[data[j+1]]].weight){
				cout<<"1:data = "<<data[j]<<"  list in sets_mem = "<<sets_mem[data[j]]<<endl;
				Sets[sets_mem[data[j]]].list.PrintAll();
				Union(Sets[sets_mem[data[j]]].list, Sets[sets_mem[data[j+1]]].list, data[j+2]);
				Sets[sets_mem[data[j]]].weight = Sets[sets_mem[data[j]]].weight+Sets[sets_mem[data[j+1]]].weight;
				sets_mem[data[j+1]] = sets_mem[data[j]];

				cout<<"_________END OF ONE UNION_________"<<endl;
			}
			else{
				cout<<"2:data = "<<data[j+1]<<"  list in sets_mem = ";
				Sets[sets_mem[data[j+1]]].list.PrintAll();
				Union(Sets[sets_mem[data[j+1]]].list, Sets[sets_mem[data[j]]].list,data[j+2]);
				Sets[sets_mem[data[j+1]]].weight = Sets[sets_mem[data[j+1]]].weight+Sets[sets_mem[data[j+1]]].weight;
				sets_mem[data[j]] = sets_mem[data[j+1]];
			}
			int x,y,w;
			x = Sets[sets_mem[data[j]]].list.ReturnAns_X();
			y = Sets[sets_mem[data[j]]].list.ReturnAns_Y();
			w = Sets[sets_mem[data[j]]].list.ReturnAns_Weight();
			cout<<x<<"  "<<y<<"  "<<w<<endl;
		}
		else{
			// ==== UNION ==== //
			if(Sets[sets_mem[data[j]]].weight >= Sets[sets_mem[data[j+1]]].weight){
				cout<<"1:data = "<<data[j]<<"  list in sets_mem = "<<sets_mem[data[j]]<<endl;
				Sets[sets_mem[data[j]]].list.PrintAll();
				Union(Sets[sets_mem[data[j]]].list, Sets[sets_mem[data[j+1]]].list, data[j+2]);
				Sets[sets_mem[data[j]]].weight = Sets[sets_mem[data[j]]].weight+Sets[sets_mem[data[j+1]]].weight;
				sets_mem[data[j+1]] = sets_mem[data[j]];

				cout<<"_________END OF ONE UNION_________"<<endl;
			}
			else{
				cout<<"2:data = "<<data[j+1]<<"  list in sets_mem = ";
				Sets[sets_mem[data[j+1]]].list.PrintAll();
				Union(Sets[sets_mem[data[j+1]]].list, Sets[sets_mem[data[j]]].list,data[j+2]);
				Sets[sets_mem[data[j+1]]].weight = Sets[sets_mem[data[j+1]]].weight+Sets[sets_mem[data[j+1]]].weight;
				sets_mem[data[j]] = sets_mem[data[j+1]];
			}

		}*/
