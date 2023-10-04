#include "map.h"
#include <iostream>
#include <fstream>
using namespace std;
int main(){
    Map mp(100, 100);
    ofstream out;
    out.open("res.txt");
    double x0, y0, x1, y1;
    while(cin>>x0>>y0>>x1>>y1){
        auto tmp = mp.retrievCellsOnLine(x0, y0, x1, y1);
        out<<x0<<" "<<y0<<" "<<x1<<" "<<y1<<endl;
        for(auto it:tmp){
            std::cout<<it.first<<" "<<it.second<<", ";
            out<<it.first<<" ";
        }
        out<<endl;
        for(auto it:tmp){
            out<<it.second<<" ";
        }
        out<<endl;
    }
    out.close();
}

/*
1.5 1.5 9 2
1.5 50 9 5
20 40 25 90
90 30 30 11
69.4 1.8 30 5


1 1 9 2
1 50 9 5
20 40 25 90
90 30 30 11
69 1 30 5

1 1 9 5
1 50 9 10
20 40 25 90
90 30 30 10
70 1 30 5

1.5 1 9 5
1.5 50 9 10
20.5 40 25.5 90
90.5 30 30 10.5
70.5 1 30.5 5.5
*/