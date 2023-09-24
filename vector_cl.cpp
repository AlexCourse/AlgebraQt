#include "vector_cl.h"
using namespace std;

template <typename T>
void ReverseVector(QVector<T>& fh)
{
    int start = 0;
    int end = fh.size() - 1;

    while (start < end) {
        qSwap(fh[start], fh[end]);
        start++;
        end--;
    }
}
