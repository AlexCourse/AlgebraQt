#include "Shunting_yard.h"
#include "PrintColourConsole.h"
#include <iostream>
#include <QVector>
#include <QStack>
#include <QDebug>
#define DEBUG 0

using namespace std;


deque<Token> shuntingYard(const deque<Token>& tokens) {
    deque<Token> eh;
    QStack<Token> st;

    // Ïîêà åñòü òîêåíû äëÿ ÷òåíèÿ:
    for (auto T : tokens) {
        // ×èòàòü òîêåí
        if (DEBUG)
        {
            eh = eh;
            st = st;
            while (0);  // Äëÿ òî÷êè îñòàíîâà
        }
        switch (T.type) {
        case Token::Type::Number:
            eh.push_back(T); // Åñëè òîêåí ïðåäñòàâëÿåò ñîáîé ÷èñëî, òî äîáàâüòå åãî â î÷åðåäü âûâîäà
            break;
        case Token::Type::Integer:
            eh.push_back(T); // Åñëè òîêåí ïðåäñòàâëÿåò ñîáîé ÷èñëî, òî äîáàâüòå åãî â î÷åðåäü âûâîäà
            break;
        case Token::Type::Real:
            eh.push_back(T); // Åñëè òîêåí ïðåäñòàâëÿåò ñîáîé ÷èñëî, òî äîáàâüòå åãî â î÷åðåäü âûâîäà
            break;
        case Token::Type::Ration:
            eh.push_back(T);
            break;
        case Token::Type::ComplexNumber:
            eh.push_back(T);
            break;
        case Token::Type::LongArithmetic:
            eh.push_back(T);
            break;
        case Token::Type::Algebra:
            eh.push_back(T);
            break;
        case Token::Type::Function:
            st.push(T);
            break;
        case Token::Type::Comma:
        {
            bool B = false;
            while (!st.empty())
            {
                Token T_1 = st.top();
                if (T_1.type == Token::Type::LeftParen) { B = true; break; }
                else
                {
                    eh.push_back(T_1);
                    st.pop();
                }
            }
            while (0);
            break;

        }
        case Token::Type::Operator:
        {
            // Åñëè òîêåí ÿâëÿåòñÿ îïåðàòîðîì, o1, òî:
            const auto o1 = T;
            // ïîêà åñòü òîêåí îïåðàòîðà,
            while (!st.empty()) {

                // o2, â âåðõíåé ÷àñòè ñòåêà, è
                const auto o2 = st.top();

                // ëèáî o1 ÿâëÿåòñÿ ëåâîàññîöèàòèâíûì, è åãî ïðèîðèòåò ðàâåí
                // *ìåíüøå èëè ðàâíî* çíà÷åíèþ o2,
                // èëè o1, åñëè àññîöèàòèâíî ñïðàâà, è èìååò ïðèîðèòåò

                if (
                        (!o1.rightAssociative && o1.precedence <= o2.precedence)
                        || (o1.rightAssociative && o1.precedence < o2.precedence) || o2.type == Token::Type::Function
                        ) {
                    if (o2.type == Token::Type::RightParen) break;
                    st.pop();
                    eh.push_back(o2);
                    continue;
                }
                break;
            }
            st.push(o1);
        }
            break;

        case Token::Type::LeftParen:
            st.push(T);
            break;

        case Token::Type::RightParen:
        {
            bool match = false;
            while (!st.empty() && st.top().type != Token::Type::LeftParen) {
                eh.push_back(st.top());
                st.pop();
                match = true;
            }
            if (!st.empty() && st.top().type == Token::Type::LeftParen)
            {
                st.pop();
                match = true;
            }
            if (st.empty() && !match) {
                std::cout << "RightParen error (" << qPrintable(T.ToString()) << ")\n";
                return {};
            }
            break;
        }
        default:
            cout << "error (" << qPrintable(T.ToString()) << endl;
            return {};
        }
    }
    while (!st.empty()) { //  output.extend(stack[::-1])
        if (st.top().type == Token::Type::LeftParen) {
            cout << "Mismatched parentheses error" << endl;
            return {};
        }
        eh.push_back(std::move(st.top()));
        st.pop();
    }

    return eh;
}

bool Out_Deffinition_Scope_DIV(double p, double q){
    if (q != 0) return false;
    else return true;
}

bool Out_Deffinition_Scope_POW(double p, const double q)
{ // p ^ q
    if (p == 0 and q <= 0) return true;
    else return false;
}

bool Out_Deffinition_Scope_LN(double x)
{ // Ïðîâåðêà îáëàñòè îïðåäåëåíèÿ ëîãàðèôìà.
    if (x > 0) return false;
    else return true;
}

bool Out_Deffinition_Scope_LOG(double p, double q)
{ // Ëîãàðèôì îò q ïî p.
    if (p > 0 and q > 0) return false;
    else return true;
}

bool Out_Deffinition_Scope_TG(double x)
{ // x != Pi/2 + Pi*n  ||   x != 3-> 2/Pi*(1 + 2*n)
    double r = (2 / M_PI * x - 1) / 2;
    if (abs(r - round(r)) < pow(10, -15)) return true; // Ïðîâåðêà r íà öåëîå ÷èñëî.
    else return false;
}

bool Out_Deffinition_Scope_CTG(double x)
{ // x != 0 + Pi*n
    double r = x / M_PI;
    if (abs(r - round(r)) < pow(10, -15)) return true; // Ïðîâåðêà r íà öåëîå ÷èñëî.
    else return false;
}

bool Out_Deffinition_Scope_ARCSIN(double x)
{
    if (abs(x) <= 1) return false;
    else return true;
}

bool Out_Deffinition_Scope_ARCCTG(double x)
{
    if (x != 0) return false;
    else return true;
}

bool Out_Deffinition_Scope_ARCCOS(double x)
{
    if (abs(x) <= 1) return false;
    else return true;
}

bool Out_Deffinition_Scope_ARCTG(double x)
{
    if (x != 0) return false;
    else return true;
}

bool Out_Deffinition_Scope_CTH(double x)
{
    if (x != 0) return false;
    else return true;
}


bool Out_Deffinition_Scope_ARCCH(double x)
{
    if (x > 1) return false;
    else return true;
}

bool Out_Deffinition_Scope_ARCTH(double x)
{
    if (abs(x) < 1) return false;
    else return true;
}

bool Out_Deffinition_Scope_ARCCTH(double x)
{
    if (abs(x) > 1) return false;
    else return true;
}

QMap< Token::Function, QString > rFunc_name =
{
    { Token::Function::EXP , "exp"},
    { Token::Function::LN   , "ln"} ,
    { Token::Function::SIN , "sin"} ,
    { Token::Function::COS , "cos"} ,
    { Token::Function::TG  , "tg"} ,
    { Token::Function::CTG , "ctg"} ,
    { Token::Function::ARCSIN , "arcsin"} ,
    { Token::Function::ARCCOS , "arccos"} ,
    { Token::Function::ARCTG , "arctg"} ,
    { Token::Function::ARCCTG , "arcctg"} ,
    { Token::Function::SH , "sh"} ,
    { Token::Function::CH , "ch"} ,
    { Token::Function::TH , "th"} ,
    { Token::Function::CTH , "cth"} ,
    { Token::Function::SH  , "sh"} ,
    { Token::Function::CH  , "ch"} ,
    { Token::Function::TH  , "th"} ,
    { Token::Function::ARCSH  , "arcsh"} ,
    { Token::Function::ARCCH  , "arcch"} ,
    { Token::Function::ARCTH  , "arcth"} ,
    { Token::Function::ARCCTH , "arccth" } ,
    { Token::Function::ABS , "abs"} ,
    { Token::Function::LOG , "log"} ,
    { Token::Function::POW , "pow"} ,
};


void PrintFuncInfoException(const Token::Function c)
{
    QString f = rFunc_name[c]; // Äîáàâèòü âûâîä êðàñíûì öâåòîì.
    QString s = "The argument of the function" + f + "outside the scope of definition";
    PrintColorText(s, Qt::red);
}

void PrintFuncInfoException(const QChar c)
{
    QString f = QString(c);
    QString s = "The argument of the function" + f + "outside the scope of definition";
    PrintColorText(s, Qt::red);
}

bool CheckValueOfFunctionException(const Token::Function c, const double x)
{
    bool B = true;
    switch (c)
    {
    case Token::Function::LN: {   B = !Out_Deffinition_Scope_LN(x); break;  }
    case Token::Function::TG: {   B = !Out_Deffinition_Scope_TG(x); break;  }
    case Token::Function::CTG: {  B = !Out_Deffinition_Scope_CTG(x); break;  }
    case Token::Function::ARCSIN: { B = !Out_Deffinition_Scope_ARCSIN(x); break;  }
    case Token::Function::ARCCOS: { B = !Out_Deffinition_Scope_ARCCOS(x); break;  }
    case Token::Function::CTH: {  B = !Out_Deffinition_Scope_CTH(x); break;  }
    case Token::Function::ARCCH: { B = !Out_Deffinition_Scope_ARCCH(x); break; }
    case Token::Function::ARCTH: { B = !Out_Deffinition_Scope_ARCTH(x); break;  }
    case Token::Function::ARCCTH: { B = !Out_Deffinition_Scope_ARCCTH(x); break;  }
    default: { B = true; break; }
    }
    return B;
}

bool CheckValueOfOperatorException(char c, double p , double q)
{
    bool B = true;
    switch (c)
    {
    case '^' : {   B = !Out_Deffinition_Scope_POW(p , q); break;  }
    case '/' : {   B = !Out_Deffinition_Scope_DIV(p , q); break;  }
    default: { B = true; break; }
    }
    return B;
}


double PolishCalculation(deque<Token> es)
{ // Âû÷èñëåíèå çíà÷åíèÿ ÷èñëåííîãî âûðàæåíèÿ â ôîðìàòå Îáðàòíîé Ïîëüñêîé Íîòàöèè.
    QStack<double> st;
    QVector<QString> cst;
    QString s;
    int n = es.size();
    if (n == 0) return 0;

    while (!es.empty()) {
        if (DEBUG) st = st;
        QString op;
        Token T = es.front();
        es.pop_front();
        switch (T.type) {
        case Token::Type::Integer:
            st.push(T.value.toInt());
            if (DEBUG) op = "Push " + T.ToString();
            break;
        case Token::Type::Real:
            st.push(T.value.toDouble());
            if (DEBUG) op = "Push " + T.ToString();
            break;
        case Token::Type::Algebra:
        {
            cst.push_back(T.value.toString());
            if (DEBUG) op = "Push" + T.ToString();
        }
        case Token::Type::Operator:
        {
            if (f_opr_two(T))
            {
                const auto p = st.top();
                st.pop();
                const auto q = st.top();
                st.pop();
                char c = T.value.toChar().toLatin1();
                if (CheckValueOfOperatorException(c , p , q))
                {
                    switch (c) {
                    default:
                        cout << "Operator error [" << qPrintable(T.ToString()) << "]" << endl;
                        // exit(0);
                        break;
                    case '^':
                        st.push(static_cast<double>(pow(q, p)));
                        break;
                    case '*':
                        st.push(q * p);
                        break;
                    case '/':
                        st.push(q / p);
                        break;
                    case '+':
                        st.push(q + p);
                        break;
                    case '-':
                        st.push(q - p);
                        break;
                    }
                }
                else
                {
                    PrintFuncInfoException(c);
                    exit(0);
                }
            }
            break;
        }
        case Token::Type::Function:
        {
            if (f_opr_one(T))
            {
                const auto x = st.top();
                st.pop();
                Token::Function c = T.value.value<Token::Function>();
                if (CheckValueOfFunctionException(c, x))
                {
                    switch (c)
                    {
                    case Token::Function::EXP: { st.push(exp(x)); break;  }
                    case Token::Function::LN: { st.push(log(x));  break;  }
                    case Token::Function::SIN: { st.push(sin(x));  break;  }
                    case Token::Function::COS: { st.push(cos(x)); break;  }
                    case Token::Function::TG: { st.push(tan(x)); break;  }
                    case Token::Function::CTG: { st.push(1 / tan(x)); break;  }
                    case Token::Function::ARCSIN: { st.push(asin(x)); break;  }
                    case Token::Function::ARCCOS: { st.push(acos(x)); break;  }
                    case Token::Function::ARCTG: { st.push(atan(x));  break;  }
                    case Token::Function::ARCCTG: { st.push(atan(1 / x));  break;  }
                    case Token::Function::SH: { st.push(sinh(x));  break;  }
                    case Token::Function::CH: { st.push(cosh(x));  break; }
                    case Token::Function::TH: { st.push(tanh(x));  break; }
                    case Token::Function::CTH: { st.push(1 / tanh(x)); break;  }
                    case Token::Function::ARCSH: { st.push(asinh(x)); break; }
                    case Token::Function::ARCCH: { st.push(acosh(x));  break; }
                    case Token::Function::ARCTH: { st.push(atanh(x));  break;  }
                    case Token::Function::ARCCTH: { st.push(atanh(1 / x));  break;  }
                    case Token::Function::ABS: { st.push(abs(x)); break;  }
                    }
                }
                else
                {
                    PrintFuncInfoException(c);
                    exit(0);
                }
            }
            else if (f_opr_two(T))
            {
                const auto p = st.top();
                st.pop();
                const auto q = st.top();
                st.pop();
                Token::Function c = T.value.value<Token::Function>();
                switch (c)
                {
                case Token::Function::POW: { st.push(pow(q, p)); break;  }
                case Token::Function::LOG: { st.push(log(p) / log(q)); break;  }
                }
            }
            break;
        }
        default:
            cout << " Token error" << endl;
            // exit(0);
        }
    }
    return st.top();

}

double PolishCalculation(QVector<Token> es)
{
    QStack<double> st;
    QVector<QString> cst;
    QString s;
    QVector<Token> eh(es.rbegin(), es.rend());
    int n = es.size();
    if (n == 0) return 0;
    while (0);

    while (!eh.empty()) {
        if (DEBUG) st = st;
        QString op;
        Token T = eh.back();
        eh.pop_back(); // ñòðàííî óäàëÿåòñÿ âñåãäà ñ êîíöà ó âåêòîðà.
        switch (T.type) {
        case Token::Type::Integer:
            st.push(T.value.toInt());
            if (DEBUG) op = "Push " + T.ToString();
            break;
        case Token::Type::Real:
            st.push(T.value.toDouble());
            if (DEBUG) op = "Push " + T.ToString();
            break;
        case Token::Type::Algebra:
        {
            cst.push_back(T.value.toString());
            if (DEBUG) op = "Push" + T.ToString();

        }
        case Token::Type::Operator:
        {
            if (f_opr_two(T))
            {
                const auto p = st.top();
                st.pop();
                const auto q = st.top();
                st.pop();
                QChar Q = T.value.toChar();
                char c = Q.toLatin1();
                if (CheckValueOfOperatorException(c, p , q))
                {
                    switch (c) {
                    default:
                        cout << "Operator error [" << qPrintable(T.ToString()) << "]" << endl;
                        // exit(0);
                        break;
                    case '^':
                        st.push(static_cast<double>(pow(q, p)));
                        break;
                    case '*':
                        st.push(q * p);
                        break;
                    case '/':
                        st.push(q / p);
                        break;
                    case '+':
                        st.push(q + p);
                        break;
                    case '-':
                        st.push(q - p);
                        break;
                    }

                    QString op = QString("Push %1 %2 %3").arg(QString::number(q)).arg(T.ToString()).arg(QString::number(p));
                    break;
                }
            }
            break;
        }
        case Token::Type::Function:
        {
            if (f_opr_one(T))
            {
                const auto x = st.top();
                st.pop();
                Token::Function c = T.value.value<Token::Function>();
                if (CheckValueOfFunctionException(c, x))
                {
                    switch (c)
                    {
                    case Token::Function::EXP: { st.push(exp(x)); break;  }
                    case Token::Function::LN: { st.push(log(x));  break;  }
                    case Token::Function::SIN: { st.push(sin(x)); break;  }
                    case Token::Function::COS: { st.push(cos(x)); break;  }
                    case Token::Function::TG: { st.push(tan(x));  break;  }
                    case Token::Function::CTG: { st.push(1 / tan(x)); break;  }
                    case Token::Function::ARCSIN: { st.push(asin(x)); break;  }
                    case Token::Function::ARCCOS: { st.push(acos(x)); break;  }
                    case Token::Function::ARCTG: { st.push(atan(x)); break;  }
                    case Token::Function::ARCCTG: { st.push(atan(1 / x)); break;  }
                    case Token::Function::SH: { st.push(sinh(x)); break;  }
                    case Token::Function::CH: { st.push(cosh(x)); break;  }
                    case Token::Function::TH: { st.push(tanh(x)); break;  }
                    case Token::Function::CTH: { st.push(1 / tanh(x)); break;  }
                    case Token::Function::ARCSH: { st.push(asinh(x)); break;  }
                    case Token::Function::ARCCH: { st.push(acosh(x)); break;  }
                    case Token::Function::ARCTH: { st.push(atanh(x)); break;  }
                    case Token::Function::ARCCTH: { st.push(atanh(1 / x)); break;  }
                    case Token::Function::ABS: { st.push(abs(x)); break;  }
                    }
                }
                else
                {
                    PrintFuncInfoException(c);
                    exit(0);
                }
            }
            else if (f_opr_two(T))
            {
                const auto p = st.top();
                st.pop();
                const auto q = st.top();
                st.pop();
                Token::Function c = T.value.value<Token::Function>();
                switch (c)
                {
                case Token::Function::POW: { st.push(pow(q, p));  break;  }
                case Token::Function::LOG: { st.push(log(p) / log(q)); break;  }
                }
            }
            break;
        }
        default:
            printf("Token error\n");
            // exit(0);
        }
    }
    return st.top();

}



double FunctionValue(deque<Token> fh, double x, QString symbol)
{ // Ïîäñòàíîâêà â ôóíêöèþ çàäàííóþ Îáðàòíîé Ïîëüñêîé Íîòàöèåé.
    // x - ïîäñòàâëÿåìîå çíà÷åíèå.
    // symbol - ñòðîêîâîé ñèìâîë , êîòîðûé çàìåíÿåì.
    deque<Token>::iterator iter;
    deque<Token> kh;
    for (iter = fh.begin(); iter != fh.end(); iter++)
    {
        if (CE(iter->value, symbol))
        {
            Token T = SetToken(x);
            kh.push_back(T);
        }
        else
        {
            Token T = *iter;
            kh.push_back(T);
        }
    }
    double r = PolishCalculation(kh);
    return r;
}


double FunctionValue(QVector<Token> fh, double x, QString symbol)
{ // Ïîäñòàíîâêà â ôóíêöèþ çàäàííóþ Îáðàòíîé Ïîëüñêîé Íîòàöèåé.
    // x - ïîäñòàâëÿåìîå çíà÷åíèå.
    // symbol - ñòðîêîâîé ñèìâîë , êîòîðûé çàìåíÿåì.
    QVector<Token>::iterator iter;
    QVector<Token> kh;
    for (iter = fh.begin(); iter != fh.end(); iter++)
    {
        if (CE(iter->value, symbol))
        {
            Token T = SetToken(x);
            kh.push_back(T);
        }
        else
        {
            Token T = *iter;
            kh.push_back(T);
        }
    }
    double r = PolishCalculation(kh);
    return r;
}

deque<Token> ReplaceElementInPolish(deque<Token> fh, double x, QString symbol)
{ // Ïîäñòàíîâêà â ôóíêöèþ çàäàííóþ Îáðàòíîé Ïîëüñêîé Íîòàöèåé.
    // x - ïîäñòàâëÿåìîå çíà÷åíèå.
    // symbol - ñòðîêîâîé ñèìâîë , êîòîðûé çàìåíÿåì.
    deque<Token>::iterator iter;
    deque<Token> kh;
    for (iter = fh.begin(); iter != fh.end(); iter++)
    {
        if (CE(iter->value, symbol))
        {
            Token T = SetToken(x);
            kh.push_back(T);
        }
        else
        {
            Token T = *iter;
            kh.push_back(T);
        }
    }
    return kh;
}


QVector<Token> ReplaceElementInPolish(QVector<Token> fh, double x, QString symbol)
{ // Ïîäñòàíîâêà â ôóíêöèþ çàäàííóþ Îáðàòíîé Ïîëüñêîé Íîòàöèåé.
    // x - ïîäñòàâëÿåìîå çíà÷åíèå.
    // symbol - ñòðîêîâîé ñèìâîë , êîòîðûé çàìåíÿåì.
    QVector<Token>::iterator iter;
    QVector<Token> kh;
    for (iter = fh.begin(); iter != fh.end(); iter++)
    {
        if (CE(iter->value, symbol))
        {
            Token T = SetToken(x);
            kh.push_back(T);
        }
        else
        {
            Token T = *iter;
            kh.push_back(T);
        }
    }
    return kh;
}
// Ïðîâåðêà ñèíòàêñè÷åñêîé êîððåêòíîñòè.
bool Check_Bracket_Matching(deque<Token> fh)
{ // Ôóíêöèÿ ïðèìåíÿåòñÿ ïîñëå ôóíêöèè exprToTokens().
    int balance = 0;
    deque<Token>::iterator iter;
    for (iter = fh.begin(); iter != fh.end(); iter++)
    {
        Token token = *iter;
        if (token.type == Token::Type::LeftParen) balance++;
        if (token.type == Token::Type::RightParen) balance--;
    }
    if (balance == 0) return true;
    else return false;
}

bool CheckBalance(deque<Token> fh)
{ // Ôóíêöèÿ ïðèìåíÿåòñÿ ïîñëå ôóíêöèè exprToTokens().
    int balance = 1;
    deque<Token>::iterator iter;
    for (iter = fh.begin(); iter != fh.end(); iter++)
    {
        Token token = *iter;
        if (f_arg(token)) balance--;
        if (f_opr_two(token)) balance++;
        if (f_opr_one(token)) {}
    }
    if (balance == 0) return true;
    else return false;
}

QString PostfixToInfix(QVector<Token>& es)
{ // Â ïåðâîì ïàðàìåòðå âûðàæåíèå â ôîðìàòå Îáðàòíîé Ïîëüñêîé íîòàöèè.
    // Ðåçóëüòàò âîçâðàùàåòñÿ âî âòîðîì ïàðàìåòðå â ôîðìå Èíôèêñíîé Çàïèñè.
    QString R[2], s, t;
    // reverse(fs.begin(), fs.end());
    QVector<Token> fs(es.rbegin(), es.rend());
    QStack<QString> st;
    QStack<int> st_opr; // Çäåñü ñîõðàíÿþòñÿ ïðèîðèòåòû îïåðàòîðîâ.
    int m, P[2];
    while (!fs.empty())
    {
        Token T = fs.back();
        fs.pop_back();
        // Äëÿ áàëàíñèðîâêè ñòåêà.
        if (T.type == Token::Type::Algebra)
        {
            s = T.ToString();
            st.push(s);
            st_opr.push(-1);
        }
        else if (T.type == Token::Type::Integer || T.type == Token::Type::Real || T.type == Token::Type::Number)
        {
            s = T.ToString();
            st.push(s);
            st_opr.push(-1);
        }
        else if (f_opr_two(T))
        {
            QString f = T.ToString();
            R[0] = st.top();
            st.pop();
            R[1] = st.top();
            st.pop();
            P[0] = st_opr.top();
            st_opr.pop();
            P[1] = st_opr.top();
            st_opr.pop();

            m = T.precedence;
            bool ra = T.rightAssociative;
            bool B = false;
            for (int i = 0; i < 2; i++)
            {
                B = false;
                if (P[i] != -1)
                {
                    if (P[i] <= m && ra) B = true;
                    if (P[i] < m && !ra) B = true;
                    if (B) s = "(" + R[i] + ")";
                    else s = R[i];
                    R[i] = s;
                }
            }
            if (T.type == Token::Type::Operator) s = R[1] + f + R[0];
            if (T.type == Token::Type::Function) s = f + '(' + R[1] + ',' + R[0] + ')';
            st.push(s);
            st_opr.push(m);

        }
        else if (f_opr_one(T))
        {
            QString f = T.ToString();
            QString p = st.top();
            st.pop();
            s = f + "(" + p + ")";
            st.push(s);
            st_opr.push(5);
        }

    }

    s = st.top();
    st.pop();
    return s;
}

QString PostfixToInfix(deque<Token>& fs)
{ // Â ïåðâîì ïàðàìåòðå âûðàæåíèå â ôîðìàòå Îáðàòíîé Ïîëüñêîé íîòàöèè.
    // Ðåçóëüòàò âîçâðàùàåòñÿ âî âòîðîì ïàðàìåòðå â ôîðìå Èíôèêñíîé Çàïèñè.
    QString R[2], s, t;
    // reverse(fs.begin(), fs.end());
    QStack<QString> st;
    QStack<int> st_opr; // Çäåñü ñîõðàíÿþòñÿ ïðèîðèòåòû îïåðàòîðîâ.
    int m, P[2];
    while (!fs.empty())
    {
        Token T = fs.front();
        fs.pop_front();
        // Äëÿ áàëàíñèðîâêè ñòåêà.
        if (T.type == Token::Type::Algebra)
        {
            s = T.ToString();
            st.push(s);
            st_opr.push(-1);
        }
        else if (T.type == Token::Type::Integer || T.type == Token::Type::Real || T.type == Token::Type::Number)
        {
            s = T.ToString();
            st.push(s);
            st_opr.push(-1);
        }
        else if (f_opr_two(T))
        {
            QString f = T.ToString();
            R[0] = st.top();
            st.pop();
            R[1]  = st.top();
            st.pop();
            P[0] = st_opr.top();
            st_opr.pop();
            P[1] = st_opr.top();
            st_opr.pop();

            m = T.precedence;
            bool ra = T.rightAssociative;
            bool B = false;
            for (int i = 0; i < 2; i++)
            {
                B = false;
                if (P[i] != -1)
                {
                    if (P[i] <= m && ra) B = true;
                    if (P[i] < m && !ra) B = true;
                    if (B) s = "(" + R[i] + ")";
                    else s = R[i];
                    R[i] = s;
                }
            }
            if (T.type == Token::Type::Operator ) s = R[1] + f + R[0];
            if ( T.type == Token::Type::Function ) s = f + '(' + R[1] + ',' + R[0] + ')';
            st.push(s);
            st_opr.push(m);

        }
        else if (f_opr_one(T)) // Èñïîëüçîâàíèå ôóíêöèè.
        {
            QString f = T.ToString();
            QString p = st.top();
            st.pop();
            s = f + "(" + p + ")";
            st.push(s);
            st_opr.push(5);
        }
    }

    s = st.top();
    st.pop();
    return s;
}


struct HW
{
    HW() :  haveOperator(false), haveFunction(false) {}
    bool haveOperator;
    bool haveFunction;
};


bool CheckSyntaxError(deque<Token> fh, BW& C)
{
    deque<tuple<int, int>> kh;
    deque<tuple<int, int>> ks = C.position;
    deque<Token>::iterator iter[3];
    int n = fh.size();
    if (n <= 3)
    {
        switch (n)
        {
        case 0: { cout << "Ïóñòîå âûðàæåíèå" << endl; break; }
        case 1:
        {
            Token token = fh[0];
            if (!f_arg(token)) kh.push_back(make_tuple(0, 1));
            break;
        }
        case 2:
        {
            Token token = fh[0];
            Token C = fh[1];
            if (f_opr_one(token))
            {
                bool B = true;
                if (!f_arg(C)) B = false;
                if (!B) kh.push_back(ks[0]); // Â ïðåäåëàõ êàêèõ ãðàíèö áóäåò çàêðàøèâàòüñÿ êðàñíûì.
            }
            break;
        }
        case 3:
        {
            Token A = fh[0];
            Token token = fh[1];
            Token C = fh[2];
            if (f_opr_two(token))
            {
                bool B = true;
                if (!f_arg(A)) B = false;
                if (!f_arg(C)) B = false;
                if (!B) kh.push_back(ks[1]); // Â ïðåäåëàõ êàêèõ ãðàíèö áóäåò çàêðàøèâàòüñÿ êðàñíûì.
            }
            break;}
        }
    }
    else
    {
        iter[0] = fh.begin();
        iter[1] = fh.begin() + 1;
        iter[2] = fh.begin() + 2;
        for (;iter[2] != fh.end(); iter[0] = iter[1] , iter[1] = iter[2] , iter[2]++)
        {
            Token token = *(iter[1]);
            if (f_opr_two(token))
            {
                bool B = true;
                Token A = *(iter[0]);
                Token C = *(iter[2]);
                if (!(f_arg(A) or (A.type == Token::Type::RightParen) or (A.type == Token::Type::Function )) ) B = false;
                if (!(f_arg(C) or (C.type == Token::Type::LeftParen) or (C.type == Token::Type::Function)) ) B = false;
                if (!B)
                {
                    int j = iter[1] - fh.begin();
                    kh.push_back(ks[j]); // Â ïðåäåëàõ êàêèõ ãðàíèö áóäåò çàêðàøèâàòüñÿ êðàñíûì.
                }
            }
            else if (f_opr_one(token))
            {
                bool B = true;
                Token C = *(iter[2]);
                if (!(f_arg(C) or (C.type == Token::Type::LeftParen)) ) B = false;
                if (!B)
                {
                    int j = iter[1] - fh.begin();
                    kh.push_back(ks[j]); // Â ïðåäåëàõ êàêèõ ãðàíèö áóäåò çàêðàøèâàòüñÿ êðàñíûì.
                }
            }
        }
    }
    C.broken_pos = kh;
    return true; // Äëÿ çàãëóøêè.
}


bool CheckSyntaxBracket(deque<Token> fh, BW& C)
{
    bool const LOCAL_DEBUG = false;
    deque<Token>::iterator iter;
    deque<tuple<int, int>> kh , ks;
    QStack<QChar> st; // ñòåê äëÿ '(' è ')'.
    QStack<int> st_level; // Âåëè÷èíà äèñáàëàíñà ñîîòâåòñóþùàÿ ïîçèöèè ïðè äîñòèæåíèè ñêîáêè.
    QStack<int> st_index; // Ñîõðàíÿåòñÿ èíäåêñ ïîñëåäíåé ñêîáêè äîáàâëåííîé â ñòåê.
    QStack<tuple<int, int>> st_pos;
    // Ïîñëåäíèå 3 ñòåêà ñîîòâåòñòâóþò äðóã äðóãó è â íèõ ðàâíîå ÷èñëî ýëåìåíòîâ.
    QVector<int> ls; // Âåêòîð äëÿ îòëàäêè ñîîòâåòñòâèå êàæäîãî ñèìâîëà ñòðîêè è åãî balance.
    ks = C.position;
    kh = C.broken_pos;
    int balance = 1;
    int m = 1;
    QChar c;
    for (iter = fh.begin(); iter != fh.end(); iter++)
    {
        Token token = *iter;
        if (f_arg(token)) balance--;
        else if (f_opr_two(token)) balance++;
        else if (f_opr_one(token)) {}
        if (LOCAL_DEBUG) ls.push_back(balance);
        if (token.type == Token::Type::LeftParen || token.type == Token::Type::RightParen)
        {
            if (token.type == Token::Type::LeftParen)
            {
                st.push('(');
                st_level.push(balance);
                int j = iter - fh.begin();
                st_pos.push(ks[j]);
                st_index.push(j);

            }
            if (token.type == Token::Type::RightParen)
            {
                c = st.top();
                st.pop();
                m = st_level.top();
                st_level.pop();
                int j = st_index.top();
                st_index.pop();
                Token token_1 = (j == 0) ? fh[j] : fh[j - 1]; // Ïðîâåðêà íà íàëè÷èå ôóíêöèè ïåðåä ñêîáêàìè. Åñëè ñêîáêè íå ñòîÿò â íà÷àëå âûðàæåíèÿ.
                if (m != balance + 1 and token_1.type != Token::Type::Function ) // Îøèáêà äèññáàëàíñ âûðàæåíèÿ.
                {
                    tuple<int, int> Q = st_pos.top();
                    kh.push_back(Q);
                }
                st_pos.pop();
            }
        }
    }
    if (!st.empty())
    {
        while (!st.empty())
        {
            kh.push_back(st_pos.top());
            st_pos.pop();
            st.pop();
        }
    }
    C.broken_pos = kh;
    if (LOCAL_DEBUG)
    {
        QVector<int>::iterator iter_1;
        bool B = false;
        for (iter = fh.begin(), iter_1 = ls.begin(); iter != fh.end(); iter++, iter_1++)
        {
            Token token = *iter;
            int q = *iter_1;
            QString s = token.ToString() + " : " + QString::number(q);
            if (token.type == Token::Type::LeftParen || token.type == Token::Type::RightParen) PrintColorText(s , Qt::red);
            else PrintColorText(s , Qt::white);
        }
    }
    if (kh.empty()) return true;
    else return false;
}

bool IsNumeric(deque<Token> fh)
{
    bool B = true;
    for (Token token : fh)
    {
        if (token.type == Token::Type::Algebra)
        {
            B = false;
            break;
        }
    }
    return B;
}

bool CheckUnknownIdentificator(deque<Token> fh, BW& C)
{
    deque<Token>::iterator iter;
    deque < tuple<int, int>> kh, ks , ls;
    kh = C.broken_pos;
    ks = C.position;
    for (iter = fh.begin(); iter != fh.end(); iter++)
    {
        Token token = *iter;
        if (token.type == Token::Type::Unknown)
        {
            int j = iter - fh.begin();
            ls.push_back(ks[j]);
        }
    }
    for (auto Q : ls) kh.push_back(Q);
    if (ls.empty()) return true;
    else return false;
}

QSet<int> LiColourProcessing(BW& C)
{
    deque<tuple<int, int>> ks = C.broken_pos;
    QSet<int> f_box; // Ñïèñîê âñåõ çàêðàøåííûõ êðàñíûì ñèìâîëîâ.
    for (auto Q : ks)
    {
        int p , q;
        tie(p, q) = Q;
        for (int i = p; i < q; i++) f_box.insert(i);
    }
    return f_box;
}


deque<Token> FToPolishI(QString expr, int& index, Enumerable q)
{ // Ôóíêöèÿ ñ îáðàáîòêîé îøèáîê.
    deque<Token> fh, eh, es;
    QSet<int> e_box;
    bool B;
    BW C = BW();
    switch (q)
    {
    case Enumerable::DEFAULT: { fh = exprToTokens(expr , C); break; }
    case Enumerable::ORDERING: { fh = exprToTokens(expr, index, C, "ORDERING"); break; } // Îòëàäî÷íûé.
    }
    deque<tuple<int, int>> kh = C.broken_pos;
    if (!kh.empty()) // Îøèáêà ñëèøêîì áîëüøîå ÷èñëî.
    {
        e_box = LiColourProcessing(C);
        PrintLineWithColorRed(expr, e_box);
        QString s = "Too large a number in the expression";
        PrintColorText(s , Qt::red);
        exit(0);
        return fh;
    }
    Tokenize_u_minus(fh);
    B = true;
    B = B and CheckSyntaxError(fh, C);
    B = B and CheckSyntaxBracket(fh, C);
    e_box = LiColourProcessing(C);
    if (!B)
    {
        PrintLineWithColorRed(expr, e_box);
        QString s = "Syntax error : ";
        PrintColorText(s , Qt::red);
    }
    if (!CheckUnknownIdentificator(fh, C))
    {
        QString s = "Unknown Identificator";
        PrintColorText(s , Qt::red);
        exit(0);
        return fh;
    }
    if (!Check_Bracket_Matching(fh))
    {
        QString s = "Mismatched parentheses error";
        PrintColorText(s , Qt::red);
        exit(0);
        return fh;
    }
    if (!CheckBalance(fh))
    {
        QString s = "Dissbalance expression error";
        PrintColorText(s , Qt::red);
        exit(0);
        return fh;
    }
    eh = ReplaceElementInPolish(fh, M_PI, "Pi");
    es = shuntingYard(eh);
    return es;
}

deque<Token> FToPolish(QString expr)
{
    int index = 0;
    deque<Token> fs = FToPolishI(expr, index, Enumerable::DEFAULT);
    return fs;
}


void PrintTokensListInformation(deque<Token> fh)
{
    deque<Token>::iterator iter;
    for (iter = fh.begin(); iter != fh.end(); iter++)
    {
        Token token = *iter;
        const Token::Type t = token.type;
        QString symbol = token.ToString();
        const int start_pos = token.start_pos;
        const int last_pos = token.last_pos;
        const int precendence = token.precedence;
        const bool rightAssociative = token.rightAssociative;
        cout << "Type : " << t << "\t";
        cout << "Symbol : " << qPrintable(symbol) << "\t";
        // cout << "start_pos : " << start_pos << "\t";
        // cout << "last_pos : " << last_pos << "\t";
        cout << "precendence : " << precendence << "\t";
        cout << "rightAssociative : " << rightAssociative << "\t";
        for(int i =0; i< 2; i++) cout << endl;
    }
}
