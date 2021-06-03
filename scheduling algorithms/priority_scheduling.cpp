#include<iostream>
#include<bits/stdc++.h>
#define vec vector<pair<int,int>> 
using namespace std;

ifstream infile("in1.txt");
ofstream outfile("out1.txt");

class process{
	int id,at,bt,priority;
	int ct,wt,tat;
	public:
		process(int process_id){
			id=process_id;
		}
		void input();
		int get_at();
		void set_ct(int time);
		int get_ct();
		int get_bt();
		int get_prior();
		int get_wt();
		int get_tt();
		void print();
		
};
vector<process> pro;
void process::input(){
	infile>>priority>>at>>bt;
}
int process::get_at(){
	return at;
}
int process::get_bt(){
	return bt;
}
int process::get_prior(){
	return priority;
}
int process::get_ct(){
	return ct;
}
int process::get_wt(){
	return wt;
}
int process::get_tt(){
	return tat;
}
void process::set_ct(int time){
	ct=time;
	tat=ct-at;
	wt=tat-bt;
}
void process::print(){
	outfile<<id<<"\t"<<priority<<"\t"<<at<<"\t"<<bt<<"\t"<<ct<<"\t"<<tat<<"\t"<<wt;
}
vector<int> compute(vec priorId,vec aId,int n){
	int count=n-1,count1=0;
	int arrival=0,ct=0; 
	unordered_map<int,bool> check; // to check curr process is completed or not
	for(int i=0; i<n; i++){
		check[i+1]=false;
	}
	
	// id for priority base
	// id1 for arriving time base
	// final id for selected id
	int final_id,id,id1;
	
	vector<int> pid;  // to store process id in execution of order
	int tc=0;         // to check status of total process complete
	while(tc!=n){

		int flag=0;    // for not infinite loop 
		// to check current priority process is completed or not
		while(check[priorId[count].second]){
			count--;
			if(count==(-1)){
				count=n-1;
				flag++;	
			}
			if(flag==2)
			break;
		}
		if(flag==2){
			break;
		}
		int id=priorId[count].second;
		
		flag=0; // for not infinite loop 
		// to find minimum arrival id 
		while(check[aId[count1].second])
		{
			count1++;
			if(count1==n){
				count1=0;
				flag++;
			}
			if(flag==2)
			break;
		}
		
		if(flag==2)
		break;
		id1=aId[count1].second;
		// min_arrival time of process in job
		int min_arrival=aId[count1].first;
		
        // Arriving time of highest priority process	
		int arrival=pro[id-1].get_at();
		
		// if highest priority un_processed job not arrive till this time
		if(arrival > ct){
			final_id=id1;
			count1++;
			if(min_arrival>ct){
				ct=min_arrival;
			}
		}
		else{
			final_id=id;
			count--;
		}
	
		ct=ct+pro[final_id-1].get_bt();
	   
		pro[final_id-1].set_ct(ct);
		check[final_id]=true;
		pid.push_back(final_id);
		tc++;
		
	}
	return pid;
}

vector<int> pri_sch(int n){
	//for sorting of process by priority
	vec priorId;
	//for sort of processes in arrival time
	vec aId;
	
	//to take input as obj of process and store it in vector of process object
	for(int i=0; i<n; i++){
		int id;
		infile>>id;
		process p(id);
		p.input();
		pro.push_back(p);
		
		priorId.push_back(make_pair(p.get_prior(),id));
		aId.push_back(make_pair(p.get_at(),id));
	}
	sort(priorId.begin(),priorId.end());
	sort(aId.begin(),aId.end());
	
	// for final list of in execution order of ids 
	vector<int> ids;
	ids=compute(priorId,aId,n);
	return ids;
}
void average_waiting(int n){
	int avg=0;
	for(int i=0; i<n; i++){
		avg=avg+pro[i].get_wt();
	}
	avg=avg/n;
	outfile<<"As process in non-preemptive thus response time waiting time"<<endl;
	outfile<<"Average waiting Time/Response time: "<<avg<<endl;
}
void average_turnAround(int n){
	int avg=0;
	for(int i=0; i<n; i++){
		avg=avg+pro[i].get_tt();
	}
	avg=avg/n;
	outfile<<"Average turnAround time: "<<avg<<endl;
}
void throughput(int n){
	float temp=n;
	float total=pro[n-1].get_ct();
	temp=temp/total;
	outfile<<"Through put is: "<<temp<<endl;
	
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
		int n;
		infile>>n;
		
		// for storing jobs in order of execution
		vector<int> v;
		v = pri_sch(n);
		outfile<<"PROCESS "<<count<<": "<<endl;
		
		// for print of gant chart
		outfile<<"Id\tPrior\t At\t Bt\t CT\t TAT\t WT"<<endl;
		for(int i=0; i<v.size(); i++){
			pro[v[i]-1].print();
			outfile<<endl;
		}
		
		// for average times
		average_waiting(n);
		average_turnAround(n);
		throughput(n);
		
		outfile<<endl;
		outfile<<"\t\t\t---------------------------";
		outfile<<endl;
		count++;
		pro.clear();
	}
}
