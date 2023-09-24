#include "Enumerate.h"
#include <set>

using namespace std;

QVector<int> CountIndex(deque<Token> fs)
{
    deque<Token>::iterator iter;
    QVector<int> kh;
    for (iter = fs.begin(); iter != fs.end(); iter++)
    {
        Token token = *iter;
        int index = token.index;
        kh.push_back(index);
    }
    return kh;
}

QVector<int> CountIndex(QVector<Token> fs)
{
    QVector<Token>::iterator iter;
    QVector<int> kh;
    for (iter = fs.begin(); iter != fs.end(); iter++)
    {
        Token token = *iter;
        int index = token.index;
        kh.push_back(index);
    }
    return kh;
}
