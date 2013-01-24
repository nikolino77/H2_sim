#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "TFile.h"
#include <cstdlib> 
#include "ConfigFile.cc"
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
//g++ -Wall -ansi launch_parallel_manyCrystals.cxx -o launchParallelManyCrystalsEXE `root-config --cflags --glibs` -lboost_thread
//TRY THIS
//g++ -Wall -ansi launch_parallel_manyCrystals.cxx -o launchParallelManyCrystalsEXE `root-config --cflags --glibs` -I /usr/include/boost -lboost_thread-mt



void myThread(int number) 
{	
	ostringstream temp1;
	temp1 << number;
	
	string rootFile = "out_H2_" + temp1 + ".root";
	command = "$G4WORKDIR/bin/Linux-g++/H2_sim " + rootFile;
	cout << command << endl;
	system(command.c_str());

	cout << "done " << boost::this_thread::get_id() << endl;
};



int main(int argc, char** argv) 
{
	boost::threadpool::thread_pool<> tpool(7);
	for(int j=0; j<7; j++)
	{
	  tpool.schedule(boost::bind(myThread, j));
	}
	tpool.wait();
	cout << "Done" << endl;

	return 0;
}
