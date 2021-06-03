#include<iostream>
#include<bits/stdc++.h>
#define vec vector<pair<int,int>>
using namespace std;

ifstream infile("in2.txt");
ofstream outfile("out2.txt");

class process{
	private:
	    int id,at,bt;
    	int ct,wt,tat;
	
	public:
    	process(int pid){
	    	id=pid;
    	}
	    void input();
    	int get_at();
	    int get_bt();
    	int get_ct();
	    int get_tat();
    	int get_wt();
	    void set_cwt(int time); //set completion watiting and turnaround time
};
vector<process> pro;

void process::input(){
    infile>>at>>bt;	
}

int process::get_at(){
	return at;
}
int process::get_bt(){
	return bt;
}
int process::get_ct(){
	return ct;
}
int process::get_wt(){
	return wt;
}
int process::get_tat(){
	return tat;
}
void process::set_cwt(int time){
	ct=time;
	tat=ct-at;
	wt=tat-bt;
}
unordered_map<int,int> create_bt(int n){
	unordered_map<int,int> mp;
	for(int i=0; i<n; i++){
		mp[i+1]=pro[i].get_bt();
	}
	return mp;
}
int  find_min_id(vec ap,unordered_map<int,bool>check){
	int min_arrival_id;
	for(auto it:ap){
     	int id=it.second;
		if(!check[id]){
			min_arrival_id=it.second;
        }
	}	
	int arriving = pro[min_arrival_id-1].get_at();
	return arriving;
}
void compute(vec ap,int n){
	unordered_map<int,int> bt;
	bt=create_bt(n);
	unordered_map<int,bool> check;
	
	for(int i=0; i<n; i++){
		check[i+1]=false;
	}
	
	int count=0,ct=0,j=0;
	int ready_count=0;
	
	ct=ap[0].first;
	int min_arrival_id=ap[0].second;
	int j_count = 0;
	j=ap[j_count].second;
	
	
	outfile<<"Id"<<"\t"<<"TI"<<"\t"<<endl;
	int loop=0;
	while(count!=n){
		loop++;
		int flag=0;
		while(check[j]){
			j_count++;
			if(j_count>=n){
				j_count=0;
				flag++;
			}
			j=ap[j_count].second;
			if(flag==2)
			break;
		}
	
		if(flag==2)
		break;
	
		if(ap[j_count].first<=ct){
			int curr_bt=bt[j];
			if(curr_bt==1 || curr_bt==2){
				bt[j]=0;
				check[j]=true;
				count++;
				outfile<<j<<"\t"<<ct<<"\tprocess completed"<<endl;
				ct=ct+curr_bt;
				pro[j-1].set_cwt(ct);
	
				if(count==n)
				break;
				
				if(j==min_arrival_id){
					int arriving = find_min_id(ap,check);
					if(arriving>ct)
					ct=arriving;
				}
			}
			else{
    			bt[j]=bt[j]-2;
    			outfile<<j<<"\t"<<ct<<endl;
    			ct=ct+2;
    		}
		}
		j_count++;
		if(j_count==n)
		j_count=0;
		j=ap[j_count].second;
	}
	
}

void execute(int n){
	vec ap;
	for(int i=0; i<n; i++){
		int id;
		infile>>id;
		process p(id);
		p.input();
		ap.push_back(make_pair(p.get_at(),id));
		pro.push_back(p);
	}
	sort(ap.begin(),ap.end());
	outfile<<"PROCESS EXECUTION ORDER"<<endl;
	int count_next=0;
	for(int i=0; i<n; i++)
	{   
	    count_next++;
    	if(count_next%29==0)
    	outfile<<endl;
		if(i==n-1)
		outfile<<ap[i].second<<endl;
		else
		outfile<<ap[i].second<<" -> ";
	}
	
	compute(ap,n);
}

void avg_wt(int n){
	int avg=0;
	for(int i=0; i<n; i++){
		avg=avg+pro[i].get_wt();
	}
	avg=avg/n;
	outfile<<"Average waiting time: "<<avg<<endl;
}
void avg_throughput(int n){
	float avg=0;
	float temp=n;
	for(int i=0; i<n; i++){
		avg=avg+pro[i].get_ct();
	}
	avg=temp/avg;
	outfile<<"Average throughput is : "<<avg<<endl;
}
void avg_tat(int n){
	int avg=0;
	for(int i=0; i<n; i++){
		avg=avg+pro[i].get_tat();
	}
	avg = avg/n;
	outfile<<"Average turn around time: "<<avg<<endl;
}
int main(){
	if(!infile){
		cout<<"File is missing";
		return 0;
	}
	int t;
	infile>>t;
	int count=1;
	while(t--){
		outfile<<"PROCESS : "<<count<<endl;
		int n;
		infile>>n;
		
		execute(n);
		avg_wt(n);
		avg_tat(n);
		avg_throughput(n);
		outfile<<endl;
		outfile<<"\t\t---------------------------------"<<endl<<endl;
		pro.clear();
		outfile<<endl;
		count++;
	}
}
