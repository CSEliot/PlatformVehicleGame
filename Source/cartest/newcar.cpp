// Fill out your copyright notice in the Description page of Project Settings.

#include "cartest.h"
#include "GravityRegion.h"
#include "newcar.h"


// Sets default values
Anewcar::Anewcar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ASSUMING DIRECT CONTROL.
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	Gravity = FVector(0.1f, 0.1f, -1960.0f);

	AccelRate = 500.0f;
	MaxVelocity = 3000.0f;
	JumpPower = 2000.0f;
	TurnRate = 0.5f;

	Root = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	Root->OnComponentBeginOverlap.AddDynamic(this, &Anewcar::Hit);
	Root->OnComponentHit.AddDynamic(this, &Anewcar::Stay);
	Root->OnComponentEndOverlap.AddDynamic(this, &Anewcar::UnHit);
	Root->AttachTo(RootComponent);

	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	Model->AttachTo(Root);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->AttachTo(Root);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(SpringArm);

	Up = CreateDefaultSubobject<UArrowComponent>(TEXT("Up"));
	Up->SetRelativeRotation(FVector::UpVector.Rotation());
	Up->AttachTo(Root);

	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Forward"));
	Forward->SetRelativeRotation(FVector::ForwardVector.Rotation());
	Forward->AttachTo(Root);

	Right = CreateDefaultSubobject<UArrowComponent>(TEXT("Right"));
	Right->SetRelativeRotation(FVector::RightVector.Rotation());
	Right->AttachTo(Root);
}

void Anewcar::UnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
	}
}

void Anewcar::Stay(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		// Get out mah way!
		if (OtherComp->IsSimulatingPhysics()) {
			//float scalefactor = FVector::VectorPlaneProject(CapsuleComponent->GetPhysicsLinearVelocity(), FVector::UpVector).Size() / PhysicsSettings.MaxVelocity;
			//scalefactor = (scalefactor > 1.0f ? FMath::Pow(scalefactor, PhysicsSettings.HighVelocityForceExponent) : 1.0f);
			//OtherComp->AddImpulse((OtherComp->GetComponentLocation() - GetActorLocation()).GetSafeNormal()*scalefactor*PhysicsSettings.PushForceFactor, NAME_None, true);
		}
	}
}

void Anewcar::Hit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Stop hitting yourself.
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (OtherActor->IsA(AGravityRegion::StaticClass())) {
			Gravity = ((AGravityRegion*)OtherActor)->GravityDirection->GetForwardVector()*((AGravityRegion*)OtherActor)->GravityStrength;
		}
	}
}

// Called when the game starts or when spawned
void Anewcar::BeginPlay()
{
	Super::BeginPlay();

	if (First != nullptr) {
		Gravity = First->GravityDirection->GetForwardVector()*First->GravityStrength;
	}
}

// Called every frame
void Anewcar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TurnInput = TurnInput.GetSafeNormal();

	//AddActorWorldRotation(FQuat::FindBetween(Up->GetForwardVector(), (-Gravity).GetSafeNormal()).GetNormalized());
	AddActorWorldRotation(FQuat::Slerp(FQuat::Identity, FQuat::FindBetween(Up->GetForwardVector(), (-Gravity).GetSafeNormal()).GetNormalized(),DeltaTime*4.0f));

	//AddActorLocalRotation(FRotator(0.0f, TurnInput.X*2.0f*PI*TurnRate, 0.0f));
	Root->AddTorque(Up->GetForwardVector()*TurnInput.X*360.0f*TurnRate, NAME_None, true);

	TArray<FHitResult> out;

	OnTheGround = false;
	if (GetWorld()->SweepMultiByChannel(out, GetActorLocation(), GetActorLocation() + Gravity.GetSafeNormal()*50.0f, GetActorQuat(), ECC_Visibility, FCollisionShape::MakeCapsule(44.0f, 44.0f))) {
		OnTheGround = true;
	}

	if (JumpNextFrame) {
		Root->AddImpulse((-Gravity).GetSafeNormal()*JumpPower, NAME_None, true);
	}

	Root->AddForce(Forward->GetForwardVector()*AccelRate, NAME_None, true);
	//Root->AddForce(Forward->GetRightVector()*AccelRate*10.0f*StrafeInput.X, NAME_None, true);

	FVector Velocity2D = Root->GetPhysicsLinearVelocity().ProjectOnTo(Forward->GetForwardVector());// FVector::VectorPlaneProject(Root->GetPhysicsLinearVelocity(), (-Gravity).GetSafeNormal());
	Root->AddForce(-Velocity2D.GetSafeNormal()*AccelRate*FMath::Pow((Velocity2D.Size() / MaxVelocity),16.0f), NAME_None, true);

	Velocity2D = Root->GetPhysicsLinearVelocity().ProjectOnTo(Right->GetForwardVector());
	Root->AddForce(-Velocity2D.GetSafeNormal()*AccelRate*FMath::Clamp(FMath::Pow((Velocity2D.Size() / (MaxVelocity/4.0f)), 4.0f),0.0f,999999.9f), NAME_None, true);

	if (!OnTheGround) {
		Root->AddForce(Gravity, NAME_None, true);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 999, FColor::Green, Gravity.ToString());

	SpringArm->SetRelativeRotation(FRotator(-30.0f,0.0f,0.0f));//

	JumpNextFrame = false;
}

// Called to bind functionality to input
void Anewcar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("Turn", this, &Anewcar::Turn);
	//InputComponent->BindAxis("Strafe", this, &Anewcar::Turn);
	InputComponent->BindAction("Jump", IE_Pressed, this, &Anewcar::Jump);
}

void Anewcar::Turn(float AxisValue) {
	TurnInput.X = AxisValue;
}

void Anewcar::Strafe(float AxisValue) {
	//StrafeInput.X = AxisValue;
}

void Anewcar::Jump() {
	if (OnTheGround) {
		JumpNextFrame = true;
	}
}
