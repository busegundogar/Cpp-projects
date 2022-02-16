//
//  main.cpp
//  busegundogar_Gundogar_Buse_hw7
//
//  Created by Buse Gündoğar on 25.05.2021.
//  Copyright © 2021 Buse Gündoğar. All rights reserved.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <random>
#include <time.h>
#include "busegundogar_Gundogar_Buse_hw7DynIntQ.h"

using namespace std;

int maxItems;
int countF = 0, countP = 0;

HW7DynIntQueue fillingQueue, packQueue;
mutex fillMutex, packMutex, coutMutex;

int random_range(const int &min, const int &max){
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}

//START:Taken and updated from IntQueue.cpp
void producer(int min, int max){
    
    int size;
    
    for(int i = 1; i <= maxItems; i++){
        
        //Adding the box to the queue
        this_thread::sleep_for (chrono::seconds(random_range(min, max)));
        fillMutex.lock();
        fillingQueue.enqueue(i);
        size = fillingQueue.getCurrentSize();
        fillMutex.unlock();
            
        
        //Displaying the enqueue statement
        coutMutex.lock();
        time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
        struct tm *ptm = localtime(&tt);// for xcode
        //struct tm *ptm = new struct tm;
        //localtime_s(ptm, &tt);
        cout << "Producer has enqueued a new box " << (i) << " to filling queue (filling queue size is " << size << "): " << put_time(ptm,"%X") << endl;
        coutMutex.unlock();
        
        
    }
}
//END:Taken and updated from IntQueue.cpp


void filler(int id, int min, int max){
    
    int box, size, sizeFinal;
    
    while(countF < maxItems){
        
        fillMutex.lock();
        if(!fillingQueue.isEmpty() ){
            
            //Taking the box from the filling queue
            fillingQueue.dequeue(box);
            size = fillingQueue.getCurrentSize();
            countF++;
            fillMutex.unlock();


            coutMutex.lock();
            time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            struct tm *ptm = localtime(&tt); //for xcode
            //struct tm *ptm = new struct tm;
            //localtime_s(ptm, &tt);
            cout << "Filler " << id << " started filling the box " << box << " (filling queue size is "<< size << "): " << put_time(ptm,"%X") << endl;
            coutMutex.unlock();
            
            
            //Waiting for the filling worker
            this_thread::sleep_for (chrono::seconds(random_range(min, max)));

            //After waiting, displaying the finishing time
            coutMutex.lock();
            tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            localtime(&tt); //for xcode
            //localtime_s(ptm, &tt);
            cout << "Filler " << id << " finished filling the box " << box << ": " << put_time(ptm,"%X") << endl;
            coutMutex.unlock();
            
            
            //Putting to packacing queue
            packMutex.lock();
            packQueue.enqueue(box);
            sizeFinal = packQueue.getCurrentSize();
            packMutex.unlock();
            
            //After putting, display the putting time
            coutMutex.lock();
            tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            localtime(&tt); //for xcode
            //localtime_s(ptm, &tt);
            cout << "Filler " << id << " put box " << box << " into packacing queue (packacing queue size is "<< sizeFinal << "): " << put_time(ptm,"%X") << endl;
            coutMutex.unlock();
        
        }
        
        else{
            fillMutex.unlock();
        }
    }
}

void packager(int id, int min, int max){
    
    int box;
    
    while(countP < maxItems){
        
        packMutex.lock();
        if(!packQueue.isEmpty() ){
            
            //Taking the box from the packaging queue
            packQueue.dequeue(box);
            countP++;
            packMutex.unlock();


            coutMutex.lock();
            time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            struct tm *ptm = localtime(&tt); //for xcode
            //struct tm *ptm = new struct tm;
            //localtime_s(ptm, &tt);
            cout << "Packager " << id << " started packaging the box " << box << " (packaging queue size is "<< packQueue.getCurrentSize() << "): " << put_time(ptm,"%X") << endl;
            coutMutex.unlock();
            
            
            //Waiting for the packaging worker
            this_thread::sleep_for (chrono::seconds(random_range(min, max)));

            //After waiting, displaying the finishing time
            coutMutex.lock();
            tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            localtime(&tt); //for xcode
            //localtime_s(ptm, &tt);
            cout << "Packager " << id << " finished packaging the box " << box << ": " << put_time(ptm,"%X") << endl;
            coutMutex.unlock();
            
        
        }
        
        else{
            packMutex.unlock();
        }
        
    }
    
}


int main() {
    int  minProducer, maxProducer, minFiller, maxFiller, minPackager, maxPackager;
    
    cout << "Please enter the total number of items: ";
    cin >> maxItems;
    
    cout << "Please enter the min-max waiting time range of producer: \nMin: ";
    cin >> minProducer;
    cout << "Max: ";
    cin >> maxProducer;
    
    cout << "Please enter the min-max waiting time range of filler workers: \nMin: ";
    cin >> minFiller;
    cout << "Max: ";
    cin >> maxFiller;
    
    cout << "Please enter the min-max waiting time range of packager workers: \nMin: ";
    cin >> minPackager;
    cout << "Max: ";
    cin >> maxPackager;
    
    //Displaying the current time before threads start
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm *ptm = localtime(&tt); //for xcode
    //struct tm *ptm = new struct tm;
    //localtime_s(ptm, &tt);
    cout << "Simulation starts " << put_time(ptm,"%X") << endl;
    
    thread threadProducer(producer, minProducer, maxProducer);
    thread threadFiller1(filler, 1, minFiller, maxFiller), threadFiller2(filler, 2, minFiller, maxFiller);
    thread threadPackager1(packager, 1, minPackager, maxPackager), threadPackager2(packager, 2, minPackager, maxPackager);

    
    
    threadProducer.join();
    threadFiller1.join();
    threadFiller2.join();
    threadPackager1.join();
    threadPackager2.join();
    
    tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    localtime(&tt); //for xcode
    //localtime_s(ptm, &tt);
    cout << "End of the simulation ends: " << put_time(ptm,"%X") << endl;
    
    return 0;
}
