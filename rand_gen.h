#ifndef RAND_GEN_H
#define RAND_GEN_H

#include <QString>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <QMessageBox>

#define DEBUG 1

static int __sum(int* __1, int __size){
    int __result = 0;
    for(int __i = 0; __i < __size; __i++) __result += __1[__i];
    return __result;
}

static int chk_ZERO(int* __1){
    int __result;
    for(int __i = 0;; __i++)
        if(__1[__i]) {
            __result = __i;
            break;
        }
    return __result;
}

QString Generate_Random(QString _1, unsigned __2){
    unsigned int __t = (unsigned int)time(0);
    //****************random*******************
    std::mt19937_64 engine(__t+__2); //mt19937 random engine
    std::uniform_int_distribution<unsigned long long> __dist(0, _1.size()-1);
    //*****************************************

//  const char t[] = "abc";

    int __i = 0;
    int* chk_CHAR = new int[_1.size()];
    QString __result; __result.resize(_1.size());
    for(int __i = 0; __i < _1.size(); __i++) chk_CHAR[__i]=1;
//  for(int __i = 0; __i < _1.size(); __i++) __result[__i] = QChar(_1[(int)__dist(engine)]);
    while(__sum(chk_CHAR, _1.size())){
        int __a = __dist(engine);
        if(chk_CHAR[__a]){
            chk_CHAR[__a] = !chk_CHAR[__a];
            __result[__i++] = QChar(_1[__a]);
        }
        if(__sum(chk_CHAR, _1.size())==1){
            __result[__i++] = QChar(_1[chk_ZERO(chk_CHAR)]);
            chk_CHAR[chk_ZERO(chk_CHAR)] = !chk_CHAR[chk_ZERO(chk_CHAR)];
        }
    }
    delete[] chk_CHAR;
    return __result;
}

#endif // RAND_GEN_H
