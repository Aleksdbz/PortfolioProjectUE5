
#include "PortfolioProjectCharacter.h"
#include "Engine/LocalPlayer.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Logging/LogMacros.h"
#include "Animation/AnimInstance.h"
#include "MyGameplayAbility.h"
#include "GameplayEffect.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameplayTagContainer.h"
#include "MyAttributeSet.h"
#include "MyEnhancedInputComponent.h"
#include "MyGameplayTags.h"
#include "PortfolioProject/ProjectPlayerState.h"
#include "PortfolioProject/Items/Sword.h"


struct FMyGameplayTags;
DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APortfolioProjectCharacter

APortfolioProjectCharacter::APortfolioProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited tent references in C++)

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystem");
	AttributesSet = CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");

	
}



void APortfolioProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	AttributesSet->SetMaxHealth(1500.0f);
	AttributesSet->SetHealth(1500.0f);
	
	
	//InitializeAttributes();
	EquipSword();
	MappingContext();
	GrandAbilities();
	
		
}


void APortfolioProjectCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

/**
void APortfolioProjectCharacter::InitializeAttributes()
{
	//APPLY GE or AbilitySystemComp to a Character
	if(DefaultGameplayEffect)
	{
		FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec
		(DefaultGameplayEffect,1,EffectContextHandle);

		if(SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->
			ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
		
	}
	
}

**/

void APortfolioProjectCharacter::GrandAbilities()
{
	for(TSubclassOf<UGameplayAbility> StartAbilities : GameplayAbility)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartAbilities, 1);
		
		if(const UMyGameplayAbility* Ability = Cast<UMyGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(Ability->StartupInputTag);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

void APortfolioProjectCharacter::MappingContext()
{
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APortfolioProjectCharacter::EquipSword()
{
	
	Sword = GetWorld()->SpawnActor<ASword>(SwordClass);
	Sword->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("hand_rSocket"));
	Sword->SetOwner(this);
	Sword->StaticMeshComp->IgnoreActorWhenMoving(this,true);
}

UE5Coro::TCoroutine<> APortfolioProjectCharacter::StartAttack(UAnimMontage* Montage)
{
	isAttacking = true;

	UAnimInstance* AnimInstance = GetAnimInstance();
	AnimInstance->Montage_Play(Montage);
	co_await UE5Coro::Anim::MontageEnded(AnimInstance,Montage);
	isAttacking = false;
	co_return;
}
UAnimInstance* APortfolioProjectCharacter::GetAnimInstance() const
{
	return GetMesh()->GetAnimInstance();
}


void APortfolioProjectCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AProjectPlayerState* State = GetPlayerState<AProjectPlayerState>();
	check(State)
	State->GetAbilitySystemComponent()->InitAbilityActorInfo(State,this);
	AbilitySystemComponent = State->GetAbilitySystemComponent();
}

void APortfolioProjectCharacter::Move(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
void APortfolioProjectCharacter::Look(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
void APortfolioProjectCharacter::StopBlock(const FInputActionValue& Value)
{
	
}
void APortfolioProjectCharacter::StartBlock(const FInputActionValue& Value)
{
	
}
void APortfolioProjectCharacter::StartLightAttack(const FInputActionValue& Value)
{
	if(isAttacking) return;
	UAnimMontage* Montages[3] = {SwordAttack,SwordAttack2,SwordAttack3};
	ComboCount = (ComboCount + 1) % 3;
	StartAttack(Montages[ComboCount]);
}
void APortfolioProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UMyEnhancedInputComponent* MyEnhancedInputComponent = Cast<UMyEnhancedInputComponent>(PlayerInputComponent);
	check(MyEnhancedInputComponent);
	const FMyGameplayTags& GameplayTags = FMyGameplayTags::Get();

	MyEnhancedInputComponent->BindActionByTag(InputConfig,GameplayTags.InputTag_LightAttack,ETriggerEvent::Triggered,
		this,&APortfolioProjectCharacter::StartLightAttack);

	MyEnhancedInputComponent->BindActionByTag(InputConfig,GameplayTags.InputTag_Move,ETriggerEvent::Triggered,
		this,&APortfolioProjectCharacter::Move);

	MyEnhancedInputComponent->BindActionByTag(InputConfig,GameplayTags.InputTag_Look_Mouse,ETriggerEvent::Triggered,
		this,&APortfolioProjectCharacter::Look);
	
	MyEnhancedInputComponent->BindActionByTag(InputConfig,GameplayTags.InputTag_Jump,ETriggerEvent::Triggered,
		this,&APortfolioProjectCharacter::Jump);
	
	
}



