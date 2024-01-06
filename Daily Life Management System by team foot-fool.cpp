#include <bits/stdc++.h>
#include <thread>
using namespace std;

struct taskStore
{
  int startHr;
  int startMn;
  int endHr;
  int endMn;
  string taskName;
};

struct TopicOfTask
{
  string topicName;
  vector<pair<string, int> > subTask;
};
deque<taskStore> task;
vector<TopicOfTask> topic; // subtask under Topic
bool compare(taskStore &node1, taskStore &node2)
{
  if (node1.startHr < node2.startHr)
  {
    return true;
  }
  else if (node1.startHr == node2.startHr)
  {
    if (node1.startMn < node2.startMn)
    {
      return true;
    }
  }
  return false;
}

// File/History Function Start
void printAllFromFile()
{ // history.txt file
  ifstream readFile("history.txt");
  if (readFile.is_open())
  {
    cout << "History: \n";
    cout << "----------------------------------------------------\n";
    string line;
    while (getline(readFile, line))
    {
      cout << line << endl;
    }
    readFile.close();
    cout << "----------------------------------------------------\n";
  }
  else
  {
    cout << "Error reading from file!" << endl;
  }
}
string dateToString(int year, int month, int day)
{
  string y = to_string(year), m = to_string(month), d = to_string(day);
  if (m.size() == 1)
    m = "0" + m;
  if (d.size() == 1)
    d = "0" + d;
  return (d + "/" + m + "/" + y);
}
void addToHistory(string task)
{
  time_t now = time(0);
  tm *time = localtime(&now);
  int year = (time->tm_year) + 1900;
  int month = time->tm_mon + 1;
  int day = time->tm_mday;
  string key = dateToString(year, month, day);

  ofstream myFile("history.txt", ios::app);
  if (myFile.is_open())
  {
    myFile << key << " ";
    myFile << task << " [";
    myFile << "Updated time: " << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << "]\n";
    myFile.close();
  }
  else
  {
    cout << "can not write\n";
  }
}
void addToHistory(taskStore node)
{
  string all;
  all += "Started at: " + to_string(node.startHr) + ":" + to_string(node.startMn) + " ";
  all += "End: " + to_string(node.endHr) + ":" + to_string(node.endMn) + " ";
  all += "Task: " + node.taskName;
  addToHistory(all);
}
// History's Funtion End
// Note Function Start
void writingNote()
{
  int cm = 0;
  cout << "Enter 1 for showing your note\n";
  cout << "Enter 2 for addind your note\n";
  cout << "Enter 3 for clearing your note\n";
  cout << "Enter 0 for exist.\n";
  cin >> cm;

  switch (cm)
  {
  case 1:
    try
    {
      cout << "---------------------------------------------------\n";
      ifstream rFile("note.txt");
      if (rFile.is_open())
      {
        string line;
        while (getline(rFile, line))
        {
          cout << line << endl;
        }
        cout << "---------------------------------------------------\n";
        rFile.close();
      }
      else
      {
        cout << "file can not open\n";
      }
    }
    catch (const exception &e)
    {
      std::cerr << "Error reading file: " << e.what() << std::endl;
    }
    break;
  case 2:
    try
    {
      ofstream noteFile("note.txt", ios::app);
      if (noteFile.is_open())
      {
        cout << "Type your note here,(after finish enter 0 ) :\n";
        string s;
        cin.ignore();
        do
        {
          getline(cin, s);
          if (s[0] != 0 || s.size() != 1)
            noteFile << s << "\n";
        } while ((s.size() != 1 && s[0] != '0'));
        noteFile.close();
      }
    }
    catch (const exception &e)
    {
      cerr << "Error reading file: " << e.what() << endl;
    }
    break;
  case 3:
    if (1)
    {
      ofstream myFile("note.txt");
      if (myFile.is_open())
      {
        myFile.clear();
        cout << "cleared successfully!\n";
        myFile.close();
        addToHistory("Note cleared.");
      }
      else
      {
        cout << "file not open\n";
      }
    }
    break;
  default:
    break;
  }
}
// Note's Function Ended
// Topic Function Start
void addTopic()
{
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  TopicOfTask newnode;
  topic.push_back(newnode);
  cout << "Enter your Topic Name:\n";
  string name;
  getline(cin, topic[topic.size() - 1].topicName);
  int cm = 1;
  addToHistory("Topic Added.Topic Name: " + topic[topic.size() - 1].topicName);

  do
  {
    cout << "Add a Subtask Under \"" << topic[topic.size() - 1].topicName << "\" Topic\n";
    string sub;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, sub);
    topic[topic.size() - 1].subTask.push_back(make_pair(sub, 0));
    cout << "Enter 1 for adding more subTask,If finished addind Enter 0 \n";
    cin >> cm;
  } while (cm != 0);
}
void printTopic()
{
  if (topic.size() == 0)
  {
    cout << "No Topic Here\n";
    return;
  }
  for (int i = 0; i < topic.size(); i++)
  {
    cout << i + 1 << " : " << topic[i].topicName << "\n";
  }
  int topicNo;
  cout << "Enter topic Number for see details\n";
  cin >> topicNo;
  if (topicNo > topic.size())
    cout << "Invalid topic No\n";
  else
  {
    for (int i = 0; i < topic[topicNo - 1].subTask.size(); i++)
    {
      cout << "Subtask " << i + 1 << " : " << topic[topicNo - 1].subTask[i].first << " ";
      if (topic[topicNo - 1].subTask[i].second == 0)
      {
        cout << "[Not done yet.]\n";
      }
      else
      {
        cout << "[Done!]\n";
      }
    }
  }
}
void subtaskMark()
{
  for (int i = 0; i < topic.size(); i++)
  {
    cout << i + 1 << " : " << topic[i].topicName << "\n";
  }
  cout << "Choose a Topic:(Enter a topic number)\n";
  int topicNo;
  cin >> topicNo;
  if (topicNo > topic.size())
    cout << "Invalid topic No\n";
  else
  {
    cout << "Topic: " << topic[topicNo - 1].topicName << "\n";
    for (int i = 0; i < topic[topicNo - 1].subTask.size(); i++)
    {
      cout << "Subtask " << i + 1 << " : " << topic[topicNo - 1].subTask[i].first << " ";
      if (topic[topicNo - 1].subTask[i].second == 0)
      {
        cout << "[Not done yet.]\n";
      }
      else
      {
        cout << "[Done!]\n";
        addToHistory("done: " + topic[topicNo - 1].subTask[i].first + " Under Topic: " + topic[topicNo - 1].topicName + ".");
      }
    }
    cout << "Which you have Done already?(enter subtask number)\n";
    int subNo;
    cin >> subNo;
    if (subNo > topic[topicNo - 1].subTask.size())
    {
      cout << "Invalid subtask no. -_-\n";
    }
    else
    {
      topic[topicNo - 1].subTask[subNo - 1].second = 1;
      cout << "Great Job!Welcome. -_-\n";
    }
  }
}
void deleteTopic()
{
  for (int i = 0; i < topic.size(); i++)
  {
    cout << i + 1 << " : " << topic[i].topicName << "\n";
  }
  cout << "which group of task or topic you want to delete?(Enter the topic number)\n";
  int topicNo;
  cin >> topicNo;
  if (topicNo > topic.size())
  {
    cout << "Invalid topic number -_-\n";
  }
  else
  {
    addToHistory("Topic: " + topic[topicNo - 1].topicName + " is deleted");
    topic.erase(topic.begin() + topicNo - 1);
    cout << "The Topic is deleted\n";
  }
}
// topic Funtion end
// Task
void printTask()
{
  cout << "--------------------------------------------------------\n";
  if (task.size() == 0)
  {
    cout << "Empty!\n";
    return;
  }
  for (int i = 0; i < task.size(); i++)
  {
    cout << "TASK NO " << i + 1 << ":\n";
    cout << task[i].taskName << "\n";
    cout << "Start at: " << task[i].startHr << " : " << task[i].startMn << " \nEnd at:  " << task[i].endHr << " : " << task[i].endMn << " \n";
  }
  cout << "--------------------------------------------------------\n";
}

void taskInput()
{
  // int size=task.size();

  taskStore newnode;
  task.push_back(newnode);

  signed int size = task.size();

  cout << "Enter start hour and min with a space (like 11 35):\n";
  cin >> task[size - 1].startHr >> task[size - 1].startMn;

  cout << "Enter end hour and min with a space:\n";
  cin >> task[size - 1].endHr >> task[size - 1].endMn;
  cout << "what task will you do:\n";
  cin.ignore();
  getline(cin, task[size - 1].taskName);
  cout << "Task is successfully added.\n";
  addToHistory(task[size - 1]); //--Adding file as history
  addToHistory("Task Inputed.");
  sort(task.begin(), task.end(), compare);
}
void deleteTask()
{
  int no = 0;
  cout << "Are you sure to delete any task? Enter 1 for delete,0 oterwise:\n";
  cin >> no;
  if (no == 0)
    return;
  printTask();

  cout << "Which task would you delete?Please Enter the task no:  \n";
  int taskNo;
  cin >> taskNo;
  task.erase(task.begin() + taskNo - 1);
  cout << "Task " << taskNo << " is deleted\n";
}
void currentAndUpcoming()
{

  time_t now = time(0);
  tm *local_time = localtime(&now);

  int hour = local_time->tm_hour;
  int minute = local_time->tm_min;
  // int second = local_time->tm_sec;
  bool flag = true;
  for (int i = 0; i < task.size(); i++)
  {

    if (hour >= task[i].startHr && hour <= task[i].endHr)
    {

      if (hour == task[i].startHr && minute < task[i].startMn)
        continue;

      if (hour == task[i].endHr && minute > task[i].endMn)
        continue;

      cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
      cout << "Your task:\n";
      cout << task[i].taskName << "\n";
      if (i != (task.size() - 1))
      {
        cout << "--------------------------------------------------------\n";
        cout << "Upcoming Task: \n"
             << task[i + 1].taskName << "\n";
        cout << "Start at: " << task[i].startHr << " : " << task[i].startMn << " \nEnd at:  " << task[i].endHr << " : " << task[i].endMn << " \n";
      }
      else
      {
        cout << "--------------------------------------------------------\n";
        cout << "No upcoming task to show!\n";
      }

      flag = false;
      break;
    }
  }
  if (flag)
  {
    // cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
    cout << "There is no Task at this time!\n";

    for (int i = 0; i < task.size(); i++)
    {

      if (hour >= task[i].startHr)
      {
        cout << "Upcoming Task: \n"
             << task[i + 1].taskName << "\n";
        cout << "Start at: " << task[i].startHr << " : " << task[i].startMn << " \nEnd at:  " << task[i].endHr << " : " << task[i].endMn << " \n";
        return;
      }
    }
    cout << "--------------------------------------------------------\n";
    cout << "No upcoming task to show!\n";
  }
}
// Function for showing time
const char *ITALIC_START = "\033[3m";
const char *ITALIC_END = "\033[0m";
const char *BLUE_COLOR = "\033[1;34m";
const char *RESET_COLOR = "\033[0m";

void displayCurrentTime()
{

  time_t currentTime = time(nullptr);
  struct tm *localTime = localtime(&currentTime);
  cout << "\n    |-----------------------------------------|" << endl;
  cout << BLUE_COLOR << ITALIC_START << "\n    Current time is:" << RESET_COLOR << asctime(localTime);
  cout << "\n    |-----------------------------------------|" << endl;

  this_thread::sleep_for(std::chrono::seconds(1));

  //  system("clear");
}
// Task Fuctionalities End
int main()
{
  bool go;

  do
  {

    go = true;
    displayCurrentTime();
    currentAndUpcoming();
    cout << "--------------------------------------------------------\n";
    cout << "Enter 1 for adding task.\n";
    cout << "Enter 2 for show all task.\n";
    cout << "Enter 3 for delete a task.\n";
    cout << "Enter 4 for delete all task.\n";
    cout << "Enter 5 for  Note(Show,Delete or update).\n";
    cout << "Enter 6 for Showing History.\n";
    cout << "Enter 7 for clear History.\n";
    cout << "Enter 8 for adding a Topic of subtask.\n";
    cout << "Enter 9 for Showing Topic and subtask.\n";
    cout << "Enter 10 for Marking a Sub task as Done.\n";
    cout << "Enter 11 for Deleting a Topic.\n";
    cout << "Enter 0 for skip:\n";

    int command = 0;
    cin >> command;
    switch (command)
    {
    case 1:
      taskInput();
      break;
    case 2:
      printTask();
      break;
    case 3:
      deleteTask();
      break;
    case 4:
      task.clear();
      addToHistory("All task cleared.");
      break;
    case 5:
      writingNote();
      break;
    case 6:
      printAllFromFile();
      break;
    case 7:
      if (1)
      {
        ofstream myFile("history.txt");
        if (myFile.is_open())
        {
          cout << "History cleared.\n";
          myFile.clear();
          myFile.close();
          addToHistory("History Cleared.");
        }
        else
        {
          cout << "file not open\n";
        }
      }
      break;
    case 8:
      addTopic();
      break;
    case 9:
      printTopic();
      break;
    case 10:
      subtaskMark();
      break;
    case 11:
      deleteTopic();
      break;
    case 0: // go=false;
      break;
    default:
      cout << "Invalid input\n";
      break;
    }
    cout << "Enter 1 for continue, 0 for terminate program.\n";
    int Enter;
    cin >> Enter;
    if (Enter == 0)
    {
      go = false;
    }
    else
    {
      system("clear");
    }
  } while (go);

  return 0;
}
