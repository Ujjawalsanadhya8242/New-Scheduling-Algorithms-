#include<bits/stdc++.h>
using namespace std;
using namespace std;
bool cmpp(vector<int>&process1,vector<int>&process2){
  if(process1[1]!=process2[1]){
    return process1[1]<process2[1];
  }
  else{
    return process1[0]<process2[0];
  }
};
bool cmp(vector<int>&process1, vector<int>&process2){
   if(process1[1]!=process2[1]){
       return process1[1]<process2[1];
    }
else if(process1[2]!=process2[2]){
    return process1[2]<process2[2];
}
else{
    return process1[0]<process2[0];   
}
};

bool compareArrival(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
};
void input() {
   
}

void changeArrival() {
    // Implementation of changeArrival function
}
void fcfs() {

   int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> ArrivalTime(n);
    vector<int> BurstTime(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the Arrival time of process " << i + 1 << ": ";
        cin >> ArrivalTime[i];
        cout << "Enter the Burst time of process " << i + 1 << ": ";
        cin >> BurstTime[i];
    }

    vector<pair<int, int>> temp;
    for (int i = 0; i < n; i++) {
        temp.push_back({ArrivalTime[i], BurstTime[i]});
    }
    sort(temp.begin(), temp.end(), compareArrival);

    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    vector<int>TurnAroundTime(n);

    completionTime[0] = temp[0].first + temp[0].second;
    waitingTime[0] = 0;

    for (int i = 1; i < n; i++) {
        if (temp[i].first > completionTime[i - 1]) {
            completionTime[i] = temp[i].first + temp[i].second;
             waitingTime[i] = 0;

        } else {
            completionTime[i] = completionTime[i - 1] + temp[i].second;
             waitingTime[i] = completionTime[i-1] - temp[i].first;
        }
       
    }
    for(int i=0;i<n;i++){
        TurnAroundTime[i]=completionTime[i]-ArrivalTime[i];
    }

    // Output completion times and waiting times
    cout << "Process\tCompletion Time\tWaiting Time\tTurnAround Time\n";
     float avgComplitionTime=0;
     float avgWaitingTime=0;
     float avgTurnaroundTime=0;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << completionTime[i] << "\t\t" << waitingTime[i] <<"\t\t"<< TurnAroundTime[i]<< endl;
        avgComplitionTime+=completionTime[i];
        avgWaitingTime+=waitingTime[i];
        avgTurnaroundTime+=TurnAroundTime[i];

    }
    cout<<"Average Compilation Time : "<<avgComplitionTime/n<<endl;
    cout<<"Average Waiting Time : "<<avgWaitingTime/n<<endl;
    cout<<"Average TurnAround Time : "<<avgTurnaroundTime/n<<endl;
    
}

void sjf() {
   
     int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> ArrivalTime(n);
    vector<int> BurstTime(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the Arrival time of process " << i + 1 << ": ";
        cin >> ArrivalTime[i];
        cout << "Enter the Burst time of process " << i + 1 << ": ";
        cin >> BurstTime[i];
    }
    
    vector<vector<int>>processDetails(n,vector<int>(6));
    //process id, arrival time, burst time, completion Time, turnaround Time, waiting Time;
    for(int i=0;i<n;i++){
        processDetails[i][0]=i+1;
        processDetails[i][1]=ArrivalTime[i];
        processDetails[i][2]=BurstTime[i];
    }
    //sort on the basis of burst time
    sort(processDetails.begin(),processDetails.end(),cmp);
    //completion Time
    processDetails[0][3]=processDetails[0][1]+processDetails[0][2];
    //turnaround time (kab tak rahi hai woh)
    processDetails[0][4]=processDetails[0][3]-processDetails[0][1];
    //waiting time
    processDetails[0][5]=processDetails[0][4]-processDetails[0][2];
    for(int i=1;i<n;i++){
        int prevCompletionTime=processDetails[i-1][3];
        int idx=i;
        int currBurstTime=processDetails[i][2];
        int currId=processDetails[i][0];

        for(int j=i;j<n;j++){
            if(prevCompletionTime>=processDetails[j][1]){
                if(currBurstTime>processDetails[j][2]){
                     currBurstTime=processDetails[j][2];
                     idx=j;
                     currId=processDetails[i][0];
                }
                else{
                    if(currBurstTime==processDetails[j][2] && currId>processDetails[j][0]){
                        idx=j;
                        currId=processDetails[i][0];
                    }
                }
            }
            
        }
        //completion time 
        processDetails[idx][3]=prevCompletionTime+processDetails[idx][2];
        //turnaround time
        processDetails[idx][4]=max(processDetails[idx][3]-processDetails[idx][1],0);
        //waiting time
        processDetails[idx][5]=max(processDetails[idx][4]-processDetails[idx][2],0);
        swap(processDetails[idx],processDetails[i]);
    }
        cout << "Process\tCompletion Time\tWaiting Time\tTurnAround Time\n";
     float avgComplitionTime=0;
     float avgWaitingTime=0;
     float avgTurnaroundTime=0;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << processDetails[i][3] << "\t\t" << processDetails[i][5] <<"\t\t"<< processDetails[i][4]<< endl;
        avgComplitionTime+=processDetails[i][3];
        avgWaitingTime+=processDetails[i][4];
        avgTurnaroundTime+=processDetails[i][5];

    }
     cout<<"Average Compilation Time : "<<avgComplitionTime/n<<endl;
    cout<<"Average Waiting Time : "<<avgWaitingTime/n<<endl;
    cout<<"Average TurnAround Time : "<<avgTurnaroundTime/n<<endl;
    

}

void rr() {
   
     int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> ArrivalTime(n);
    vector<int> BurstTime(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the Arrival time of process " << i + 1 << ": ";
        cin >> ArrivalTime[i];
        cout << "Enter the Burst time of process " << i + 1 << ": ";
        cin >> BurstTime[i];
    }
    int qt;
    cin>>qt;
    vector<vector<int>>process(n,vector<int>(6));
    vector<int>remTime(n);
    for(int i=0;i<n;i++){
        process[i][0]=i;
        process[i][1]=ArrivalTime[i];
        process[i][2]=BurstTime[i];

        remTime[i]=BurstTime[i];

    }
    sort(process.begin(),process.end(),cmpp);
   int lastId=1;
    int completed=0;
     int currentTime=process[0][1];
     vector<int>completionTime(n);
  
    queue<int>readyQueue;
    readyQueue.push(process[0][0]);
  while(completed!=n){
    int id=readyQueue.front();
    readyQueue.pop();
    if(remTime[id]>qt){
         remTime[id]=remTime[id]-qt;
         currentTime+=qt;
    }
    else{
        currentTime+=remTime[id];
        completionTime[id]=currentTime;
       // process[id][4]=currentTime;
        completed++;
        remTime[id]=0;
    }
    while(lastId<n && process[lastId][1]<=currentTime){
        readyQueue.push(process[lastId][0]);
        lastId=lastId+1;
    }
    if(remTime[id]>0){
        readyQueue.push(id);
    }
    if(readyQueue.empty()){
          if(lastId!=n){
            currentTime=process[lastId][1];
            readyQueue.push(process[lastId][0]);
            lastId++;
          
          }
    }
  }

  vector<int>turnAroundTime(n);
  vector<int>waitingTime(n);

  for(int i=0;i<n;i++){
    turnAroundTime[i]=completionTime[i]-ArrivalTime[i];
    waitingTime[i]=turnAroundTime[i]-BurstTime[i];
  }
  cout << "Process\tCompletion Time\tWaiting Time\tTurnAround Time\n";
     float avgComplitionTime=0;
     float avgWaitingTime=0;
     float avgTurnaroundTime=0;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << completionTime[i] << "\t\t" << waitingTime[i] <<"\t\t"<< turnAroundTime[i]<< endl;
        avgComplitionTime+=completionTime[i];
        avgWaitingTime+=waitingTime[i];
        avgTurnaroundTime+=turnAroundTime[i];

    }
    cout<<"Average Compilation Time : "<<avgComplitionTime/n<<endl;
    cout<<"Average Waiting Time : "<<avgWaitingTime/n<<endl;
    cout<<"Average TurnAround Time : "<<avgTurnaroundTime/n<<endl;
    
}

void srtf() {
       int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> ArrivalTime(n);
    vector<int> BurstTime(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the Arrival time of process " << i + 1 << ": ";
        cin >> ArrivalTime[i];
        cout << "Enter the Burst time of process " << i + 1 << ": ";
        cin >> BurstTime[i];
    }

    vector<int> remTime = BurstTime;
    vector<vector<int>> processDetails(n, vector<int>(6));
    for (int i = 0; i < n; i++) {
        processDetails[i][0] = i + 1;
        processDetails[i][1] = ArrivalTime[i];
        processDetails[i][2] = BurstTime[i];
    }
    sort(processDetails.begin(), processDetails.end(), cmp);

    int completed = 0;
    int currentTime = 0;
    vector<int> completionTime(n);
    vector<bool> isCompleted(n, false);

    while (completed != n) {
        int selectedProcessIndex = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processDetails[i][1] <= currentTime && !isCompleted[i]) {
                if (remTime[i] < minimum) {
                    minimum = remTime[i];
                    selectedProcessIndex = i;
                }
            }
        }

        if (selectedProcessIndex == -1) {
            currentTime++;
        }
        else {
            remTime[selectedProcessIndex]--;
            currentTime++;
            if (remTime[selectedProcessIndex] == 0) {
                completionTime[selectedProcessIndex] = currentTime;
                completed++;
                isCompleted[selectedProcessIndex] = true;
            }
        }
    }

    vector<int> turnAroundTime(n);
    vector<int> waitingTime(n);
    float avgComplitionTime = 0;
    float avgWaitingTime = 0;
    float avgTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = completionTime[i] - ArrivalTime[i];
        waitingTime[i] = turnAroundTime[i] - BurstTime[i];
        avgComplitionTime += completionTime[i];
        avgWaitingTime += waitingTime[i];
        avgTurnaroundTime += turnAroundTime[i];
    }

    cout << "Process\tCompletion Time\tWaiting Time\tTurnAround Time\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << completionTime[i] << "\t\t" << max(0,waitingTime[i]) << "\t\t" << max(0,turnAroundTime[i]) << endl;
    }

    cout << "Average Compilation Time: " << avgComplitionTime / n << endl;
    cout << "Average Waiting Time: " << avgWaitingTime / n << endl;
    cout << "Average TurnAround Time: " << avgTurnaroundTime / n << endl;

    
}

void innovative() {
    // Implementation of the innovative algorithm
}

void display(int choice) {
    // Implementation of display function
}

int main() {
    cout << "Welcome to CPU Scheduling:" << endl << endl;
    input();
    int c, choice;
    changeArrival();
    cout << "Choice\tAlgorithm used" << endl;
    cout << "1\tFCFS Algorithm" << endl;
    cout << "2\tSJF Algorithm" << endl;
    cout << "3\tRound robin" << endl;
    cout << "4\tSRTF Algorithm" << endl;
    cout << "5\tOur innovative algorithm" << endl;
    do {
        cout << "Enter your choice from the above table: ";
        cin >> c;
        switch (c) {
            case 1: fcfs(); break;
            case 2: sjf(); break;
            case 3: rr(); break;
            case 4: srtf(); break;
            case 5: innovative(); break;
            default:
                cout << "Please enter choice from 1 to 5 only" << endl;
                break;
        }
        display(c);
        cout << "\nEnter 1 to continue, 0 to stop: ";
        cin >> choice;
    } while (choice == 1);

    return 0;
}
