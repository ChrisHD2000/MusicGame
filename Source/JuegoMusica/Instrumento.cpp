// Fill out your copyright notice in the Description page of Project Settings.


#include "Instrumento.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Ritmo.h"
#include "JuegoMusicaCharacter.h"
// Sets default values
AInstrumento::AInstrumento()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MallaInstrumento = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	MallaInstrumento->SetMobility(EComponentMobility::Movable);
	MallaInstrumento->SetWorldScale3D(0.25f*FVector(1.f,1.f,1.f));
	RootComponent = MallaInstrumento;

	ritmo = Cast<ARitmo>(UGameplayStatics::GetActorOfClass(this, ARitmo::StaticClass()));
	


	// Carga la malla 3D del tom1
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tom1Mesh(TEXT("/Game/Assets3D/Tom1.Tom1"));
	if (Tom1Mesh.Succeeded()) {
		Tom1 = Tom1Mesh.Object;
	}



	// Carga la malla 3D del tom2
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tom2Mesh(TEXT("/Game/Assets3D/Tom2.Tom2"));
	if (Tom2Mesh.Succeeded()) {
		Tom2 = Tom2Mesh.Object;
	}


	// Carga la malla 3D de la caja
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CajaMesh(TEXT("/Game/Assets3D/Caja.Caja"));
	if (CajaMesh.Succeeded()) {
		Caja = CajaMesh.Object;
	}



	// Carga la malla 3D del bombo
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BomboMesh(TEXT("/Game/Assets3D/Bombo.Bombo"));
	if (BomboMesh.Succeeded()) {
		Bombo = BomboMesh.Object;
	}



	// Carga la malla 3D del Hi-hat
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Hi_HatMesh(TEXT("/Game/Assets3D/Hihat.Hihat"));
	if (Hi_HatMesh.Succeeded()) {
		Hi_hat = Hi_HatMesh.Object;
	}


	// Carga la malla 3D del platillo
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatilloMesh(TEXT("/Game/Assets3D/Platillo.Platillo"));
	if (PlatilloMesh.Succeeded()) {
		Platillo = PlatilloMesh.Object;
	}



	// Carga la malla 3D del Ride
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RideMesh(TEXT("/Game/Assets3D/Ride.Ride"));
	if (RideMesh.Succeeded()) {
		Ride = RideMesh.Object;
	}



	// Personaliza la esfera de detecciond e colision
	Colision = CreateDefaultSubobject<USphereComponent>(TEXT("EsferaDeColision"));
	Colision->SetupAttachment(RootComponent);
	Colision->SetSphereRadius(50.f);

	Colision->OnComponentBeginOverlap.AddDynamic(this, &AInstrumento::OverlapJugador);
}

void AInstrumento::inicializar(int idInstrumento, float VelocidadValor) {
	this->id_instrumento = idInstrumento;
	this->velocidad = VelocidadValor;

}

// Called when the game starts or when spawned
void AInstrumento::BeginPlay()
{
	Super::BeginPlay();

	// Eligue la malla del instrumento
	ElegirMallaInstrumento();


	
}

// Called every frame
void AInstrumento::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Caer(DeltaTime);
	FRotator rotNueva = GetActorRotation();
	rotNueva +=  FRotator(0.f, DeltaTime * 100.f,0.f);
	SetActorRotation(rotNueva);
	if (GetActorLocation().Z < 100.f) {
		seDestruye = true;
		Destroy();
	}
	
}

void AInstrumento::Caer(float DeltaTime) {
	// mueve al objeto en direccion vertical
	FVector Posicion = GetActorLocation();
	FVector Direccion = FVector(0.f, 0.f, -1.f);
	Posicion += Direccion * velocidad * DeltaTime;
	SetActorLocation(Posicion);
}

void AInstrumento::ElegirMallaInstrumento() {
	//elige el instrumento segun el id_instrumento y su respectivo sonido
	if (id_instrumento == 1) {
		MallaInstrumento->SetStaticMesh(Tom1);
		
		nombre = "Tom1";
	}
	if (id_instrumento == 2) {
		MallaInstrumento->SetStaticMesh(Tom2);
		
		nombre = "Tom2";
	}
	if (id_instrumento == 3) {
		MallaInstrumento->SetStaticMesh(Caja);
		
		nombre = "Caja";
	}
	if (id_instrumento == 4) {
		MallaInstrumento->SetStaticMesh(Bombo);
		
		nombre = "Bombo";
	}
	if (id_instrumento == 5) {
		MallaInstrumento->SetStaticMesh(Hi_hat);
		
		nombre = "Hi_hat";
	}
	if (id_instrumento == 6) {
		MallaInstrumento->SetStaticMesh(Platillo);
		
		nombre = "Platillo";
	}
	if (id_instrumento == 7) {
		MallaInstrumento->SetStaticMesh(Ride);
	
		MallaInstrumento->SetWorldScale3D( 0.65f*MallaInstrumento->GetRelativeScale3D());
		nombre = "Ride";
	}

}

int AInstrumento::getIdInstrumento() {
	return id_instrumento; //retorna el id del instrumento
}

void AInstrumento::OverlapJugador(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor) {
	
		if (this->id_instrumento == ritmo->getInstrumentoActual() && ritmo->bEsUnisono == ritmo->bHacerUnisono) {
			this->bEsCorrecto = true;
		}
		if (this->id_instrumento == ritmo->getInstrumentoSiguiente() && ritmo->bEsUnisonoElSiguiente()) {
			ritmo->Intercambiar();
			this->bEsCorrecto = true;
		}

		if (id_instrumento == 1) {
			UE_LOG(LogTemp, Warning, TEXT("Tom1"))
				UGameplayStatics::PlaySound2D(this, tom1SoundBase);
		}
		if (id_instrumento == 2) {
			UE_LOG(LogTemp, Warning, TEXT("Tom2"))
				UGameplayStatics::PlaySound2D(this, tom2SoundBase);
		}
		if (id_instrumento == 3) {
			UE_LOG(LogTemp, Warning, TEXT("Caja"))
				UGameplayStatics::PlaySound2D(this, cajaSoundBase);
		}
		if (id_instrumento == 4) {
			UE_LOG(LogTemp, Warning, TEXT("Bombo"))
				UGameplayStatics::PlaySound2D(this, bomboSoundBase);
		}
		if (id_instrumento == 5) {
			UE_LOG(LogTemp, Warning, TEXT("Hi_hat"))
				UGameplayStatics::PlaySound2D(this, hihatSoundBase);
		}
		if (id_instrumento == 6) {
			UE_LOG(LogTemp, Warning, TEXT("Platillo"))
				UGameplayStatics::PlaySound2D(this, platilloSoundBase);
		}
		if (id_instrumento == 7) {
			UE_LOG(LogTemp, Warning, TEXT("Ride"))
				UGameplayStatics::PlaySound2D(this, rideSoundBase);
		}
		if (bEsCorrecto) {
			UE_LOG(LogTemp, Warning, TEXT("Correcto"))			
			ritmo->siguienteInstrumento();
		}
		if (!bEsCorrecto && id_instrumento!=0) {
			UE_LOG(LogTemp, Warning, TEXT("Incorrecto"))
			AJuegoMusicaCharacter* personaje = Cast<AJuegoMusicaCharacter>(OtherActor);
			personaje->perderVida();
			UE_LOG(LogTemp, Warning, TEXT("VIDAS: %i"), personaje->vidas)
		}
		Destroy(); // se destruye el instrumento cada vez que choca con el actor
	}

}