/********************************************/
/*                                          */
/*  assignment3finalcopy.c                  */
/*  Allen Peng Lu                           */
/*  ID: 1498902                             */
/* Collaborating Classmates: Ali Reza Mosavi*/
/*Ankush Sharma                             */
/********************************************/
 
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//Some function prototypes
int getrand(int time1, int time2);
void createFiles(int m,int n,int t2,int k);
double maxNum(double a,double b);


 
int intchecker1(FILE *fp, int *vint)
{
 
    if (fscanf(fp, "%d", vint) != 1)
    {
        printf("Error in reading the instance!\n");
        exit(-2);
    }
    else
        return 0;
}
 
 
int lpt    (int time, int num_jobs, int num_machines,int originalindex[],int sorted_job[][3]);
int johnson(int time, int num_jobs, int num_machines,int originalindex[],int sorted_job[][3]);
 
 
//Do process i, taking input from a FILE* (which can either be stdin or a normal file)
//The argument printOutput determines whether to print text output
double process_i_fp(FILE *fp, _Bool printOutput) {
	int num_machines, num_jobs;
    intchecker1(fp, &num_machines);
    intchecker1(fp, &num_jobs);
 
    int job[num_jobs][3];
 
    // printf("Enter in each line the processing times for a job: \n");
    //Jobs are stored in a 2d array while checking if the processing times are correct
    for (int i=0; i<num_jobs; i++)
    {
        for (int j = 0; j<3; j++)
        {
            intchecker1(fp, &job[i][j]);
        }
    }
 
    // lpt column reading
 
    //make copy for sorting
    int sorted_job   [num_jobs][3];
    int originalindex[num_jobs];
    for (int j=0; j < num_jobs; j++){
        for (int col=0; col<3; col++) {
            sorted_job[j][col] = job[j][col];
        }
        originalindex[j] = j;
    }

    int someIndex[num_jobs];
    for (int i = 0;i<num_jobs;i++) {
        someIndex[i] = originalindex[i];

    }
 
    //sort
    int temp;
    int temp2;
    for (int i = 0; i < num_jobs; i++){
        for (int j = 1; j < (num_jobs - i); j++){
            _Bool prevSmallerThanNext =
                ( sorted_job   [j-1][0] < sorted_job   [j][0] ) ? 1 :
                ( sorted_job   [j-1][0] > sorted_job   [j][0] ) ? 0 :
                ( sorted_job   [j-1][1] < sorted_job   [j][1] ) ;
            if (prevSmallerThanNext){
                // the bucket process of switching objects
 
                //switch a row in sorted_job
                for (int col=0; col<3; col++) {
                    temp                 = sorted_job[j-1][col];
                    sorted_job[j-1][col] = sorted_job[j  ][col];
                    sorted_job[j  ][col] = temp;
                }
 
                //switch originalindex
                temp2              = originalindex[j-1];
                originalindex[j-1] = originalindex[j];
                originalindex[j  ] = temp2;
            }
        }
    }

 
    //first call
    int makespan1_lpt     =                           lpt    (0       , num_jobs,num_machines, originalindex, sorted_job);
    int makespan1_johnson = (num_jobs>num_machines) ? johnson(0       , num_jobs,num_machines, originalindex, sorted_job) : 0;
 
    //find next time
    int makespan1_max = makespan1_lpt>=makespan1_johnson ? makespan1_lpt : makespan1_johnson;
    int nextTime = makespan1_max;
 
    //second call
    int makespan2_lpt     = (num_jobs>num_machines) ? lpt    (nextTime, num_jobs,num_machines, originalindex, sorted_job) : 0;
    int makespan2_johnson =                           johnson(nextTime, num_jobs,num_machines, originalindex, sorted_job);
 
    //overall makespan
    int makespan2_max = makespan2_lpt>=makespan2_johnson ? makespan2_lpt : makespan2_johnson;
    int lpt_johnson_makespan = makespan1_max + makespan2_max;

    int S = lpt_johnson_makespan;
    int J1 = sorted_job[0][0];
//    int Jn = sorted_job[num_jobs-1][0];
    int sumOfTime = 0;
    for (int i=0;i<num_jobs-1;i++) {
        sumOfTime = sumOfTime + sorted_job[i][0];
    }
    double a1Sum = (sumOfTime/(double)num_machines);
    double L1 = maxNum(J1,a1Sum);
    int    L2 = johnson(0,num_jobs,num_jobs,someIndex,sorted_job);
    double L = maxNum(L1,L2);
    double r = (S/L);
    //printf("%f\n",r);
    
    //print output
    if (printOutput) {
        printf("a_1 = %d\n", J1);
        printf("average load = %f\n", a1Sum);
        printf("L_1 = %f\n", L1);
        printf("L_2 = %d\n", L2);
        printf("L = %f\n", L);
        printf("LPT_Johnson schedule makespan = %d\n", S);
        printf("r = %f\n", r);
    }
 
    return r;
}

int process_i() {
    process_i_fp(stdin, true);
    return 0;
}

float generate_ratio(int *arr, int n, int m){
    //essentially copy the above statement and put in terms of its own function
    //essentially 
	return 0;
}

//copy the sorting process over to another function



double maxNum(double a,double b) {
    if (a>b) {
        return a;
    } else if (b>a) {
        return b;
    } else {
        return a;
    }
}
 
int process_r() {
    /*int t_1, t_2;
    int instances;
    srand(time(NULL));
 
    printf("Generating random instances... \n");
    printf("Enter the number of machines in stage 1: ");
    //check for valid number of machinery, not done yet.
	int num_machines, num_jobs;
    scanf("%d", &num_machines);
    if (num_machines < 1)
    {
        printf("Error in reading the Instance!\n");
        return -2;
    }
 
    printf("Enter the number of jobs: ");
    scanf("%d", &num_jobs);
    if (num_jobs < 1)
    {
        printf("Error in reading the instance!\n");
        return -2;
    }
 
    printf("Enter the processing time interval [t_1, t_2]: ");
    //another check for proper input? (eg, t_2 is always bigger than t_1 etc etc
    scanf("%d %d", &t_1, &t_2);
 
    if (t_1 > t_2)
    {
        printf("t_1 must be lesser than t_2");
        return -2;
    }
 
 
    printf("Enter the number of instances to be generated: ");
    //Does it need to be 4 instances like said in the assignment?
    scanf("%d", &instances);
    if (instances < 1)
    {
        printf("Error in reading the instance number input!\n");
        return -2;
    }
    //This is where we generate the instances*/

    for             (int m= 1;m<= 20;m+= 1) {
        for         (int n=10;n<=200;n+=10) {
            for     (int t=10;t<=100;t+=10) {
                for (int k= 1;k<=100;k+= 1) {
                    createFiles(m,n,t,k);
                }
            }
        }
    }

    return 0;
}

void createFiles(int m,int n,int t2,int k){
    FILE *file;
    char strList[50];
    //Create file name
    sprintf(strList,"instance%d_%d_%d_%d_%d.txt",m,n,1,t2,k);
    printf("%s\n",strList);
    //Open the file
    file = fopen(strList,"w");
    if (file == NULL){
        perror("failed to open the file\n");
        exit(-1);
    } 
    //Gets machine and num_job value
    fprintf(file,"%d\n",m);
    fprintf(file,"%d\n",n);
    int job[n][3];
    for (int i = 0; i < n; i++) {
                for ( int j = 0; j < 3; j++) {
                    //Get a random value
                    job[i][j] = getrand(1,t2);
                    fprintf(file,"%d ", job[i][j]);
                }
                fprintf(file,"\n");
            }
    // printf("#end of instance\n\n");
    fprintf(file,"\n");

    fclose(file);
    //generate_ratio(m,n,t2,k,strList);

}

//This is where we generate a ratio file
/*float generate_ratio(int m,int n, int t, int k, char instancefile[]){
    //FILE *fp;
    char BashCmd[100];
    // char ratiofile[50];
   
    // sprintf(ratiofile,"ratio%d_%d_1_%d_%d.txt",m,n,t,k);

    strcpy(BashCmd,"./a.out -i <");
    strcat(BashCmd,instancefile);
    strcat(BashCmd,">> ");
    strcat(BashCmd,"output.txt");
    system(BashCmd);

    int ratio = 0;

    return ratio;

}**/


//This function gets random values in the desired range
int getrand(int time1, int time2) {
    return (rand()%(time2-time1)+time1);
}
 
int main(int argc, char *argv[])
{
    //grab the input as myprogram -i or myprogram -r, still have yet to do that!!
 
    if( argc == 1){
        printf("assignment1finalcopy2.c -i | -r \n");
        return -1;
    }
 
    if( !((strcmp(argv[1],"-i")==0) != (strcmp(argv[1],"-r")==0)) ){
        printf("assignment1finalcopy2.c -i | -r \n");
        return -1;
    }
 
    //functionality 2, does not check if -i or -r
    // error instance reading
    if (strcmp(argv[1], "-i" ) == 0)
    {
        return process_i();
    }
    if (strcmp(argv[1], "-r") == 0)
    {
        process_r();

        //start measure time
        time_t starttime = time(NULL);
        
        //open output file
        const char *output_fileName = "result.txt";
        FILE *fp_output = fopen(output_fileName, "w");
        if (! fp_output) {
            printf("Failed to open file: %s\n", output_fileName);
            exit(-1);
        }
        
        //average ratios
        double avgRatio_MxN[20][20];
        double avgRatio_M[20];
        double avgRatio_N[20];
        double avgRatio;
        double z = 0;

        //avg - for each (m,n) pair
        FILE *fp_instance;

        const char *plot_data_file = "plot1data.txt";
        FILE *plot1data = fopen(plot_data_file, "w");
        char instance[4096];
        for             (int m= 1, mI=0; m<= 20; m+= 1, mI++) {
            for         (int n=10, nI=0; n<=200; n+=10, nI++) {
                z = 0;
                for     (int t=10      ; t<=100; t+=10      ) {
                    for (int k= 1      ; k<=100; k+= 1      ) {
                        //open file
                        sprintf(instance,"instance%d_%d_%d_%d_%d.txt",m,n,1,t,k);
                        fp_instance = fopen(instance,"r");
                        if (! fp_instance) {
                            printf("Failed to open file: %s\n", instance);
                            exit(-1);
                        }
                        
                        //get ratio
                        z += process_i_fp(fp_instance, false);
                        
                        //free the variable 
                        fclose(fp_instance);
                    }
                }
                avgRatio_MxN[mI][nI] = z/1000;
                fprintf(fp_output, "%f ", avgRatio_MxN[mI][nI]);
                fprintf(plot1data, "%d %d %f\n",m,n,avgRatio_MxN[mI][nI]);
            }
            fprintf(fp_output, "\n");
        }
        fprintf(fp_output, "\n");
        

        //avg - for each m

        const char *plot2_data_file = "plot2data.txt";
        FILE *plot2data = fopen(plot2_data_file, "w");

        for (int mI=0; mI<20; mI++) {
            z = 0;
            for (int nI=0; nI<20; nI++) {
                z += avgRatio_MxN[mI][nI];
            }
            avgRatio_M[mI] = z / 20;
            fprintf(fp_output, "%f ", avgRatio_M[mI]);
            fprintf(plot2data,"%d %f\n",mI+1, avgRatio_M[mI]);
        }
        fprintf(fp_output, "\n\n");
        
        //avg - for each n
        const char *plot3_data_file = "plot3data.txt";
        FILE *plot3data = fopen(plot3_data_file, "w");

        for (int nI=0; nI<20; nI++) {
            z = 0;
            for (int mI=0; mI<20; mI++) {
                z += avgRatio_MxN[mI][nI];
            }
            avgRatio_N[nI] = z / 20;
            fprintf(fp_output, "%f ", avgRatio_N[nI]);
            fprintf(plot3data,"%d %f\n",(nI*10)+10,avgRatio_N[nI]);
        }
        fprintf(fp_output, "\n\n");
        
        //avg - for all
        z = 0;
        for (int mI=0; mI<20; mI++) {
            z += avgRatio_M[mI];
        }
        avgRatio = z / 20;
        fprintf(fp_output, "%f\n\n", avgRatio);
        
        //running time
        
        fprintf(fp_output,"%f\n", difftime(time(NULL),starttime));

        fclose(fp_output);

        return 0;
    }
}
 
int lpt(int time, int num_jobs, int num_machines,int originalindex[],int sorted_job[][3]){
    //number of jobs to schedule
    int minimumOfJobOrMachine = (num_jobs<num_machines) ? num_jobs : num_machines;
    int jobsToSchedule = (time==0) ? minimumOfJobOrMachine : num_jobs - num_machines;
    if (jobsToSchedule <= 0)
        return 0;
 
    //list of jobs to schedule
    // printf("\nLPT order:");
    int nextJobs_id    [jobsToSchedule];
    int nextJobs_length[jobsToSchedule];
    for (int jStart=(time==0?0:num_machines), j=0; j<jobsToSchedule; j++) {
        nextJobs_id    [j] = originalindex[jStart+j];
        nextJobs_length[j] = sorted_job   [jStart+j][0];
    }
    int nextJobIndex = 0;
 
    //storing result of scheduling
    int sched_id        [num_machines][num_jobs];
    int sched_startTime [num_machines][num_jobs];
    int sched_endTime   [num_machines][num_jobs];
    int schedCount      [num_machines];
    for (int m=0; m<num_machines; m++)
        schedCount[m] = 0;
    (void)sched_id;
    (void)sched_startTime;
 
    // printf("\nJob information:\n");
 
    //schedule the tasks
    int timeNow = time;
    while (1) {
        //find out which machine is free
        int m_free;
        for (int m=0; m<num_machines; m++) {
            _Bool endsNow = schedCount[m]==0 || (sched_endTime[m][schedCount[m]-1] == timeNow);
            if (endsNow) {
                m_free = m;
                break;
            }
        }
 
        //give free machine the next job
        int j_newlyAdded = schedCount[m_free];
        sched_id        [m_free][j_newlyAdded] = nextJobs_id[nextJobIndex];
        sched_startTime [m_free][j_newlyAdded] = timeNow;
        sched_endTime   [m_free][j_newlyAdded] = timeNow + nextJobs_length[nextJobIndex];
        schedCount      [m_free]               += 1;
        nextJobIndex++;
 
        //have more jobs?
        _Bool haveMoreJobToSchedule = nextJobIndex < jobsToSchedule;
 
        if (! haveMoreJobToSchedule)
            break;
 
        //see if any job ends now
        _Bool moreMachineFreeNow = 0;
        for (int m=0; m<num_machines; m++) {
            _Bool endsNow = schedCount[m]==0 || (sched_endTime[m][schedCount[m]-1] == timeNow);
            if (endsNow) {
                moreMachineFreeNow = 1;
                break;
            }
        }
        if (moreMachineFreeNow)
            continue;
 
        //no more job ends now, find out the time to do next processing
        int minEndTime_time = sched_endTime[0][schedCount[0]-1];
        for (int m=1; m<num_machines; m++) {
            if (minEndTime_time > sched_endTime[m][schedCount[m]-1] ) {
                minEndTime_time = sched_endTime[m][schedCount[m]-1];
            }
        }
        timeNow = minEndTime_time;
    }
 
 
    //makespan
    int maxEndTime_time = sched_endTime[0][schedCount[0]-1];
    for (int m=1; m<num_machines; m++) {
        int endTime = schedCount[m]==0 ? time : sched_endTime[m][schedCount[m]-1];
        if (maxEndTime_time < endTime ) {
            maxEndTime_time = endTime;
        }
    }
    int makespan = maxEndTime_time-time;

 
    return makespan;
}
 
int johnson(int time, int num_jobs, int num_machines,int originalindex[],int sorted_job[][3]){
 
    //how many jobs to process
    int jobsToSchedule;
    int jStart;
    if (num_jobs > num_machines) {
        jobsToSchedule = (time==0) ? num_jobs - num_machines : num_machines;
        jStart         = (time==0) ? num_machines : 0;
    }
    else {
        jobsToSchedule = num_jobs;
        jStart         = 0;
    }
 
    //get list of job - copying
    int   unsorted_nextJobs_id    [jobsToSchedule];
    int   unsorted_nextJobs_length[jobsToSchedule][2];
    _Bool unsorted_processed      [jobsToSchedule];
    for (int j=0; j<jobsToSchedule; j++) {
        unsorted_nextJobs_id    [j]    = originalindex[ jStart + j ];
        unsorted_nextJobs_length[j][0] = sorted_job   [ jStart + j ][1];
        unsorted_nextJobs_length[j][1] = sorted_job   [ jStart + j ][2];
        unsorted_processed      [j]    = 0;
    }
    int nextJobs_id    [jobsToSchedule];
    int nextJobs_length[jobsToSchedule][2];
    (void)nextJobs_id;
 
    //get list of job - ordering
    int insertI_head = 0;
    int insertI_tail = jobsToSchedule-1;
    for (int jProcessed=0; jProcessed<jobsToSchedule; jProcessed++) {
        //look for the smallest value in col B and C
        int   smallest_value = 1000000000;
        int   smallest_j     = -1;
        _Bool isInColC       = 0;
        for (int j=0; j<jobsToSchedule; j++) {
            //ignore processed rows
            if (unsorted_processed[j])
                continue;
 
            for (int col=0; col<2; col++) {
                _Bool foundSmaller = smallest_value > unsorted_nextJobs_length[j][col];
                if (foundSmaller) {
                    smallest_value = unsorted_nextJobs_length[j][col];
                    smallest_j     = j;
                    isInColC       = col==1;
                }
            }
        }
 
        //insert the smallest
        int insertI = isInColC ? insertI_tail : insertI_head;
        nextJobs_id    [insertI]    = unsorted_nextJobs_id    [smallest_j];
        nextJobs_length[insertI][0] = unsorted_nextJobs_length[smallest_j][0];
        nextJobs_length[insertI][1] = unsorted_nextJobs_length[smallest_j][1];
        unsorted_processed[smallest_j] = 1;
 
        //increment head or tail
        if (isInColC)
            insertI_tail --;
        else
            insertI_head ++;
    }
 
    //schedule task to run
    int b_startTime[jobsToSchedule];
    int b_endTime  [jobsToSchedule];
    int c_startTime[jobsToSchedule];
    int c_endTime  [jobsToSchedule];
    b_startTime[0] = time;
    b_endTime  [0] = b_startTime[0] + nextJobs_length[0][0];
    c_startTime[0] = b_endTime  [0];
    c_endTime  [0] = b_endTime  [0] + nextJobs_length[0][1];
    for (int j=1; j<jobsToSchedule; j++) {
        b_startTime[j] = b_endTime  [j-1];
        b_endTime  [j] = b_startTime[j] + nextJobs_length[j][0];
        c_startTime[j] = b_endTime[j]>c_endTime[j-1] ? b_endTime[j] : c_endTime[j-1];
        c_endTime  [j] = c_startTime[j] + nextJobs_length[j][1];
    }
 
    int makespan = 0;
    makespan = c_endTime[jobsToSchedule - 1] - time;
 
    return makespan;
}
