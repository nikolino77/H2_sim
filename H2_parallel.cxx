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



void myThread(int number, string name) 
{	
	ostringstream temp1;
	temp1 << number;
	string command;	

	string rootFile = name + temp1.str();
	command = "$G4WORKDIR/bin/Linux-g++/H2_sim " + rootFile;
	cout << command << endl;
	system(command.c_str());

	cout << "done " << boost::this_thread::get_id() << endl;
};



int main(int argc, char** argv) 
{
    if (argc < 3)
    {
      cout << "Command: ./H2_parallel [n_cpu] [output_name]" << endl;
      return 1;
    }
    
	int n_cpu = atoi(argv[1]);
    string filename = argv[2];
    	
	boost::threadpool::thread_pool<> tpool(7);
	for(int j=0; j<n_cpu; j++)
	{
	  tpool.schedule(boost::bind(myThread, j, filename));
	}
	tpool.wait();
	cout << "Done" << endl;

	return 0;
}
