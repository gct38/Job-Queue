#include <vector>
#include <string>
#include <cassert>

#include "Job.h"
#include "UrgentQueue.h"

//copy constructor for urgentqueue
UrgentQueue::UrgentQueue(const UrgentQueue& u) {
  m_heap = u.m_heap;
}

//job pointer to the top of the heap
const Job* UrgentQueue::top() {
  //make sure the heap isn't empty, then return the first index in the heap
  assert(!m_heap.empty());
  m_heap[0]->urgent_hook = 0;
  return m_heap[0];
}

//push to the end of the queue
void UrgentQueue::push(Job* &j) {
  //push back the job to the end of the queue
  m_heap.push_back(j);
  //define the hook and pointer
  //then percolate up
  int i = m_heap.size()-1;
  m_heap[i]->urgent_hook = i;
  m_heap[i]->priority_ptr = this;
  percolate_up(i);
}

//percolate up is a helper function for push
void UrgentQueue::percolate_up(int i) {
  //while a parent still exists
  while ((i-1)/2 >= 0) {
    //if the current priority is greater than the parent's priority
    //  swap the two
    if (m_heap[i]->getPriority() > m_heap[(i-1)/2]->getPriority()) {
      //manually swapping the two
      Job* temp = m_heap[i];
      m_heap[i] = m_heap[(i-1)/2];
      m_heap[(i-1)/2] = temp;
      //now swapping the hooks
      uq_hook replace = m_heap[i]->urgent_hook;
      m_heap[i]->urgent_hook = m_heap[(i-1)/2]->urgent_hook;
      m_heap[(i-1)/2]->urgent_hook = replace;
      //after changing the index, must redefine it
      i = (i-1)/2;
    } else { break; }
  }
}

//pop will delete the highest prioritized job
Job* UrgentQueue::pop() {
  //make sure the heap isn't empty
  //need to swap the first and last jobs
  //  because vectors don't have a pop_front function
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

//percolate down is a helper function for pop and remove from index
void UrgentQueue::percolate_down(int i) {
  //while a left child still exists
  while (2*i+1 < m_heap.size()) {
    //want to pick the smaller priority job to compare with
    int child;
    //first check that right child is within range,
    //  then make sure that the right child's priority is less that of the left child's
    //  set the child to whichever one is of the smaller priority
    if (2*i + 2 < m_heap.size() &&
        m_heap[2*i + 2]->getPriority() > m_heap[2*i + 1]->getPriority()) {
      child = 2*i + 2;
    } else { child = 2*i + 1; }
    //if the priority of child is less than that of the current job,
    //  swap the child and the current jobs,
    //else break out of the loop
    if (m_heap[child]->getPriority() > m_heap[i]->getPriority()) {
      //swap the jobs
      Job* temp = m_heap[child];
      m_heap[child] = m_heap[i];
      m_heap[i] = temp;
      //now swapping the hooks
      i = child;
      uq_hook replace = m_heap[i]->urgent_hook;
      m_heap[i]->urgent_hook = m_heap[child]->urgent_hook;
      m_heap[child]->urgent_hook = replace;
    } else { break; }
  }
}

//printing out the heap
void UrgentQueue::printHeap(std::ostream &outfile) {
  outfile << "UQ " << m_heap.size() << " jobs:" << std::endl;

  for (unsigned int i=0; i<m_heap.size(); i++) {
    outfile << "\t" << m_heap[i];
  }

}

//uses an index and deletes it from the heap
void UrgentQueue::remove_from_index(uq_hook position) {
  //want to swap the job to delete w/ the last one
  //  this way can just use pop_back funtion
  //after deleting from the heap, but put back in order
  //  so will percolate down from the given index
  Job* swap = m_heap[position];
  m_heap[position] = m_heap[m_heap.size()-1];
  m_heap[m_heap.size()-1] = swap;
  m_heap.pop_back();
  percolate_down(position);
}
