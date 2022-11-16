/* @Author
Student Name: Serhat Sarı   
Student ID : 150200068
Date: 17.10.2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
   mpHead = NULL;
   mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep* head)
{
    mpHead = head;
    mpTail = mpHead;
}


FIFORep::~FIFORep()
{
    delete this -> mpHead;

}

void FIFORep::setHead(ProcessRep* head)
{
    this -> mpHead = head;
}

ProcessRep* FIFORep::getHead()
{
    return this -> mpHead;
}

void FIFORep::setTail(ProcessRep* tail)
{
    this -> mpTail = tail;
}

ProcessRep* FIFORep::getTail()
{
    return this -> mpTail;
}

void FIFORep::queue(ProcessRep* p)
{
    ProcessRep* x = getHead();

    if(getHead()== NULL){       //Linked list de eleman yoksa
         setHead(p);
         setTail(p);
    }

    else{
        getTail()->setNext(p);
        setTail(p);
    }
}
ProcessRep* FIFORep::dequeue()
{   
    ProcessRep* p = getHead();

    if(getHead() == NULL){      //Linked list de eleman yoksa
        return NULL;
    }

    else if(getHead() == getTail()){        //Linked list de tek eleman varsa

        setHead(NULL);
        setTail(NULL);
        p-> setNext(NULL);
        return p;
       
    }

    else{
        
        setHead(getHead()->getNext());
        p -> setNext(NULL);
        return p;
    
    }
    
}

ProcessRep* FIFORep::searchID(int id)
{   
    ProcessRep* p = getHead();
    while(p->getNext()->getProcessID() != id && p->getNext()!=NULL){

        p = p->getNext();
    }

    if(p->getProcessID() == id){
        return p;
    }

    else{
        return NULL;
    }
        
   
}


void FIFORep::printFIFO()
{
    ProcessRep* p = getHead();
    if(getHead() == NULL){
    }
    else{
    while(p!=getTail()){
        cout << p->getProcessType() << p->getProcessID() << " " << p->startTime << " " <<  p->endTime << " ";
        p = p->getNext();
    }
    cout << p->getProcessType() << p->getProcessID() << " " << p->startTime << " " <<  p->endTime << " ";
}
}