#ifndef CVSCLASS_H
#define CVSCLASS_H

#include <stdint.h>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>

class cvsclass
{
public:
    uint64_t id = NULL;
    struct ById{};
    std::string partner={0};
    struct BypPartner{};
    uint32_t number=NULL;
    struct ByNumber{};
    uint32_t time=NULL;
    struct ByTime{};
    bool status=NULL;
    struct ByStatus{};

    cvsclass();
    ~cvsclass();
    void pars(std::string str);

}
;


#endif // CVSCLASS_H
