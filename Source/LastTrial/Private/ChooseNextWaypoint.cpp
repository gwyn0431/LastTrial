// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Public/PatrollingGuard.h" // TODO remove coupling

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO protect against empty patrol routes

	// Get Patrol Points
	auto AIController = OwnerComp.GetAIOwner();
	auto PatrollingGuard = Cast<APatrollingGuard>(AIController->GetPawn());
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	// Set Next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();	
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]); 

	// Cycle Index
	Index = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}
