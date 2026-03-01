// Scientific Ways

#include "Tags/ScWCoreTags.h"

//#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWCoreTags)

namespace FScWCoreTags
{
	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TestTag : AllTags)
			{
				if (TestTag.ToString().Contains(TagString))
				{
					UE_LOG(LogScWGameCore, Display, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
					Tag = TestTag;
					break;
				}
			}
		}
		return Tag;
	}
	// Object init states
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_Spawned, "InitState.Spawned", "1: Actor/component has initially spawned and can be extended");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_DataAvailable, "InitState.DataAvailable", "2: All required data has been loaded/replicated and is ready for initialization");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_DataInitialized, "InitState.DataInitialized", "3: The available data has been initialized for this actor/component, but it is not ready for full gameplay");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InitState_GameplayReady, "InitState.GameplayReady", "4: The actor/component is fully ready for active gameplay");

	// Ability state events
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Event_Added, "Ability.Event.Added", "[Native] Ability add to owner event.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Event_Removed, "Ability.Event.Removed", "[Native] Ability remove from owner event.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Event_Activated, "Ability.Event.Activated", "[Native] Ability activation event.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Event_Commited, "Ability.Event.Commited", "[Native] Ability commit event.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Event_Failed, "Ability.Event.Failed", "[Native] Ability failure event.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Event_Ended, "Ability.Event.Ended", "[Native] Ability end event.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Event_Ended_Cancelled, "Ability.Event.Ended.Cancelled", "[Native] Ability cancel event.");

	// Ability activate failure modes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_CanActivate, "Ability.ActivateFail.CanActivate", "[Native] Ability failed to activate because can activate check was not passed.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_Cooldown, "Ability.ActivateFail.Cooldown", "[Native] Ability failed to activate because it is on cool down.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_Cost, "Ability.ActivateFail.Cost", "[Native] Ability failed to activate because it did not pass the cost checks.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_GameMode, "Ability.ActivateFail.GameMode", "[Native] Ability failed to activate because game mode is blocking it.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_TagsBlocked, "Ability.ActivateFail.TagsBlocked", "[Native] Ability failed to activate because tags are blocking it.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_TagsMissing, "Ability.ActivateFail.TagsMissing", "[Native] Ability failed to activate because tags are missing.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_Networking, "Ability.ActivateFail.Networking", "[Native] Ability failed to activate because it did not pass the network checks.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_ActivationGroup, "Ability.ActivateFail.ActivationGroup", "[Native] Ability failed to activate because of its activation group.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_ActivateFail_OwnerDead, "Ability.ActivateFail.OwnerDead", "[Native] Ability failed to activate because its owner is dead.");

	// Ability general behaviors
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Behavior_IgnoreDeath, "Ability.Behavior.IgnoreDeath", "[Native] An ability with this type tag should not be canceled due to death.");

	// Character types
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_Type_Player, "Character.Type.Player", "[Native] Should be used to define AbilitySystem owner as player");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_Type_NPC, "Character.Type.NPC", "[Native] Should be used to define AbilitySystem owner as NPC");

	// Character movement
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementFlag, "Character.MovementFlag", "[Native] Character movement mode flag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementFlag_OrientRotationToMovement, "Character.MovementFlag.OrientRotationToMovement", "[Native] Character movement mode flag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementFlag_BlockOrientRotationToMovement, "Character.MovementFlag.BlockOrientRotationToMovement", "[Native] Character movement mode flag.");

	// Character movement modes
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementMode, "Character.MovementMode", "[Native] Used to check for any movement mode tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementMode_None, "Character.MovementMode.None", "[Native] Character movement mode tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementMode_Walking, "Character.MovementMode.Walking", "[Native] Character movement mode tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementMode_Walking_Nav, "Character.MovementMode.Walking.Nav", "[Native] Character movement mode tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementMode_Falling, "Character.MovementMode.Falling", "[Native] Character movement mode tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementMode_Swimming, "Character.MovementMode.Swimming", "[Native] Character movement mode tag.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_MovementMode_Flying, "Character.MovementMode.Flying", "[Native] Character movement mode tag.");

	// Input
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Movement, "Input.Movement", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Look, "Input.Look", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Look_Mouse, "Input.Look.Mouse", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Look_Stick, "Input.Look.Stick", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Ability_Pressed, "Input.Ability.Pressed", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Ability_Released, "Input.Ability.Released", "[Native] TODO: Add description");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Block, "Input.Block", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Block_Movement, "Input.Block.Movement", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Block_Look, "Input.Block.Look", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Input_Block_Ability, "Input.Block.Ability", "[Native] TODO: Add description");

	// Camera
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Camera_Type_FirstPerson, "Camera.Type.FirstPerson", "[Native] TODO: Add description");

	// Collisions
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collision, "Collision", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Collision_None, "Collision.None", "[Native] TODO: Add description");

	//UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayEvent_Death, "GameplayEvent.Death", "[Native] Event that fires on death. This event only fires on the server.");
	//UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayEvent_Reset, "GameplayEvent.Reset", "[Native] Event that fires once a player reset is executed.");
	//UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayEvent_RequestReset, "GameplayEvent.RequestReset", "[Native] Event to request a player's pawn to be instantly replaced with a new one at a valid spawn location.");

	// Set by caller
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(SetByCaller_Duration, "SetByCaller.Duration", "[Native] SetByCaller tag used by gameplay effects with custom duration.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(SetByCaller_Magnitude, "SetByCaller.Magnitude", "[Native] SetByCaller tag used by gameplay effects with custom magnitude.");

	// Cheats
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Cheat_NoTarget, "Cheat.NoTarget", "[Native] NoTarget cheat is active on the owner.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Cheat_Invulnerable, "Cheat.Invulnerable", "[Native] Invulnerable cheat is active on the owner.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Cheat_UnlimitedHealth, "Cheat.UnlimitedHealth", "[Native] UnlimitedHealth cheat is active on the owner.");

	// Capability states
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_State_Dead, "Character.State.Dead", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_State_Dead_Started, "Character.State.Dead.Started", "[Native] Owner is dead but not yet destroyed (most likely to be destroyed in the next tick).");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_State_Dead_Finished, "Character.State.Dead.Finished", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_State_Stunned, "Character.State.Stunned", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_State_Ragdoll, "Character.State.Ragdoll", "[Native] TODO: Add description");

	// Damage states
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_State_IgnoreAnyDamage, "Character.State.IgnoreAnyDamage", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_State_BlockAnyDamage, "Character.State.BlockAnyDamage", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Character_State_EvadeAnyDamage, "Character.State.EvadeAnyDamage", "[Native] TODO: Add description");

	// Cues
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayCue_Damage_Impact, "GameplayCue.Damage.Impact", "[Native] TODO: Add description");

	// Teams
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Team_None, "Team.None", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Team_Player, "Team.Player", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Team_Enemy, "Team.Enemy", "[Native] TODO: Add description");

	// Messages
	//UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayMessage_Pawn_Ready, "GameplayMessage.Pawn.Ready", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayMessage_Ability_ActivateFail_PlayMontage, "GameplayMessage.Ability.ActivateFail.PlayMontage", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayMessage_Ability_ActivateFail_UserFacingSimple, "GameplayMessage.Ability.ActivateFail.UserFacingSimple", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayMessage_Damage, "GameplayMessage.Damage", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayMessage_Damage_Ignored, "GameplayMessage.Damage.Ignored", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayMessage_Damage_Blocked, "GameplayMessage.Damage.Blocked", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayMessage_Damage_Evaded, "GameplayMessage.Damage.Evaded", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayMessage_Damage_Applied, "GameplayMessage.Damage.Applied", "[Native] TODO: Add description");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(GameplayMessage_Died, "GameplayMessage.Died", "[Native] TODO: Add description");
}
