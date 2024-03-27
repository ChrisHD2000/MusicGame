// Fill out your copyright notice in the Description page of Project Settings.


#include "AdministradorDeInstrumentos.h"
#include "Kismet/GameplayStatics.h"
#include "Instrumento.h"
#include "TimerManager.h"
// Sets default values
AAdministradorDeInstrumentos::AAdministradorDeInstrumentos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAdministradorDeInstrumentos::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAdministradorDeInstrumentos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("bloqueado? %s"), bBloqueado? TEXT("true") : TEXT("false"))
	
		CrearInstrumento();
		//bBloqueado = true; // se bloquea la aparicion de nuevos instrumentos por 2.0 segundos
		//GetWorldTimerManager().SetTimer(retardo, this, &AAdministradorDeInstrumentos::Desbloquear, 2.0f);
	
	
	
}

void AAdministradorDeInstrumentos::CrearInstrumento() {

	float variacionY = FMath::RandRange(-500.f, 500.f);
	FTransform SpawnTransform(FRotator(0.f, 0.f, 0.f),GetActorLocation()+FVector(0.f, variacionY,0.f));
	auto InstrumentoNuevo = Cast<AInstrumento>
	(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, InstrumentoClass, SpawnTransform));  //Spawnea un instrumento en el escenario
	
	if (!bBloqueado && InstrumentoNuevo != nullptr) { // cuando se desboquea
		
			InstrumentoNuevo->inicializar(id_instrumento, 400); // se llaman estos parametros del instrumento antes de su constructor
			UGameplayStatics::FinishSpawningActor(InstrumentoNuevo, SpawnTransform); // se termina de llamar al instrumento y se crea
			id_instrumento = FMath::RandRange(1, 7); // enseguida luego de crearse, se define el id del instrumento siguiente y la posicion donde aparece, ambos aleatoriamente
			//UE_LOG(LogTemp, Warning, TEXT("siguiente instrumento: %i"), id_instrumento);
			bBloqueado = true; // se bloquea la aparicion de nuevos instrumentos por 1.0 segundos
			GetWorldTimerManager().SetTimer(retardo, this, &AAdministradorDeInstrumentos::Desbloquear, 1.35f);
	
	}
	id_instrumento_actual = InstrumentoNuevo->id_instrumento;
}

void AAdministradorDeInstrumentos::Desbloquear() { // desbloquea la variable bBloqueado para que pueda generarse un nuevo instrumento 
	//id_instrumento = id_instrumentoSiguiente;
	bBloqueado = false;
}