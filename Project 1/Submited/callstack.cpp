#include "callstack.h"
#include<vector>
using namespace std;

ostream& operator<<(ostream& out, Function_t& s)
{
  out << "Function " << s.name << " with " << s.numArguments << " args and ";
  out << s.numLocals << " locals" ;
  return out;
}

void CallStack::call(Function_t f, int RA, int BP, int *args, int *locals)
{
  info.push(f);                       // push function
  int* p = args + f.numArguments - 1; // offset and set ptr

  while (p >= args) {
    rawStack.push(*p);  // push args to stack 
    p--;
  }
  rawStack.push(RA);    // push RA to stack
  rawStack.push(BP);    // push BP to stack

  int* q = locals;
  while (q < locals + f.numLocals) {
    rawStack.push(*q);  // push locals to stack
    q++;
  }
}

Function_t CallStack::currentFunction(void)
{
  return info.peek(); // return top of function stack
}

int CallStack::getLocal(int n)
{
  int result = 0, i = 0;
  vector<int> temp;           // to holds stack elements 

  Function_t f = info.peek(); // current function 
  int count = f.numLocals;

  if(n < count && n>=0)
  {
    for(; i < count-n; i++) {
      temp.push_back(rawStack.pop()); // push elements to container
    }
      
    result = temp[i-1];               // grab element to return
    for(; i > 0; i--) {
      rawStack.push(temp[i-1]);       // restore stack
    }
  } else
      throw InvalidIndex();

  return result;
}

void CallStack::setLocal(int n, int val)
{
  int i = 0;
  vector<int> temp;           // to holds stack elements
  Function_t f = info.peek(); // current function
  int count = f.numLocals;

  if(n < count)
  {
    for(; i < count-n; i++) {
      temp.push_back(rawStack.pop()); // push elements to container
    }
    rawStack.push(val);               // add local to stack
    i--;                              // fix index

    for(; i > 0; i--) {
      rawStack.push(temp[i-1]);       // restore stack
    }
  }
  else
    throw InvalidIndex();
}

int CallStack::getArg(int n)
{
  int result = 0, i = 0;
  vector<int> temp;            // to holds stack elements
  Function_t f = info.peek();  // current function 
  int count1 = f.numLocals+2;  // +2 is for BP and RA
  int count2 = f.numArguments;

  if(n < count2)
  {
    for(; i <= count1+n; i++) {
      temp.push_back(rawStack.pop()); // push elements to container
    }
    result = temp[i-1];               // grab element to return
    for(i=count1+n; i >= 0; i--) {
      rawStack.push(temp[i]);         // restore stack
    }
  } else
      throw InvalidIndex();

  return result;
}

void CallStack::setArg(int n, int val) 
{
  Function_t f = info.peek();   // current function
  int argCount = f.numArguments;
  int localCount = f.numLocals;

  if(n < argCount)
  {
    Stack<int> temp;
    while (localCount >= 0) {
      temp.push(rawStack.pop()); // move locals to temp
      localCount--;
    }
    temp.push(rawStack.pop());   // move BP to temp
    temp.push(rawStack.pop());   // move RA to temp
    rawStack.pop();              // pop arg to be set
    rawStack.push(val);          // set arg

    while (!temp.empty()) {      // restore rawStack
      rawStack.push(temp.pop());
    }
  } else
      throw InvalidIndex();
}

int CallStack::getBP()
{
  int result = 0, i = 0;
  vector<int> temp;           // to holds stack elements
  Function_t f = info.peek(); // current function 
  int count = f.numLocals;

  for(; i <= count; i++) {
    temp.push_back(rawStack.pop()); // push elements to container
  }
  result = temp[i-1];               // grab element to return

  for(i=count; i >= 0; i--) {
    rawStack.push(temp[i]);         // restore stack
  }
  return result;
}

int CallStack::getRA()
{
  int result = 0, i = 0;
  vector<int> temp;           // to holds stack elements
  Function_t f = info.peek(); // current function 
  int count = f.numLocals+1;

  for(; i <= count; i++) {
    temp.push_back(rawStack.pop()); // push elements to container
  }
  result = temp[i-1];               // grab element to return

  for(int i=count; i >= 0; i--) {
    rawStack.push(temp[i]);         // restore stack
  }
  return result;
}

void CallStack::do_return(void)
{
  int result = 0;
  Function_t f = info.pop();   // remove function 
  int count1 = f.numLocals+2;  // +2 is for BP and RA
  int count2 = f.numArguments;
  
  for(int i=0; i < count1+count2; i++) { // remove associated elements
    rawStack.pop();
  }
}

ostream& operator<<(ostream& out, CallStack& s)
{
  Function_t f = s.currentFunction(); // function to output
  int count1 = f.numLocals;
  int count2 = f.numArguments;
  
  for(int i = count1-1; i>=0; i--) {  // output Locals
    out << s.getLocal(i) << " Local " << i << " for " << f.name << endl; 
  }
  out << s.getBP() << " BP for " << f.name << endl; // output BP
  out << s.getRA() << " RA for " << f.name << endl; // output RA

  for(int i=0; i < count2; i++) {     // output Args
    out << s.getArg(i) << " Arg " << i << " for " << f.name << endl;
  }

  return out;
}
