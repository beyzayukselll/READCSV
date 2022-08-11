#include <iostream>
#include <Eigen/Dense>
#include <fstream>
#include <iterator>
#include <complex>
#include <valarray>
#include <vector>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost::algorithm;
#include "plot.h"
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>


Eigen::MatrixXd readCSV(std::string file) {
  ifstream fin(file);
    string lines;
     vector<string> v;
  

    while (getline(fin, lines)) {       
        vector<string> parts;
          v.push_back(lines);
        split(parts, lines, boost::is_any_of(";"));
        
       
    }
    fin.close();
     


    int rows = v.size();
    int cols = v[0].size()/2+1; // if all rows have same #of cols
std::cout<<cols;
  std::ifstream in(file);
  
  std::string line;

  int row = 0;
  int col = 0;

  Eigen::MatrixXd res = Eigen::MatrixXd(rows, cols);
   
   
  if (in.is_open()) {
    
   
    while (getline(in, line)) {

     
      char *ptr = (char *) line.c_str();
      int len = line.length();
     
      col = 0;

      char *start = ptr;
      for (int i = 0; i < len; i++) {

        if (ptr[i] == ';') {
          res(row, col++) = atof(start);
          start = ptr + i + 1;
          
        }
      }
      res(row, col) = atof(start);
       
      row++;
      }
    

    in.close();
  }
  return res;
}

int main()
{
 
  
    string filePath="../../mil-cnc-min_log/mil-cnc-min/trajectory_dump.csv";   

    Eigen::MatrixXd result = readCSV(filePath);    
   
    int i=1;  
    Eigen::VectorXd pos=result.col(0);
    Eigen::VectorXd vel=result.col(1);
    Eigen::VectorXd act=result.col(2);
   
  Plot plot ;
  plot.logPlot(pos,vel,act);     
      


  std::cout << pos << "\n";
 

   

}
