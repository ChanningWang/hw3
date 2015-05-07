//============================================================================
// Name        : Assignment_C.cpp
// Author      : chengbin wang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "DataEngine.cpp"

using namespace std;

using namespace boost::gregorian;


int main() {

//	date date1 = from_simple_string("2014-01-31");
//	date date2 = from_simple_string("2014-02-01");
//	months ms{1};
//	days d1{1};
//	Timer timer(date1,date2);
//	string s;
//	while(!boost::iequals(s=timer.next(),"end")){
//		cout<<s<<endl;
//	}

	DataEngine engine("FRB_H15.csv");
	engine.getBasicStats();
	engine.generateSyntheticData("FedData.csv");

//	std::default_random_engine generator;
//	  std::normal_distribution<double> distribution(0,1.0);
//	  for(int i=0;i<100;i++){
//		  cout<<distribution(generator)<<endl;
//	  }

	return 0;
}
