//shortest job first
#include<iostream>
#include<bits/stdc++.h>
#define vec vector<pair<int,int>>
using namespace std;

ifstream infile("in1.txt");
ofstream outfile("out2.txt");

class process{
	int process_id;
	
	int at,bt;
	//arrival time,burst time, turn around time,completion time, waiting time.
	public : 
	int tt,ct,wt;
    	process(int id){
		    process_id=id;
	    }
    	void set_input();
    	void set_ct(int time);
	    int get_bt();
	    int get_at();
	    int get_ct();
	    int get_tt();
	    int get_wt();
	    void print_gant();
};
vector<process> pr;
int process::get_at(){
	return at;
}
int process::get_bt(){
	return bt;
}
void process::set_input(){
	infile>>at;
	infile>>bt;
}
void process::print_gant(){
	outfile<<process_id<<"\t"<<at<<"\t"<<bt<<"\t  "<<ct<<"\t   "<<tt<<"\t\t"<<wt;
}
int process::get_ct(){
	return ct;
}
int process::get_tt(){
	return tt;
}
int process::get_wt(){
	return wt;
}
void process::set_ct(int time){
	 ct=time;
	 tt=ct-at;
	 wt=tt-bt;
}
vector<int> compute(int n,vec vbt,vec vat){
	unordered_map<int,bool> check;
	for(int i=0; i<n; i++){
		check[i+1]=false;
	}
	
	int arrival,count=0,count1=0;
	int ct=0;
	vector<int> v;
	while(count!=n && count1!=n){
		while(check[vbt[count].second])
		count++;
		while(check[vat[count1].second])
		count1++;
		int id = vbt[count].second;
		int id1 = vat[count1].second;
		int final_id = id; // only initially set
		
		arrival = pr[id-1].get_at();
		if(arrival > ct){ 
		    final_id = id1;
		    count1++;
		}
		else{
			final_id = id;
			count++;	
		}
		v.push_back(final_id);
		ct=ct+pr[final_id-1].get_bt();
		pr[final_id-1].set_ct(ct);
		check[final_id]=true;
    }
    return v;
}

vec create_at(int n){
	vec v;
	for(int i=0; i<n; i++){
		int id=i+1;
		int at=pr[i].get_at();
		v.push_back(make_pair(at,id));
	}
	sort(v.begin(),v.end());
	return v;
}
vec create_bt(int n){
	vec v;

	for(int i=0; i<n; i++){
		int id=i+1;
		int bt=pr[i].get_bt();
		v.push_back(make_pair(bt,id));
	}
	sort(v.begin(),v.end());
	return v;
}
vector<int> input(int n){
	// burst time and process id
	
	vec vbt;
	vec vat;
	
	for(int i=0; i<n; i++){//initial id =1
	    int id;
	    infile>>id;
		process obj(id);
		obj.set_input();
		pr.push_back(obj);
	}	
	vat=create_at(n);
	vbt=create_bt(n);
	vector<int> pids; //id to store as execution;
	pids = compute(n,vbt,vat);
	return pids;
}
void average_waitng(int n){
	int avg=0;
	for(int i=0; i<n; i++){
		avg=avg+pr[i].get_wt();
	}
	avg=avg/n;
	outfile<<"As process in non-preemptive thus response time waiting time"<<endl;
	outfile<<"Average waiting Time/Response time: "<<avg<<endl;
}
void average_turnAround(int n){
	int avg=0;
	for(int i=0; i<n; i++){
		avg=avg+pr[i].get_tt();
	}
	avg=avg/n;
	outfile<<"Average turnAround time: "<<avg<<endl;
}
int main(){
	srand(time(0));
	
	if(!infile){
		cout<<"File missing";
		return 0;
	}
	int t;
	infile>>t;
	int count=0;
	while(t--){
		count++;
		outfile<<"PROCESS "<<count<<": "<<endl;
    	int n;
    	infile>>n;
    	vector<int> pids;
	    pids = input(n);
	    outfile<<" OUTPUT CHART "<<endl;
        outfile<<"PId   Arrival  Burst  Completion  TurnAround   Waiting"<<endl;
    	for(int i=0; i<n; i++){
	    	pr[pids[i]-1].print_gant();
		    outfile<<endl;
         }
         average_waitng(n);
         average_turnAround(n);
         float total=pr[n-1].get_ct();
         float temp=n;
         float avg_through=temp/total;
         outfile<<"Average throughput time is : "<<avg_through;
         pr.clear();
		 outfile<<endl; 
		 outfile<<"\t\t-------------------------"<<endl;
     }
 }

