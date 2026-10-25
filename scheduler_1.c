#include <stdio.h>
#include <stdlib.h>

// Structure to represent a Process
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int is_completed;
} Process;

// Function prototypes
void fcfs(Process proc[], int n);
void sjf(Process proc[], int n);
void print_results(Process proc[], int n);

int main(void) {
    int n;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    Process *proc_fcfs = (Process *)malloc(n * sizeof(Process));
    Process *proc_sjf = (Process *)malloc(n * sizeof(Process));

    if (proc_fcfs == NULL || proc_sjf == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        proc_fcfs[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        if (scanf("%d %d", &proc_fcfs[i].arrival_time, &proc_fcfs[i].burst_time) != 2) {
            printf("Invalid input.\n");
            free(proc_fcfs);
            free(proc_sjf);
            return 1;
        }
        proc_fcfs[i].is_completed = 0;
        
        // Copy initial data to SJF array
        proc_sjf[i] = proc_fcfs[i];
    }

    printf("\n");
    fcfs(proc_fcfs, n);
    sjf(proc_sjf, n);

    free(proc_fcfs);
    free(proc_sjf);

    return 0;
}

// Function to simulate FCFS (First Come First Served)
void fcfs(Process proc[], int n) {
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].arrival_time > proc[j + 1].arrival_time) {
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    int execution_order[100];

    for (int i = 0; i < n; i++) {
        if (current_time < proc[i].arrival_time) {
            current_time = proc[i].arrival_time;
        }

        proc[i].waiting_time = current_time - proc[i].arrival_time;
        proc[i].response_time = proc[i].waiting_time; // Non-preemptive: RT == WT
        current_time += proc[i].burst_time;
        proc[i].turnaround_time = current_time - proc[i].arrival_time;

        execution_order[i] = proc[i].pid;
    }

    // Print Gantt Chart
    printf("=== First Come First Served (FCFS) ===\n");
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", execution_order[i]);
    }
    printf("|\n");

    print_results(proc, n);
}

// Function to simulate SJF (Shortest Job First - Non-preemptive)
void sjf(Process proc[], int n) {
    int current_time = 0;
    int completed = 0;
    int execution_order[100];
    int order_idx = 0;

    while (completed < n) {
        int idx = -1;
        int min_burst = 1e9;

        // Find available process with shortest burst time
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= current_time && !proc[i].is_completed) {
                if (proc[i].burst_time < min_burst) {
                    min_burst = proc[i].burst_time;
                    idx = i;
                } else if (proc[i].burst_time == min_burst) {
                    // Tie-breaker: choose process with earlier arrival time
                    if (proc[i].arrival_time < proc[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        // If no process has arrived yet, advance time
        if (idx == -1) {
            int next_arrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (!proc[i].is_completed && proc[i].arrival_time < next_arrival) {
                    next_arrival = proc[i].arrival_time;
                }
            }
            current_time = next_arrival;
            continue;
        }

        // Execute selected process
        proc[idx].waiting_time = current_time - proc[idx].arrival_time;
        proc[idx].response_time = proc[idx].waiting_time;
        current_time += proc[idx].burst_time;
        proc[idx].turnaround_time = current_time - proc[idx].arrival_time;
        proc[idx].is_completed = 1;

        execution_order[order_idx++] = proc[idx].pid;
        completed++;
    }

    // Sort process array back by PID for clean tabular display
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].pid > proc[j + 1].pid) {
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    // Print Gantt Chart
    printf("=== Shortest Job First (SJF) ===\n");
    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", execution_order[i]);
    }
    printf("|\n");

    print_results(proc, n);
}

// Function to print results table and calculated averages
void print_results(Process proc[], int n) {
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].waiting_time,
               proc[i].turnaround_time,
               proc[i].response_time);

        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
        total_rt += proc[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n\n", total_rt / n);
}
