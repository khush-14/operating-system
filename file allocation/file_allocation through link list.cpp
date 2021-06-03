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
	link_list *root;
	string name;
	int size,start,end;
	public:
		file(link_list* head,string nam,int siz){
			root=head;
			name=nam;
			size=siz;
			compute_start_end();
		}
		void compute_start_end(){
			link_list* val=root;
			start=root->address;
			while((val->next)!=NULL){
				val=val->next;
			}
			end=val->address;
		}
		string ret_name(){
			return name;
		}
		int ret_size(){
			return size;
		}
		link_list* ret_head(){
			return root;
		}
		int ret_beg(){
			return start;
		}
		int ret_end(){
			return end;
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
	
	
	link_list *head,*last,*temp;
	head = new link_list();
	head->address=next_loc();
	last=head;
	arr[head->address]=true;	
	count_size=size-1;
	while(count_size--){
		temp = new link_list();
		temp->address=next_loc();
		arr[temp->address]=true;
		last->next=temp;
		last=temp;
	}
	last->next=NULL;
	
	file f(head,name,size);
	pro.push_back(f);
	return true;
}

int check(string name){
	int count=-1;
	for(auto it:pro){
		count++;
		string value=it.ret_name();
		if(value==name){
			return count;
		}
	}
	return count;
}

bool deleting(string name){
	int i=check(name);
	if(i==-1)
	return false;
	
	link_list* head= pro[i].ret_head();
	if(head){
	
		int size=pro[i].ret_size();
		link_list *val= head;
		
		// convert all address location to unoccupied
		while(val!=NULL){
			arr[val->address]=false;
			val=val->next;
		}
		
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

bool delete_pro(){ 
    string name;
    cin>>name;
	bool result=deleting(name);
	if(result){
		cout<<"File "<<name<<" is deallocated"<<endl;
	}	
	else
	cout<<"File "<<name<<" is not present"<<endl;
}
void adding(){
	string name;
	int size;
	cin>>name>>size;
	bool result=add_new(name,size);
	if(result)
	cout<<"File "<<name<<" is allocated"<<endl;
	else
	cout<<"File "<<name<<" is not allocated"<<endl;
}

void print_gant(){
	cout<<endl<<"File allocation chart: "<<endl;
	cout<<"FILE NAME\ts_loc\tend_loc"<<endl;
	for(auto it:pro){
		string name=it.ret_name();
		int beg=it.ret_beg();
		int end=it.ret_end();
		cout<<name<<"\t";
		if(name.length()<8)
		cout<<"\t";
		cout<<beg<<"\t"<<end<<endl;
	}
}
void random_alloc(){
	int check;
	cin>>check;
	while(check!=2){
		if(check==1)
			adding();
		else
	    	delete_pro();
		    	
	    cin>>check;	
	}
	
	return ; 
		
}
void initialize(int count){
	unfill();
	pro.clear();
	cout<<endl<<"FILE ALLOCATION TASK "<<count<<endl;
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
			delete_pro();
		}
		
		// enter 1 -to enter new process or 0-to delete process 2-exit
		random_alloc();
		print_gant();
	}
}
