#ifndef TIMER_H_
#define TIMER_H_
#include <vector>

const int CACHE_SIZE = 800;

class Timer
{
  private:
    int _ticks;
    int _totalTicks;
    int _tickCache[CACHE_SIZE];
    int _currentCache;
  public:
    Timer();
    void start();
    double reset();
    double stop();
    double total();
    std::vector<int> getTickHistory();

    bool wait(int seconds);
};

#endif // TIMER_H_
