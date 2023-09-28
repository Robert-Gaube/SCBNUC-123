#include <bits/stdc++.h>
 
#define FILE_IN "data.txt"
#define MAXTASKS 10001
#define MAXMACHINES 51
#define MAXDISKS 31
 
using namespace std;
 
int number_tasks, number_machines, number_disks;
 
struct TASK {
    int size, data, number_data_dependencies, number_task_dependencies, output_disk, start_time, machine_run, pre_read_time; 
    unordered_map<int, bool> data_dependencies; 
    unordered_map<int, bool> task_dependencies; 
    bool finished, started;
    vector<int> machines; 
};
TASK tasks[MAXTASKS];
 
struct MACHINE {int power, task_id, task_start_time, task_pre_write_end_time, task_end_time;};
MACHINE machines[MAXMACHINES];
 
struct DISK {int speed, capacity;};
DISK disks[MAXDISKS];
 
void show_tasks() {
    int i, j, size;
    unordered_map<int, bool>::iterator itr;
    for(i = 1; i <= number_tasks; ++i) {
        cout << i << ": " << tasks[i].size << ", " << tasks[i].data << ", Machines "
        << tasks[i].machines.size() << ": ";
        size = tasks[i].machines.size();
        for(j = 0; j < size; ++j) 
            cout << tasks[i].machines[j] << " ";
        cout << "Data dependencies " << tasks[i].number_data_dependencies << ": ";
        for (itr = tasks[i].data_dependencies.begin(); itr != tasks[i].data_dependencies.end(); itr++)
            cout << itr -> first << " ";
        cout << "Task dependencies " << tasks[i].number_task_dependencies << ": ";
        for (itr = tasks[i].task_dependencies.begin(); itr != tasks[i].task_dependencies.end(); itr++)
            cout << itr -> first << " ";
        cout << '\n';
    }
    cout << '\n';
}
void read() {
    // ifstream in(FILE_IN);
    cin >> number_tasks;
    int machine_counter, id, counter, machine, task_number_machines;
 
    // Reading task data
    for(counter = 0; counter < number_tasks; ++counter) {
        cin >> id >> tasks[id].size >> tasks[id].data;
        cin >> task_number_machines;
        for(machine_counter = 0; machine_counter < task_number_machines; ++machine_counter) {
            cin >> machine;
            tasks[id].machines.push_back(machine);
        }
        tasks[counter].number_data_dependencies = 0;
        tasks[counter].number_task_dependencies = 0;
        tasks[counter].finished = false;
        tasks[counter].started = false;
        tasks[counter].pre_read_time = 0;
    }
    cin >> number_machines;
 
    // Reading machine data
    for(counter = 0; counter < number_machines; ++counter) {
        cin >> id >> machines[id].power;
        machines[id].task_end_time = machines[id].task_pre_write_end_time = -1;
    }
    
    cin >> number_disks;
 
    //Reading disk data
    for(counter = 0; counter < number_disks; ++counter)
        cin >> id >> disks[id].speed >> disks[id].capacity;
 
    int number_dependencies, x, y;
 
    //Reading data dependencies
    cin >> number_dependencies;
    for(counter = 0; counter < number_dependencies; ++counter) {
        cin >> x >> y;
        tasks[y].data_dependencies[x] = true;
        tasks[y].number_data_dependencies++;
    }
 
    //Reading task dependencies
    cin >> number_dependencies;
    for(counter = 0; counter < number_dependencies; ++counter) {
        cin >> x >> y;
        tasks[y].task_dependencies[x] = true;
        tasks[y].number_task_dependencies++;
    }
    // in.close(); 
}
int choose_machine_for_task(TASK task, int time) {
    int i, machines_size = task.machines.size();
    int best_id = 0, max_power = 0;
    for(i = 0; i < machines_size; ++i) {
        if(machines[task.machines[i]].task_end_time <= time)
            if(machines[task.machines[i]].power > max_power) {
                max_power = machines[task.machines[i]].power;
                best_id = task.machines[i];
            }
    }
    return best_id;
}
int choose_disk_for_task(TASK task) {
    int i, best_speed = 0, best_id = 0;
    for(i = 1; i <= number_disks; ++i) {
        if(task.data <= disks[i].capacity) 
            if(disks[i].speed > best_speed) {
                best_speed = disks[i].speed;
                best_id = i;
            }
    }
    return best_id;
}
int task_duration(TASK task, MACHINE machine, DISK disk) {
    return ceil((double)task.size / machine.power) + ceil((double)task.data / disk.speed) + task.pre_read_time;
}
void start_task(int task_index, MACHINE &machine, int disk_index, int time) {
    // cout << "Start task " << task_index << " at "<< time << " and end at " << time + task_duration(tasks[task_index], machine, disks[disk_index]) << endl;
 
    machine.task_id = task_index;
    machine.task_start_time = time;
    machine.task_end_time = time + task_duration(tasks[task_index], machine, disks[disk_index]);
    machine.task_pre_write_end_time = machine.task_end_time - ceil((double)tasks[task_index].data / disks[disk_index].speed);
 
    disks[disk_index].capacity -= tasks[task_index].data;
 
    tasks[task_index].output_disk = disk_index;
    tasks[task_index].started = true;
 
}
void delete_data_dependencies(int task_index) {
    int i;
    for(i = 1; i <= number_tasks; ++i) {
        if(tasks[i].data_dependencies.find(task_index) != tasks[i].data_dependencies.end()) {
            if(tasks[i].data_dependencies[task_index] == true) {
                tasks[i].data_dependencies[task_index] = false;
                tasks[i].pre_read_time += ceil((double)tasks[task_index].data / disks[tasks[task_index].output_disk].speed);
                tasks[i].number_data_dependencies--;
            }
        }
    }
}
void delete_task_dependencies(int task_index) {
    int i;
    for(i = 1; i <= number_tasks; ++i) {
        if(tasks[i].task_dependencies.find(task_index) != tasks[i].task_dependencies.end()) {
            if(tasks[i].task_dependencies[task_index] == true) {
                tasks[i].task_dependencies[task_index] = false;
                tasks[i].number_task_dependencies--;
            }
        }
    }
}
void solution() {
    int number_tasks_finished = 0, time = 0, i, machine_id, disk_id, task_id, next_time, max_time = 0;
    priority_queue <pair<int,int> > available_tasks;
    TASK task;
 
    while(number_tasks_finished < number_tasks) {
        
        next_time = max_time;
        for(i = 1; i <= number_machines; ++i) { // Check if any tasks finished and update accordingly
            if(time == machines[i].task_end_time) {
                tasks[machines[i].task_id].finished = true;
                number_tasks_finished++;
                task_id = machines[i].task_id;
 
                tasks[task_id].start_time = machines[i].task_start_time;
                tasks[task_id].machine_run = i;
 
                delete_data_dependencies(machines[i].task_id);
            }
            else if(time == machines[i].task_pre_write_end_time) {
                delete_task_dependencies(machines[i].task_id);
            }
        }
        for(i = 1; i <= number_tasks; ++i) { // Try to start a task
            if(!tasks[i].started && !tasks[i].number_data_dependencies && !tasks[i].number_task_dependencies) {
               available_tasks.push(make_pair(tasks[i].size, i));
            }
        }
 
        while(!available_tasks.empty()) {
            task = tasks[available_tasks.top().second];
            machine_id = choose_machine_for_task(task, time);
            if(machine_id != 0) {
                disk_id = choose_disk_for_task(task);
                start_task(available_tasks.top().second, machines[machine_id], disk_id, time);
                max_time = max(max_time, machines[machine_id].task_end_time);
            }
            available_tasks.pop();
        }
 
        for(i = 1; i <= number_machines; ++i) {
            if(tasks[machines[i].task_id].started && !tasks[machines[i].task_id].finished) {
                next_time = min(next_time, machines[i].task_pre_write_end_time);
                next_time = min(machines[i].task_end_time, next_time);
            }
        }
        time = max(time + 1, next_time);
        //cout << time << endl;
    }
}
void show_solution() {
    int i;
    for(i = 1; i <= number_tasks; ++i) {
        cout << i << " " << tasks[i].start_time << " " << tasks[i].machine_run << " " << tasks[i].output_disk << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    read();
    solution();
    show_solution();
    return 0;
}