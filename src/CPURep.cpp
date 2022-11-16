/* @Author
Student Name: Serhat Sarı   
Student ID : 150200068
Date: 
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    mFinishedProcess = new FIFORep();
}

CPURep::~CPURep()
{
    delete this->mFinishedProcess;
}

ProcessRep* CPURep::runCPU(ProcessRep* p, int time)
{   
    if(p->startTime == -1)      //Node ilk defa CPUda işleme alınıyorsa startTime'ını totalTime'a eşitle
        p->startTime = time;


    p->remainingTime--;

    if(p->remainingTime == 0){      //Node un işi bitmişse finishedProcess'e ekle
        mFinishedProcess->queue(p);
        p->endTime = time+1;
        return NULL;
    } 
    
    else
    return p;

}

FIFORep* CPURep::getFinishedProcess()
{
  return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep* finishedProcess)
{
    this-> mFinishedProcess = finishedProcess;
}