#include "model.h"

Model::Model()
{
    hMutex = CreateMutex(nullptr, false,nullptr);

    hStopEventX   = CreateEvent( NULL, TRUE, FALSE, NULL );
    hStopEventY   = CreateEvent( NULL, TRUE, FALSE, NULL );

    hUpdateX = CreateEvent( NULL, TRUE, FALSE, NULL );
    hUpdateY = CreateEvent( NULL, TRUE, FALSE, NULL );
}

Model::~Model()
{    StopThreadX();
     StopThreadY();
     CloseHandle(hMutex);
     CloseHandle(hStopEventX);
     CloseHandle(hStopEventY);
     CloseHandle(hUpdateX);
     CloseHandle(hUpdateY);

}
void Model::StartThreadX()
{
    ResetEvent( hStopEventX);
    hThreadX = CreateThread(NULL,0, ThreadFuncX, this, 0 , NULL);
}

void Model::StartThreadY()
{
       ResetEvent( hStopEventY);
       hThreadY = CreateThread(NULL,0, ThreadFuncY, this, 0 , NULL);
}

void Model::StopThreadX()
{
    SetEvent(hStopEventX);

}

void Model::StopThreadY()
{
    SetEvent(hStopEventY);

}
DWORD Model::ThreadFuncX(LPVOID ptr)
{
    Model* _this = (Model*)ptr;
     if( !_this ) return 1;

     while(true){
              if(!_this->isDataUpdated()){
                  double ax = _this->getAx();
                  double wx = _this->getWx();
                  double dx = _this->getDx();
                  double t = _this->getTime();

                  double newX = ax * sin(wx * t + dx);
                  _this->setX(newX);
                   _this->setTime(t+0.01);
              }


         if( WaitForSingleObject( _this->hStopEventX, 0 ) != WAIT_TIMEOUT )
                     break;
     }

    return 0;
}

DWORD Model::ThreadFuncY(LPVOID ptr)
{
    Model* _this = (Model*)ptr;
     if( !_this ) return 1;

     while(true){
         if(!_this->isDataUpdated()){
             double ay = _this->getAy();
             double wy = _this->getWy();
             double dy = _this->getDy();

             double t = _this->getTime();


             double newY = ay * sin(wy * t + dy);
             _this->setY(newY);
             _this->setTime(t+0.01);
         }


         if( WaitForSingleObject( _this->hStopEventY, 0 ) != WAIT_TIMEOUT )
                     break;

     }

     return 0;
}

bool Model::isDataUpdated()
{
     return WaitForSingleObject( hUpdateX, 0 ) == WAIT_OBJECT_0 || WaitForSingleObject( hUpdateY, 0 ) == WAIT_OBJECT_0;;
}


double Model::getTime() const
{
    MutexLocker guard(hMutex);
    return time;
}

void Model::setTime(double newTime)
{
    MutexLocker guard(hMutex);
    time = newTime;
}

int Model::getY() const
{
    MutexLocker guard(hMutex);
    ResetEvent(hUpdateY);
    return Y;
}

void Model::setY(int newY)
{
    MutexLocker guard(hMutex);
    Y = newY;
    SetEvent(hUpdateY);


}

int Model::getX() const
{
    MutexLocker guard(hMutex);
    ResetEvent(hUpdateX);
    return X;

}

void Model::setX(int newX)
{
    MutexLocker guard(hMutex);
    X = newX;
    SetEvent(hUpdateX);

}

double Model::getDy() const
{
    return Dy;
}

void Model::setDy(double newDy)
{
    Dy = newDy;
    pointsQ.clear();
}

double Model::getWy() const
{
    return Wy;
}

void Model::setWy(double newWy)
{
    Wy = newWy;
    pointsQ.clear();
}

double Model::getAy() const
{
    return Ay;
}

void Model::setAy(double newAy)
{
    Ay = newAy;
    pointsQ.clear();
}

double Model::getDx() const
{
    return Dx;
}

void Model::setDx(double newDx)
{
    Dx = newDx;
    pointsQ.clear();
}

double Model::getWx() const
{
    return Wx;
}

void Model::setWx(double newWx)
{
    Wx = newWx;
    pointsQ.clear();
}

double Model::getAx() const
{
    return Ax;
}

void Model::setAx(double newAx)
{
    Ax = newAx;
    pointsQ.clear();
}
