#include <stdio.h>
#include <time.h>


enum Level 
{
    LOW,
    MEDIUM,
    HIGH,

};

enum Status 
{
    DEVELOP,
    COMPLETED,
    INCOMPLETED,
    PAUSE,
};

struct Task
{
public:
    Task() = default;
    Task(char*,char32_t* ,Level, Status, time_t);

    char* getName() const;
    Level getLevel() const;
    Status getStatus() const;
    char32_t* getDescription() const;
    time_t getDeadline() const;

    void setStatus(Status);
    void setName(char*);
    void setLevel(Level);
    void setDescription(char32_t*);
    void setDeadLine(time_t);

    
private: 
    char* name;
    time_t deadline;
    char32_t* description;
    Level complexity;
    Status status;
};

struct TaskManager
{
    public:
        Task* getAllTasks() const;
        TaskManager() = default;
        TaskManager(Task*); 
        void addTask(const Task&);
        void completeTask(const Task&);
        int getTasksCount() const; 
    private: 
        Task* tasks;
};


