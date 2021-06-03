#include<iostream>
#include<bits/stdc++.h>
using namespace std;

const int MAX=100;
bool filled[MAX]={false};
class process{
	string name;
	int size;
	int beg_space;
	int end_space;
	public:
		process(string nam,int siz){
			this->name=nam;
			this->size=siz;
		}
		int ret_size(){
			return size;
		}
		int ret_end(){
			return end_space;
		}
		int ret_beg(){
			return beg_space;
		}
		string ret_name(){
			return name;
		}
		int set_space(int s,int e){
			beg_space=s;
			end_space=e;
		}
};
void fill(int beg,int end){
	for(int i=beg; i<=end; i++){
		filled[i]=true;
	}
}
void unfill(int beg,int end){
	for(int i=beg; i<=end; i++)
	filled[i]=false;
}
vector<process> pro;
int return_beg_first(int size){
	int count=0,beg_space,end=-1;	
	for(int i=0; i<MAX; i++){
		if(filled[i]){
			beg_space=i+1;
			count=0;
			continue;
		}
		count++;
		
		if(count==size){
    		end=i;
			fill(beg_space,end);
    		break;
    	}
	}
	if(end==-1)
	return -1;
	return beg_space;
}

int return_beg_worst(int size){
	int max=-1;
	int beg=0;
	int beg_temp=0;
	int count=0;
	for(int i=0; i<MAX; i++){
		if(filled[i]){
			beg_temp=i+1;
			count=0;
			continue;
		}
		count++;
		
		if(count>=size){
			if(max<count){
		    	max=count;
		    	beg=beg_temp;
	    	}
    	}
	}
	if(max==-1)
	return -1;
	return beg;
}

int return_beg_best(int size){
	int beg=-1,temp_beg=0,count=0;
	int min_size=MAX;
	for(int i=0; i<MAX; i++){
		if(filled[i]){
			
			if(count>=size){
				if(count<min_size){
					beg=temp_beg;
    				min_size=count;
    			}
			}
			
			temp_beg=i+1;
			count=0;
		}
		else count++;
	}
	if(count>=size && count<=min_size){
		beg=temp_beg;
		min_size=count;
	}
	return beg;
}
bool add_new(string name,int size,int order){
	process p(name,size);
	
	int count=0;
	int flag=0;
	int max=-1;
	int beg_space=-1;
	switch(order){
		case 1:{
	        beg_space=return_beg_first(size);
			break;
		}
		case 2:{
			beg_space=return_beg_worst(size);
			break;
		}
		case 3:{
			beg_space=return_beg_best(size);
			break;
		}
		
    }
	if(beg_space==-1)
	return false;
	
	p.set_space(beg_space,beg_space+size-1);
	pro.push_back(p);
	fill(beg_space,beg_space+size-1);
	return true;
}
int check(string name){
	int count=-1;
	for(auto it:pro){
		count++;
		string nam=it.ret_name();
		if(nam==name)
		return count;
	}
	return -1;
}
bool delete_process(string name){
	int result=check(name);
	if(result==-1)
	return false;
	int beg=pro[result].ret_beg();
	int end=pro[result].ret_end();
	
	int count=0;
	vector<process>::iterator it;
	for(it=pro.begin(); it!=pro.end(); it++){
		if(count==result){
			pro.erase(it);
			break;
		}
		count++;
	}
	unfill(beg,end);
	return true;
}
void print_gant(){
	cout<<endl<<"gant chart: "<<endl;
	cout<<"name\t\tbeg\tend"<<endl;
	
	for(auto it:pro){
		cout<<it.ret_name()<<"\t";
		if((it.ret_name()).length()<8)
		cout<<"\t";
		cout<<it.ret_beg()<<"\t"<<it.ret_end()<<endl;
	}
	cout<<endl;
}
void adding(int order){
	string name;
	int size;
	cin>>name>>size;
	bool result=add_new(name,size,order);
	if(!result)
	cout<<"SPACE IS INSUFFICIENT FOR PROCESS: "<<name<<endl;
	else
	cout<<"PROCESS "<<name<<" ALLOCATED"<<endl;	
}
void deleting(){
	string name="    ";
	cin>>name;
	bool result=delete_process(name);
	if(result)
	cout<<"PROCESS "<<name<<" DELETED"<<endl;
	else
	cout<<"PROCESS NOT EXIST"<<endl;	
}
int main(){
	freopen("in1.txt","r",stdin);
	freopen("out1.txt","w",stdout);
	
	int t;
	cin>>t;
	int order;
	cin>>order;
	
	int count=1;
	while(t--){
		cout<<"TASK :"<<count;
		// enter the number of process 
		int n,check,no_del;
		cin>>n;
		for(int i=0; i<n; i++){
			adding(order);
		}
		print_gant();
		cin>>no_del;
		for(int i=0; i<no_del; i++){
			deleting();
		}
		
		// enter 1 -to enter new process or 0-to delete process 2-exit
		cin>>check;
		while(check==0 || check==1){
			if(check==1)
				adding(order);
			else
		    	deleting();
		    	
		    cin>>check;	
		} 
		print_gant();
		pro.clear();
		unfill(0,99);
		count++;
		cout<<endl<<endl;
		
	}
}
