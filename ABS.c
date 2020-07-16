#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
int main()
{
    float vehicle_speed,wheel_speed,difference,hydraulic_ratio;
    int count;
    FILE *fptr;
    if ((fptr = fopen("program.txt","r")) == NULL){
       printf("Error! opening file");
       exit(1);
    }
    FILE *optr;
    if ((optr = fopen("program_out.txt","w")) == NULL){
       printf("Error! opening file");
       exit(1);
    }
    
    printf("VEHICLE SPEED\tWHEEL SPEED\tHYDRAULIC RATIO\n");
    fprintf(optr,"STATUS\t\tVEHICLE SPEED\tWHEEL SPEED\tHYDRAULIC RATIO\tTIMESTAMP\n");
    while(fscanf(fptr,"%f %f", &vehicle_speed,&wheel_speed) == 2)
    {
        count=0;
    do
    {
        difference=vehicle_speed/2-wheel_speed;
        time_t mytime = time(NULL);
        char *time_str = ctime(&mytime);
        time_str[strlen(time_str)-1] = '\0';
        printf("WARNING!\n");
        fprintf(optr,"WARNING!\t");
        hydraulic_ratio=(vehicle_speed-wheel_speed)/10;
        printf("%.2f\t\t%.2f\t\t%.2f\n\n",vehicle_speed,wheel_speed,hydraulic_ratio);
        fprintf(optr,"%.2f\t\t%.2f\t\t%.2f\t\t%s\n",vehicle_speed,wheel_speed,hydraulic_ratio,time_str);
        count++;
        if(difference>20)
        {
            wheel_speed+=20;
            sleep(1);
        }
        else
        {            
            wheel_speed+=difference;
            sleep(1);
            break;
        }
    }while((vehicle_speed-wheel_speed)!=(vehicle_speed/2));
    hydraulic_ratio=(vehicle_speed-wheel_speed)/10;
    time_t mytime = time(NULL);
    char *time_str = ctime(&mytime);
    time_str[strlen(time_str)-1] = '\0';
    printf("SUCCESS!\n");
    fprintf(optr,"SUCCESS!\t");
    printf("%.2f\t\t%.2f\t\t%.2f\n\n\n",vehicle_speed,wheel_speed,hydraulic_ratio);
    fprintf(optr,"%.2f\t\t%.2f\t\t%.2f\t\t%s\n",vehicle_speed,wheel_speed,hydraulic_ratio,time_str);
    printf("----------------------------------------------------------\n");
    fprintf(optr,"------------------------------------------------------------------------------------------\n");
    sleep(5-count);
    }
    fclose(fptr);
    fclose(optr);
    return 0;
}
