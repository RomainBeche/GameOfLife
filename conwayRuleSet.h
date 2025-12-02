#ifndef CONWAY_RULE_SET_H
#define CONWAY_RULE_SET_H
#include "ruleSet.h"

class ConwayRuleSet : public RuleSet {
public:
    CellState* calculateNextState(bool currentlyAlive, int neighbors) override;
};

#endif // conwayRuleSet.h
