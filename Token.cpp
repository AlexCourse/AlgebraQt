#include "Token.h"
#include <regex>
#include <limits>
#define INT_MAX 2147483647.

#define DEBUG 0

using namespace std;

Token::Token() : type(Type::Unknown), value(""), index(0), start_pos(0), last_pos(0), precedence(-1), rightAssociative(false) {}

Token::Token(Type t, QString& s, int prec, bool ra) : type(t), value(s), precedence(prec), rightAssociative(ra), index(0), start_pos(0), last_pos(0) {}

Token::Token(const Type t, const int m) : type(t), value(m), index(0), start_pos(0), last_pos(0), precedence(-1), rightAssociative(false) {}

Token::Token(const Type t, const double m) : type(t), value(m), index(0), start_pos(0), last_pos(0), precedence(-1), rightAssociative(false) {}

Token::Token(Type t,  Token::Function m) : type(t), value(QVariant::fromValue(static_cast<int>(m))), index(0), start_pos(0), last_pos(0), precedence(1), rightAssociative(false) {}

Token::Token(const Type t, QChar c, const int prec, bool ra) : type(t), value(c), index(0), start_pos(0), last_pos(0), precedence(prec), rightAssociative(ra) {}

Token::Token(const Token& other) : type(other.type), value(other.value), index(other.index), start_pos(other.start_pos), last_pos(other.last_pos), precedence(other.precedence), rightAssociative(other.rightAssociative) {}

Token::Token(Type t , std::string s) : type(t) , value(QString::fromStdString(s)) , index(0), start_pos(0), last_pos(0), precedence(1), rightAssociative(false){}

// string
Token::Token(const Type t, QString& s, const int index, const int start_pos, const int last_pos, const int prec , const bool ra) : type(t), value(s),
index(index), start_pos(start_pos), last_pos(last_pos), precedence(prec), rightAssociative(ra) {}

Token::Token(const Type t, QString& s, const int index, const int start_pos, const int last_pos) : type(t), value(s), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(-1), rightAssociative(false) {}
// char
Token::Token(const Type t, QChar c, const int index,  const int start_pos, const int last_pos, const int prec , const bool ra) : type(t), value(c), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(prec), rightAssociative(ra) {}

Token::Token(const Type t , QChar c , const int index , int prec , bool ra) : type(t), value(c), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(prec), rightAssociative(ra) {}

// int
Token::Token(const Type t, const int m, const int index, const int start_pos, const int last_pos) : type(t), value(m), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(-1), rightAssociative(false) {}
// double
Token::Token(const Type t, const double m, const int index, const int start_pos, const int last_pos) : type(t), value(m), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(-1), rightAssociative(false) {}

Token::Token(const Token& other, const int index, const int start_pos, const int last_pos) : type(other.type), value(other.value), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(other.precedence), rightAssociative(other.rightAssociative) {}


Token::Token(const Type t, const Token::Function m, const int index, const int start_pos, const int last_pos) : type(t), value(QVariant::fromValue(static_cast<int>(m))), index(index),
start_pos(start_pos), last_pos(last_pos), precedence(1), rightAssociative(false) {}

void Token::SetValue(QVariant& newValue) {
    this->value = newValue;
}


QVariant Token::GetValue() const {
    return this->value;
}

QMap< QString, Token::Function>  func_name =
{ { "exp" , Token::Function::EXP },
  { "ln" , Token::Function::LN   } ,
  {"sin" , Token::Function::SIN} ,
  { "cos" , Token::Function::COS} ,
  { "tg"  , Token::Function::TG } ,
  { "ctg"  , Token::Function::CTG } ,
  { "arcsin"  , Token::Function::ARCSIN } ,
  { "arccos"  , Token::Function::ARCCOS } ,
  { "arctg"   , Token::Function::ARCTG } ,
  { "arcctg"  , Token::Function::ARCCTG } ,
  { "sh"      , Token::Function::SH } ,
  { "ch"      , Token::Function::CH } ,
  { "th"      , Token::Function::TH } ,
  { "cth"     , Token::Function::CTH } ,
  { "sh"      , Token::Function::SH } ,
  { "ch"      , Token::Function::CH } ,
  { "th"      , Token::Function::TH } ,
  { "arcsh"     , Token::Function::ARCSH } ,
  { "arcch"     , Token::Function::ARCCH } ,
  { "arcth"     , Token::Function::ARCTH } ,
  { "arccth"    , Token::Function::ARCCTH } ,
  { "abs"      , Token::Function::ABS } ,
  { "log"      , Token::Function::LOG } ,
  { "pow"      , Token::Function::POW }
};

QMap< Token::Function, QString > rfunc_name =
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
    { Token::Function::POW , "pow"}
};

QMap<Token::Type, QString > type_token = { { Token::Type::Unknown , "Unknown"} ,
                                           { Token::Type::Number , "Number"} ,
                                           { Token::Type::Integer , "Integer" } ,
                                           { Token::Type::Real , "Real"} ,
                                           { Token::Type::LongArithmetic , "LongArithmetic"} ,
                                           { Token::Type::Operator , "Operator" } ,
                                           { Token::Type::LeftParen , "LeftParen" } ,
                                           { Token::Type::RightParen , "RightParen" } ,
                                           { Token::Type::Algebra , "Algebra" } ,
                                           { Token::Type::Ration, "Ration" } ,
                                           { Token::Type::ComplexNumber , "ComplexNumber"},
                                           { Token::Type::Function , "Function" },
                                           { Token::Type::Comma , "Comma" }
                                         };

Token Token::operator=(const Token& other) {
    return Token(other);
}

bool Token::operator==(const Token& other) {
    return (type == other.type && value == other.value && precedence == other.precedence && rightAssociative == other.rightAssociative);
}

bool Token::operator == (const int m)
{
    QVariant t = this->value;
    if (t.canConvert<int>()) {
        int p = t.toInt();
        if (p == m) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Token::operator == (const double m)
{
    QVariant t = this->value;
    if (t.canConvert<double>()) {
        double p = t.toDouble();
        if (p == m) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Token::operator == (QString s)
{
    QVariant t = this->value;
    if (t.canConvert<QString>()) {
        QString p = t.toString();
        if (p == s) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Token::operator == (QChar c)
{
    QVariant t = this->value;
    if (t.canConvert<QChar>()) {
        QChar p = t.toChar();
        if (p == c) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Token::operator == (const Token::Function f_able)
{
    QVariant t = this->value;
    if (t.canConvert<Token::Function>()) {
        Token::Function g_able = t.value<Token::Function>();
        if (g_able == f_able) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}




std::ostream& operator<<(std::ostream& os, const Token& token) {
    if (token.value.canConvert<QString>()) {
        QString s = qvariant_cast<QString>(token.value);
        os << s.toStdString();
    }
    else if (token.value.canConvert<int>()) {
        int m = qvariant_cast<int>(token.value);
        os << m;
    }
    else if (token.value.canConvert<double>()) {
        double m = qvariant_cast<double>(token.value);
        os << m;
    }
    else if (token.value.canConvert<QChar>()) {
        QChar c = qvariant_cast<QChar>(token.value);
        os << c.toLatin1();
    }
    else if (token.value.canConvert<Token::Function>()) {
        Token::Function p = qvariant_cast<Token::Function>(token.value);
        QString s = rfunc_name[p];
        os << s.toStdString();
    }
    return os;
}

ostream& operator<<(ostream& os, const Token::Type p)
{
    QString s = type_token[p];
    os << s.toStdString();
    return os;
}

QSet<QString> operator_info_two = { "+" , "-", "/", "*", "^" };
QSet<QString> operator_info_one = { "!" };
QSet<QString> func_info_one = { "sin", "cos", "tg", "ctg", "ln", "exp", "sec", "cosec", "arcsin", "arccos", "arctg", "arcctg",
                                "sqrt", "sh", "ch", "th", "cth", "arcsh", "arcch", "arcth", "arccth", "abs", "factorial" };
QSet<QString> func_info_two = { "log" , "pow" , "S" , "Integral" };
QSet<QString> func_info_free = { "D" , "Z" , "P" , "Derivate" };
QSet<QString> func_info = { "sin", "cos", "tg", "ctg", "ln", "exp", "sec", "cosec", "arcsin", "arccos", "arctg", "arcctg",
                            "sqrt", "sh", "ch", "th", "cth", "arcsh", "arcch", "arcth", "arccth", "abs", "factorial" , "log" , "pow" };

struct Operator {
    int precedence;
    QChar associativity;
};

QMap<QChar, Operator> operator_info = { { '+' , { 2, 'L'}} ,
                                        {'-' , { 2, 'L'}},
                                        {'/' , { 3, 'L'}},
                                        {'*' , { 3, 'L'}},
                                        {'^' , { 4, 'R'}},
                                      };


QString Token::ToString()
{
    QString s = "";
    if (value.canConvert<QString>()) {
        s = value.toString().toStdString().c_str();
    }
    else if (value.canConvert<int>()) {
        int m = value.toInt();
        s = QString::number(m);
    }
    else if (value.canConvert<double>()) {
        double m = value.toDouble();
        s = QString::number(m);
    }
    else if (value.canConvert<QChar>()) {
        QChar c = value.toChar();
        s = QString(c.toLatin1());
    }
    else if (value.canConvert<Token::Function>()) {
        Token::Function p = value.value<Token::Function>();
        static QMap<Token::Function, std::string> rfunc_name;
        s = QString::fromStdString(rfunc_name[p]);
    }

    return s;
}

string ToString(QVariant value)
{
    string s = "";
    if (value.canConvert<QString>()) {
        s = value.toString().toStdString();
    }
    else if (value.canConvert<int>()) {
        int m = value.toInt();
        s = to_string(m);
    }
    else if (value.canConvert<double>()) {
        double m = value.toDouble();
        s = to_string(m);
    }
    else if (value.canConvert<QChar>()) {
        QChar c = value.toChar();
        s = string(1, c.toLatin1());
    }
    else if (value.canConvert<Token::Function>()) {
        Token::Function p = value.value<Token::Function>();
        static map<Token::Function, string> rfunc_name;
        s = rfunc_name[p];
    }

    return s;

}

bool f_arg(const Token& T) {
    if (T.type == Token::Type::Algebra || T.type == Token::Type::Number || T.type == Token::Type::Integer ||
            T.type == Token::Type::Real || T.type == Token::Type::Ration || T.type == Token::Type::LongArithmetic ||
            T.type == Token::Type::ComplexNumber)
        return true;
    else
        return false;
}

bool f_opr_two(const Token& T) { // Ïðîâåðêà ÿâëÿåòñÿ ëè îïåðàòîðàòîðîì ñ äâóìÿ îïåðàíäàìè
    Token token = T;
    bool B = false;
    if (T.type == Token::Type::Operator)
        B = true;
    else if (T.type == Token::Type::Function)
    {
        Token::Function p = T.value.value<Token::Function>();
        switch (p)
        {
        case Token::Function::LOG: { B = true; break; }
        case Token::Function::POW: { B = true; break; }
        }
    }
    else return false;
    return B;
}

bool f_opr_one(const Token& T) { // Ïðîâåðêà ÿâëÿåòñÿ ëè îïåðàòîðîì ñ îäíèì îïåðàíäîì.
    Token token = T;
    bool B = true;
    if (T.type == Token::Type::Operator)
        B = false;
    else if (T.type == Token::Type::Function)
    {
        Token::Function p = T.value.value<Token::Function>();
        switch (p)
        {
        case Token::Function::LOG: { B = false; break; }
        case Token::Function::POW: { B = false; break; }
        }
    }
    else return false;
    return B;
}


bool f_opr_free(const Token& T) { // Ïðîâåðêà ÿâëÿåòñÿ ëè îïåðàòîðîì ñ òðåìÿ îïåðàíäàìè.
    Token token = T;
    QString p = token.ToString();
    if (func_info_free.contains(p)) {
        return true;
    }
    return false;
}

bool isliter(QChar p) {
    if ((p >= 'A' && p <= 'Z') || (p >= 'a' && p <= 'z')) {
        return true;
    }
    else {
        return false;
    }
}

Token::~Token() {
    // Destructor definition
    // Add any necessary cleanup code here
}

bool CE(QVariant value, QString s)
{
    if (value.canConvert<QString>())
    {
        QString t = value.toString();
        if (t == s) return true;
        else return false;
    }
    else return false;
}


bool CE(QVariant value, int m)
{
    bool B = false;
    if (value.canConvert<int>())
    {
        int q = value.toInt();
        if (m == q) B = true; // Дополнительная функция для обработки глюка компилятора при сравнении двух целых чисел равных при случае p = q = 1
        else B = false;
    }
    else B = false;
    return B;
}

bool CE(QVariant value, double m)
{
    if (value.canConvert<double>())
    {
        double q = value.toDouble();
        if (q == m) return true;
        else return false;
    }
    else return false;
}

bool CE(const QVariant value, const QChar c)
{
    if (value.canConvert<QChar>())
    {
        QChar q = value.toChar();
        if (q == c) return true;
        else return false;
    }
    else return false;
}

bool CE(const QVariant value, const Token::Function p)
{
    if (value.canConvert<Token::Function>())
    {
        Token::Function q = value.value<Token::Function>();
        if (q == p) return true;
        else return false;
    }
    else return false;
}

template <typename T>
T sign(T x)
{
    if (x > 0) return 1;
    else if (x == 0) return 0;
    else if (x < 0) return -1;
}

int CompareString(QString s, QString f)
{
    int m, n, r;
    n = s.size();
    m = f.size();
    if (n != m) return sign(m - n);
    else
    {
        for (int i = 0; i < n; i++)
        {
            int t = s[i].unicode() - f[i].unicode();
            if (t == 0) continue;
            else if (t < 0) return -1;
            else if (t > 0) return 1;
        }
        return 0;
    }
}

deque<Token> exprToTokens(QString &expr, int &index, BW &C, QString q = "DEFAULT")
{
    deque<Token> tokens;
    deque<tuple<int, int>> positions;
    deque<tuple<int, int>> ks;
    if (q == "DEFAULT") index = 0;
    if (expr.isEmpty()) return tokens;
    const QChar * const c_begin = expr.constData();
    const QChar *b = &expr[0];
    int i = 0, j = 0;
    for (const QChar *p = expr.constData(); !p->isNull(); ++p, i++)
    {
        QChar Q = *p;
        char c = Q.toLatin1();
        if (Q.isSpace())
        {
            // do nothing
        }
        else if (Q.isDigit())
        {
            if (Q == '.')
            {
                int pr = -1;
                QString s = QString::fromLatin1(&c, 1);
                tokens.push_back(Token{ Token::Type::Unknown, s, index++, j, i, pr, false });
                positions.push_back(std::make_tuple(j, i));
                cout << "Недопустимая позиция точки" << endl;
            }
            Token::Type t = Token::Type::Integer;
            b = p;
            j = i;
            while (Q.isDigit() || Q == '.')
            {
                if (Q == '.') t = Token::Type::Real;
                ++p;
                ++i;
                Q = *p;
            }
            QString s = QString(b, p - b);
            if (t == Token::Type::Integer)
            {
                QString f = QString::number(INT_MAX);
                int r = CompareString(s, f);
                if (r >= 0)
                {
                    bool ok;
                    int m = s.toInt(&ok);
                    tokens.push_back(Token{ t, m , index++ , j , i });
                    positions.push_back(make_tuple(j, i));
                }
                else // Îøèáêà ñëèøêîì äëèííîå ÷èñëî , íóæíà äëèííàÿ àðèôìåòèêà.
                {
                    ks.push_back(make_tuple(j, i));
                    break;
                }
            }
            else if (t == Token::Type::Real)
            {
                if (s.size() <= 308)
                {
                    bool ok;
                    double m = s.toDouble(&ok);
                    tokens.push_back(Token{ t, m , index++ , j , i });
                    positions.push_back(make_tuple(j, i));
                }
                else // Îøèáêà ñëèøêîì äëèííîå ÷èñëî , íóæíà äëèííàÿ àðèôìåòèêà.
                {
                    ks.push_back(make_tuple(j, i));
                    break;
                }
            }
            --p;
            --i;
        }
        else if (Q.isLetter()) {
            b = p;
            j = i;
            while (Q.isLetter()) {
                ++p;
                ++i;
                Q = *p;
            }
            QString s = QString(b, p - b);
            int u_start = b - c_begin;
            int u_last = p - c_begin;
            if (func_info.contains(s)) {
                tokens.push_back(Token{ Token::Type::Function, func_name[s] , index++ , j , i });
                positions.push_back(std::make_tuple(j, i));
            }
            else {
                tokens.push_back(Token{ Token::Type::Algebra, s , index++ , j , i , -1 , false });
                positions.push_back(std::make_tuple(j, i));
            }
            p--;
            i--;
            continue;
        }
        else if (Q == ',') {
            QString s = QString::fromLatin1(&c, 1);
            tokens.push_back(Token{ Token::Type::Comma , s , index++ , i , i + 1, -1 , false });
            positions.push_back(std::make_tuple(i, i + 1));
        }
        else {
            Token::Type t = Token::Type::Unknown;
            int pr = -1;            // ïðèîðèòåò
            bool ra = false;        // rightAssociative
            bool is_operator = false;
            switch (c) {
            default:                                    break;
            case '(':   t = Token::Type::LeftParen;     break;
            case ')':   t = Token::Type::RightParen;    break;
            case '^':   is_operator = true;   break;
            case '*':   is_operator = true;    break;
            case '/':   is_operator = true;    break;
            case '+':   is_operator = true;    break;
            case '-':   is_operator = true;    break;
            }
            if (is_operator)
            {
                t = Token::Type::Operator;
                pr = operator_info[c].precedence;
                ra = !(operator_info[c].associativity == 'L');
            }
            tokens.push_back(Token{ t, Q, index++ , i , i + 1, pr , ra });
            positions.push_back(make_tuple(i, i + 1));
            while (0); // Äëÿ òî÷êè îñòàíîâà.
        }
    }
    C.position = positions;
    C.broken_pos = ks;
    if (!ks.empty()) return {};
    else return tokens;
}



deque<Token> exprToTokens(QString& expr, int& index, QString q)
{
    BW C = BW();
    deque<Token> fh = exprToTokens(expr, index, C, q);
    return fh;
}


deque<Token> exprToTokens(QString& expr, BW& C)
{
    int index = 0;
    deque<Token> fs = exprToTokens(expr, index, C, "DEFAULT");
    return fs;
}

deque<Token> exprToTokens(QString& expr)
{
    int index = 0;
    BW C = BW();
    deque<Token> fs = exprToTokens(expr, index, C, "DEFAULT");
    return fs;
}

deque<Token> exprToTokens(const string s)
{
    QString qs = QString::fromStdString(s);
    deque<Token> fh = exprToTokens(qs);
    return fh;
}

Token _SetToken(const int m)
{
    Token T = Token{ Token::Type::Integer, m };
    return T;
}

Token _SetToken(const double m)
{
    Token T = Token{ Token::Type::Real, m };
    return T;
}

Token _SetToken(const int m, int& index)
{
    Token T = Token{ Token::Type::Integer, m , index++ , 0 , 1 };
    return T;
}

Token _SetToken(const double m, int& index)
{
    Token T = Token{ Token::Type::Real, m , index++ , 0 , 1 };
    return T;
}


Token _SetToken(QString& expr, int& index)
{
    int n = expr.size();
    if (n == 1) {
        for (int i = 0; i < expr.size(); ++i) {
            QChar c = expr[i];
            if (c.isSpace()) {
                // do nothing
            }
            else if (c.isDigit()) {
                if (c == '.') {
                    int pr = -1;
                    QString s = expr.mid(i, 1);
                    Token T = Token(Token::Type::Unknown, s, index++, 0, 1, pr, false);
                    return T;
                }
                int j = i;
                Token::Type t = Token::Type::Integer;
                while (expr[j].isDigit() || expr[j] == '.') {
                    if (expr[j] == '.') t = Token::Type::Real;
                    if ( j + 1 < expr.size()) j++;
                    else break;
                }
                j++;
                QString s = expr.mid(i, j - i);
                if (t == Token::Type::Integer) {
                    int m = s.toInt();
                    Token T = Token(t, m, index++, 0, 1);
                    return T;
                }
                else if (t == Token::Type::Real) {
                    double m = s.toDouble();
                    Token T = Token(t, m, index++, 0, 1);
                    return T;
                }
                i = j - 1;
            }
            else if (isliter(c.toLatin1())) {
                int j = i;
                while (isliter(expr[j].toLatin1())) {
                    ++j;
                }
                QString s = expr.mid(i, j - i);
                if (func_info.contains(s)) {
                    Token T = Token(Token::Type::Function, func_name[s], index++, 0, 1);
                    return T;
                }
                else {
                    Token T = Token(Token::Type::Algebra, s, index++, 0, 1, -1, false);
                    return T;
                }
                i = j - 1;
            }
            else {
                Token::Type t = Token::Type::Unknown;
                int pr = -1;
                bool ra = false;
                bool is_operator = false;
                switch (c.toLatin1()) {
                default:                                    break;
                case '(':   t = Token::Type::LeftParen;     break;
                case ')':   t = Token::Type::RightParen;    break;
                case '^':   is_operator = true;             break;
                case '*':   is_operator = true;             break;
                case '/':   is_operator = true;             break;
                case '+':   is_operator = true;             break;
                case '-':   is_operator = true;             break;
                }
                if (is_operator) {
                    t = Token::Type::Operator;
                    pr = operator_info[c.toLatin1()].precedence;
                    ra = !(operator_info[c.toLatin1()].associativity == 'L');
                }
                Token T = Token(t, c, index++, pr, ra);
                return T;
            }
        }
        Token T;
        return T;
    }
    else {
        deque<Token> fs;
        fs = exprToTokens(expr, index, "ORDERING");
        Tokenize_u_minus(fs);
        Token T = fs.front();
        fs.pop_front();
        return T;
    }
}

Token _SetToken(QString& expr)
{
    int index;
    Token token = _SetToken(expr, index);
    return token;
}

Token _SetToken(QChar c, int& index)
{
    QString s = QString(1, c);
    Token token = _SetToken(s, index);
    return token;
}

Token _SetToken(QChar c)
{
    int index = 0;
    Token token = _SetToken(c, index);
    return token;
}

Token _SetToken(const Token::Function f_able)
{
    int index = 0;
    Token token = Token(Token::Type::Function, f_able, index, 0, 1);
    return token;
}

Token _SetToken(string s)
{
    QString f = QString::fromStdString(s);
    Token token = _SetToken(f);
    return token;
}

Token _SetToken(const Token::Function f_able, int& index)
{
    Token token = Token(Token::Type::Function, f_able, index, 0, 1);
    return token;
}

Token SetToken(const QVariant value)
{
    if (value.canConvert<QString>())
    {
        QString f = value.value<QString>();
        Token T = _SetToken(f);
        return T;
    }
    else if (value.canConvert<int>())
    {
        int m = value.value<int>();
        Token T = _SetToken(m);
        return T;
    }
    else if (value.canConvert<double>())
    {
        double m = value.value<double>();
        Token T = _SetToken(m);
        return T;
    }
    else if (value.canConvert<QChar>())
    {
        QChar c = value.value<QChar>();
        Token T = _SetToken(c);
        return T;
    }
    else if (value.canConvert<Token::Function>())
    {
        Token::Function f_able = value.value<Token::Function>();
        Token T = _SetToken(f_able);
        return T;
    }
}

Token SetToken(const QVariant& value, int& index) {
    if (value.type() == QVariant::String) {
        QString f = value.toString();
        Token T = _SetToken(f, index);
        return T;
    }
    else if (value.type() == QVariant::Int) {
        int m = value.toInt();
        Token T = _SetToken(m, index);
        return T;
    }
    else if (value.type() == QVariant::Double) {
        double m = value.toDouble();
        Token T = _SetToken(m, index);
        return T;
    }
    else if (value.type() == QVariant::Char) {
        QChar c = value.toChar();
        Token T = _SetToken(c, index);
        return T;
    }
    else if (value.type() == QVariant::UserType) {
        Token::Function f_able = qvariant_cast<Token::Function>(value);
        Token T = _SetToken(f_able, index);
        return T;
    }
}

bool operator == (Token& C, Token& S)
{
    if (C.value == S.value) return true;
    else return false;
}

void Tokenize_u_minus(deque<Token>& fh) {
    const bool LOCAL_DEBUG = false;
    QString patthern = "(-";
    deque<Token>::iterator iter[2];
    QVector<int> entries;
    iter[0] = iter[1] = fh.begin();
    int n = fh.size();
    if (n >= 2) iter[1]++;
    else return;
    int i = 0;
    while (iter[1] != fh.end())
    {

        Token& T_0 = *(iter[0]);
        Token& T_1 = *(iter[1]);
        if (T_0.type == Token::Type::LeftParen)
            if (T_1.type == Token::Type::Operator)
                if (T_1.value.toChar() == '-') entries.push_back(i);
        iter[0] = iter[1];
        iter[1]++;
        i++;
    }
    while (0); // Äëÿ òî÷êè îñòàíîâà.

    if (n >= 4) // Èùåì (-a) è çàìåíÿåì íà ðåçóëüòàò (-1)*a , ãäå à - ÷èñëî.
    {
        QString f, r;
        if (DEBUG) f = TokensToStr(fh);
        reverse(entries.begin(), entries.end()); // Íà÷èíàåì ñ ïîñëåäíåãî , ÷òîáû íå êîððåêòèðîâàòü èíäåêñû ïðè óäàëåíèè.
        for (int p : entries)
        {
            Token& T_0 = fh[p + 3];
            Token& T_1 = fh[p + 2];
            if (T_0.type == Token::Type::RightParen)
            {
                if (T_1.type == Token::Type::Number || T_1.type == Token::Type::Integer || T_1.type == Token::Type::Real)
                {
                    double q = -1;
                    if (T_1.type == Token::Type::Integer)
                    {
                        q =  (double)T_1.value.toInt();
                        q = (-1) * q;
                    }
                    else if (T_1.type == Token::Type::Real)
                    {
                        q = T_1.value.toDouble();
                        q = (-1) * q;
                    }
                    const deque<Token>::iterator start = fh.begin();
                    Token T_2 = _SetToken(q);
                    if (LOCAL_DEBUG) r = TokensToStr(fh);
                    f = r;
                    if (LOCAL_DEBUG) {
                        const Token T_3 = *(start + p);
                        const Token T_4 = *(start + p + 4);
                        deque<Token> eh = fh;
                        while (0); // Äëÿ òî÷êè îñòàíîâà.
                    }
                    if (LOCAL_DEBUG)
                    {
                        deque<Token> ls;
                        copy(fh.begin(), fh.end(), back_inserter(ls));
                        deque<Token>::iterator iter;
                        int i, j;
                        int m = fh.size();
                        for (iter = fh.begin(), i = 0; iter != fh.end(); iter++, i++) { cout << i << ":" << *(iter) << endl; }
                        r = TokensToStr(fh);
                        tie(i, j) = make_pair(16, 19); // Äàííûå äëÿ îòëàäêè
                        Token T_5 = *(start + i);
                        Token T_6 = *(start + j);
                        ls.erase(start + i, start + j); //
                        QString f = TokensToStr(ls);
                        int l = 5;
                        for (i = 0; i < m - l - 1; i++)
                        {
                            deque<Token> lh;
                            copy(fh.begin(), fh.end(), back_inserter(lh));
                            lh.erase(start + i, start + i + l);
                            f = TokensToStr(lh);
                            cout << qPrintable(f) << endl;
                        }
                        while (0);
                    }
                    fh.erase(start + p, start + p + 4); //
                    if (LOCAL_DEBUG) r = TokensToStr(fh);
                    f = r;
                    fh.insert(fh.begin() + p, T_2); // fh.insert(start + p, T_2);
                    if (LOCAL_DEBUG) r = TokensToStr(fh);
                    f = r;
                }
                else if (T_1.type == Token::Type::Algebra)
                {
                    const deque<Token>::iterator start = fh.begin();
                    if (LOCAL_DEBUG) {
                        const Token T_3 = *(start + p);
                        const Token T_4 = *(start + p + 4);
                        deque<Token> eh = fh;
                        while (0); // Äëÿ òî÷êè îñòàíîâà.
                    }
                    fh.erase(start + p - 1, start + p + 4 - 1);
                    if (LOCAL_DEBUG) r = TokensToStr(fh);
                    f = r;
                    deque<Token> es = exprToTokens("(-1)*a");
                    es.pop_back();
                    es.push_back(T_1);
                    fh.insert(fh.begin() + p, T_1);
                    if (LOCAL_DEBUG) r = TokensToStr(fh);
                    f = r;
                }
            }
        }
    }
    n = fh.size();
    if (n >= 2)
    {
        Token& T_0 = fh.front();
        Token& T_1 = fh[1];
        if (T_0.type == Token::Type::Operator)
        {
            if (T_0.value.toChar() == '-')  // Ýòîò ñëó÷àé íå ïåðåñåêàåòñÿ ñ ïðåäûäóùèì ñëó÷àåì.
            {   // Ñëó÷àé êîãäà óíàðíûé ìèíóñ ñòîèò â íà÷àëå ñòðîêè.
                QString f, r;
                if (T_1.type == Token::Type::Number || T_1.type == Token::Type::Integer || T_1.type == Token::Type::Real)
                {
                    fh.pop_front();
                    fh.pop_front();
                    double m = -1;
                    if (T_1.type == Token::Type::Integer)
                    {
                        m = (double)T_1.value.toInt();
                    }
                    else if (T_1.type == Token::Type::Real)
                    {
                        m = T_1.value.toDouble();
                    }
                    m = (-1) * m;
                    Token T_2 = _SetToken(m);
                    fh.insert(fh.begin(), T_2); // Äîáàâëåíèå âïåðåä î÷åðåäè.
                    if (LOCAL_DEBUG) r = TokensToStr(fh);
                    f = r;
                }
                else if (T_1.type == Token::Type::Algebra)
                {
                    fh.pop_front();
                    deque<Token> es = exprToTokens("(-1)*a");
                    es.pop_back();
                    es.push_back(T_1); //
                    fh.insert(fh.begin(), T_1);
                    if (LOCAL_DEBUG) r = TokensToStr(fh);
                    f = r;
                }
            }
        }
    }
}




QString TokensToStr(const deque<Token> fh)
{
    QString s = "";
    for (Token token : fh)
    {
        if (token.type == Token::Type::Algebra) {
            QString f = token.value.toString();
            s = s + f;
        }
        else if (token.type == Token::Type::Integer) {
            int m = token.value.toInt();
            s = s + QString::number(m);
        }
        else if (token.type == Token::Type::Real) {
            double m = token.value.toDouble();
            s = s + QString::number(m);
        }
        else if (token.type == Token::Type::Operator) {
            QChar c = token.value.toChar();
            s = s + c;
        }
        else if (token.type == Token::Type::Function)
        {
            Token::Function p = token.value.value<Token::Function>();
            QString f = rfunc_name[p];
            s = s + f;
        }
    }
    return s;
}
