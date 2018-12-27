#ifndef __URGENTQ_H_
#define __URGENTQ_H_
//You can change/add to these #includes
#include <ctime>
#include <iostream>
#include <vector>

typedef int uq_hook; //Used to point to a location in the heap, fill in the "???"

//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);

class UrgentQueue{

//////////FILL THIS IN///////////
public:
  //default constructor (empty urgentqueue)
  //copy constructor
  UrgentQueue() {}
  UrgentQueue(const UrgentQueue& u);
  const Job* top();
  void push(Job* &j);
  void percolate_up(int i);
  Job* pop();
  void percolate_down(int i);
  void printHeap(std::ostream &outfile);
  void remove_from_index(uq_hook position);

private:
  std::vector<Job*> m_heap;

};

#endif
