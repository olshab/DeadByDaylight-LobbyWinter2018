#include "PathStrategy.h"

UPathStrategy::UPathStrategy()
{
	this->DefaultPathBuilders = TArray<UPathBuilder*>();
	this->RefreshPartialPathDelay = 3.000000;
	this->StartNextBranchBuildDelay = 0.500000;
	this->MaxActiveTimeSeconds = -1.000000;
	this->StrategyEndCooldownSeconds = -1.000000;
	this->_aiOwner = NULL;
	this->_pathBuilders = TArray<UPathBuilder*>();
}
