#include "cvsclass.h"

cvsclass::cvsclass()
{
}

cvsclass::~cvsclass()
{

}

void cvsclass::pars(std::string str)
{
        std::string buffstr;
        cvsclass buff;
        str.push_back(';');
        int a=0;
        for (auto i:str) {

            buffstr.push_back(i);
            if(i==';'){
                a++;
                buffstr.pop_back();
                if(a==1){
                    this->id=std::atoi(buffstr.c_str());
                    buffstr.clear();
                }
                if(a==2){
                    this->partner=buffstr;
                    buffstr.clear();
                }
                if(a==3){
                    this->number=std::atoi(buffstr.c_str());
                    buffstr.clear();
                }
                if(a==4){
                    this->time=std::atoi(buffstr.c_str());
                    buffstr.clear();
                }
                if(a==5){
                    std::istringstream(buffstr)>>this->status;
                }

            }
        }
        //std::cout<<id<<" "<<partner<<" "<<number<<" "<<time<<" "<<status<<std::endl;

}
