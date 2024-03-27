// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ritmo.generated.h"

UCLASS()
class JUEGOMUSICA_API ARitmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARitmo();
	UPROPERTY(EditAnywhere)
	int idInstrumentoActual; // id del instrumento que es el correcto 
	UPROPERTY(EditAnywhere)
	int idInstrumentoSiguiente; // id del siguiente instrumento correcto 
	UPROPERTY(EditAnywhere)
	int dificultad = 2; // numero que define la dificultad 
	UFUNCTION()
	int getInstrumentoActual(); // obtiene el id del instrumento actual 
	UFUNCTION()
	int getInstrumentoSiguiente(); // obtiene el id del isntrumento siguiente si existe
	UFUNCTION()
	void siguienteInstrumento(); // obtiene el siguiente instrumento una vez tocado el correcto o la secuencia correcta
	UFUNCTION()
	void IntercambiarInstrumento(int& siguiente, int& actual);
	UFUNCTION()
		void Intercambiar();
	UFUNCTION()
	bool bEsUnisonoElSiguiente(); // depende si el siguiente instrumento es unisono
	UPROPERTY(BlueprintReadOnly)
	int i = 0; // contador para recorrer el arreglo secuencia del ritmo 


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHacerUnisono = false; // esta variable cambia a true cuando se aplasta el boton de unisono
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEsUnisono = false; // Verdadero o falso, dependerá del arreglo secuenciaUnisono

	


	TArray<int32> facil;
	TArray<bool> UnisonoFacil;
	TArray<int32> medio;
	TArray<bool> UnisonoMedio;
	TArray<int32> dificil;
	TArray<bool> UnisonoDificil;

	UPROPERTY(BlueprintReadOnly)
	TArray<int32> secuencia;
	TArray<bool> secuenciaUnisono;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
