#include <iostream>
#include <thread>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;
using namespace boost::algorithm;
using namespace boost::gregorian;

class Timer{


public:
  date startDate;
  date endDate;
  date dateCursor;
  int hh;
  int mm;
  int ss;
  int milss;
  days d;




   Timer(date startDate, date endDate){
	 this->startDate=startDate;
	 this->endDate=endDate;
	 this->dateCursor=startDate;
	 hh=0;
	 mm=0;
	 ss=0;
	 milss=0;
	 d=days{1};
  }

   string next(){
//       if(milss+1<1000){
//    	   milss++;
//       }else{
    	   milss=0;
    	   if(ss+1<60){
             ss++;
    	   }else{
    		   ss=0;
    		   if(mm+1<60){
    			   mm++;
    		   }else{
    			   mm=0;
    			   if(hh+1<24){
    				   hh++;
    			   }else{
    				   hh=0;
    				   if(dateCursor+d<endDate){
    					   dateCursor+=d;
    				   }else{
    					   return "end";
    				   }

    			   }
    		   }
    	   }
      // }

    	   return this->toString();
//       std::ostringstream os;
//       os<<this->dateCursor.year() << "-" <<this->dateCursor.month()<<"-"<<this->dateCursor.day()<<" " << this->hh <<"." << this->mm<<"."<<this->ss<<"."<<this->milss<<endl;
//       return os.str();
   }

	string toString() {
		const std::locale fmt(std::locale::classic(),
				new boost::gregorian::date_facet("%Y.%m.%d"));
		std::ostringstream os;
		os.imbue(fmt);
		os << this->dateCursor << "," << this->hh << "." << this->mm << "."
				<< this->ss << "." << this->milss ;
		return os.str();
	}



  friend ostream &operator<<( ostream &output,const Timer &D )
        {
           //output << "Timestamp : " << D.timestamp << " Price : " << D.price <<" Unit : " << D.units<<endl;
	      output << D.dateCursor.year() << "-" <<D.dateCursor.modjulian_day()<<"-"<<D.dateCursor.day()<<" " << D.hh <<"." << D.mm<<"."<<D.ss<<"."<<D.milss<<endl;
          return output;
        }





};
