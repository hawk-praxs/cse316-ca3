#include <bits/stdc++.h> 
using namespace std; 

public class Process
{   
    // Process and its attributes
    public:
    int process_id; 
    int burst_time; 
    int temp_burst_time; 
    int response_time; 
    int arrival_time; 
    int priority; 
    int out_time; 
    int in_time;

    private:
    // Insert processes for execution in the ready queue
    // queueSize defines the number of processes in execution depending on the currentTime variable
    // currentTime keeps a record of the current CPU time. 
    void insert(Process Queue[], Process value, int* queue_size, int* current_time)  
    { 
      int start = *queue_size, i; 
      Queue[*queue_size] = value; 
      if (Queue[*queue_size].intime == -1) 
          Queue[*queue_size].intime = *current_time; 
      ++(*queue_size); 
  
      // Sorting Queue[]
      while (start != 0 && Queue[(start - 1) / 2].priority > Queue[start].priority)
      { 
          Process temp = Queue[(start - 1) / 2]; 
          Queue[(start - 1) / 2] = Queue[start]; 
          Queue[start] = temp; 
          start = (start - 1) / 2; 
      } 
    } 

    // Sort Queue[] again after insertion of new processes
    void sort(Process Queue[], int* queue_size, int start)  
    { 
      int smallest = start; 
      int left = 2 * start + 1; 
      int right = 2 * start + 2; 
      if (left < *queue_size && Queue[left].priority < Queue[smallest].priority) 
          smallest = left; 
      if (right < *queue_size && Queue[right].priority < Queue[smallest].priority) 
          smallest = right; 
  
      // Sorting the Queue
      if (smallest != start)
      { 
          Process temp = Queue[smallest]; 
          Queue[smallest] = Queue[start]; 
          Queue[start] = temp; 
          order(Queue, queue_size, smallest); 
      } 
    } 
  
    // Find highest priority process and sort the Queue[] again
    Process extractminimum(Process Queue[], int* queue_size, int* current_time) //
    { 
      Process min = Queue[0]; 
      if (min.response_time == -1) 
          min.response_time = *current_time - min.arrival_time; 
    
      --(*queue_size); 
    
      if (*queue_size >= 1)
      { 
          Queue[0] = Queue[*queue_size]; 
          order(Queue, queue_size, 0); 
      } 
      return min;
    } 
  
    // Compares two intervals of processes according to staring times
    bool compare(Process p1, Process p2) 
    { 
      return (p1.arrival_time < p2.arrival_time); 
    } 
  
    // Execute the highest priority process from Queue[] 
    void scheduling(Process Queue[], Process array[], int n, int* queue_size, int* current_time) 
    { 
      if (queue_size == 0) 
        return; 
  
      Process min = extractminimum(Queue, queue_size, current_time); 
      min.out_time = *current_time + 1; 
      --min.burst_time;
      cout << "Process ID = " << min.process_id << "Current Time = " << *current_time;
  
      //Reinsert the unfinished process into the Queue[] 
      if (min.burst_time > 0)
      { 
          insert(Queue, min, queue_size, current_time); 
          return; 
      } 
  
      for (int i = 0; i < n; i++)
      {
          if (array[i].process_id == min.process_id)
          {
            array[i] = min; 
            break; 
          }
      }
    } 
  
// This function is responsible for 
// managing the entire execution of the 
// processes as they arrive in the CPU 
// according to their arrival time. 
    void priority(Process array[], int n) 
    {
      sort(array, array + n, compare); 
  
      int total_waiting_time = 0;
      int total_burst_time = 0;
      int total_turnaround_time = 0;
      int inserted_process = 0; 
      int queue_size = 0;
      int current_time = array[0].arrival_time; 
      int total_response_time = 0;
  
      Process Queue[4 * n]; 
  
      // Calculating the total burst time of the processes 
      for (int i = 0; i < n; i++)
      { 
          total_burst_time += array[i].burst_time; 
          array[i].temp_burst_time = array[i].burst_time; 
      } 
  
      // Inserting the processes in Heap 
      // according to arrival time 
      do{
        if (inserted_process != n)
        {
          for (i = 0; i < n; i++)
          {
            if (array[i].arrival_time == current_time)
            {
              ++inserted_process; 
              array[i].in_time = -1; 
              array[i].response_time = -1; 
              insert(Queue, array[i], &heap_size, current_time); 
            } 
          } 
        } 
        scheduling(Queue, array, n, &queue_size, current_time); 
        ++current_time; 
        if (queue_size == 0 && inserted_process == n) 
            break;
      }while (1); 
  
      for (int i = 0; i < n; i++)
      {
        total_response_time += array[i].response_time; 
        total_waiting_time += (array[i].out_time - array[i].in_time - array[i].temp_burst_time); 
        total_burst_time += array[i].burst_time; 
      }
      
      cout << "Average waiting time \n" << (float)totalwaitingtime / (float)n; 
      cout << "Average response time \n" << (float)totalresponsetime / (float)n; 
      cout << "Average turn around time \n" << (float)(totalwaitingtime + totalbursttime) / (float)n; 
    }
}

int main() 
{
  int n, process_id, priority, arrival_time, burst_time;
  cout << "Enter no. of processes: ";
  cin >> n;
  
  Process process[n];
  cout << "Enter Process ID, Priority, Arrival Time & Burst Time:";
  for(int i = 0; i < n; i++)
  {
    cout << i;
    cin >> process_id >> priority >> arrival_time >> burst_time;
    process[i].process_id = process_id;
    process[i].priority = priority;
    process[i].arrival_time = arrival_time;
    process[i].burst_time = burst_time;
  }
  
  priority(process, n);
  
  return 0; 
} 
