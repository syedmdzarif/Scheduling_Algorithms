//Submitted By -> Syed Abu Ammar Muhammad Zarif (011202009)
//Round robin no preemption

#include <iostream>
#include <queue>
#include <algorithm>
#include <numeric>
#include <fstream>

using namespace std;

class Process
{
public:
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int end_time;
    int tat;
    int wt;
    int rt;

//    Process(int _pid, int _arrival_time, int _burst_time) :pid(_pid), arrival_time(_arrival_time), burst_time(_burst_time),
//            remaining_time(_burst_time), start_time(-1), end_time(-1), tat(0), wt(0), rt(0) {}
};

int index = 0;
Process finished_processes[100];

struct CompareProcess       // prioritize based on arrival time
{
    bool operator()(const Process& p1, const Process& p2) const
    {
        return p1.remaining_time > p2.remaining_time;
    }
};

void roundRobin(int quantum, int totalStep, int p, int n, int l)
{
    priority_queue<Process, vector<Process>, CompareProcess> processQueue;
    int currentTime = 0;
    int timeStep = 0;
    int totalProcesses = 0;

    srand(50);      //seed

    while (currentTime < totalStep && timeStep < totalStep)
    {
        float low = 0.0;
        float high = 1.0;
        int decimal = 100;
        int randInt = rand() % ((static_cast<int>((low - high) * decimal)) + 1);
        float probability = (static_cast<float>(randInt) / decimal) + low;      //p is the probability for process arrival

        if(probability > p)
        {
            int numProcesses = rand() % n + 1;  //number of processes 1 to n
            cout << endl;
            cout << "At time step " << timeStep << ", no. of new processes created is: " << numProcesses << endl;
            cout << endl;

            for (int i = 0; i < numProcesses; ++i)
            {
                int burstTime = rand() % l + 1;     //burst time 1 to l
                //int burstTime = 7;
                Process newProcess;
                newProcess.pid = ++totalProcesses;
                newProcess.arrival_time = timeStep;
                newProcess.burst_time = burstTime;
                newProcess.remaining_time = burstTime;
                newProcess.start_time = -1;
                newProcess.end_time = -1;
                newProcess.tat = 0;
                newProcess.wt = 0;
                newProcess.rt = 0;
                processQueue.push(newProcess);
            }

            if (!processQueue.empty())
            {
                Process currentProcess = processQueue.top();
                processQueue.pop();

                int timeLeft = totalStep - min(currentTime, timeStep); // Remaining time in the current time step
                int executeTime = min(quantum, min(currentProcess.remaining_time, timeLeft)); // Time quantum = 3

                if (currentProcess.start_time == -1)
                {
                    currentProcess.start_time = currentTime;
                }

                currentTime += executeTime;
                currentProcess.remaining_time -= executeTime;

                while (currentProcess.remaining_time > 0 && currentTime <= 50)
                {
                    currentProcess.end_time = currentTime;
                    if(currentProcess.end_time > 50)
                    {
                        break;
                    }
                    currentProcess.tat = currentProcess.end_time - currentProcess.arrival_time;
                    currentProcess.wt = currentProcess.tat - currentProcess.burst_time;
                    currentProcess.rt = currentProcess.start_time - currentProcess.arrival_time;


                    cout << "Process ID -> " << currentProcess.pid << " Arrival Time -> " << currentProcess.arrival_time
                         << " Burst Time -> " << currentProcess.burst_time << " Remaining Time -> " << currentProcess.remaining_time
                         << " Turnaround Time -> " << currentProcess.tat << ", Waiting Time -> " << currentProcess.wt
                         << " Response Time -> " << currentProcess.rt << ", Start Time -> " << currentProcess.start_time <<" End Time -> " << currentProcess.end_time << endl;

                    currentProcess.remaining_time -= executeTime;
                    currentTime += executeTime;
                    timeStep++;

                    int timeLeft = totalStep - min(currentTime, timeStep); // Remaining time in the current time step
                    int executeTime = min(quantum, min(currentProcess.remaining_time, timeLeft)); // Time quantum = 3

                }
                if(currentTime <= 50){
                currentProcess.end_time = currentTime;
                if(currentProcess.wt < 0){
                    currentProcess.wt = 0;
                }

                currentProcess.tat = currentProcess.end_time - currentProcess.arrival_time;
                currentProcess.wt = currentProcess.tat - currentProcess.burst_time;
                currentProcess.rt = currentProcess.start_time - currentProcess.arrival_time;



                cout << "Process ID -> " << currentProcess.pid << " Arrival Time -> " << currentProcess.arrival_time
                         << " Burst Time -> " << currentProcess.burst_time << " Remaining Time -> " << currentProcess.remaining_time
                         << " Turnaround Time -> " << currentProcess.tat << ", Waiting Time -> " << currentProcess.wt
                         << " Response Time -> " << currentProcess.rt << ", Start Time -> " << currentProcess.start_time <<" End Time -> " << currentProcess.end_time << endl;

                finished_processes[index] = currentProcess;     //add the finished processes to array
                index++;
                }
//                else
//                {
//                    //currentProcess.wt=-1;
//                    cout << "Process ID -> " << currentProcess.pid << " Arrival Time -> " << currentProcess.arrival_time
//                         << " Burst Time -> " << currentProcess.burst_time << " Remaining Time -> " << currentProcess.remaining_time << endl;
//
//                    processQueue.push(currentProcess);
//                }
            }
            else
            {
                currentTime++;
            }

            timeStep++;
        }
        else
        {
            currentTime++;
            timeStep++;
        }
    }
}

int main()
{
    float p=0.9;      //p > probability for new process to arrive
    int n=7;        //number of process to arrive between 1 and n
    int l=4;        //burst time for each process between 1 and l
    int quantum = 3;
    int totalStep = 50;
    roundRobin(quantum, totalStep, p, n, l);

    int maxTAT_PID = 0, maxWT_PID = 0, maxRT_PID = 0;
    float TAT_sum = 0, WT_sum = 0, RT_sum = 0;

    cout << endl;

    for(int i = 0; i < index; i++)
    {
        cout << "Finished Process -> " << finished_processes[i].pid << " Arrival -> " << finished_processes[i].arrival_time << " Start -> " << finished_processes[i].start_time
             << " Remaining ->  " << finished_processes[i].remaining_time <<
             " End Time -> " << finished_processes[i].end_time << " TAT -> " << finished_processes[i].tat << " WT -> "
             << finished_processes[i].wt << " RT -> " << finished_processes[i].rt << endl;

        TAT_sum = TAT_sum + finished_processes[i].tat;
        WT_sum = WT_sum + finished_processes[i].wt;
        RT_sum = RT_sum + finished_processes[i].rt;

        if(finished_processes[i].tat > finished_processes[maxTAT_PID].tat)
        {
            maxTAT_PID = i;
        }
        if(finished_processes[i].wt > finished_processes[maxWT_PID].wt)
        {
            maxWT_PID = i;
        }
        if(finished_processes[i].rt > finished_processes[maxRT_PID].rt)
        {
            maxRT_PID = i;
        }
    }

    cout << endl;

    cout << "Highest TAT -> " << finished_processes[maxTAT_PID].tat << " for Process ID -> " << finished_processes[maxTAT_PID].pid << endl;
    cout << "Average TAT -> " << (float) TAT_sum/index << endl;

    cout << "Highest WT -> " << finished_processes[maxWT_PID].wt << " for Process ID -> " << finished_processes[maxWT_PID].pid << endl;
    cout << "Average WT -> " << (float) WT_sum/index << endl;

    cout << "Highest RT -> " << finished_processes[maxRT_PID].rt << " for Process ID -> " << finished_processes[maxRT_PID].pid << endl;
    cout << "Average RT -> " << (float) RT_sum/index << endl;

    cout<<endl;

//    cout<< "Start Gantt Chart" << endl;
    ofstream file("processes.txt");
    for(int i = 0; i < index; i++)
    {
        file << finished_processes[i].pid << " " << finished_processes[i].arrival_time << " " << finished_processes[i].start_time
             << " " << finished_processes[i].burst_time << " " << finished_processes[i].end_time << " " << finished_processes[i].tat << " "
             << finished_processes[i].wt << " " << finished_processes[i].rt << endl;
    }
    file.close();
//    cout<< "End Gantt Chart" << endl;
}
