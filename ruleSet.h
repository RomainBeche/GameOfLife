#ifndef RULE_SET_H
#define RULE_SET_H
#include "cellState.h"

class RuleSet {
public:
    virtual ~RuleSet() = default;
    virtual CellState* calculateNextState(bool currentlyAlive, int neighbors) = 0;
};

#endif // ruleSet.h