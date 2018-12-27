#include <vector>
#include <string>
#include <cassert>

#include "Job.h"
#include "TimeQueue.h"


//copy constructor for TimeQueue
TimeQueue::TimeQueue(const TimeQueue& t) {
  m_heap = t.m_heap;
}

//Job Pointer to the top of the heap
const Job* TimeQueue::top() {
  //make sure the heap isn't empty, then return the first index in the heap
  assert(!m_heap.empty());
  //define the hook
  m_heap[0]->time_hook = 0;
  return m_heap[0];
}

//push to the end of the Queue
void TimeQueue::push(Job* &j) {
  //push back the Job to the end of the Queue
  m_heap.push_back(j);
  //define the hook and pointers
  //percolate up
  int i = m_heap.size()-1;
  m_heap[i]->time_hook = i;
  m_heap[i]->time_ptr = this;
  percolate_up(i);
}

void TimeQueue::percolate_up(int i) {
  //while a parent still exists
  while ((i-1)/2 >= 0) {
    //current time is less than the parent's time
    //  swap the two
    //else, break
    if (m_heap[i]->getTime() < m_heap[(i-1)/2]->getTime()) {
      //swapping the two jobs
      Job* temp = m_heap[i];
      m_heap[i] = m_heap[(i-1)/2];
      m_heap[(i-1)/2] = temp;
      //now swapping the hooks
      tq_hook replace = m_heap[i]->time_hook;
      m_heap[i]->time_hook = m_heap[(i-1)/2]->time_hook;
      m_heap[(i-1)/2]->time_hook = replace;
      //after changing the index, must redefine it
      i = (i-1)/2;
    } else { break; }
  }
}

//pop deletes the job that has been in the queue the longest
Job* TimeQueue::pop() {
  //make sure the heap isn't empty
  //need to swap the first and last jobs
  //  because vectors dont have a pop_front function
  //  so will have to swap so can use pop_back
  assert(!m_heap.empty());
  Job* return_val = m_heap[0];
  //swapping the two jobs
  Job* temp = m_heap[0];
  m_heap[0] = m_heap[m_heap.size()-1];
  m_heap[m_heap.size()-1] = temp;

  m_heap.pop_back();
  //percolate down
  int i=0;
  percolate_down(i);
  return return_val;
}

//percolate down is a helper function for pop and remove_from_index
void TimeQueue::percolate_down(int i) {
  //while a left child still exists
  while (2*i + 1 < m_heap.size()) {
    //want to pick the smaller time Job to compare w/
    int child;
    //first check that the right child is within range,
    //  then make sure that the right child's time is less than that of the left child's
    //  set the child to whichever one has the smaller time
    if (2*i + 2 < m_heap.size() &&
        m_heap[2*i + 2]->getTime() < m_heap[2*i + 1]->getTime()) {
      child = 2*i + 2;
    } else { child = 2*i + 1; }
    //if the time of the child is less than that of the current Job,
    //  swap the child and the current Jobs
    //else break out of the loop
    if (m_heap[child]->getTime() < m_heap[i]->getTime()) {
      //swapping the jobs
      Job* swap = m_heap[child];
      m_heap[child] = m_heap[i];
      m_heap[i] = swap;

      //now swapping the hooks
      tq_hook temp = m_heap[i]->time_hook;
      m_heap[i]->time_hook = m_heap[(i-1)/2]->time_hook;
      m_heap[(i-1)/2]->time_hook = temp;
      i = child;
    } else { break; }
  }
}

//print out the heap
void TimeQueue::printHeap(std::ostream &outfile) {
  outfile << "TQ " << m_heap.size() << " jobs:" << std::endl;

  for (unsigned int i=0; i<m_heap.size(); i++) {
    outfile << "\t" << m_heap[i];
  }
}

//uses an index and deletes it from the heap
void TimeQueue::remove_from_index(tq_hook position) {
  //want to use pop_back function for vectors
  //  so will swap the Job at the position
  //  for the Job at end of vector
  //then pop_back the Job and percolate down
  Job* swap = m_heap[position];
  m_heap[position] = m_heap[m_heap.size()-1];
  m_heap[m_heap.size()-1] = swap;
  m_heap.pop_back();
  percolate_down(position);
}
