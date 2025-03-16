#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;
class Task
{
    public:
        static int count;
        int *arrival_time;
        int *burst_time;
        int *priority;
        double through_put[5];
        double avg_turn_around_time[5];
        double avg_waiting_time[5];
        Task(int n)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            arrival_time=new int[n];
            burst_time=new int[n];
            priority=new int[n];
            for(int i=0;i<n;i++)
            {
                arrival_time[i] = 0;
                SetConsoleTextAttribute(hConsole, 5);
                cout<<"Enter Information About Task "<<i+1<<": "<<endl;
                SetConsoleTextAttribute(hConsole, 6);
                cout<<"Enter The Completion Time of the Task : ";cin>>burst_time[i];
                while(1)
                {
                    cout<<"Enter The Priority of the task (1-20) : ";cin>>priority[i];
                    if(priority[i]<1 || priority[i]>20)
                    {
                        cout<<"Invalid Input for Priority !!"<<endl;
                    }
                    else
                        break;
                }
            }
            getchar();
            cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
            system("cls");
            SetConsoleTextAttribute(hConsole, 5);
            FIFO(n);
            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Press Enter to continue: ";
            getchar();
            system("cls");
            SetConsoleTextAttribute(hConsole, 5);
            RR(n);
            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Press Enter to continue: ";
            getchar();
            system("cls");
            SetConsoleTextAttribute(hConsole, 5);
            SJF(n);
            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Press Enter to continue: ";
            getchar();
            system("cls");
            SetConsoleTextAttribute(hConsole, 5);
            PQ(n);
            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Press Enter to continue: ";
            getchar();
            system("cls");
            SetConsoleTextAttribute(hConsole, 5);
            display();
            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Press Enter to continue: ";
            getchar();
            system("cls");
            SetConsoleTextAttribute(hConsole, 5);
            displaygraph(n);
            SetConsoleTextAttribute(hConsole, 7);
            cout<<"Press Enter to Exit: ";
            getchar();
            system("cls");
        }
        void FIFO(int n)
        {
            cout<<"First Come First Serve Scheduling Algorithm "<<endl;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            int sum1=0,sum2=0;
            int *completion_time=new int[n];
            int *waiting_time=new int[n];
            int *turn_around_time=new int[n];
            completion_time[0]=burst_time[0];
            for(int i=1;i<n;i++)
            {
                completion_time[i]=burst_time[i]+completion_time[i-1];
            }
            for(int i=0;i<n;i++)
            {
                turn_around_time[i]=completion_time[i]-arrival_time[i];
                sum1+=turn_around_time[i];
                waiting_time[i]=turn_around_time[i]-burst_time[i];
                sum2+=waiting_time[i];
            }
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"|"<<setw(10)<<"T"<<setw(10)<<"|"<<setw(10)<<"AT"<<setw(10)<<"|"<<setw(10)<<"BT"<<setw(10)<<"|"<<setw(10)<<"CT"<<setw(10)<<"|"<<setw(10)<<"TAT"<<setw(10)<<"|"<<setw(10)<<"WT"<<setw(10)<<"|"<<endl;
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
            for(int i=0;i<n;i++)
            {
                cout<<"|"<<setw(10)<<i+1<<setw(10)<<"|"<<setw(10)<<arrival_time[i]<<setw(10)<<"|"<<setw(10)<<burst_time[i]<<setw(10)<<"|"<<setw(10)<<completion_time[i]<<setw(10)<<"|"<<setw(10)<<turn_around_time[i]<<setw(10)<<"|"<<setw(10)<<waiting_time[i]<<setw(10)<<"|"<<endl;
            }
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
            avg_turn_around_time[0]=0;
            avg_waiting_time[0]=0;
            avg_turn_around_time[0]=float(sum1)/n;
            avg_waiting_time[0]=float(sum2)/n;
            cout<<"Average Turn Around Time : "<<avg_turn_around_time[0]<<endl;
            cout<<"Average Waiting Time     : "<<avg_waiting_time[0]<<endl;
            SetConsoleTextAttribute(hConsole, 5);
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
        }
        void RR(int n)
        {
            cout<<"Round Robin Scheduling Algorithm "<<endl;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            int sum1=0,sum2=0;
            int *completion_time=new int[n];
            int *waiting_time=new int[n];
            int *turn_around_time=new int[n];
            int *temp=new int[n];
            int time_quantum=2;
            int current_time=0;
            int flag=0;
            for(int i=0;i<n;i++)
            {
                    temp[i]=burst_time[i];
                    arrival_time[i]=0;
            }
            while (1)
            {
                for(int i=0;i<n;i++) 
                {
                    if(temp[i]>0)
                    {
                        if(temp[i]>time_quantum)
                        {
                            current_time+=time_quantum;
                            temp[i]-=time_quantum;    
                        }
                        else
                        {
                            current_time+=temp[i];
                            completion_time[i]=current_time;
                            temp[i]=0;
                        }
                    }
                }
                for(int i=0;i<n;i++)
                {
                    if(temp[i]!=0)
                    {
                        flag=0;
                        break;
                    }

                    flag=1;
                }
                if(flag==1)
                    break;
            }
            for(int i=0;i<n;i++)
            {
                turn_around_time[i]=completion_time[i]-arrival_time[i];
                sum1+=turn_around_time[i];
                waiting_time[i]=turn_around_time[i]-burst_time[i];
                sum2+=waiting_time[i];
            }
            avg_turn_around_time[1]=0;
            avg_waiting_time[1]=0;
            avg_turn_around_time[1]=float(sum1)/n;
            avg_waiting_time[1]=float(sum2)/n;
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"|"<<setw(10)<<"T"<<setw(10)<<"|"<<setw(10)<<"AT"<<setw(10)<<"|"<<setw(10)<<"BT"<<setw(10)<<"|"<<setw(10)<<"CT"<<setw(10)<<"|"<<setw(10)<<"TAT"<<setw(10)<<"|"<<setw(10)<<"WT"<<setw(10)<<"|"<<endl;
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
            for(int i=0;i<n;i++)
            {
                cout<<"|"<<setw(10)<<i+1<<setw(10)<<"|"<<setw(10)<<arrival_time[i]<<setw(10)<<"|"<<setw(10)<<burst_time[i]<<setw(10)<<"|"<<setw(10)<<completion_time[i]<<setw(10)<<"|"<<setw(10)<<turn_around_time[i]<<setw(10)<<"|"<<setw(10)<<waiting_time[i]<<setw(10)<<"|"<<endl;
            }
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"Average Turn Around Time : "<<avg_turn_around_time[1]<<endl;
            cout<<"Average Waiting Time     : "<<avg_waiting_time[1]<<endl;
            SetConsoleTextAttribute(hConsole, 5);
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
        }
        void SJF(int n)
        {
            cout<<"Shortest Job First Scheduling Algorithm"<<endl;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            int i,j;
            int *completion_time = new int[n];
            int *turn_around_time = new int[n];
            int *waiting_time = new int[n];
            int *ord_bt = new int[n];
            for(i=0;i<n;i++)
            {
                ord_bt[i] = i;
                arrival_time[i]=0;
            }
            for(i=0;i<n-1;i++)
            {
                for(j=0;j<n-1-i;j++)
                {
                    if(burst_time[j]>burst_time[j+1])
                    {
                        int temp1 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1] = temp1;
                        int temp2 = ord_bt[j];
                        ord_bt[j] = ord_bt[j+1];
                        ord_bt[j+1] = temp2;
                        int temp3 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1] = temp3;
                    }
                }
            }
            completion_time[0] = burst_time[0];
            for(i=1;i<n;i++)
            {
                completion_time[i] = burst_time[i] + completion_time[i-1];
            }
            for(i=0;i<n;i++)
            {
                turn_around_time[i] = completion_time[i] - arrival_time[i];
                waiting_time[i] = turn_around_time[i] - burst_time[i];
            }
            for(i=0;i<n;i++)
            {
                for(j=0;j<n-i-1;j++)
                {
                    if(ord_bt[j]>ord_bt[j+1])
                    {
                        int temp1 = ord_bt[j];
                        ord_bt[j] = ord_bt[j+1];
                        ord_bt[j+1] = temp1;
                        int temp2 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1] = temp2; 
                        int temp3 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1] = temp3;
                        int temp4 = completion_time[j];
                        completion_time[j] = completion_time[j+1];
                        completion_time[j+1] = temp4;
                        int temp5 = turn_around_time[j];
                        turn_around_time[j] = turn_around_time[j+1];
                        turn_around_time[j+1] = temp5;
                        int temp6 = waiting_time[j];
                        waiting_time[j] = waiting_time[j+1];
                        waiting_time[j+1] = temp6;
                    }
                }
            }
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"|"<<setw(10)<<"T"<<setw(10)<<"|"<<setw(10)<<"AT"<<setw(10)<<"|"<<setw(10)<<"BT"<<setw(10)<<"|"<<setw(10)<<"CT"<<setw(10)<<"|"<<setw(10)<<"TAT"<<setw(10)<<"|"<<setw(10)<<"WT"<<setw(10)<<"|"<<endl;
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
            for(int i=0;i<n;i++)
            {
                cout<<"|"<<setw(10)<<i+1<<setw(10)<<"|"<<setw(10)<<arrival_time[i]<<setw(10)<<"|"<<setw(10)<<burst_time[i]<<setw(10)<<"|"<<setw(10)<<completion_time[i]<<setw(10)<<"|"<<setw(10)<<turn_around_time[i]<<setw(10)<<"|"<<setw(10)<<waiting_time[i]<<setw(10)<<"|"<<endl;
            }
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
            avg_turn_around_time[2]=0;
            avg_waiting_time[2]=0;
            for(i=0;i<n;i++)
            {
                avg_turn_around_time[2] += turn_around_time[i];
                avg_waiting_time[2] += waiting_time[i];
            }
            avg_turn_around_time[2] = avg_turn_around_time[2]/5;
            avg_waiting_time[2] = avg_waiting_time[2]/5;
            cout<<"Average Turn Around Time : "<<avg_turn_around_time[2]<<endl;
            cout<<"Average Waiting Time : "<<avg_waiting_time[2]<<endl;
            SetConsoleTextAttribute(hConsole, 5);
            cout<<"-------------------------------------------------------------------------------------------------------------------------"<<endl;
        }
        void PQ(int n)
        {
            cout<<"Priority Queue Scheduling Algorithm"<<endl;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            int i,j;
            int *completion_time = new int[n];
            int *turn_around_time = new int[n];
            int *waiting_time = new int[n];
            int *o = new int[n];
            for(i=0;i<n;i++)
            {
                o[i] = i;
            }
            for(i=0;i<n-1;i++)
            {
                for(j=0;j<n-1-i;j++)
                {
                    if(priority[j]>priority[j+1])
                    {
                        int temp1 = priority[j];
                        priority[j] = priority[j+1];
                        priority[j+1] = temp1;
                        int temp2 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1] = temp2;
                        int temp3 = o[j];
                        o[j] = o[j+1];
                        o[j+1] = temp3; 
                        int temp4 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1] = temp4;
                    }
                }
            }
            completion_time[0] = burst_time[0];
            for(i=1;i<n;i++)
            {
                completion_time[i] = burst_time[i] + completion_time[i-1];
            }
            for(i=0;i<n;i++)
            {
                turn_around_time[i]=completion_time[i]-arrival_time[i];
                waiting_time[i]=turn_around_time[i]-burst_time[i];
            }
            for(i=0;i<n;i++)
            {
                for(j=0;j<n-i-1;j++)
                {
                    if(o[j]>o[j+1])
                    {
                        int temp1 = o[j];
                        o[j] = o[j+1];
                        o[j+1] = temp1;
                        int temp2 = priority[j];
                        priority[j] = priority[j+1];
                        priority[j+1] = temp2;
                        int temp3 = burst_time[j];
                        burst_time[j] = burst_time[j+1];
                        burst_time[j+1] = temp3; 
                        int temp4 = arrival_time[j];
                        arrival_time[j] = arrival_time[j+1];
                        arrival_time[j+1] = temp4;
                        int temp5 = completion_time[j];
                        completion_time[j] = completion_time[j+1];
                        completion_time[j+1] = temp5;
                        int temp6 = turn_around_time[j];
                        turn_around_time[j] = turn_around_time[j+1];
                        turn_around_time[j+1] = temp6;
                        int temp7 = waiting_time[j];
                        waiting_time[j] = waiting_time[j+1];
                        waiting_time[j+1] = temp7;
                    }
                }
            }
            cout<<"---------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"|"<<setw(10)<<"T"<<setw(10)<<"|"<<setw(10)<<"AT"<<setw(10)<<"|"<<setw(10)<<"BT"<<setw(10)<<"|"<<setw(15)<<"Priority"<<setw(5)<<"|"<<setw(10)<<"CT"<<setw(10)<<"|"<<setw(10)<<"TAT"<<setw(10)<<"|"<<setw(10)<<"WT"<<setw(10)<<"|"<<endl;
            cout<<"---------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            for(int i=0;i<n;i++)
            {
                cout<<"|"<<setw(10)<<i+1<<setw(10)<<"|"<<setw(10)<<arrival_time[i]<<setw(10)<<"|"<<setw(10)<<burst_time[i]<<setw(10)<<"|"<<setw(10)<<priority[i]<<setw(10)<<"|"<<setw(10)<<completion_time[i]<<setw(10)<<"|"<<setw(10)<<turn_around_time[i]<<setw(10)<<"|"<<setw(10)<<waiting_time[i]<<setw(10)<<"|"<<endl;
            }
            cout<<"---------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            avg_turn_around_time[3]=0;
            avg_waiting_time[3]=0;
            for(i=0;i<n;i++)
            {
                avg_turn_around_time[3] += turn_around_time[i];
                avg_waiting_time[3] += waiting_time[i];
            }
            avg_turn_around_time[3] = avg_turn_around_time[3]/5;
            avg_waiting_time[3] = avg_waiting_time[3]/5;
            cout<<"Average Turn Around Time : "<<avg_turn_around_time[3]<<endl;
            cout<<"Average Waiting Time : "<<avg_waiting_time[3]<<endl;
            SetConsoleTextAttribute(hConsole, 5);
            cout<<"--------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        }
        void display()
        {
            cout<<"Comparison Table: "<<endl;
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 2);
            cout<<"------------------------------------------------------------"<<endl;
            cout<<"|"<<setw(10)<<"Scheduling Alg"<<setw(6)<<"|"<<setw(10)<<"Avg TAT"<<setw(10)<<"|"<<setw(10)<<"Avg WT"<<setw(10)<<"|"<<endl;
            cout<<"------------------------------------------------------------"<<endl;
            cout<<"|"<<setw(10)<<"FCFS"<<setw(10)<<"|"<<setw(10)<<avg_turn_around_time[0]<<setw(10)<<"|"<<setw(10)<<avg_waiting_time[0]<<setw(10)<<"|"<<endl;
            cout<<"|"<<setw(10)<<"RR"<<setw(10)<<"|"<<setw(10)<<avg_turn_around_time[1]<<setw(10)<<"|"<<setw(10)<<avg_waiting_time[1]<<setw(10)<<"|"<<endl;
            cout<<"|"<<setw(10)<<"SJF"<<setw(10)<<"|"<<setw(10)<<avg_turn_around_time[2]<<setw(10)<<"|"<<setw(10)<<avg_waiting_time[2]<<setw(10)<<"|"<<endl;
            cout<<"|"<<setw(10)<<"PQ"<<setw(10)<<"|"<<setw(10)<<avg_turn_around_time[3]<<setw(10)<<"|"<<setw(10)<<avg_waiting_time[3]<<setw(10)<<"|"<<endl;
            SetConsoleTextAttribute(hConsole, 5);
            cout<<"------------------------------------------------------------"<<endl;
        }
        void displaygraph(int n)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            string a[4]={"FIFO : ","RR   : ","SJF  : ","PQ   : "};
            cout<<"Comparison Chart of Average Turn Around Time :"<<endl;
            for(int i=0;i<4;i++)
            {
                SetConsoleTextAttribute(hConsole, 1+i);
                cout<<a[i];
                for(int j=0;j<int(avg_turn_around_time[i]);j++)
                {
                    cout<<" * ";
                }
                cout<<endl;
            }
            SetConsoleTextAttribute(hConsole, 8);
            cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
            SetConsoleTextAttribute(hConsole, 5);
            cout<<"Comparison Chart of Average Waiting Time :"<<endl;
            for(int i=0;i<4;i++)
            {
                SetConsoleTextAttribute(hConsole, 1+i);
                cout<<a[i];
                for(int j=0;j<int(avg_waiting_time[i]);j++)
                {
                    cout<<" * ";
                }
                cout<<endl;
            }
            SetConsoleTextAttribute(hConsole, 8);
            cout<<"----------------------------------------------------------------------------------------------------------------"<<endl;
        } 
};
int Task :: count=0; 
int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);
    int n;
    cout<<"Enter Total Number Of Tasks : ";cin>>n;
    Task T(n);
    SetConsoleTextAttribute(hConsole, 7);
    return 0;
}
