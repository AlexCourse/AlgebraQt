#pragma once
#pragma once

#include <deque>
#include <QSet>
#include <QString>
#include <QMap>
#include <math.h>
#include "Token.h"

enum Enumerable
{
    DEFAULT,
    ORDERING
};

bool IsNumeric(std::deque<Token> fh);
QString PostfixToInfix(QVector<Token>& fs);
QString PostfixToInfix(std::deque<Token>& fs);
std::deque<Token> FToPolish(QString expr);
std::deque<Token> FToPolishI(QString expr, int& index, Enumerable q);
double FunctionValue(std::deque<Token> fh, double value, QString symbol);
double FunctionValue(QVector<Token> fh, double value, QString symbol);
QVector<Token> ReplaceElementInPolish(QVector<Token> fh, double x, QString symbol);
std::deque<Token> ReplaceElementInPolish(std::deque<Token> fh, double x, QString symbol);
void PrintTokensListInformation(std::deque<Token> fh);
