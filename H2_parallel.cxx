#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "TFile.h"
#include <cstdlib> 
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <bind.hpp>
#include <thread.hpp>
#include <thread/mutex.hpp>
#include <threadpool.hpp>

using namespace std;
using boost::mutex;
using boost::thread;

//TO COMPILE  
//g++ -Wall -ansi H2_parallel.cxx -o H2_parallel `root-config --cflags --glibs` -lboost_thread
//TRY THIS
//g++ -Wall -ansi H2_parallel.cxx -o H2_parallel `root-config --cflags --glibs` -I /usr/include/boost -lboost_thread-mt



void myThread(int number, string name, Bool_t energy_data, Bool_t init_data, Bool_t pos_fiber) 
{	
	ostringstream temp1;
	temp1 << number;
	string command;	
	
	ostringstream temp2;
	ostringstream temp3;
	ostringstream temp4;
	temp2 << energy_data;
	temp3 << init_data;
	temp4 << pos_fiber;
	
	string rootFile = name + temp1.str();
	command = "$G4WORKDIR/bin/Linux-g++/H2_sim " + rootFile + temp2.str() + temp3.str() + temp4.str();
	cout << command << endl;
	system(command.c_str());
};



int main(int argc, char** argv) 
{

    int n_cpu          = atoi(argv[1]);
    int n_processi     = atoi(argv[2]);
    string filename    = argv[3];
    Bool_t energy_data = 1;
    Bool_t init_data   = 1;
    Bool_t pos_fiber   = 0;
    
    if (argc == 7)
    {
      energy_data = atoi(argv[4]);
      init_data   = atoi(argv[5]);
      pos_fiber   = atoi(argv[6]);
    }
    	
	boost::threadpool::thread_pool<> tpool(n_cpu);
	for(int j=0; j<n_processi; j++)
	{
	  tpool.schedule(boost::bind(myThread, j, filename, energy_data, init_data, pos_fiber));
	}
	tpool.wait();
	cout << "Done" << endl;

	return 0;
}
