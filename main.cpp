#include <QCoreApplication>
#include "Algebra.h"
#include "Algebra_node.h"
#include "Shunting_yard.h"
#include "Algebra.h"
#include "Derivate.h"
#include "simplify.h"
#define DEBUG 1


QString examples_1[12] = { "(1+3/4)^2*(1-5/7*4/11)*2+(1+5/6)" ,
                          "4*(3+7)^2" ,
                          "2*6/(3+4/5)*(1-2/(3+4/5-9/71)+7/9-7/23)^2",
                          "cos(1)*sin(2)",
                          "arcsin(11/679)",
                          "arccos(5/17)" ,
                          "arctg(1 + exp(3^2))",
                          "tg(11*Pi/16)" ,
                          "sin(Pi/4)*cos(Pi/6)*sin(Pi/6)",
                          "log(16 , 64)",
                          "ln(2+1/901)",
                          "ln(3/4+8/91)*6/7*(1+7/29)/(1+tg(3/4*Pi)*9/13*(3/4-8/11)^2)"
};

QString examples_3[12] = { "x" ,
                      "x^2" ,
                      "1+x+x^2",
                     "x*tg(x)" ,
                     "x^2/(x*sin(x)+1)^2" ,
                     "(x+2*(7/19+6*x*(x+1) ))/(2/7+x^2*(x-1)+(x-4)^2*(x+3) )" ,
                     "sh(x)/(1+3*ch(x))",
                     "arcsin(1/(1+3*x^2))" ,
                     "x*(x^2+x*sin(x))^2 + x*(x-1)/(x+2)" ,
                     "x^5+x^4+x^3+x^2+1" ,
                     "sin(x)*cos(2*x)*(3*sin(x/2)-5*cos(x/2))" ,
                     "x/(x^2+3*tg(x))^2"
                   };

void task_1()
{
    std::cout << "Enter a numerical expression" << std::endl;
    std::cout << "If you want us to show an example of a function, introduce -man" << std::endl;
    QString s;
    QTextStream stream(stdin);
    stream >> s;
    while (0);
    if (s == "-man")
    {
        int m = examples_1->size();
        int r = std::rand() % m;
        s = examples_1[r];
        std::cout << "Example of a function for calculating a derivate function : " << std::endl;
        std::cout << qPrintable(s) << std::endl;
    }
    {
        std::deque<Token> fh = FToPolish(s);
        if (!IsNumeric(fh)) PrintColorText("Expression is not numeric", Qt::red);
        else
        {
            double r = PolishCalculation(fh);
            std::cout << "The value of this expression is : " << r << std::endl;
        }
    }

}

void task_2()
{
    std::cout << "Enter an expression to show it as a tree." << std::endl;
    std::cout << "If you want us to show an example of a function, introduce -man" << std::endl;
    QString s;
    QTextStream stream(stdin);
    stream >> s;
    if (s == "-man")
    {
        int m = examples_3->size();
        int r = std::rand() % m;
        s = examples_3[r];
        std::cout << "Example of a function for calculating a derivate function : " << std::endl;
        std::cout << qPrintable(s) << std::endl;
    }
    {
        Algebra_Node* root = SetOperatorTree(s);
        Print_Tree_R(root , std::string("") , true , true);
    }
}

void task_3()
{
    std::cout << "Enter the function for diphrency" << std::endl;
    std::cout << "If you want us to show an example of a function, introduce -man" << std::endl;
    QString s;
    QTextStream stream(stdin);
    stream >> s;
    while (0);
    if (s == "-man")
    {
        int m = examples_3->size();
        int r = std::rand() % m;
        s = examples_3[r];
        std::cout << "Example of a function for calculating a derivate function : " << std::endl;
        std::cout << qPrintable(s) << std::endl;
    }
    {
        std::deque<Token> fh = FToPolish(s);
        Algebra_Node* root = PolishToTree(fh);
        Algebra_Node* second_root = DerivateFunction(root);
        std::deque<Token> fs;
        TreeToPolish(second_root, fs);
        QString f = PostfixToInfix(fs);
        std::cout << "The expression for the derivative of the function is" << std::endl;
        std::cout << qPrintable(f) << std::endl;
        RecursiveDestructor(root);
        RecursiveDestructor(second_root);
        while (0);
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString tasks[] = { "1 : CALCULATOR" , "2 : SHOW_OPERATOR_TREE"  , "3 : CALC_DERIVATE"};
    if(DEBUG) Verify();
    else
    {
        int n = tasks->size();
        std::cout << "Select a task number from 1 to 3 and enter number:" << std::endl;
        for (QString s : tasks)
        {
            std::cout << qPrintable(s) << std::endl;
        }
        int p;
        std::cin >> p;
        switch (p)
        {
        case 1: { task_1(); break; }
        case 2: { task_2(); break; }
        // case 3: { task_3(); break; }
        }

    }
    return a.exec();
}
