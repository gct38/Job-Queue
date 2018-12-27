#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>
#include <vector>
#include <iostream>

typedef int tq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class TimeQueue{

//////////FILL THIS IN///////////
public:
  //default constructor empty timequeue
  //copy constructor
  TimeQueue() {}
  TimeQueue(const TimeQueue& t);
  //top to get to the top of the heap
  const Job* top();
  //push and pop functions to add/delete jobs
  //percolate up is a helper function for push
  //percolate down is a helper function for pop
  void push(Job* &j);
  void percolate_up(int i);
  Job* pop();
  void percolate_down(int i);
  //prints out the current heap
  void printHeap(std::ostream &outfile);
  //supposed to be able to use an index and delete it from the heap
  void remove_from_index(tq_hook position);



private:
  std::vector<Job*> m_heap;


};

#endif
