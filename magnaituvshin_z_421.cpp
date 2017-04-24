/**
 * calculate the longest common subsequencs between two strings
 * @author Zorig Magnaituvshin
 * @version 21 April 2017
 */
#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include "matrix.h"

using namespace std;
typedef unsigned int uint;

// set infinity to one less than the maximum so we can add one to
// infinity and not overflow around to zero
const uint INFTY = UINT_MAX - 1;

/**
 * the recursive, memoized optimum function for computing the LCS
 * between two strings
 * @param s the first string
 * @param i the index of the first string
 * @param t the second string
 * @param j the index of the second string
 * @param memo the memo table
 */
uint opt( const string & s, uint i, const string & t, uint j,
          Matrix< uint > & memo )
{
  // base cases are built into the memo table with entries of INFTY
  if( memo.at(i, j) == INFTY )
  {
    if( s.at(i) == t.at(j) )
    {
      memo.at(i, j) = opt( s, i - 1, t, j - 1, memo ) + 1;
      opt( s, i - 1, t, j, memo );
      opt( s, i, t, j-1, memo );
    }
    else
      memo.at(i, j) = max( opt( s, i - 1, t, j, memo ),
                            opt( s, i, t, j - 1, memo ));
  }
  return memo.at(i, j);
}

/**
 * get the two strings from the command line
 * set up the memo table
 * print the results
 */
int main( int argc, char * argv [] )
{
  if( argc != 3 )
  {
    cerr << "Usage: " << argv[0] << " s1 s2 where s1 and s2 are the strings"
         << endl;
    return 1;
  }

  // add a space to the beginning of each string so the string indices
  // will match the memo indices
  string s = argv[1];
  s = ' ' + s;
  string t = argv[2];
  t = ' ' + t;

  // fill the memo table with infinities
  Matrix< uint > memo( s.size() + 1, t.size() + 1 );
  for( uint row = 1; row <= s.size(); row++ )
    for( uint col = 1; col <= t.size(); col++ )
      memo.at( row, col ) = INFTY;

  // hard-code the base cases
  for( uint row = 0; row <= s.size(); row++ )
    memo.at( row, 0 ) = 0;
  for( uint col = 0; col <= t.size(); col++ )
    memo.at( 0, col ) = 0;

  uint result = opt( s, s.size() - 1, t, t.size() - 1, memo );

  cout << "The LCS has length " << result << endl;

  
  cout << endl << "The completed memo table: " << endl << endl;

  // figure out the spacing required for the output table
  uint field_width = 2;
  if( t.size() > 9 )
    field_width++;

  cout << setw( field_width + 1 ) << ' ';
  for( uint col = 0; col < t.size(); col++ )
  {
    cout << std::right << setw( field_width ) << t.at( col );
  }
  cout << endl;

  cout << setw( field_width + 1 ) << ' ';
  for( uint col = 0; col < t.size(); col++ )
  {
    cout << std::right << setw( field_width ) << col;
  }
  cout << endl;

  for( unsigned int row = 0; row < s.size(); row++ )
  {
    cout << s.at(row) << std::right << setw( field_width ) << row;
    for( unsigned int col = 0; col < t.size(); col++ )
    {
      if( memo.at( row, col ) == INFTY )
        cout << std::right << setw( field_width ) << '-';
      else
        cout << std::right << setw( field_width ) << memo.at( row, col );
    }
    cout << endl;
  }
  
  
  uint m = s.size() - 1;
  uint n = t.size() - 1;
  string word;
  
  while(memo.at(m,n) != 0)
  {
     if(memo.at(m,n) > memo.at(m-1,n) && 
        memo.at(m,n) > memo.at(m,n-1) && 
        memo.at(m,n) > memo.at(m-1,n-1)) 
     {
        //add letter to string
        
        word = t.at(n) + word;
        m--;
        n--;
     }
     else if(memo.at(m,n) == memo.at(m-1,n-1))
     {
        m--;
        n--;
     }
     else if(memo.at(m,n) != memo.at(m-1,n-1) && 
             memo.at(m,n) == memo.at(m-1,n))
     {
        m--;
     }
     else if(memo.at(m,n) != memo.at(m-1,n-1) && 
             memo.at(m,n) == memo.at(m,n-1))
     {
        n--;
     }
  }
  
  cout << "The LCS is " << word << endl;
  

  return 0;
}
