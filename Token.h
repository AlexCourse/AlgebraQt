#pragma once

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <QChar>
#include <QString>
#include <QMap>
#include <deque>
#include <QVector>
#include <unordered_set>
#include <QVariant>

// #include "vector_cl.h"
// Ôîðìàò äàííûõ : Îïåðàòîð - ñèìâîëüíîãî òèïà , Ôóíêöèÿ - ïåðå÷åñëèìîãî òèïà Token::Function, ×èñëî - int , double , long_arithmetic , Àëãåüðàè÷åñêèé ñèìâîë - ñòðîêîâîãî òèïà.



class Token {
public:
    enum class Type {
        Unknown,
        Number,
        Integer,
        Real,
        LongArithmetic,
        Operator,
        LeftParen,
        RightParen,
        Algebra,
        Ration,
        ComplexNumber,
        Function,
        Comma,
    };
    enum class Function
    {
        EXP,
        LN,
        SIN,
        COS,
        TG,
        CTG,
        ARCSIN,
        ARCCOS,
        ARCTG,
        ARCCTG,
        SH,
        CH,
        TH,
        CTH,
        ARCSH,
        ARCCH,
        ARCTH,
        ARCCTH,
        ABS,
        LOG,
        POW
    };

    const Type type;
    QVariant value;
    const int precedence;
    const bool rightAssociative;
    const int index; // Óíèêàëüíûé íîìåð òîêåíà.
    const int start_pos; // Èíäåêñ ïåðâîãî âõîæäåíèÿ òîêåíà êàê ïîäñòðîêè â èñõîäíóþ ñïàðøåííóþ ñòðîêó. Ýòè 2 äëÿ âûâîäà ñèíòàêñè÷åñêîé îøèáêè.
    const int last_pos; // Èíäåêñ ïîñëåäíåãî âõîæäåíèÿ òîêåíà êàê ïîäñòðîêè â èñõîäíóþ ñïàðøåííóþ ñòðîêó.

    Token();
    Token(Type t , std::string s);
    Token(Type t, QString& s, int prec = -1, bool ra = false);
    Token(const Token& other);
    Token(Type t, QChar c, int prec, bool ra);
    Token(Type t, const int m);
    Token(Type t, const double m);
    Token(Type t, const Token::Function m);

    Token(const Type t, QString& s, const int index, const int start_index, const int last_index, const int prec = -1, const bool ra = false);
    Token(const Type t, QString& s, const int index, const int start_index, const int last_index);
    Token(const Token& other, int index, int start_index, int last_index);
    Token(const Type t, QChar c, const int index, const int prec, const bool ra);
    Token(const Type t, QChar c, const int index, const int start_pos, const int last_pos, const int prec, const bool ra);
    Token(const Type t, const int m, const int index, const int start_index, const int last_index);
    Token(const Type t, const double m, const int index, const int start_index, const int last_index);
    Token(const Type t, const Token::Function m, const int index, const int start_index, const int last_index);

    Token operator=(const Token& other);
    bool operator==(const Token& other);
    bool operator == (const int m);
    bool operator == (const double m);
    bool operator == (QString m);
    bool operator == (QChar c);
    bool operator == (const Token::Function f_able);
    friend std::ostream& operator << (std::ostream& os, const Token& token);
    friend std::ostream& operator << (std::ostream& os, const Token::Type p);
    QString ToString();

    void SetValue(QVariant& newValue);
    QVariant GetValue() const;

    ~Token();
};



class BW
{
public:
    BW() : isCorrect(true) {}
    bool isCorrect;
    std::deque<std::tuple<int, int>> position;
    std::deque<std::tuple<int, int>> broken_pos;
};

bool f_arg(const Token& T);
bool f_opr_two(const Token& T);
bool f_opr_one(const Token& T);
bool f_opr_free(const Token& T);

QString ToString(QVariant& value);

bool CE(QVariant value, QString s); // #
bool CE(QVariant value, int m); // #
bool CE(QVariant value, double m); // #
bool CE(QVariant value, QChar c);
bool CE(QVariant value, Token::Function p);

Token SetToken(QVariant value);
Token SetToken(QVariant value, int& index);

Token _SetToken(QString& expr);
Token _SetToken(std::string s);
Token _SetToken(QChar c, int& index);
Token _SetToken(QChar c);
Token _SetToken(const Token::Function f_able);
Token _SetToken(const Token::Function f_able, int& index);

std::string ToString(QVariant value);
QString TokensToStr(const std::deque<Token> fh);
std::deque<Token> exprToTokens(QString& expr);
std::deque<Token> exprToTokens(QString& expr, BW& C);
std::deque<Token> exprToTokens(QString& expr, int& index, QString q);
std::deque<Token> exprToTokens(QString& expr, int& index, BW& C, QString q);
void Tokenize_u_minus(std::deque<Token>& fh);
std::deque<Token> shuntingYard(const std::deque<Token>& tokens);
double PolishCalculation(std::deque<Token> es);
double PolishCalculation(QVector<Token> es);


#endif
