// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Public/PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the patrol route
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRouteComponent = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	
	TArray<AActor*> PatrolPoints;
	if (!ensure(PatrolRouteComponent)) 
	{ 
		return EBTNodeResult::Failed;
	}

	PatrolPoints = PatrolRouteComponent->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Patrol Points"))
		return EBTNodeResult::Failed;
	}

	// Set Next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle Index
	Index = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);
	
	

	

	return EBTNodeResult::Succeeded;
}
