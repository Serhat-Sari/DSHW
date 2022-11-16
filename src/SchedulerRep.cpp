/* @Author
Student Name: Serhat Sarı   
Student ID : 150200068
Date: 27.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    totalTime = 0;
    timeSliceCount = 0;

    this->pCpuObj = new CPURep();

    mpRunningProcess = NULL;

    for(int i = 0 ; i<3;i++)
    mpProcessFIFO[i] = new FIFORep();
}
SchedulerRep::~SchedulerRep()
{
    delete this-> pCpuObj;
    delete this-> mpProcessFIFO[0];
    delete this-> mpProcessFIFO[1];
    delete this-> mpProcessFIFO[2];
    delete this-> mpRunningProcess;

}
FIFORep* SchedulerRep::getProcessFIFO(int index)
{
    return mpProcessFIFO[index];
}

void SchedulerRep::setProcessFIFO(FIFORep* fifo, int index)
{
    this -> mpProcessFIFO[index] = fifo;
}

void SchedulerRep::setRunningProcess(ProcessRep* p)
{
    this -> mpRunningProcess = p;
}

ProcessRep* SchedulerRep::getRunningProcess()
{
    return this -> mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep* p)
{
    if(p->getProcessType()[0] == 'A'){
        mpProcessFIFO[0]->queue(p);
    }
    else if(p->getProcessType()[0] == 'B'){
        mpProcessFIFO[1]->queue(p);
}
    else if(p->getProcessType()[0] == 'C'){
        mpProcessFIFO[2]->queue(p);
}
}

ProcessRep* SchedulerRep::popProcess()
{
    for(int i = 0 ; i<3; i++){      //Üstünlük sıralamasına göre gerekli FIFO'dan node çıkart.
        if(mpProcessFIFO[i]->getHead() != NULL){
            return mpProcessFIFO[i]->dequeue();
        }
        
    }
    return NULL;
}

bool SchedulerRep::checkTimeSlice()
{
    if(getRunningProcess()->getProcessType()[0] == 'A' && timeSliceCount == 2){
        return true;
    } 
    else if(getRunningProcess()->getProcessType()[0] == 'B' && timeSliceCount == 4){
        return true;
    } 
    else if(getRunningProcess()->getProcessType()[0] == 'C' && timeSliceCount == 8){
        return true;
    } 
    else
        return false;

}
ProcessRep* SchedulerRep::sendProcessToCPU(ProcessRep* p){
    timeSliceCount++;
    pCpuObj-> runCPU(p,totalTime);
    totalTime++;
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{   
    ProcessRep* p = new ProcessRep(type, id, arrivalTime, processTime);
    
    if(mpRunningProcess != NULL){       //CPU da process varsa buraya gir
        if(mpRunningProcess->remainingTime != 0){       //Process in süresi bitmemişse buraya gir
            if(checkTimeSlice() == false){      //Process in quantum süresi dolmamışsa buraya gir
                if(type == "A" && mpRunningProcess->getProcessType() != "A"){
                    pushProcess(mpRunningProcess);
                    timeSliceCount = 0;
                    setRunningProcess(p);
                }
                else if(type == "A" && mpRunningProcess->getProcessType() == "A"){
                    pushProcess(p);
                }
                if(type == "B" && (mpRunningProcess->getProcessType() != "A" && mpRunningProcess->getProcessType() != "B")){
                    pushProcess(mpRunningProcess);
                    timeSliceCount = 0;
                    setRunningProcess(p);
                }
                else if(type == "B" && (mpRunningProcess->getProcessType() == "A" || mpRunningProcess->getProcessType() == "B")){
                    pushProcess(p);
                }
                if(type == "C"){
                    pushProcess(p);
                }
            }
            else{       //Process in quantum süresi dolmuşsa buraya gir
                if(type == "A" && getProcessFIFO(0)->getHead() == NULL){
                    pushProcess(mpRunningProcess);
                    setRunningProcess(p);
                    timeSliceCount = 0;
                }
                else if(type == "A" && getProcessFIFO(0)->getHead() != NULL){
                    pushProcess(p);
                    pushProcess(mpRunningProcess);
                    setRunningProcess(popProcess());
                    timeSliceCount = 0;
                }
                if(type == "B" && getProcessFIFO(0) -> getHead() == NULL && getProcessFIFO(1)-> getHead() == NULL){
                    pushProcess(mpRunningProcess);
                    setRunningProcess(p);
                    timeSliceCount = 0;
                }
                else if(type == "B" && (getProcessFIFO(0) -> getHead() != NULL || getProcessFIFO(1)-> getHead() != NULL)){
                    pushProcess(p);
                    pushProcess(mpRunningProcess);
                    setRunningProcess(popProcess());
                    timeSliceCount = 0;
                }
                if(type == "C" && getProcessFIFO(0) -> getHead() == NULL && getProcessFIFO(1)-> getHead() == NULL && getProcessFIFO(2)->getHead() == NULL){
                    pushProcess(mpRunningProcess);
                    setRunningProcess(p);
                    timeSliceCount = 0;
                }
                else if(type == "C" && (getProcessFIFO(0) -> getHead() != NULL || getProcessFIFO(1)-> getHead() != NULL || getProcessFIFO(2)->getHead() != NULL)){
                    pushProcess(p);
                    setRunningProcess(popProcess());
                    timeSliceCount = 0;
                }
            }
        }
        else{       //Process in süresi bitmişse buraya gir
                if(type == "A" && getProcessFIFO(0)->getHead() == NULL){
                    setRunningProcess(p);
                    timeSliceCount = 0;
                }
                else if(type == "A" && getProcessFIFO(0)->getHead() != NULL){
                    pushProcess(p);
                    setRunningProcess(popProcess());
                    timeSliceCount = 0;
                }
                if(type == "B" && getProcessFIFO(0) -> getHead() == NULL && getProcessFIFO(1)-> getHead() == NULL){
                    setRunningProcess(p);
                    timeSliceCount = 0;
                }
                else if(type == "B" && (getProcessFIFO(0) -> getHead() != NULL || getProcessFIFO(1)-> getHead() != NULL)){
                    pushProcess(p);
                    setRunningProcess(popProcess());
                    timeSliceCount = 0;
                }
                if(type == "C" && getProcessFIFO(0) -> getHead() == NULL && getProcessFIFO(1)-> getHead() == NULL && getProcessFIFO(2)->getHead() == NULL){
                    setRunningProcess(p);
                    timeSliceCount = 0;
                }
                else if(type == "C" && (getProcessFIFO(0) -> getHead() != NULL || getProcessFIFO(1)-> getHead() != NULL || getProcessFIFO(2)->getHead() != NULL)){
                    pushProcess(p);
                    setRunningProcess(popProcess());
                    timeSliceCount = 0;
                }
            }    
    }
    else{       //CPU da process yoksa buraya gir (ilk job buraya girecek)
        setRunningProcess(p);
        timeSliceCount = 0;
    }

    sendProcessToCPU(mpRunningProcess);
    if(mpRunningProcess->remainingTime == 0){
        timeSliceCount = 0;
        setRunningProcess(popProcess());
    }
}
void SchedulerRep::schedule(ProcessRep* p)
{   
    if(p == NULL){  
       if(mpRunningProcess != NULL){        //CPU da process varsa buraya gir
            if(mpRunningProcess->remainingTime != 0){       //CPU daki işlem bitmediyse buraya gir       
                if(checkTimeSlice() == false){      //İşlemin quantum süresi dolmamışsa buraya gir
                    sendProcessToCPU(mpRunningProcess);                
                }
                else{       //İşlemin quantum süresi dolmuşsa buraya gir
                    timeSliceCount = 0;
                    if(getProcessFIFO(0) -> getHead() != NULL || getProcessFIFO(1)-> getHead() != NULL || getProcessFIFO(2)->getHead() != NULL){        //Herhangi bir FIFO boş değilse buraya gir
                        pushProcess(mpRunningProcess);
                        setRunningProcess(popProcess());
                        sendProcessToCPU(mpRunningProcess);
                    }
                    else{       //Tüm FIFO lar boşsa buraya gir
                        sendProcessToCPU(mpRunningProcess);
                    }
                }
            }
            else{       //İşlemin quantum süresi dolmuşsa buraya gir
                timeSliceCount = 0;
                if(getProcessFIFO(0) -> getHead() != NULL || getProcessFIFO(1)-> getHead() != NULL || getProcessFIFO(2)->getHead() != NULL){        //Herhangi bir FIFO boş değilse buraya gir
                    setRunningProcess(popProcess());
                    sendProcessToCPU(mpRunningProcess);
                }
                else{       //Tüm FIFO lar boşsa buraya gir
                    setRunningProcess(NULL);
                }
            }
            if(mpRunningProcess->remainingTime == 0){       //İşlemin quantum süresi dolmuşsa buraya gir.
                timeSliceCount = 0;
                if(getProcessFIFO(0) -> getHead() != NULL || getProcessFIFO(1)-> getHead() != NULL || getProcessFIFO(2)->getHead() != NULL){        //Herhangi bir FIFO boş değilse buraya gir
                    setRunningProcess(popProcess());
                }
                else{       ////Tüm FIFO lar boşsa buraya gir
                    setRunningProcess(NULL);
                }
            }  
        }
        else{       //CPU da işlem yoksa buraya gir
            if(getProcessFIFO(0) -> getHead() != NULL || getProcessFIFO(1)-> getHead() != NULL || getProcessFIFO(2)->getHead() != NULL){        //Herhangi bir FIFO boş değilse buraya gir
                setRunningProcess(popProcess());
                sendProcessToCPU(mpRunningProcess);
            }
            else{}      //Tüm FIFO lar boşsa bir şey yapma.
        }
    }
    
} 



