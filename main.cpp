#define CROW_MAIN
#include "crow.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int priority;
    int response_time;
};

//First Come First Serve
void calculateTimesFCFS(std::vector<Process>& processes) {
    int current_time = 0;
    for (auto& process : processes) {
        if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }
        process.waiting_time = current_time - process.arrival_time;
        process.turnaround_time = process.waiting_time + process.burst_time;
        process.completion_time = current_time + process.burst_time;
        current_time += process.burst_time;
        process.response_time = process.waiting_time;
    }
}

//Shortest Remaining Time First
void calculateTimesSRTF(std::vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    int completed = 0;

    for (auto& process : processes) {
        process.remaining_time = process.burst_time;
        process.response_time = -1;
    }

    while (completed != n) {
        int min_remaining_time = INT_MAX;
        int shortest = -1;
        bool check = false;

        for (int i = 0; i < n; i++) {
            if ((processes[i].arrival_time <= current_time) && (processes[i].remaining_time < min_remaining_time) && 
                (processes[i].remaining_time > 0)) {
                min_remaining_time = processes[i].remaining_time;
                shortest = i;
                check = true;
            }
        }

        if (check == false) {
            current_time++;
            continue;
        }
        if(processes[shortest].response_time==-1){
            processes[shortest].response_time = current_time - processes[shortest].arrival_time;
        }
        processes[shortest].remaining_time--;

        current_time++;

        if (processes[shortest].remaining_time == 0) {
            completed++;
            processes[shortest].completion_time = current_time;
            processes[shortest].waiting_time = processes[shortest].completion_time - processes[shortest].arrival_time - processes[shortest].burst_time;
            if (processes[shortest].waiting_time < 0) {
                processes[shortest].waiting_time = 0;
            }
            processes[shortest].turnaround_time = processes[shortest].burst_time + processes[shortest].waiting_time;
        }
    }
}

// Priority Scheduling (Lower Number Higher Priority)
void calculateTimesPriority(std::vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    int aging_interval = 60000; // 1 minute
    int aging_factor = 1; // Priority decrement factor per aging interval
    std::vector<bool> completed(n, false);
    int completed_count = 0;

    while (completed_count < n) {
        int highest_priority = std::numeric_limits<int>::max();
        int idx = -1;

        // Find the process with the highest priority (lowest priority number) that is ready to execute
        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrival_time <= current_time && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            // If the highest priority process has not started yet or is preempting another process
            if (current_time < processes[idx].arrival_time) {
                current_time = processes[idx].arrival_time;
            }
            if(processes[idx].response_time==-1){
                processes[idx].response_time = current_time-processes[idx].arrival_time;
            }
            // Execute the process for one time unit
            processes[idx].remaining_time--;

            // Update waiting time for other processes
            for (int i = 0; i < n; i++) {
                if (i != idx && !completed[i] && processes[i].arrival_time <= current_time) {
                    processes[i].waiting_time++;
                }
            }

            current_time++;
            // Check if the process has completed execution
            if (processes[idx].remaining_time == 0) {
                processes[idx].turnaround_time = current_time - processes[idx].arrival_time;
                processes[idx].completion_time = current_time;
                completed[idx] = true;
                completed_count++;
            }

            // Apply aging to all non-completed processes
            for (int i = 0; i < n; i++) {
                if (!completed[i] && processes[i].arrival_time <= current_time) {
                    if (((current_time - processes[i].arrival_time) % aging_interval) == 0) {
                        processes[i].priority -= aging_factor;
                        // Ensure priority does not drop below a certain minimum (optional)
                        if (processes[i].priority < 0) {
                            processes[i].priority = 0;
                        }
                    }
                }
            }
        } else {
            current_time++; // No process is ready to execute, move to next time unit
        }
    }
}

// Round Robin Algorithm
void calculateTimesRR(std::vector<Process>& processes, int time_quantum) {
    int n = processes.size();
    int current_time = 0;
    std::queue<int> q;
    std::vector<int> remaining_time(n);
    std::vector<bool> is_in_queue(n, false);

    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time) {
            q.push(i);
            is_in_queue[i] = true;
        }
    }

    while (!q.empty()) {
        int idx = q.front();
        q.pop();
        is_in_queue[idx] = false;
        if(processes[idx].response_time==-1){
            processes[idx].response_time = current_time-processes[idx].arrival_time;
        }
        if (remaining_time[idx] > time_quantum) {
            current_time += time_quantum;
            remaining_time[idx] -= time_quantum;

            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && i!=idx && !is_in_queue[i] && remaining_time[i] > 0) {
                    q.push(i);
                    is_in_queue[i] = true;
                }
            }

            q.push(idx);
            is_in_queue[idx] = true;
        } else {
            current_time += remaining_time[idx];
            remaining_time[idx] = 0;
            processes[idx].completion_time = current_time;
            processes[idx].waiting_time = processes[idx].completion_time - processes[idx].arrival_time - processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].waiting_time + processes[idx].burst_time;

            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && !is_in_queue[i] && remaining_time[i] > 0) {
                    q.push(i);
                    is_in_queue[i] = true;
                }
            }
        }
    }
}

//Auto schedule the processes
void auto_schedule(std::vector<Process>& processes,int time_quantum){
    double sum = 0,mean = 0,STDDEV = 0,N = processes.size();
    for(int i=0;i < (int)processes.size();i++){
        sum+=processes[i].burst_time;
    }
    mean = (sum/(N*1.0))*1.0;
    for(int i=0;i < (int)processes.size();i++)
    {
        STDDEV += ((processes[i].burst_time - mean) * (processes[i].burst_time - mean));
    }
    STDDEV = sqrt(STDDEV/N);
    if(STDDEV < mean/2.0) {
       calculateTimesFCFS(processes);
       return;
    }
    if(N > 7){
        calculateTimesRR(processes,time_quantum);
        return;
    }
    
    calculateTimesSRTF(processes);
}

//For display in terminal
void displayProcesses(const std::vector<Process>& processes) {
    int n = processes.size();
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    std::cout << "PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        std::cout << process.pid << "\t"
                  << process.arrival_time << "\t\t"
                  << process.burst_time << "\t\t"
                  << process.waiting_time << "\t\t"
                  << process.turnaround_time << "\n";
        total_waiting_time += process.waiting_time;
        total_turnaround_time += process.turnaround_time;
    }

    std::cout << "\nAverage Waiting Time: " << (float)total_waiting_time / n << "\n";
    std::cout << "Average Turnaround Time: " << (float)total_turnaround_time / n << "\n";
}

void sorted(std::vector<Process>& processes){
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if(a.arrival_time==b.arrival_time && a.priority==b.priority) return a.pid<b.pid;
        else if(a.arrival_time==b.arrival_time)return a.priority<b.priority;
        return a.arrival_time < b.arrival_time;
    });
}

//Scheduler
void scheduler(const std::string& algorithm, std::vector<Process>& processes, int time_quantum = 1) {
    sorted(processes);
    if (algorithm == "FCFS") {
        calculateTimesFCFS(processes);
    } else if (algorithm == "SRTF") {
        calculateTimesSRTF(processes);
    } else if (algorithm == "Priority") {
        calculateTimesPriority(processes);
    } else if (algorithm == "RR") {
        calculateTimesRR(processes, time_quantum);
    } else if (algorithm == "auto") {
        auto_schedule(processes,time_quantum);
    } else {
        std::cout << "Unsupported scheduling algorithm.\n";
        return;
    }
    //for display in terminal
    displayProcesses(processes);
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/api/schedule").methods("POST"_method)([](const crow::request& req) {
        auto j = crow::json::load(req.body);
        if (!j) {
            return crow::response(400, "Invalid JSON");
        }
        
        // Extract algorithm
        std::string algorithm = j["algorithm"].s();
        // Extract timeQuantum (if exists)
        int timeQuantum = j.has("timeQuantum") ? j["timeQuantum"].i() : -1;

        std::vector<Process> processes;
        for (const auto& p : j["processes"]) {
            Process it = {
                static_cast<int>(processes.size() + 1),
                p["arrival_time"].i(),
                p["burst_time"].i(),
                p["burst_time"].i(),
                0,
                0,
                0,
                p["priority"].i(),
                -1
            };
            processes.push_back(it);
        }
        
        scheduler(algorithm,processes,timeQuantum);

        int n = processes.size();
        int total_waiting_time = 0;
        int total_turnaround_time = 0;
        for (const auto& process : processes) {
            total_waiting_time += process.waiting_time;
            total_turnaround_time += process.turnaround_time;
        }
        float avg_waiting_time = (float)total_waiting_time / n;
        float avg_turnaround_time = (float)total_turnaround_time / n;
        
        // Construct the JSON response
        crow::json::wvalue response;
        response["algorithm"] = algorithm;
        response["avg_waiting_time"] = avg_waiting_time;
        response["avg_turnaround_time"] = avg_turnaround_time;
    
        // Add processes to the response
        crow::json::wvalue::list processArray;
        for (const auto& process : processes) {
            crow::json::wvalue processJson;
            processJson["pid"] = process.pid;
            processJson["arrival_time"] = process.arrival_time;
            processJson["burst_time"] = process.burst_time;
            processJson["waiting_time"] = process.waiting_time;
            processJson["turnaround_time"] = process.turnaround_time;
            processJson["completion_time"] = process.completion_time;
            processJson["priority"] = process.priority;
            processJson["response_time"] = process.response_time;
            processArray.emplace_back(std::move(processJson));
        }
        response["processes"] = std::move(processArray);

        return crow::response(response);
    });

    std::cout << "Server listening on port 8080" << std::endl;
    app.bindaddr("127.0.0.1").port(8080).multithreaded().run();

    return 0;
}
