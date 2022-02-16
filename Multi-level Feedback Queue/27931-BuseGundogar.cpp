//
//  main.cpp
//
//  Created by Buse Gündoğar on 3.11.2021.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "TemplatedQueue.h"

using namespace std;

struct myVec{
    vector<char> vec;
    int num;
};

void toTheTopMost(vector<Queue<myVec>> &vec, ofstream &outFile){
    
    for(int i = 1; i < vec.size(); i++){
        
        while(!(vec[i].isEmpty())){
            myVec temp;
            vec[i].dequeue(temp);
            
            vec[0].enqueue(temp);
            cout << "B, PC" << temp.num << ", Q" << vec.size() << endl;
            outFile << "B, PC" << temp.num << ", Q" << vec.size() << endl;
        }
    }
}

bool endCheck (vector<Queue<myVec>> &vec){
    int emptyCount = 0;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i].isEmpty()){
            emptyCount++;
        }
    }
    
    if(emptyCount == vec.size()){
        return true;
    }
    
    return false;
}

vector<char> processRead(vector<char> &pVec, string fname, ifstream &inp){
    char x;
    inp.open(fname);
    
    while(inp.get(x)){
        if(x == '1' || x == '0' || x == '-'){
            pVec.push_back(x);
        }
    }
    
    inp.close();
    return pVec;
}


void confRead(int &q, int &p, int &s, ifstream &inp, string conf){
    string line;
    inp.open(conf);
    
    getline(inp,line);
    q = stoi(line);
    getline(inp,line);
    p = stoi(line);
    getline(inp,line);
    s = stoi(line);
    
    inp.close();
}

int main() {
    
    string folderName, confFile;
    int queueNum, processNum, sizeS;
    ifstream input;
    ofstream outFile;
    
    cout << "Please enter the folder name:";
    cin >> folderName;
    
    
    outFile.open(folderName + "/output.txt");
    
    cout << "When all processes are completed, you can find execution sequence in  \"" << folderName  << "/output.txt\"." << endl;
    
    
    //Reading configuration.txt
    confFile = folderName + "/configuration.txt";
    confRead(queueNum,processNum,sizeS,input,confFile);
    
    //Create queue vector
    vector<Queue<myVec>> queueVec;
    
    //Adding the queues to the queue vector
    for(int i = 0; i < queueNum; i++){
        Queue<myVec> myQueue;
        
        //Add the processes to the first queue 
        if(i == 0){
            for(int j = 1; j <= processNum; j++){
                string jStr = to_string(j);
                string processFileName = folderName +  "/p" + jStr + ".txt";
                
                myVec processVec;
                processVec.vec = processRead(processVec.vec, processFileName,input);
                processVec.num = j;
                myQueue.enqueue(processVec);
                
                input.close();
            }
        }
        queueVec.push_back(myQueue);
    }
    
    
    bool end = false;
    int i = 0;
    int sCount = 0;

    
    while(!end){
        while(!(queueVec[i].isEmpty())){
            
            //Case 0
            if (queueVec[i].returnFront()->value.vec[0] == '0'){
                if(queueVec[i].returnFront()->value.vec[1] == '-'){
                    myVec temp;
                    queueVec[i].dequeue(temp);
                    
                    sCount++;
                    cout << "E, PC" << temp.num << ", QX" << endl;
                    outFile << "E, PC" << temp.num << ", QX" << endl;
                }
                
                else{
                    myVec temp;
                    queueVec[i].dequeue(temp);
                    
                    temp.vec.erase(temp.vec.begin()+0);
                    
                    queueVec[i].enqueue(temp);
                    
                                    
                    sCount++;
                    cout << "0, PC" << temp.num <<   ", Q" << queueVec.size()-i << endl;
                    outFile << "0, PC" << temp.num <<   ", Q" << queueVec.size()-i << endl;
                }
            }
            
            
            
            //Case 1
            else if (queueVec[i].returnFront()->value.vec[0] == '1'){
                //Check if it is the last value in the vector
                if(queueVec[i].returnFront()->value.vec[1] == '-'){
                    myVec temp;
                    queueVec[i].dequeue(temp);
                    
                    sCount++;
                    cout << "E, PC" << temp.num << ", QX" << endl;
                    outFile << "E, PC" << temp.num << ", QX" << endl;
                }
                else{
                    myVec temp;
                    queueVec[i].dequeue(temp);
                    
                    temp.vec.erase(temp.vec.begin()+0);
                    
                    if(i+1 < queueVec.size()){ //If I have another queue in vector, add there.
                        queueVec[i+1].enqueue(temp);
                        cout << "1, PC" << temp.num << ", Q" << queueVec.size()-(i+1) << endl;
                        outFile << "1, PC" << temp.num << ", Q" << queueVec.size()-(i+1) << endl;
                    }
                    else{                      //If there is no other queue at the end, at to the same level.
                        queueVec[i].enqueue(temp);
                        cout << "1, PC" << temp.num << ", Q" << queueVec.size()-(i) << endl;
                        outFile << "1, PC" << temp.num << ", Q" << queueVec.size()-(i) << endl;
                    }
                    
                    sCount++;
                }
            }

            if(sCount == sizeS){
                toTheTopMost(queueVec, outFile);
                sCount = 0;
                i = 0;
            }
            
        }
        
        
        if( i+1 < queueVec.size()){
            i++;
        }

        //If all queues are empty, loop terminates.
        end = endCheck(queueVec);
    }

    return 0;
}
