#include<iostream>
#include<bits/stdc++.h>
using namespace std;

const int MAX=100;
bool arr[MAX]={false};

ifstream infile("in1.txt");
ofstream outfile("out1.txt");

typedef struct link_list{
	int address;
	struct link_list* next;
};

void unfill(){
	for(int i=0; i<MAX; i++)
	arr[i]=false;
}

class file{
	link_list* head;
	string name;
	list<link_list*> adj;
	int size;
	int head_add;
	public:
		file(link_list* val,int siz,string nam){
			head=val;
			size=siz;
			name=nam;
			head_add=head->address;
		}
		void add_next(link_list* temp){
			adj.push_back(temp);
		}
		int ret_size(){
			return size;
		}
		int ret_add(){
			return head_add;
		}
		link_list* ret_head(){
			return head;
		}
		string ret_name(){
			return name;
		}
		void delete_file(){
			for(auto it:adj){
				int loc=it->address;
				arr[loc]=false;
			}
		}
};
vector<file> pro;


int next_loc(){
	for(int i=0; i<MAX; i++){
		if(!arr[i]){
			return i;
		}
	}
}

bool add_new(string name,int size){
	int count_size=0;
	for(int i=0; i<MAX; i++){
		if(!arr[i])
		count_size++;
	}
	
	if(count_size<size)
	return false;
	
	
	link_list *head,*temp;
	head = new link_list();
	head->address=next_loc();
	arr[head->address]=true;
	
	file f(head,size,name);
		
	count_size=size-1;
	while(count_size--){
		temp = new link_list();
		temp->address=next_loc();
		arr[temp->address]=true;
		f.add_next(temp);
	//	cout<<temp->address<<" ";
	}
	pro.push_back(f);
	return true;
}
int check(string name){
	int count=-1;
	for(auto it:pro){
		count++;
		string value=it.ret_name();
		if(value==name)
		return count;
	}
	return -1;
}
bool delete_file(string name){
	int i=check(name);
	if(i==-1)
	return false;
	
	link_list* head= pro[i].ret_head();
	if(head){
		// convert all address location to unoccupied
		pro[i].delete_file();
		//delete from vector
		int count=0;
    	vector<file>::iterator it;
    	for(it=pro.begin(); it!=pro.end(); it++){
	    	if(count==i){
		    	pro.erase(it);
			    break;
    		}
	    	count++;
    	}
    	return true;
	}
	return false;

}
void adding(){
	string name;
	int size;
	cin>>name>>size;
	bool result = add_new(name,size);
	if(result)
	cout<<"File "<<name<<" Allocated"<<endl;
	else
	cout<<"Insufficient space file: "<<name<<endl;
}
void deleting(){
	string name;
	cin>>name;
	bool result = delete_file(name);
	if(result)
	cout<<"File "<<name<<" Deallocated"<<endl;
	else
	cout<<name<<" File not exist"<<endl;
}
void print_gant(){
	cout<<endl<<"File allocation chart: "<<endl;
	cout<<"FILE NAME\thead location"<<endl;
	for(auto it:pro){
		string name=it.ret_name();
		int address=it.ret_add();
		cout<<name<<"\t";
		if(name.length()<8)
		cout<<"\t";
		cout<<address<<endl;
	}
}
void random_alloc(){
	int check;
	cin>>check;
	while(check!=2){
		if(check==1)
			adding();
		else
	    	deleting();
		    	
	    cin>>check;	
	}
	
	return ; 
		
}
void initialize(int count){
	unfill();
	pro.clear();
	cout<<endl<<endl<<"FILE ALLOCATION TASK "<<count<<endl<<endl;
	return ;
}

int main(){
	freopen("in1.txt","r",stdin);
	freopen("out1.txt","w",stdout);
	
	int t;
	cin>>t;
	int count=0;
	while(t--){
		count++;
		initialize(count);
		
		// enter the number of process 
		int n;
		cin>>n;
		for(int i=0; i<n; i++){
			adding();
		}
		
		cout<<endl;
		print_gant();
		cout<<endl;
		
		int no_del;
		cin>>no_del;
		for(int i=0; i<no_del; i++){
			deleting();
		}
		
		// enter 1 -to enter new process or 0-to delete process 2-exit
		random_alloc();
		print_gant();
		cout<<endl;
	}
}
