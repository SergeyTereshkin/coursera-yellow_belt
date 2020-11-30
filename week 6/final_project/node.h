#pragma once
#include "date.h"
#include <iostream>


enum class LogicalOperation {
    Or,
    And
};

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

class Node {
public:
    Node(const Date &date = Date(1, 1, 1), const std::string &event = "") : date_(date), event_(event) {}
    virtual bool Evaluate(const Date& date, const std::string& event) const=0;
    const Date date_;
    const std::string event_;
};

class EmptyNode : public Node {
public:
    EmptyNode() : Node() {}
    bool Evaluate(const Date& date, const std::string& event) const override;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& l, const std::shared_ptr<Node>& n1, const std::shared_ptr<Node>& n2);
    bool Evaluate(const Date& date, const std::string& event) const override;
private:
    LogicalOperation logicalOperation;
    std::shared_ptr<Node> n;
    std::shared_ptr<Node> expr;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& c, const Date& d);
    bool Evaluate(const Date& date, const std::string& event) const override;
private:
    Comparison cmp;
    Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& c, const std::string& val);
    bool Evaluate(const Date& date, const std::string& event) const override;
private:
    Comparison cmp;
    const std::string value;
};
