#include <QCoreApplication>
#include <cvsclass.h>
#include <vector>
#include <cstdlib>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>

using boost::multi_index_container;
using namespace boost::multi_index;

typedef multi_index_container<
  cvsclass,
  indexed_by<
    ordered_unique<
        //cvsclass, uint64_t, &cvsclass::id
        tag<cvsclass::ById>, member<cvsclass,uint64_t,&cvsclass::id>

    >,
    ordered_unique<
        //cvsclass, std::string, &cvsclass::partner
        tag<cvsclass::BypPartner>, member<cvsclass,std::string,&cvsclass::partner>
    >,
    ordered_non_unique<
        //cvsclass, uint32_t, &cvsclass::number
        tag<cvsclass::ByNumber>, member<cvsclass,uint32_t,&cvsclass::number>
    >,
    ordered_non_unique<
        //cvsclass, uint32_t, &cvsclass::time
        tag<cvsclass::ByTime>, member<cvsclass,uint32_t,&cvsclass::time>
    >,
    ordered_non_unique<
        //cvsclass, bool, &cvsclass::status
        tag<cvsclass::ByStatus>, member<cvsclass,bool,&cvsclass::status>
    >
  >
> tabl;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::cout<<"start"<<std::endl;
    std::vector<cvsclass> dat;
    tabl tablmulti;
    int size=0;
    std::ifstream load("testcpp.csv");
    if(load.is_open()){std::cout<<"open"<<std::endl;}
      for (;!load.eof();) {
            size++;
            std::cout<<"parsing"<<std::endl;
            std::string buffstr;
            cvsclass buff;
            std::getline(load,buffstr,'\n');
            buff.pars(buffstr);
            dat.push_back(buff);
            }
    load.close();
    std::cout<<"parsink is end "<<size<<std::endl;
    for (int i=0;dat[i].id!=NULL;i++) {
        std::cout<<dat[i].id<<"|"<<dat[i].partner<<"|"<<dat[i].number<<
                   "|"<<dat[i].time<<"|"<<dat[i].status<<std::endl;
    }
    //filling multi_index
    for (int i=0;i<size;i++) {
        tablmulti.insert(dat[i]);
    }
    //found string with max id(because multi_index sort strings by id, i just call last elent)
    std::cout<<"string with max id"<<std::endl;
    uint32_t kek;
    for (auto i:tablmulti) {
       kek=i.id;
    }
    tabl::index<cvsclass::ById>::type::const_iterator foo=tablmulti.get<cvsclass::ById>().find(kek);
    std::cout<<foo->id<<"|"<<foo->partner<<"|"<<foo->number<<"|"<<foo->time<<"|"<<foo->status<<"|"<<std::endl;


    //found string with id =100
    uint64_t find_id = 100;
    tabl::index<cvsclass::ById>::type & sas = tablmulti.get<cvsclass::ById>();
    tabl::index<cvsclass::ById>::type::const_iterator sas_ = sas.find(find_id);
    std::cout<<"id = 100"<<std::endl;
    std::cout<<sas_->id<<"|"<<sas_->partner<<"|"<<sas_->number<<"|"<<sas_->time<<"|"<<sas_->status<<"|"<<std::endl;


    //find stings after 2019(in .csv all data after 2019)
    std::cout<<"strings after 2019 \n wait pls"<<std::endl;
    uint32_t g=1546293661;
    uint32_t b;
    for (auto i:tablmulti) {
        if((i.time>1546293661)&&(i.time<g)){
            g=i.time;
            break;
        }
        b=i.time;
    }

    auto &time_index = tablmulti.get<cvsclass::ByTime>();
    auto it_ = time_index.lower_bound(g);
    auto end = time_index.upper_bound(b);


    for (;it_!=end;++it_){

        std::cout<<it_->id<<"|"<<it_->partner<<"|"<<it_->number<<"|"<<it_->time<<"|"<<it_->status<<"|"<<std::endl;
    }
    return a.exec();
}
