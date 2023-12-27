#include <bits/stdc++.h>
//#include <ctime>
#include <thread>
using namespace std;

const char* ITALIC_START = "\033[3m";
const char* ITALIC_END = "\033[0m";
const char* BLUE_COLOR = "\033[1;34m";
const char* RESET_COLOR = "\033[0m";

struct taskStore
{
    int startHr;
    int startMn;
    int endHr;
    int endMn;
    string taskName;
};
bool compare(taskStore &node1,taskStore &node2)
{
  if(node1.startHr<node2.startHr){
    return true;
  }
  else if(node1.startHr==node2.startHr){
    if(node1.startMn<node2.startMn){
      return true;
    }
  }
  return false;
}
deque<taskStore>task;
void printTask(){
  cout<<"--------------------------------------------------------\n";
  if(task.size()==0){
    cout<<"Empty!\n";
    return;
  }
  for(int i=0;i<task.size();i++){
    cout<<"TASK NO "<<i+1<<":\n";
    cout<<task[i].taskName<<"\n";
    cout<<"Start at: "<<task[i].startHr<<" : "<<task[i].startMn<<" \nEnd at:  "<<task[i].endHr<<" : "<<task[i].endMn<<" \n";
  }
  cout<<"--------------------------------------------------------\n";
}
void deleteTask(){
  int no=0;
  cout<<"Are you sure to delete any task? type 1 for delete,0 oterwise:\n";
  cin>>no;
  if(no==0)return;
  printTask();

  cout<<"Which task would you delete?Please type the task no:  \n";
  int taskNo;
  cin>>taskNo;
  task.erase(task.begin()+taskNo-1);
  cout<<"Task "<<taskNo<<" is deleted\n";
}


void taskInput(){
  //int size=task.size();

  taskStore newnode;
  task.push_back(newnode);

   signed int size=task.size();

  cout<<"type start hour and min with a space (like 11 35):\n";
    cin>>task[size-1].startHr>>task[size-1].startMn;

  cout<<"type end hour and min with a space:\n";
    cin>>task[size-1].endHr>>task[size-1].endMn;
  cout<<"what task will you do:\n";
    cin>>task[size-1].taskName;
    cout<<"Task is successfully added.\n";
    sort(task.begin(),task.end(),compare);
}

void currentAndUpcoming(){
  
    time_t now = time(0); 
    tm* local_time = localtime(&now); 

    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;
    //int second = local_time->tm_sec;
    bool flag=true;
    for(int i=0;i<task.size();i++){

      if(hour>=task[i].startHr&&hour<=task[i].endHr){
       
        if(hour==task[i].startHr&&minute<task[i].startMn)continue;
     
        if(hour==task[i].endHr&&minute>task[i].endMn)continue;
       
       cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
        cout<<"Your task:\n";
        cout<<task[i].taskName<<"\n";
        if(i!=(task.size()-1)){
          cout<<"--------------------------------------------------------\n";
        cout<<"Upcoming Task: \n"<<task[i+1].taskName<<"\n";
        }
        else{
          cout<<"No upcoming task to show!\n";
        }
        
        flag=false;
        break;
      }
    }
    if(flag){
     // cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
      cout<<"There is no Task at this time!\n";
      
      for(int i=0;i<task.size();i++){

      if(hour>=task[i].startHr){
          cout<<"Upcoming Task: \n"<<task[i+1].taskName<<"\n";
          cout<<"Start at: "<<task[i].startHr<<" : "<<task[i].startMn<<" \nEnd at:  "<<task[i].endHr<<" : "<<task[i].endMn<<" \n";
          return;
      }

    }
    cout<<"--------------------------------------------------------\n";
      cout<<"No upcoming task to show!\n";
      
    }
       
}
void displayCurrentTime() {
  
      
        time_t currentTime = time(nullptr);
        struct tm* localTime = localtime(&currentTime);
        cout << "\n    |-----------------------------------------|"  << std::endl;
        cout << BLUE_COLOR << ITALIC_START << "\n    Current time is:"<< RESET_COLOR << asctime(localTime);
        cout << "\n    |-----------------------------------------|"  << std::endl;
         
        this_thread::sleep_for(std::chrono::seconds(1));
        
      //  system("clear");
      
   
}
int main(){
  bool go;
  
  do{
   
     go=true;
     displayCurrentTime();
     currentAndUpcoming();
     cout<<"--------------------------------------------------------\n";
     cout<<"Type 1 for adding task.\n";
     cout<<"Type 2 for show all task.\n";
     cout<<"Type 3 for delete a task.\n";
     cout<<"Type 4 for delete all task.\n";
     cout<<"Type 0 for terminate program.\n";
     
     int command=0;
     cin>>command;
     switch(command){
      case 1 :taskInput();
              break;
      case 2 :printTask();
              break;
      case 3 :deleteTask();
              break;
      case 4 :task.clear();
              break;
      case 0 :go=false;
              break;
      default :cout<<"Invalid input\n";
               break;
     }
     system("clear");
  }
  while(go);
    
  return 0;
}
