#ifndef SEQUENCE_H
#define SEQUENCE_H

/*********************************************************
 *Collect useful algorithms for sequences NOT in STL here 
 *********************************************************/
namespace cxxadt{

  /********************************************************************
   *Append the contents of sequence s1  to the end of sequence s2. s2 *
   *can an empty sequence. Return s2.                                 *
   ********************************************************************/
  template <class T>
    class AppendSequence{
    public:
    T& operator()(T& s1, T& s2)const;

  };
  //use back_insert_iterator to add elements of s1 to the end of s2.
  template <class T>
    T& AppendSequence<T>::operator()(T& s1, T& s2)const
    {
      typename T::iterator first = s1.begin();
      typename T::iterator last = s1.end();
      back_insert_iterator<T> back(s2);

      while (first != last)
	*back++ = *first++;
      
      return s2;
    }

}//closing namespace 
#endif
