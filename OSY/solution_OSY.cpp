#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include "progtest_solver.h"
#include "sample_tester.h"
using namespace std;
#endif /* __PROGTEST__ */

struct my_send
{
  uint32_t id;
  CBigInt cnt;
};

class CSentinelHacker
{
  vector<AReceiver> receivers;
  vector<ATransmitter> transmitters;
  queue<uint64_t> buffer1;
  queue<my_send> buffer2;
  set<uint32_t> incomplete_ids; // set  of incomplete messages

  size_t control_receivers = 0; //flag for buffer1;
  map<uint32_t, vector<uint64_t>> message;

  vector<thread> receiver_thread;
  vector<thread> transmitter_thread;
  vector<thread> worker_thread;

  bool flag1 = true;
  bool flag2 = true;
  bool flag3 = true;

  mutex buff1_mutex, buff2_mutex, receiver_mutex, transmitter_mutex, incomplete_ids_mutex;
  condition_variable cv_recCv, cv_buffer1Cv, cv_buffer2Cv;

public:
  static bool SeqSolve(const vector<uint64_t> &fragments, CBigInt &res);
  void AddTransmitter(ATransmitter x);
  void AddReceiver(AReceiver x);
  void AddFragment(uint64_t x);
  void Start(unsigned thrCount);
  void Stop(void);
  void My_Rec(AReceiver rec);
  void My_Transmits(ATransmitter transmit);
  void my_work();
};

/*******************************************************************************************************************/
bool CSentinelHacker::SeqSolve(const vector<uint64_t> &fragments, CBigInt &res)
{
  std::vector<CBigInt> result;
  if (FindPermutations(fragments.data(), fragments.size(),
                       [&res, &result](const uint8_t *arr, size_t size) {
                         CBigInt resCountexp = CountExpressions(arr + 4, size - 32);
                         result.push_back(resCountexp);
                       }))
  {
    res = *max_element(result.begin(), result.end(),
                       [](const CBigInt &i1, const CBigInt &i2) -> bool {
                         return i1.CompareTo(i2) == -1;
                       });
    return true;
  }
  return false;
}
void CSentinelHacker::AddTransmitter(ATransmitter x)
{
  transmitters.push_back(x);
}
void CSentinelHacker::AddReceiver(AReceiver x)
{
  receivers.push_back(x);
}
void CSentinelHacker::AddFragment(uint64_t x)
{
  std::unique_lock<std::mutex> lock(buff1_mutex);
  buffer1.push(x);
  cv_buffer1Cv.notify_all();
}

void CSentinelHacker ::My_Rec(AReceiver receiv)
{
  {
    //cout << "starts my_Rec " << endl;
    std::unique_lock<std::mutex> lock(receiver_mutex);
    control_receivers++;
    cv_recCv.notify_all();
  }
  //lock.unlock();
  //cout << "before addFragment in My_rec" << endl;
  uint64_t rec_data;
  while (receiv->Recv(rec_data))
    AddFragment(rec_data);
  {
    std::unique_lock<std::mutex> lock(receiver_mutex);
    control_receivers--;
  }
}

void CSentinelHacker::My_Transmits(ATransmitter transmit)
{
  unique_lock<std::mutex> lock1(buff2_mutex);
  //unique_lock<std::mutex> lock1(flag2_mutex);
  //cout << "my trasmit starts " << endl;
  while (flag2 || !buffer2.empty())
  {
           flag3 = false;
    while (buffer2.empty())
    {
      if (flag2)
      {
        cv_buffer2Cv.wait(lock1);
      }
      else
      {
        flag3 = true;
        break;
      }
    }
    //cout<< "before !flag2 " << endl;
    if (flag3)    
      break;   
    // cout<< "after !flag2" << endl;
    my_send element_of_2buffer = buffer2.front();
    buffer2.pop();
    lock1.unlock();
    //cout<< "before transmit->Send" <<endl;
    transmit->Send(element_of_2buffer.id, element_of_2buffer.cnt);
    lock1.lock();
    //cout<< "after transmit->Send" <<endl;
  }
  lock1.unlock();
  unique_lock<std::mutex> lock2(incomplete_ids_mutex);
  //cout<< "set of incomplete ids" <<endl;
  while (!incomplete_ids.empty())
  {
    uint32_t incomp_elem = *incomplete_ids.begin();
    incomplete_ids.erase(incomplete_ids.begin());
    lock2.unlock();
    //cout<< " transmit->Incomplete" <<endl;
    transmit->Incomplete(incomp_elem);
    lock2.lock();
  }
}

void CSentinelHacker::my_work()
{
  unique_lock<std::mutex> lock3(buff1_mutex);
  // unique_lock<std::mutex> lock1(flag1_mutex);
  // unique_lock<std::mutex> lock2(control_receivers_mutex);
  while (!buffer1.empty() || flag1  || control_receivers > 0)
  {

    while (buffer1.empty()) //if buffer1 is empty , flaf is true, wait...
    {
      //cout << " empty" << endl;
      if (flag1 || control_receivers > 0)
      {
        // cout << "wait" << endl;
        cv_buffer1Cv.wait(lock3);
      }
      else
      {
        // cout << "return_work" << endl;
        return;
      }
    }
    uint64_t elem_buffer1 = buffer1.front();
    buffer1.pop();
    //lock1.unlock();
    //lock2.unlock();
    lock3.unlock();
    uint32_t id = elem_buffer1 >> 37;
    {
      std::unique_lock<std::mutex> lock(transmitter_mutex);
      // cout << "before message.count(id)" << endl;
      if (message.count(id))
      {
        message[id].push_back(elem_buffer1);
      }
      else
      {
        message[id] = vector<uint64_t>({elem_buffer1});
        {
          std::unique_lock<std::mutex> lock1(incomplete_ids_mutex);
          incomplete_ids.insert(id);
        }
      }
    }
    CBigInt outp_seqsolve;
    if (SeqSolve(message[id], outp_seqsolve))
    {
      {
        my_send send = {id, outp_seqsolve};
        std::unique_lock<std::mutex> lock(buff2_mutex);
        buffer2.push(send);
        cv_buffer2Cv.notify_all();
      }
      {
        std::unique_lock<std::mutex> lock1(incomplete_ids_mutex);
        incomplete_ids.erase(id);
      }
    }
    lock3.lock();
  }
}

void CSentinelHacker::Start(unsigned thrCount)
{
  for (AReceiver receiver : receivers)
    receiver_thread.push_back(thread(&CSentinelHacker::My_Rec, this, receiver));
  {
    unique_lock<std::mutex> lock1(receiver_mutex);
    if (!control_receivers)
    {
      cv_recCv.wait(lock1);
    }
    lock1.unlock();
    for (ATransmitter trans : transmitters)
      transmitter_thread.push_back(thread(&CSentinelHacker::My_Transmits, this, trans));
  }
  for (unsigned int i = 0; i < thrCount; ++i)
    worker_thread.push_back(thread(&CSentinelHacker::my_work, this));
}
void CSentinelHacker::Stop(void)
{
  for (thread &rec_th : receiver_thread)
    rec_th.join();
  //unique_lock<mutex> lockf2(flag1_mutex);
  flag1 = false;
  cv_buffer1Cv.notify_all();
  cv_buffer2Cv.notify_all();
  for (thread &work_th : worker_thread)
    work_th.join();
  //unique_lock<mutex> lockf(flag2_mutex);
  flag2 = false;
  cv_buffer2Cv.notify_all();
  for (thread &transm_th : transmitter_thread)
    transm_th.join();
}

//-------------------------------------------------------------------------------------------------/#define
#ifndef __PROGTEST__
int main(void)
{
  using namespace std::placeholders;
  for (const auto &x : g_TestSets)
  {
    CBigInt res;
    assert(CSentinelHacker::SeqSolve(x.m_Fragments, res));
    assert(CBigInt(x.m_Result).CompareTo(res) == 0);
  }

  CSentinelHacker test;
  auto trans = make_shared<CExampleTransmitter>();
  AReceiver recv = make_shared<CExampleReceiver>(initializer_list<uint64_t>{0x02230000000c, 0x071e124dabef, 0x02360037680e, 0x071d2f8fe0a1, 0x055500150755});

  test.AddTransmitter(trans);
  test.AddReceiver(recv);
  test.Start(15);

  static initializer_list<uint64_t> t1Data = {0x071f6b8342ab, 0x0738011f538d, 0x0732000129c3, 0x055e6ecfa0f9, 0x02ffaa027451, 0x02280000010b, 0x02fb0b88bc3e};
  thread t1(FragmentSender, bind(&CSentinelHacker::AddFragment, &test, _1), t1Data);

  static initializer_list<uint64_t> t2Data = {0x073700609bbd, 0x055901d61e7b, 0x022a0000032b, 0x016f0000edfb};
  thread t2(FragmentSender, bind(&CSentinelHacker::AddFragment, &test, _1), t2Data);
  FragmentSender(bind(&CSentinelHacker::AddFragment, &test, _1), initializer_list<uint64_t>{0x017f4cb42a68, 0x02260000000d, 0x072500000025});

  static initializer_list<uint64_t> t3Data = {0x123456789abc, 0x23487abdff23, 0xdffafff23111, 0x234561fbcacb};
  thread t3(FragmentSender, bind(&CSentinelHacker::AddFragment, &test, _1), t3Data);
  FragmentSender(bind(&CSentinelHacker::AddFragment, &test, _1), initializer_list<uint64_t>{0x12345acbdafb, 0x12345cbcbdda, 0xabcdf32abcff});

  static initializer_list<uint64_t> t4Data = {0x0009000001ea, 0x0047000000b5, 0x019c05a5ae58, 0x00260000004c};
  thread t4(FragmentSender, bind(&CSentinelHacker::AddFragment, &test, _1), t4Data);
  FragmentSender(bind(&CSentinelHacker::AddFragment, &test, _1), initializer_list<uint64_t>{0x0193000f19c5, 0x02c40000001f, 0x033700496e85});

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  test.Stop();
  cout << "TotalSent " << trans->TotalSent() << endl;
  cout << "TotalIncomplete " << trans->TotalIncomplete() << endl;
 // assert(trans->TotalSent() == 4);
 // assert(trans->TotalIncomplete() == 2);
  return 0;
}
#endif /* __PROGTEST__ */
