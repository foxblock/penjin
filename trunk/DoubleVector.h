#ifndef DOUBLEVECTOR_H
#define DOUBLEVECTOR_H

/*
vector in a vector
class based on code examples here: http://www.tek-tips.com/faq.cfm?pid=116
Modifications by Kevin Winfield-Pantoja
*/


#include "PenjinTypes.h"
#include <vector>

template <typename T>
class DoubleVector
{
    public:
        DoubleVector(){;}
        DoubleVector(CRuint rows,CRuint cols)	//	Create a vectorInVector with specified dimensions.
        :data(rows, std::vector<T>(cols))
        {;}

        /// ARRAY ACCESS
        std::vector<T> & operator[](CRuint i){return data[i];}                  // return vector of T
        const std::vector<T> & operator[] (CRuint i) const{return data[i];}
        std::vector<T> & at(CRuint i){return data[i];}
        const std::vector<T> & at(CRuint i) const{return data[i];}
        T & at(CRuint i, CRuint j){return data[i][j];}                          // return T
        T & at(CRuint i, CRuint j) const{return data[i][j];}

        /// RESIZE
        void resize(CRuint rows){data.resize(rows);}
        void resize(CRuint rows,CRuint cols)		//	Change the vectorInVector dimensions
        {
            data.resize(rows);
            for(int i = rows-1;i >= 0;--i)
                data[i].resize(cols);
        }

        /// Clear
        void clear()					//	Clears all the vectorInVector contents
        {
            //	clear all sub entries
            for (int i = data.size()-1; i >= 0; --i)
            {
                data[i].clear();
            }
            //	clear top level
            data.clear();
        }
        void clear(CRuint index){data[index].clear();}

        /// SIZE
        size_t size()const{return data.size();}
        size_t size(CRuint index)			//	Return the number of data elements stored in a specific vector
        {
            size_t mySize = 0;

            //	Check if the index value is valid
            if (index >= 0 && index < data.size())
            {
                mySize = data[index].size();
            }
            return mySize;
        }
    private:
        std::vector<std::vector<T> > data;
};
#endif //	DOUBLEVECTOR_H
