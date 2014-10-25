#include "SDL.h"
#include "timer.h"

Timer::Timer():
    _totalTicks(0), _currentCache(0)
{
    for (int i = 0; i < CACHE_SIZE; i++)
        _tickCache[i] = 1000/60;
}

void Timer::start()
{
  _ticks = SDL_GetTicks();
}

double Timer::reset()
{
  int previousTicks = _ticks;
  start();
  int difference = _ticks - previousTicks;


  _totalTicks += difference;
  _tickCache[_currentCache] = difference;
  _currentCache = (_currentCache+1)%CACHE_SIZE;
  int totalDifference = 0;
  for (int i = 0; i < CACHE_SIZE; i++)
      totalDifference += _tickCache[i];
  return difference / (1000.0);
}

double Timer::total()
{
  return _totalTicks / 1000.0;
}

double Timer::stop()
{
  int totalTicks = _totalTicks;
  _totalTicks = 0;
  return totalTicks / 1000.0;
}

bool Timer::wait(int seconds)
{
    int current = SDL_GetTicks();
    return (current - _ticks) < (seconds * 1000);
}

std::vector<int> Timer::getTickHistory()
{
    std::vector<int> history;
    for (int i = 0; i < CACHE_SIZE; i++)
    {
        history.push_back(_tickCache[(i + _currentCache)%CACHE_SIZE]);
    }
    return history;
}
