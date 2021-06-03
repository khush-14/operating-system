#include<iostream>
#include<bits/stdc++.h>
using namespace std;

ofstream outfile("out1.txt");
ifstream infile("in1.txt");


class process{
	public:
		int at,bt,pid;
		int wt,tat,ct;
		void get_input(int count){
			pid=count;
			infile>>at;
			infile>>bt;
		}
		int arrival(){
			return at;
		}
		int burst(){
			return bt;
		}
		int process_id(){
			return pid;
		}
		void completion_time(int time){
			ct=time;
		}
		int completion(){
			return ct;
		}
		void waiting_time(){
			wt=tat-bt;
		}
		int waiting()
		{
			return wt;
		}
		void turnaround_time(){
			tat=ct-at;
		}
		int turnaround(){
			return tat;
		}
		
};
vector<process> pro;
void provide(vector<int>rp){
	int completion=0;
	int n=pro.size();
	outfile<<" OUTPUT CHART : "<<endl;
 	outfile<<"p\tAt\tBt\tCt\tTat\tWt"<<endl;
	for(int i=0; i<n; i++){
		completion=completion+pro[rp[i]-1].burst();
		pro[rp[i]-1].completion_time(completion);
	}
	for(int i=0; i<n; i++){
    	pro[rp[i]-1].turnaround_time();	
    	pro[rp[i]-1].waiting_time();
	}
	for(int i=0; i<pro.size(); i++){
		int j=rp[i]-1;
		outfile<<rp[i]<<"\t"<<pro[j].arrival()<<"\t"<<pro[j].burst()<<"\t"<<pro[j].completion()<<"\t"<<pro[j].turnaround()<<"\t"<<pro[j].waiting()<<endl;
	}
}
void execute(int n){
	//arrival  and id
	vector<pair<int,int>>pai;
	//id and burst
	unordered_map<int,int> pib;
	
    for(int i=0; i<n; i++){
		process p;
		int id;
		infile>>id;
		p.get_input(i+1);
		
		pai.push_back(make_pair(p.arrival(),id));
		pro.push_back(p);
	}
	sort(pai.begin(),pai.end());
	
	
	int total=0,i=0;
	//to store process id in sequence of execution
	vector<int> rp;
	for(int i=0; i<n; i++){
		rp.push_back(pai[i].second); // pai[i].second store the id of process in sequence of execution
	}
	provide(rp);
}
void average_waiting(int n){
	int avg=0;
	for(int i=0; i<n; i++){
		avg=avg+pro[i].waiting();
	}
	avg=avg/n;
	outfile<<"As process in non-preemptive thus response time waiting time"<<endl;
	outfile<<"Average waiting Time/Response time: "<<avg<<endl;
}
void average_turnaround(int n){
	int avg=0;
	for(int i=0; i<n; i++){
		avg=avg+pro[i].turnaround();
	}	
	avg=avg/n;
	outfile<<"Average turnAround time: "<<avg<<endl;	
}
void throughput(int n){
	float temp=n;
	float total=pro[n-1].completion();
	temp=temp/total;
	outfile<<"Through put is: "<<temp;
}
int main(){
	if(!infile){
		cout<<"file is missing";
		return 0;
	}
	srand(time(0));
	int t;
	infile>>t;
	int count=0;
	while(t--){
		outfile<<"PROCESS "<<count<<" : "<<endl;
    	int n;
    	infile>>n;
    	
		execute(n);
	    average_waiting(n);
	    average_turnaround(n);
	    throughput(n);
	    outfile<<endl;
	    
	    outfile<<"\t\t-------------------------";
	    outfile<<endl;
	    pro.clear();
	    count++;
	}
	
	return 0;
}
