//----------------------
// template functions implementation
//----------------------

///----------------------
/// analysis
///----------------------

template <class T>
int NumberUtility::sign(const T& value)
{
    return (value > 0) - (0 > value);
}

///----------------------
/// statistics
///----------------------

template <class T, int length>
T NumberUtility::getGreatest(const T (&arr)[length])
{
    T result = arr[length - 1];
    for (int I = length - 2; I >= 0; --I)
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
    int result = length - 1;
    for (int I = length - 2; I >= 0; --I)
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
    for (int I = length - 1; I >= 0; --I)
    {
        if (arr[I] > arr[index])
        {
            return false;
        }
    }
    return true;
}
