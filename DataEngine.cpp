#include <iostream>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/math/distributions.hpp>
#include <boost/math/distributions/chi_squared.hpp>

#include <iostream>     // std::cout
#include <algorithm>    // std::for_each
#include <vector>

#include <string.h>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

#include "Logging.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/math/distributions/inverse_gaussian.hpp>
#include <random>

#include "Timer.cpp"

using namespace boost::accumulators;
using namespace std;
using namespace boost::algorithm;
using namespace boost::gregorian;
using boost::math::inverse_gaussian;

class DataEngine{

public:
   vector<float> originV;
   vector<float> returnV;
   vector<float> syntheticV;
   float E;
   float V;
   float retE;
      float retV;
   int SKIP_LINE=10;
   int LINE_LIMIT=5; //100000
   log4cpp::Category & root=InitLogging::getRoot();

   date startDate;
   date endDate;


   DataEngine(string file){
     load(file);
   }

   void load(string file){
	   string line;
	   string pre_line;
	   int line_counter=0;
		std::vector<string> strs;
		std::ifstream fileStream(file);

		for (int i = 0; i <= SKIP_LINE; i++) {
			getline(fileStream, line, '\n');

		}

		while (getline(fileStream, line, '\n') && line_counter < LINE_LIMIT) {
			line_counter++;
			trim(line);
			boost::split(strs, line, boost::is_any_of(","));
			trim(strs[1]);
			if (!boost::iequals(strs[1], "ND")) {
				originV.push_back(stof(strs[1]));
				if (line_counter == 1) {
					startDate = from_simple_string(strs[0]);
				}
				endDate = from_simple_string(strs[0]);
			}
		}

		for (int i = 1; i < originV.size(); i++) {
			returnV.push_back(originV[i] / originV[i - 1] - 1);
		}
   }

	void getBasicStats(){
		  accumulator_set<float, stats<tag::mean,tag::variance> > acc1;
		  accumulator_set<float, stats<tag::mean,tag::variance> > acc2;
		  acc1=for_each(originV.begin(), originV.end(), acc1);
          E=mean(acc1);
          V=sqrt((float)variance(acc1));
          acc2=for_each(returnV.begin(), returnV.end(), acc2);
          retE=mean(acc2);
          retV=sqrt((float)variance(acc2));

          std::ostringstream os;
          os<<endl<<"---Basic Return Specs---"<<endl<<"Size of Sample="<<originV.size()<<endl<<"Mean="<<E<<endl<<
        		  "Standard Deviation="<<V<<endl<<"Start Date: "<<startDate <<endl<<"End Date: "<<endDate<<endl<<"Return Mean="<<retE
        		  <<endl<<"Return Standard Deviation="<<retV<<endl;
          root.info(os.str());
	}

	void generateSyntheticData(string file){
		ofstream myfile;
		 myfile.open (file);
		std::default_random_engine generator;
		float dt=1.0;
		 std::normal_distribution<double> distribution((retE-retV*retV/2.0)*dt,retV*sqrt(dt));
		//inverse_gaussian my_ig(retE, retV);
		  string s;
		  Timer timer(startDate,endDate);

		 // float rand=originV[0]*(1+distribution(generator));
		  float rand=0;
		  while(!boost::iequals(s=timer.next(),"end")){
			  rand=E*(1+distribution(generator));
			  myfile<<s<<","<<rand<<endl;
			  //rand=rand*(1+distribution(generator));
		  }

		  myfile.close();

	}

};
