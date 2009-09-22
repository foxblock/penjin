#ifndef VARIABLE_H
#define VARIABLE_H

#include "PenjinTypes.h"
#include <string>
using std::string;
class Variable
{
    public:
		Variable()
		{
            setNULL();
        }
		~Variable(){}
		Variable(const int& value)
		{
		    setNULL();
			setInt(value);
		}
		Variable(const float& value)
		{
		    setNULL();
			setFloat(value);
		}
		Variable(const string& value)
		{
		    setNULL();
			setString(value);
		}
		Variable(const double& value)
		{
		    setNULL();
			setDouble(value);
		}

		void setValue(const int& value){setInt(value);}
		void setValue(const float& value){setFloat(value);}
		void setValue(const double& value){setDouble(value);}
		void setValue(const string& value){setString(value);}
		void setValue(Variable value);

		void setInt(const int& value)
		{
			intValue = value;
			stored[0] = true;
		}
		void setFloat(const float& value)
		{
            floatValue = value;
            stored[1] = true;
		}
		void setDouble(const double& value)
		{
			doubleValue = value;
			stored[2] = true;
		}
		void setString(const string& value)
		{	stringValue = value;
			stored[3] = true;
		}

		int getInt()const
		{
		    if(stored[0])
                return intValue;
            return NULL;
		}
		float getFloat()const
		{
		    if(stored[1])
                return floatValue;
        #ifndef PENJIN_FIXED
            return NULL;
        #endif
        }
		double getDouble()const
		{
		    if(stored[2])
                return doubleValue;
            return NULL;
        }
		string getString()const
		{
		    if(stored[3])
                return stringValue;
            return "NULL";
        }
        /*
        /// get the values are set in the param list
        /// it returns an int to say which value was set
        */
        int getNumber(int& intV,float& floatV)const
        {
            int t = hasNumber();
            switch(t)
            {
                case 0:
                {
                    intV = this->intValue;
                    break;
                }
                case 1:
                {
                    floatV = this->floatValue;
                    break;
                }
            };
            return t;
        }
        int hasNumber()const
        {
            if(hasInt())
                return 0;
            else if(hasFloat())
                return 1;
            return -1;
        }
		bool hasInt()const
		{
            return stored[0];
		}
		bool hasFloat()const
		{
            return stored[1];
		}
		bool hasDouble()const
		{
			return stored[2];
		}
		bool hasString()const
		{
			return stored[3];
		}

		//	Operators
		bool operator==(Variable value);
        bool operator!=(Variable value);
		Variable& operator= (const Variable& value){setValue(value);return *this;}
		Variable& operator= (const int& value){setValue(value);return *this;}
		Variable& operator= (const float& value){setValue(value);return *this;}
		Variable& operator= (const double& value){setValue(value);return *this;}
		Variable& operator= (const string& value){setValue(value);return *this;}
        void setNULL()
        {
        #ifndef PENJIN_FIXED
 		    this->doubleValue = NULL;
		    this->floatValue = NULL;
		    this->intValue = NULL;
        #endif
		    this->stringValue = "NULL";
		    for(int i = 3; i >= 0; --i)
                stored[i] = false;
        }

	private:
		int intValue;
		float floatValue;
		double doubleValue;
		string stringValue;
		bool stored[4];
		bool equals(Variable value);

};
#endif	//	VARIABLE_H

