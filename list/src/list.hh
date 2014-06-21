#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include<Jing/AbstractList.hh>
//#include<Jing/except>

namespace Jing{

//listIterator defined at bottom of the file.
class listIterator;

class list:public AbstractList{
private:
  bool sameType;

protected:
  class listNode{
    friend class list;
  private:
    Object& data;
    listNode *prev;
    listNode *next;

  public:
    listNode(Object& obj);
    listNode(Object& obj, listNode* prev, listNode* next);

    bool add(Object& obj);
    bool add(Object& obj, Jing::index_t n);
    Object& remove(Jing::index_t idx);
    Object& get(Jing::index_t n) const;
    bool assign(Jing::index_t idx, Jing::Object& obj);
    Jing::index_t find(Jing::Object& obj, Jing::index_t n);
    Jing::index_t backFind(Object& obj, Jing::index_t n);
  };

  listNode *first;
  listNode *last;
  size_t count;
  listIterator *iter;

public:
//TODO:clear warnings
//TODO:equals method
//TODO:hashing
//TODO:classID dynamic infrastructure
//TODO:allow iterators to be used as insertion points
//TODO:Allow for multiple iterators
//TODO:remove character include
//TODO:remove iostream pieces and parts

//Constructors
  list();
  list(Collection& c);
//Inserts
//  [inherited from abstractlist]
  void insert(Object& obj, Jing::index_t idx);
  void insertAll(Collection& c, Jing::index_t idx);
//  [inherited from collection]
  void insert(Object& obj);
  void insertAll(Collection& c);
//Removes
  Object& remove();
//  [inherited from abstractlist]
  Object& remove(Jing::index_t idx);
  void removeRange(Jing::index_t srtIdx, Jing::index_t endIdx);
//  [inherited from collection]
  void remove(Object& obj);
  void removeAll(Collection& c);
//Gets
//  [inherited from abstractlist]
  Object& get(Jing::index_t idx) const;
//clean up with delete
  virtual AbstractList& get(index_t start, index_t end) const;
//Assign
//  [inherited from abstractlist]
  void assign(Jing::index_t idx, Object& obj);
//Contains
//  [inherited from collection]
  bool contains(Object& obj) const;
  bool containsAll(Collection& c) const;
//Reverse gets
//  [inherited from abstractlist]
  Jing::index_t indexOf(Object& obj) const;
  Jing::index_t lastIndexOf(Object& obj) const;
//Equality
//  [inherited from Object]
  bool equals(Object& obj) const;
//Iterator
//  [inherited from Iterable]
  Iterator& iterator() const;
//States
//  hash
//  [inherited from Object]
  int hash() const;
//  ID
//  [inherited from Object]
  int classID() const;
//  clone
//  [inherited from Object]
//memory management may be up to the user.
//clean up with delete
  Object* clone() const;
//  [inherited from abstractlist]
  Object* toArray() const;
  void toArray(Object* arr) const;
//  isempty
//  [inherited from collection]
  bool isEmpty() const;
//  size
//  [inherited from collection]
  size_t size() const;
//  clear
//  [inherited from collection]
  void clear();
};

//Exceptions not currently needed in list
/*
class listException:public exception{
};

class listIndexOutOfBounds:public listException{
private:
  void initWithList(const Jing::list& theList);
public:
  listIndexOutOfBounds(const char * message);
  listIndexOutOfBounds(const Jing::string& message);
  listIndexOutOfBounds(const list& theList);
  listIndexOutOfBounds(const list& theList, Jing::index_t index);
  listIndexOutOfBounds(const listNode& node);

//  const string& what() const;
};
*/

class listIterator:public Iterator{
private:
//OPTIMIZE:Make friend to list to point directly to nodes.
//  friend class list;
  Jing::index_t idx;
  list& theList;

public:
  listIterator(Jing::list& thisList);
  listIterator(Jing::list& thisList, Jing::index_t n);

  bool hasNext();
  Object& next();
  void remove();
  void reset();
};

}

//#include"list.cc"

#endif
