//----------------------
// template functions implementation
//----------------------

///----------------------
/// analysis
///----------------------

template <class T>
int NumberUtility::sign(const T& value)
{
    return (Value > 0) - (0 > Value);
}

///----------------------
/// statistics
///----------------------

template <class T, int length>
T NumberUtility::getGreatest(const T (&arr)[length])
{
    T result = arr[0];
    for (int I = 1; I < length; I++)
    {
        if (arr[I] > result)
        {
            result = arr[I];
        }
    }
    return result;
}

template <class T, int length>
int NumberUtility::getGreatestIndex(const T (&arr)[length])
{
    int result = 0;
    for (int I = 1; I < length; I++)
    {
        if (arr[I] > arr[result])
        {
            result = I;
        }
    }
    return result;
}

template <class T, int length>
bool NumberUtility::isGreatest(const T (&arr)[length], CRuint index)
{
    for (int I = 0; I < length; I++)
    {
        if (arr[I] > arr[index])
        {
            return false;
        }
    }
    return true;
}
