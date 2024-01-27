#include <bits/stdc++.h>
#include <thread>
using namespace std;
const char *Reset = "\033[0m";
const char *Extra = "\033[1;9m";
const char *Bold = "\033[1m";
const char *Black = "\033[1;30m";
const char *Red = "\033[1;31m";
const char *Green = "\033[1;32m";
const char *Yellow = "\033[1;33m";
const char *Blue = "\033[1;34m";
const char *Magenta = "\033[1;35m";
const char *Cyan = "\033[1;36m";
const char *White = "\033[1;37m";
const char *Italic = "\033[0m";
// Finance Class
class health
{
private:
public:
    double calculateBMI(double weight, double height)
    {
        return weight / (height * height);
    }

    double convertToMeters(double feet, double inches)
    {
        const double meters_per_feet = 0.3048;
        const double inches_per_meter = 39.37;

        double heightInMeters = (feet * meters_per_feet) + (inches / inches_per_meter);
        return heightInMeters;
    }

    void displayBMICategory(double bmi)
    {
        if (bmi < 18.5)
        {
            cout << Magenta << Bold << "Underweight\n"
                 << Reset;
        }
        else if (bmi < 25)
        {
            cout << Green << Bold << "Normal weight\n"
                 << Reset;
        }
        else if (bmi < 30)
        {
            cout << Red << Bold << "Overweight\n"
                 << Reset;
        }
        else
        {
            cout << Red << Bold << "Obese\n"
                 << Reset;
        }
    }

    void trackWeight(double weight)
    {
        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);

        ofstream file("weight.txt", ios::app);
        if (file.is_open())
        {
            file << "Weight on " << ctime(&currentTime) << ": " << weight << " kg\n";
            file.close();
        }
        else
        {
            cout << "Error opening file for writing.\n";
        }
    }

    void viewPreviousWeight()
    {
        ifstream file("weight.txt");
        if (file.is_open())
        {
            string line;
            cout << Green << Bold << "\nPrevious Days' Weight:\n"
                 << Reset;
            while (getline(file, line))
            {
                if (!line.empty())
                {
                    cout << line;
                    if (line[line.length() - 1] != '\n')
                    {
                        cout << "\n";
                    }
                }
            }
            file.close();
        }
        else
        {
            cout << "Error opening file for reading.\n";
        }
    }
    void run()
    {
        double weight, feet, inches;

        cout << Bold << "Enter your weight in kilograms: " << Reset;
        cin >> weight;

        cout << Bold << "Enter your height in feet and inches:\n"
             << Reset;
        cout << Bold << "Feet: " << Reset;
        cin >> feet;
        cout << Bold << "Inches: " << Reset;
        cin >> inches;

        double heightInMeters = convertToMeters(feet, inches);
        double bmi = calculateBMI(weight, heightInMeters);

        cout << Bold << "Your BMI: " << bmi << "\n"
             << Reset;
        cout << Bold << "BMI Category: " << Reset;
        displayBMICategory(bmi);

        trackWeight(weight);

        if (bmi < 18.5 || bmi >= 30)
        {
            cout << Red << Bold << "Alert: Your BMI is not in the ideal range. Consider consulting with a healthcare professional.\n"
                 << Reset;
        }

        char viewOption;
        cout << Bold << "Do you want to view previous days' weight? (y/n): " << Reset;
        cin >> viewOption;

        if (viewOption == 'y' || viewOption == 'Y')
        {
            viewPreviousWeight();
        }
    }
};
class Finance
{
private:
public:
    void displayMenu()
    {
        cout << Bold << "1. Add Income" << Reset << '\n';
        cout << Bold << "2. Add Expense\n"
             << Reset;
        cout << Bold << "3. View Balance\n"
             << Reset;
        cout << Bold << "4. View Balance With Details\n"
             << Reset;
        cout << Bold << "5. Exit\n"
             << Reset;
    }

    void addIncome(double &balance)
    {
        string incomeSource;
        double income;

        cout << Bold << "Enter the income source: " << Reset;
        cin.ignore();
        getline(cin, incomeSource);

        cout << Bold << "Enter the amount of income: tk" << Reset;
        cin >> income;

        balance += income;

        chrono::system_clock::time_point now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);

        ofstream file("finance.txt", ios::app);
        if (file.is_open())
        {
            file << "Income from " << incomeSource << " on " << ctime(&currentTime) << "amount : +" << income << "\n";
            file.close();
        }
        else
        {
            cout << "Error opening file for writing.\n";
        }
    }

    void addExpense(double &balance)
    {
        string expenseTopic;
        double expense;

        cout << Bold << "Enter the expense topic: " << Reset;
        cin.ignore();
        getline(cin, expenseTopic);

        cout << Bold << "Enter the amount of expense: tk" << Reset;
        cin >> expense;

        if (expense > balance)
        {
            cout << Red << Bold << "Insufficient balance. Expense cannot be added.\n"
                 << Reset;
            return;
        }

        balance -= expense;

        chrono::system_clock::time_point now = std::chrono::system_clock::now();
        time_t currentTime = std::chrono::system_clock::to_time_t(now);

        ofstream file("finance.txt", ios::app);
        if (file.is_open())
        {
            file << "Expense of " << expenseTopic << " on " << ctime(&currentTime) << " amount : -" << expense << "\n";
            file.close();
        }
        else
        {
            cout << "Error opening file for writing.\n";
        }
    }

    void viewBalanceDetails(double balance)
    {
        cout << Green << Bold << "Current Balance: tk" << balance << "\n"
             << Reset;

        ifstream file("finance.txt");
        if (file.is_open())
        {
            string line;
            cout << Magenta << Bold << "\nPrevious Income and Expense Details:\n"
                 << Reset;
            while (getline(file, line))
            {
                cout << line << "\n";
            }
            file.close();
        }
        else
        {
            cout << "Error opening file for reading.\n";
        }
    }
    void runFinance()
    {
        double balance = 0.0;
        int choice;

        ifstream file("finance.txt");
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line.find("amount") != string::npos)
                {
                    size_t pos = line.find("+");
                    if (pos != string::npos)
                    {
                        balance += stod(line.substr(pos + 1));
                    }
                }
                else if (line.find("amount") != string::npos)
                {
                    size_t pos = line.find("-");
                    if (pos != string::npos)
                    {
                        balance -= stod(line.substr(pos + 1));
                    }
                }
            }
            file.close();
        }
        else
        {
            cout << "Error opening file for reading.\n";
        }
        do
        {
            displayMenu();
            cout << Green << Bold << "Enter your choice (1-5): " << Reset;
            cin >> choice;

            switch (choice)
            {
            case 1:
                addIncome(balance);
                break;
            case 2:
                addExpense(balance);
                break;
            case 3:
                cout << Green << Bold << "Your Current Balance is tk : " << balance << '\n'
                     << Reset;
                break;
            case 4:
                viewBalanceDetails(balance);
                break;
            case 5:
                cout << "Exiting the Finance Manager..... Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
};
// To Do List Class
//------------------------------------------------------vv
class ToDoList
{
private:
    struct taskStore
    {
        string key;
        int startHr;
        int startMn;
        int endHr;
        int endMn;
        string taskName[3];
    };

    deque<taskStore> task;
    map<string, pair<int, int> > topicTime;
    map<string, int> historySet;
    static bool compare(taskStore &node1, taskStore &node2)
    {
        if (node1.key < node2.key)
        {
            return true;
        }
        else if (node1.key > node2.key)
        {
            return false;
        }
        if (node1.startHr < node2.startHr)
        {
            return true;
        }
        else if (node1.startHr == node2.startHr)
        {
            return node1.startMn < node2.startMn;
        }
        return false;
    }

    string dateToString(int key)
    {
        time_t now = time(0);
        tm *time = localtime(&now);
        int year = (time->tm_year) + 1900;
        int month = time->tm_mon + 1;
        int day = time->tm_mday;

        string y = to_string(year), m = to_string(month), d = to_string(day);
        if (m.size() == 1)
            m = "0" + m;
        if (d.size() == 1)
            d = "0" + d;
        if (key)
            return y + m + d;
        return (d + "/" + m + "/" + y);
    }
    pair<int, int> secondToTime(int sec)
    {

        int hour = sec / 3600;
        int remSec = sec % 3600;
        int minutes = remSec / 60;
        if (sec < 0)
        {
            pair<int, int> par;
            par.first = 0;
            par.second = 0;
            return par;
        }
        pair<int, int> par;
        par.first = hour;
        par.second = minutes;
        return par;
    }
    pair<int, int> sumOfTime(pair<int, int> time1, pair<int, int> time2)
    {
        pair<int, int> res;
        res.first = (time1.first + time2.first);
        if (time1.second + time2.second >= 60)
        {
            int hour = (time1.second + time2.second) / 60;
            res.first += hour;
        }
        int minutes = (time1.second + time2.second) % 60;
        res.second = minutes;
        return res;
    }

public:
    vector<string> topic;
    void addTopic()
    {
        string topicName;
        cin.ignore();
        cout << Bold << "Enter a Topic Name: \n";
        getline(cin, topicName);
        topic.push_back(topicName);
        cout << "Topic added\n"
             << Reset << "\n";
    }
    void printFromTopicNo(int topicNo)
    {
        int no = 1, fl = 1;
        for (int i = 0; i < task.size(); i++)
        {
            if (task[i].taskName[0] == topic[topicNo - 1])
            {
                fl = 0;
                cout << "Task No: " << no << " \n";
                no++;
                cout << "Task Type : " << task[i].taskName[0] << "\n";
                cout << task[i].taskName[1] << " "
                     << "[" << task[i].taskName[2] << "]\n";
                cout << "Start at: " << task[i].startHr << " : " << task[i].startMn << " End at:  " << task[i].endHr << " : " << task[i].endMn << " \n";
                if (dateToString(1) == task[i].key)
                    cout << "Date: Today\'s Task.\n";
                else if (task[i].key.size() == 8)
                {
                    cout << "Upcoming Date: ";
                    string d, y, m;
                    for (int j = 0; j < 4; j++)
                        y += task[i].key[j];
                    for (int j = 4; j < 6; j++)
                        m += task[i].key[j];
                    for (int j = 6; j < 8; j++)
                        d += task[i].key[j];
                    cout << d << "/" << m << "/" << y << "\n";
                }
                else
                {
                    cout << "Daily work\n";
                }
                cout << "\n";
            }
        }
        if (fl)
        {
            cout << "Topic is Empty!\n";
        }
    }
    void printByTopic()
    {
        cout << Magenta << Bold << "All Topic Name: \n"
             << Reset;
        for (int i = 0; i < topic.size(); i++)
        {
            cout << Bold << "Topic No: " << i + 1 << ": " << topic[i] << "\n"
                 << Reset;
        }
        cout << Bold << "Please Enter a Topic Number for see details.or,Enter 0 for see all Topic with Tasks.\n";
        int topicNo;
        cin >> topicNo;
        if (topicNo > topic.size())
        {
            cout << Red << "Ivalid Topic Number!\n"
                 << Reset << Bold;
            return;
        }
        if (topicNo != 0)
        {
            cout << "Topic " << topicNo << " : " << topic[topicNo - 1] << "\n";
            printFromTopicNo(topicNo);
        }
        else
        {
            cout << "Topic and task:\n ";
            for (int i = 0; i < topic.size(); i++)
            {
                cout << "Topic " << i + 1 << " : " << topic[i] << "\n";
                printFromTopicNo(i + 1);
                cout << "\n";
            }
        }
        cout << Reset;
    }

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
                ifstream rFile("note1.txt");
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
                ofstream noteFile("note1.txt", ios::app);
                if (noteFile.is_open())
                {
                    cout << "Type your note here,(after finish enter 0 ) :\n";
                    string s;
                    cin.ignore();
                    do
                    {
                        getline(cin, s);
                        if (s[0] != 0 && s.size() != 1)
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
                ofstream myFile("note1.txt");
                if (myFile.is_open())
                {
                    myFile.clear();
                    cout << "cleared successfully!\n";
                    myFile.close();
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
            cout << "Task Type : " << task[i].taskName[0] << "\n";
            cout << task[i].taskName[1] << " "
                 << "[" << task[i].taskName[2] << "]\n";
            cout << "Start at: " << task[i].startHr << " : " << task[i].startMn << " End at:  " << task[i].endHr << " : " << task[i].endMn << " \n";
            if (dateToString(1) == task[i].key)
                cout << "Date: Today\'s Task.\n";
            else if (task[i].key.size() == 8)
            {
                cout << "Upcoming Date: ";
                string d, y, m;
                for (int j = 0; j < 4; j++)
                    y += task[i].key[j];
                for (int j = 4; j < 6; j++)
                    m += task[i].key[j];
                for (int j = 6; j < 8; j++)
                    d += task[i].key[j];
                cout << d << "/" << m << "/" << y << "\n";
            }
            else
            {
                cout << "Daily work\n";
            }
            cout << "\n";
        }
        cout << "--------------------------------------------------------\n";
    }

    void taskInput()
    {
        if (topic.size() == 0)
        {
            topic.push_back("Academic");
            topic.push_back("Exercise");
            topic.push_back("Home Work");
            topic.push_back("Skill development");
        }
        taskStore newnode;
        task.push_back(newnode);

        signed int size = task.size();
        int dateset;
        cout << "Enter 1(for todays task)Enter:2 (for Everydays task),Enter 3 and set date \n";
        cin >> dateset;
        if (dateset == 1)
        {
            task[size - 1].key = dateToString(1);
        }
        else if (dateset == 2)
        {
            task[size - 1].key = "0";
        }
        else
        {
            cout << "set the Task\'s Date(Day Month Year) with space like(15 01 2024):\n";
            string sday, syear, smonth;
            cin >> sday >> smonth >> syear;
            if (sday.size() == 1)
                sday = "0" + sday;
            if (smonth.size() == 1)
                smonth = "0" + smonth;
            task[size - 1].key = (syear + smonth + sday);
        }
        cout << "Enter start hour and min and End hour and min with space (like 11 35 12 30):\n";
        cin >> task[size - 1].startHr >> task[size - 1].startMn;
        cin >> task[size - 1].endHr >> task[size - 1].endMn;
        cout << "Select a Topic and Enter a Topic number(Enter 0 for None): \n";
        for (int i = 0; i < topic.size(); i++)
        {
            cout << "Topic No: " << i + 1 << " : " << topic[i] << "\n";
        }
        int topicNo;
        cin >> topicNo;
        if (topicNo <= topic.size() && topicNo != 0)
        {
            task[size - 1].taskName[0] = topic[topicNo - 1];
            int time1 = task[size - 1].startHr * 3600 + task[size - 1].startMn * 60;
            int time2 = task[size - 1].endHr * 3600 + task[size - 1].endMn * 60;
            pair<int, int> time = secondToTime(time2 - time1);
            topicTime[topic[topicNo - 1]] = sumOfTime(time, topicTime[topic[topicNo - 1]]);
        }
        else
        {
            task[size - 1].taskName[0] = "None";
        }
        cin.ignore();
        cout << "Task name:\n";
        getline(cin, task[size - 1].taskName[1]);
        task[size - 1].taskName[2] = "Not Done yet";
        cout << "Task is successfully added.\n";
        sort(task.begin(), task.end(), compare);
    }
    void taskMarkAsDone(int deleteMark)
    {
        if (deleteMark)
            cout << "If you will Mark any task this time,it will also be deleted.";
        cout << "Enter 1 for marking done todays all tasks\n";
        cout << "Enter 2 for marking done a specific task\n";
        cout << "Enter 0 for going back\n";
        int enter;
        cin >> enter;
        if (enter == 1)
        {
            string date = dateToString(1);
            for (int i = 0; i < task.size(); i++)
            {
                if (task[i].key == date)
                {
                    task[i].taskName[2] = "Done";
                    if (deleteMark)
                    {
                        task.erase(task.begin() + i);
                        i--;
                    }
                }
            }
            return;
        }
        else if (enter == 0)
        {
            return;
        }
        printTask();
        cout << "Which task have you done?Please Enter the task no:  \n";
        int taskNo;
        cin >> taskNo;
        if (taskNo > task.size())
        {
            cout << "Invalid input\n";
        }
        else if (task[taskNo - 1].taskName[2] != "Done")
        {
            task[taskNo - 1].taskName[2] = "Done";
            cout << "Well done! Keep going on.\n";
            if (deleteMark)
            {
                task.erase(task.begin() + taskNo - 1);
            }
        }
        else
        {
            if (deleteMark)
            {
                task.erase(task.begin() + taskNo - 1);
            }
            cout << "The task is allready done\n";
        }
    }
    void TodaysAllTask()
    {
        string date = dateToString(1);
        bool noTask = true;
        for (int i = 0; i < task.size(); i++)
        {
            if (task[i].key == date || task[i].key == "0")
            {
                noTask = false;
                cout << "TASK NO " << i + 1 << " [" << task[i].taskName[2] << "]\n";
                cout << "Task Type : " << task[i].taskName[0] << "\n";
                cout << "Your Task: " << task[i].taskName[1] << "\n";
                cout << "Start at: " << task[i].startHr << " : " << task[i].startMn << " End at:  " << task[i].endHr << " : " << task[i].endMn << " \n";
                if (task[i].key.size() == 8)
                    cout << "Date: Today\'s Task.\n";
                else
                    cout << "Every days Task";
                cout << "\n";
            }
        }
        if (noTask)
            cout << "No Task Today\n";
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
    // Histoty related
    void summaryToday()
    {
        map<string, pair<int, int> >::iterator it;
        cout << Bold << "Topic name : Hour"
             << "\n";
        int index = 1;
        for (it = topicTime.begin(); it != topicTime.end(); it++)
        {
            cout << index++ << " | " << it->first << " : " << it->second.first << " Hour " << it->second.second << " Minutes\n";
        }
    }
    void addSummaryToHistory()
    {
        time_t now = time(0);
        tm *time = localtime(&now);
        string key = dateToString(0);
        if (historySet[key] == 1)
        {
            cout << "Already set to file\n";
            return;
        }
        historySet[key] = 1;
        ofstream myFile("summary.txt", ios::app);
        if (myFile.is_open())
        {
            myFile << "***\nDate: " << key << "\n";
            myFile << "Topic name : Hour\n";
            int index = 1;
            map<string, pair<int, int> >::iterator it;
            for (it = topicTime.begin(); it != topicTime.end(); it++)
            {
                myFile << index++ << " | " << it->first << " : " << it->second.first << " Hour " << it->second.second << " Minutes\n";
            }
            myFile.close();
        }
        else
        {
            cout << "can not write\n";
        }
    }
    void showSummary()
    {
        ifstream readFile("summary.txt");
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

    void clearSummary()
    {
        if (1)
        {
            ofstream myFile("summary.txt");
            if (myFile.is_open())
            {
                cout << "History cleared.\n";
                myFile.clear();
                myFile.close();
            }
            else
            {
                cout << "file not open\n";
            }
        }
    }

    //

    void currentAndUpcoming(int &currHave)
    {
        const char *Red = "\033[1;31m";
        const char *Green = "\033[1;32m";
        const char *Reset = "\033[0m";
        time_t now = time(0);
        tm *local_time = localtime(&now);
        int hour = local_time->tm_hour;
        int minute = local_time->tm_min;
        // int second = local_time->tm_sec;
        if (hour == 23 && minute == 59 && historySet[dateToString(0)] == 0)
            addSummaryToHistory();
        bool flag = true;
        cout << Bold;
        cout << "*----------------------------------------------------------------------------------*\n";
        cout << Green << "\t\t\t\tCURRENT TASK: \n\n"
             << Reset << Bold;
        for (int i = 0; i < task.size(); i++)
        {
            if (task[i].key != "0" && dateToString(1) != task[i].key)
                continue;
            if (hour >= task[i].startHr && hour <= task[i].endHr)
            {

                if (hour == task[i].startHr && minute < task[i].startMn)
                    continue;

                if (hour == task[i].endHr && minute > task[i].endMn)
                    continue;
                currHave = i;
                cout << "Your task Now: "
                     << "[" << task[i].taskName[2] << "]\n";
                cout << "Task Type : " << task[i].taskName[0] << "\n";
                cout << "Have to done: " << task[i].taskName[1] << "\n";
                cout << "Started at: " << task[i].startHr << " : " << task[i].startMn << " End at:  " << task[i].endHr << " : " << task[i].endMn << " \n";
                if (i != (task.size() - 1))
                {

                    cout << "*----------------------------------------------------------------------------------*\n";
                    cout << Blue << "\t\t\t\tUPCOMING TASK: \n"
                         << Reset << Bold;
                    cout << "Task Type : " << task[i + 1].taskName[0] << "\n";
                    cout << task[i + 1].taskName[1] << " "
                         << "[" << task[i + 1].taskName[2] << "]\n";
                    if (dateToString(1) == task[i + 1].key)
                        cout << "Date: Today\'s Task.\n";
                    else if (task[i + 1].key.size() == 8)
                    {
                        cout << "Upcoming Date: ";
                        string d, y, m;
                        for (int j = 0; j < 4; j++)
                            y += task[i + 1].key[j];
                        for (int j = 4; j < 6; j++)
                            m += task[i + 1].key[j];
                        for (int j = 6; j < 8; j++)
                            d += task[i + 1].key[j];
                        cout << d << "/" << m << "/" << y << "\n";
                    }
                    else
                    {
                        cout << "Daily work\n";
                    }
                    cout << "Start at: " << task[i].startHr << " : " << task[i].startMn << " \nEnd at:  " << task[i].endHr << " : " << task[i].endMn << " \n";
                }
                else
                {
                    cout << "*----------------------------------------------------------------------------------*\n";
                    cout << Blue << "\t\t\t\tUPCOMING TASK: \n"
                         << Reset << Bold;
                    cout << "No upcoming task to show!\n";
                }

                flag = false;
                break;
            }
        }
        if (flag)
        {

            cout << "There is no Task at this time!\n\n";
            cout << "*----------------------------------------------------------------------------------*\n";
            cout << Blue << "\t\t\t\tUPCOMING TASK: \n"
                 << Reset << Bold;
            for (int i = 0; i < task.size(); i++)
            {

                if (hour <= task[i].startHr)
                {
                    cout << "Task Type : " << task[i].taskName[0] << "\n";
                    cout << "Task Name : " << task[i].taskName[1] << " "
                         << "[" << task[i].taskName[2] << "]\n";
                    if (dateToString(1) == task[i].key)
                        cout << "Date: Today\'s Task.\n";
                    else if (task[i + 1].key == "1")
                    {
                        cout << "Daily work\n";
                    }
                    else
                    {
                        cout << "Upcoming Date: ";
                        string d, y, m;
                        for (int j = 0; j < 4; j++)
                            y += task[i + 1].key[j];
                        for (int j = 4; j < 6; j++)
                            m += task[i + 1].key[j];
                        for (int j = 6; j < 8; j++)
                            d += task[i + 1].key[j];
                        cout << d << "/" << m << "/" << y << "\n";
                    }
                    cout << "Start at: " << task[i].startHr << " : " << task[i].startMn << " \nEnd at:  " << task[i].endHr << " : " << task[i].endMn << " \n";
                    return;
                }
            }
            cout << "No upcoming task to show!\n";
            cout << "*----------------------------------------------------------------------------------*\n";
        }
        cout << Reset;
    }

    // Function for showing time

    void displayCurrentTime()
    {
        const char *ITALIC_START = "\033[3m";
        const char *ITALIC_END = "\033[0m";
        const char *BLUE_COLOR = "\033[1;34m";
        const char *RESET_COLOR = "\033[0m";

        time_t currentTime = time(nullptr);
        struct tm *localTime = localtime(&currentTime);
        cout << "\n\t\t***-----------------------------------------***"
             << "\n"
             << endl;
        cout << BLUE_COLOR << ITALIC_START << Bold << "\n\t\t    Current time is:" << RESET_COLOR << White << Bold << asctime(localTime);
        cout << Reset << "\n\n\t\t***-----------------------------------------***"
             << "\n"
             << endl;

        this_thread::sleep_for(std::chrono::seconds(1));
        // system("clear");
    }

    void run()
    {
        bool go;

        do
        {
            go = true;
            int currInd = -1;
            displayCurrentTime();
            // this_thread::sleep_for(std::chrono::seconds(2));
            currentAndUpcoming(currInd);

            cout << Bold << "------------------------------------------------------------------------------------\n";
            cout << "Enter 1 for adding task.\n";
            cout << "Enter 2 for immediate Marking(Done) current Task.\n";
            cout << "Enter 3 for  Finance Manager.\n";
            cout << "Enter 4 for  BMI .\n";
            cout << "Enter 5 for  Note(Show,Delete or update).\n";
            cout << "Enter 6 for todays Task History.\n";
            cout << "Enter 7 for Marking Task.\n";
            cout << "Enter 8 for show all task.\n";
            cout << "Enter 9 for delete a task.\n";
            cout << "Enter 10 for delete all task.\n";
            cout << "Enter 11 for Adding Topic.\n";
            cout << "Enter 12 for Print task by Topic.\n";
            cout << "Enter 13 for Todays summary\n";
            cout << "Enter 14 for show,set or clear History(Summary)\n";
            cout << "Enter 0 for Refresh:\n"
                 << Reset;
            int command = 0;
            cin >> command;
            switch (command)
            {
            case 1:
                taskInput();
                break;
            case 2:
                if (currInd == -1)
                {
                    cout << "Sorry!There are no task at current time,please Refresh and check again\n";
                }
                else
                {
                    cout << "Enter 1 for only marking or Enter 2 for delete while marking\n";
                    int enter;
                    cin >> enter;
                    task[currInd].taskName[2] = "Done";
                    if (enter == 2)
                        task.erase(task.begin() + currInd);
                }
                break;
            case 3:
                Finance financeManager;
                financeManager.runFinance();
                break;
            case 4:
                health BMI;
                BMI.run();
                break;
            case 5:
                writingNote();
                break;
            case 6:
                cout << "Todays Task History.";
                TodaysAllTask();
                break;

            case 7:
                cout << "Enter 1 for delete while marking.Enter 0 for only marking\n";
                int deleteMark;
                cin >> deleteMark;
                taskMarkAsDone(deleteMark);
                break;

            case 8:
                printTask();
                break;

            case 9:
                deleteTask();
                break;

            case 10:
                task.clear();
                break;

            case 11:
                addTopic();
                break;
            case 12:
                printByTopic();
                break;
            case 13:
                summaryToday();
                break;
            case 14:
                cout << "Enter 1 for Show previous history\nEnter 2 for set history\nEnter 3 for clear History\n";
                int comd;
                cin >> comd;
                if (comd == 1)
                {
                    showSummary();
                }
                else if (comd == 2)
                {
                    addSummaryToHistory();
                }
                else if (comd == 3)
                {
                    clearSummary();
                }
                break;
            case 0:
                break;
            default:
                cout << "Invalid input\n";
                break;
            }
            cout << "Enter 1 for continue, 0 for terminate program.\n";
            int Enter = 1;
            if (command)
                cin >> Enter;
            if (Enter == 0)
            {
                go = false;
            }
            else
            {
                system("clear");
            }
            // this_thread::sleep_for(std::chrono::seconds(2));
        } while (go);
    }
};
// 3 file : note1.txt,finance.txt,weight.txt,summary.txt
int main()
{
    ToDoList toDoList;
    toDoList.run();

    return 0;
}
