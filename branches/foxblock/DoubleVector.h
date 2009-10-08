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
        DoubleVector(){};
        DoubleVector(CRuint rows,CRuint cols)	//	Create a vectorInVector with specified dimensions.
        :data(rows, vector<T>(cols))
        {}

        vector<T> & operator[](CRuint i){return data[i];}

        const vector<T> & operator[] (CRuint i) const{return data[i];}

        void resize(CRuint rows,CRuint cols)		//	Change the vectorInVector dimensions
        {
            data.resize(rows);
            for(int i = rows-1;i >= 0;--i)
                data[i].resize(cols);
        }

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

        uint size(){return data.size();}

        uint size(CRuint index)			//	Return the number of data elements stored in a specific vector
        {
            uint mySize = 0;

            //	Check if the index value is valid
            if (index >= 0 && index < data.size())
            {
                mySize = data[index].size();
            }
            return mySize;
        }
    private:
        vector<vector<T> > data;
};
#endif //	DOUBLEVECTOR_H
