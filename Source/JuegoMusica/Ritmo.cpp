// Fill out your copyright notice in the Description page of Project Settings.


#include "Ritmo.h"

// Sets default values
ARitmo::ARitmo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// tom1 --- 1
	// tom2 --- 2
	// caja --- 3
	// bombo --- 4
	// hihat --- 5
	// crash --- 6
	// ride --- 7
	facil = {2, 2, 3, 2, 2, 3, 6}; // orden para los instrumentos faciles
	UnisonoFacil = {false, false, false, false, false, false, false}; 
	medio = {5, 3, 7, 3, 6, 4}; //orden para los instrumentos medios
	UnisonoMedio = { false, false, false, false, false, true }; // true cuando debe ser unisono con el anterior
	dificil = { 6, 4, 7, 3, 4, 7, 4, 7, 3, 4, 3, 3, 1, 1, 3, 5 }; //orden para los instrumentos dificiles
	UnisonoDificil = { false , true, false, true, false, false, true, false, 
		               true, false, false, false, false, false, false, true };
}

// Called when the game starts or when spawned
void ARitmo::BeginPlay()
{
	Super::BeginPlay();
	if (dificultad == 1) {
	
		secuencia = facil;
			secuenciaUnisono = UnisonoFacil;
	}
	if (dificultad == 2) {

		secuencia = medio;
		secuenciaUnisono = UnisonoMedio;
	}
	if (dificultad == 3) {

		secuencia = dificil;
		secuenciaUnisono = UnisonoDificil;
	}
	idInstrumentoActual = secuencia[0];
}

// Called every frame
void ARitmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Hacer unisono: %i"), bHacerUnisono)
}

int ARitmo::getInstrumentoActual() {

	return idInstrumentoActual;
}

int ARitmo::getInstrumentoSiguiente()
{
	if (secuencia.IsValidIndex(i + 1)) {
		return secuencia[i + 1];
	}
	return 0;
}

void ARitmo::siguienteInstrumento()
{
	i++;
	if (secuencia.IsValidIndex(i)) {
		bEsUnisono = secuenciaUnisono[i];
		idInstrumentoActual = secuencia[i];
	}
	bHacerUnisono = false;
}

void ARitmo::IntercambiarInstrumento(int& siguiente, int& actual)
{
	int aux = siguiente;
	siguiente = actual;
	actual = aux;
}

void ARitmo::Intercambiar()
{
	IntercambiarInstrumento(secuencia[i+1], secuencia[i]);
}

bool ARitmo::bEsUnisonoElSiguiente()
{
	if (secuenciaUnisono.IsValidIndex(i + 1)) {
		return secuenciaUnisono[i+1];
	}
	return false;
}
