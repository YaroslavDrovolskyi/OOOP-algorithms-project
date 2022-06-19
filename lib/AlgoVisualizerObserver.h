#ifndef ALGOVISUALIZEROBSERVER_H
#define ALGOVISUALIZEROBSERVER_H
#include <iostream>
#include <vector>
#include <string>
class baseVisualizerObserver
{
public:
     virtual void highlight(int i, int j,std::string color)=0;
     virtual void swap(size_t i, size_t j)=0;
     virtual void setStopped(bool b)=0;
    virtual void clearFrame()=0;
    virtual bool isStopped()=0;
    enum Colors
     {
        YELLOW,RED
     };

     virtual std::string getColor(Colors color)
    {
        switch (color) {
        case(YELLOW):
        return yellow;
        break;
        case(RED):
            return red;
            break;
        default:
            return black;
        }
    };

protected:
    std::string yellow = "rgb(184,184,0)";
    std::string red ="rgb(150, 70, 70)";
    std::string black ="rgb(0, 0, 0)";
};

template<typename T>
class visualizerObserver: public baseVisualizerObserver
{
public:

    virtual void readVector(std::vector<T>vec)=0;
    virtual void reReadVector(std::vector<T>vec,int i, int j)=0;
};


#endif // ALGOVISUALIZEROBSERVER_H
