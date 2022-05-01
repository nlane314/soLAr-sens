#include<iostream>
#include<fstream>
#include<iterator>
#include<algorithm>

using namespace std;


int optical_detectors(){

  std::ofstream opt_det;
  opt_det.open("x20_opt_dets.txt",std::ios_base::app);

  vector<double> x;
  for(int i=0;i<200;++i){
    x.push_back(595-i*2.925);
  } 
  //double x_reverse[50]={11.83138,2*11.83138,3*11.83138,4*11.83138,5*11.83138,6*11.83138,7*11.83138,8*11.83138,9*11.83138,10*11.83138,11*11.83138,12*11.83138,13*11.83138,14*11.83138,15*11.83138,16*11.83138,17*11.83138,18*11.83138,19*11.83138,20*11.83138, 21*11.83138, 22*11.83138, 23*11.83138, 24*11.83138, 25*11.83138, 26*11.83138, 27*11.83138, 28*11.83138, 29*11.83138, 30*11.83138, 31*11.83138, 32*11.83138, 33*11.83138, 34*11.83138, 35*11.83138, 36*11.83138, 37*11.83138, 38*11.83138, 39*11.83138, 40*11.83138, 41*11.83138, 42*11.83138, 43*11.83138, 44*11.83138, 45*11.83138, 46*11.83138, 47*11.83138, 48*11.83138, 49*11.83138, 50*11.83138}; 
  vector<double> x_reverse;
  for(int i=0;i<200;++i){
    x_reverse.push_back(10+i*2.925);
  }
  
  double y[24]={1357.47,1308.67,1245.87,1197.07,1125.08,1076.28,1013.48,964.679,892.689,843.889,781.089,732.289,660.299,611.499,548.699,499.899,427.909,379.109,316.309,267.509,195.519,146.719,83.9188,35.1188};
  vector<double> x_array;
  vector<double> x_array_neg;
  vector<double> y_array;
 
  for (int i=0;i<24;++i){
    for(int j=0;j<200;++j){
      x_array.push_back(x[j]);
   
    } 
  }

  //std::reverse(x.begin(), x.end());
   
  for (int i=0;i<24;++i){
    for(int j=0;j<200;++j){
    
      x_array_neg.push_back(-x_reverse[j]);
     
    }
  }  

  for(int i=0;i<24;++i){
    
      y_array.insert(y_array.end(),200,y[i]);
   
    }

  for(int i=0;i<4800;++i){
    x_array.push_back(x_array_neg[i]);
    y_array.push_back(y_array[i]);
  }
 
  for(int i=0;i<9600;++i){
    if(i<4800){
      opt_det<<i<<" "<<0.05<<" "<<x_array[i]<<" "<<y_array[i]<<" "<<1<<"\n";
    }
    else{
      opt_det<<i<<" "<<-0.05<<" "<<x_array[i]<<" "<<y_array[i]<<" "<<1<<"\n";
      cout<<x_array[i]<<endl;
    }
  }

  return 0;
 
}
