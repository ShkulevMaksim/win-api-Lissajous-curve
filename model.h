#ifndef MODEL_H
#define MODEL_H
#include <QPoint>
#include <QQueue>
#include <windows.h>

class Model
{
public:
    QQueue<QPoint> pointsQ;
     bool isDataUpdated();
    Model();
    ~Model();
    void StartThreadX();
    void StartThreadY();
    void StopThreadX();
    void StopThreadY();

    double getAx() const;
    void setAx(double newAx);

    double getWx() const;
    void setWx(double newWx);

    double getDx() const;
    void setDx(double newDx);

    double getAy() const;
    void setAy(double newAy);

    double getWy() const;
    void setWy(double newWy);

    double getDy() const;
    void setDy(double newDy);

    int getX() const;
    void setX(int newX);

    int getY() const;
    void setY(int newY);

    double getTime() const;
    void setTime(double newTime);
private:



    HANDLE hMutex;
    HANDLE hThreadX;
    HANDLE hThreadY;

    HANDLE hStopEventX;
    HANDLE hStopEventY;

    HANDLE hUpdateX;
    HANDLE hUpdateY;


    static DWORD WINAPI ThreadFuncX (LPVOID ptr);
    static DWORD WINAPI ThreadFuncY (LPVOID ptr);

    volatile double Ax = 99 , Wx = 1 , Dx = 0;
    volatile double Ay = 99 , Wy = 2 , Dy = 0;

    int X = 0 ;
    int Y = 0 ;
    double time = 0 ;

};

class MutexLocker{
private:
    HANDLE hMutex;
public:
    MutexLocker(HANDLE mutex):hMutex(mutex){
        WaitForSingleObject(hMutex,INFINITE);
    }
    ~MutexLocker(){
        ReleaseMutex(hMutex);
    }
};

#endif // MODEL_H
