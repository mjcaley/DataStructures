#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using std::priority_queue;
using std::vector;
using std::cin;
using std::cout;



struct WorkerThread
{
    WorkerThread() = default;
    WorkerThread(int id) : id(id) {};
    
    int id { 0 };
    long long finish_time { 0 };
    
    bool operator>(const WorkerThread& wt) const
    {
        if (finish_time == wt.finish_time)
        {
            return id > wt.id;
        }
        else if (finish_time > wt.finish_time)
        {
            return true;
        }
        else// if (finish_time < wt.finish_time)
        {
            return false;
        }
    }
};


class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;
    
    vector<int> assigned_workers_;
    vector<long long> start_times_;
    
    priority_queue<WorkerThread, vector<WorkerThread>, std::greater<WorkerThread>> workers;
    
    void init_worker_threads(int n)
    {
        for (auto i = 0; i < n; ++i)
        {
            workers.emplace(WorkerThread(i));
        }
    }
    
    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }
    
    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        
        init_worker_threads(num_workers_);
        
        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }
    
    void AssignJobs() {
        for (auto job : jobs_)
        {
            auto next_worker = workers.top();
            auto job_start_time = next_worker.finish_time;
            workers.pop();
            next_worker.finish_time += job;
            
            // save worker & start time
            assigned_workers_.emplace_back(next_worker.id);
            start_times_.emplace_back(job_start_time);
            
            workers.push(next_worker);
        }
    }
    
public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
