#include <iostream>
#include <fstream>

void cut_file(){
    ifstream myfile;
    myfile.open("data/nacl_mag_run5_total.dat", ios::in | ios::out); 
    ofstream out_file("data/nacl_mag_run5.dat");
    if (myfile.is_open()){
        string tp;
        int number=0;
        while(getline(myfile, tp) && number <22850){ //read data from file object and put it into string.
            out_file<< tp <<endl;
            number++;
        }
    }
            
}