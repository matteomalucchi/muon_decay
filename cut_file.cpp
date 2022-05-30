#include <iostream>
#include <fstream>

void cut_file(){
    ifstream myfile;
    myfile.open("data/fe4_pb4_run4_total.dat", ios::in | ios::out); 
    ofstream out_file("data/fe4_pb4_run4.dat");
    if (myfile.is_open()){
        string tp;
        int number=0;
        while(getline(myfile, tp)){ //read data from file object and put it into string.
            if (number <1888339 || number >1986795) out_file<< tp <<endl;
            number++;
        }
    }
            
}