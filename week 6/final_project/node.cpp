#include "node.h"
#include "database.h"

bool EmptyNode::Evaluate(const Date &date, const std::string &event) const {
    return true;
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &l,
        const std::shared_ptr<Node> &n1,
        const std::shared_ptr<Node> &n2) : Node(), logicalOperation(l), n(n1), expr(n2)
        {}
DateComparisonNode::DateComparisonNode(const Comparison &c, const Date &d) : Node(d), cmp(c) {}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const {
    switch (logicalOperation) {
        case LogicalOperation::And:
            return n->Evaluate(date, event) && expr->Evaluate(date, event);
        case LogicalOperation::Or:
            return n->Evaluate(date, event) || expr->Evaluate(date, event);
    }
}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    switch (cmp) {
        case Comparison::Less:
            return date < date_;
        case Comparison::LessOrEqual:
            return date < date_ || date == date_;
        case Comparison::Greater:
            return date_ < date;
        case Comparison::GreaterOrEqual:
            return date_ < date || date_ == date;
        case Comparison::Equal:
            return date_ == date;
        case Comparison::NotEqual:
            return !(date_ == date);
    }
}

EventComparisonNode::EventComparisonNode(const Comparison &c, const std::string &val) : Node(Date(1,1,1), val), cmp(c) {}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    switch (cmp) {
        case Comparison::Equal:
            return event == event_;
        case Comparison::NotEqual:
            return event_ != event;
        case Comparison::GreaterOrEqual:
            return event >= event_;
        case Comparison::Greater:
            return event > event_;
        case Comparison::LessOrEqual:
            return event <= event_;
        case Comparison::Less:
            return event < event_;
    }
    return false;
}
