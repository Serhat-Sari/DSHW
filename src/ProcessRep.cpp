/* @Author
Student Name: Serhat Sarı   
Student ID : 150200068
Date: 17.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string>
#include "ProcessRep.h"


using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime)
{   
    this -> mProcessType = processType;
    this -> mProcessID = processID;
    this -> mDeliverTime = deliverTime;
    this -> mProcessTime = processTime;
    this -> mpNext = NULL;
    remainingTime = mProcessTime;
    startTime = -1;
    endTime = -1;
}

ProcessRep::~ProcessRep()
{
    delete this->mpNext;
}

ProcessRep* ProcessRep::getNext()
{
   return this-> mpNext;
}

void ProcessRep::setNext(ProcessRep *next)
{
    this->mpNext = next;
}

string ProcessRep::getProcessType()
{
    return this-> mProcessType;
}

void ProcessRep::setProcessType(string processType)
{
    this -> mProcessType = processType;
}

int ProcessRep::getDeliverTime()
{
    return this-> mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime)
{
    this-> mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID()
{
    return this-> mProcessID;
}

void ProcessRep::setProcessID(int processID)
{
    this -> mProcessID = processID;
}

int ProcessRep::getProcessTime()
{
   return this-> mProcessTime;
}

void ProcessRep::setProcessTime(int processTime)
{
    this -> mProcessTime = processTime;
}