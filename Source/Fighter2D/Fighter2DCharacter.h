// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "AbilitySystemInterface.h"
#include "Fighter2DCharacter.generated.h"


enum CharacterState
{
	CHARACTER_JUMP,
	CHARACTER_FALL,
	CHARACTER_WALK,
	CHARACTER_RUN,
	CHARACTER_KICK,
	CHARACTER_IDLE
};

class UTextRenderComponent;
/**
 * This class is the default character for Fighter2D, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */
UCLASS(config=Game)
class AFighter2DCharacter : public APaperCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;

	//Get FPS
	//UFUNCTION(BlueprintCallable, Category = "FPS")
	UFUNCTION(BlueprintPure, Category = "FPS")
		float UpdateFPS();
	//UFUNCTION(BlueprintCallable, Category = "FPS")
	UFUNCTION(BlueprintPure, Category = "CharacterVelocity")
		float UpdateVx();
	//UFUNCTION(BlueprintCallable, Category = "FPS")
	UFUNCTION(BlueprintPure, Category = "CharacterVelocity")
		float UpdateVy();

private:
	UPROPERTY(EditAnywhere, Category = "FPS")
		float fps;
	//Check Character is On Air
	
	enum CharacterState characterState;

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	// The animation to play while jump 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpAnimation;
	
	// The animation to play while fall
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* FallAnimation;

	// The animation to play while kcik1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* Kick1Animation;
	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Called for Kick (K Key) input */
	void OnKick();

	void UpdateCharacter();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
	UPROPERTY()
		UWorld* World;
public:
	AFighter2DCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	/** ability system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystem;
	UAbilitySystemComponent* GetAbilitySystemComponent() const
	{
		return AbilitySystem;
	};
	/** ability list */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
		TArray<TSubclassOf<class UGameplayAbility>> AbilityList;

	/** BeginPlay, PossessedBy override */
	//virtual void BeginPlay() override;
	//virtual void PossessedBy(AController* NewController) override;
};
