#ifndef APYTHONINTERPRETER_STATEMENTS_HPP
#define APYTHONINTERPRETER_STATEMENTS_HPP

#include <iostream>
#include <vector>

#include "ExprNode.hpp"
#include "SymTab.hpp"
// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.


class Statement {
public:
    Statement();

    virtual void print() = 0;
    virtual void evaluate(SymTab &symTab) = 0;
};

// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.
class Statements {
public:
    Statements();

    void addStatement(Statement *statement);
    void evaluate(SymTab &symTab);
    void print();
private:
    std::vector<Statement *> _statements;
};


// AssignmentStatement represents the notion of an lValue having been assigned an rValue.
// The rValue is an expression.

class AssignmentStatement : public Statement {
public:
    AssignmentStatement();
    AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr);

    std::string &lhsVariable();
    ExprNode *&rhsExpression();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::string _lhsVariable;
    ExprNode *_rhsExpression;
};

// Prints the evaluated variable name stored as a string 
class PrintStatement : public Statement {
    public:
        PrintStatement();

        PrintStatement(std::string value);

        void print();

        void evaluate(SymTab &symTab);

    private:
        std::string _value;
};
// Runs for loop of all needed values within the statement
// if: _statements contains any statements, then those will run in a recursive manner.

class ForStatement : public Statement {
    public:
        ForStatement();
        
        ForStatement(AssignmentStatement *firstAssign, AssignmentStatement *secondAssign, ExprNode *relExpr, 
        
        Statements *statements);

        void print();

        void evaluate(SymTab & symTab);

    private:
        AssignmentStatement *_firstAssign;
        AssignmentStatement *_secondAssign;
        ExprNode *_relExpr;
        Statements *_statements;  
};








#endif //APYTHONINTERPRETER_STATEMENTS_HPP
