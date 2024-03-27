// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AdministradorDeInstrumentos.generated.h"

UCLASS()
class JUEGOMUSICA_API AAdministradorDeInstrumentos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdministradorDeInstrumentos();
	UPROPERTY(EditDefaultsOnly, Category = Instrumento)
		TSubclassOf<class AInstrumento> InstrumentoClass;
	UPROPERTY(BlueprintReadWrite)
		int32 id_instrumento = 0;
	UPROPERTY(BlueprintReadWrite)
		int32 id_instrumento_actual = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle retardo; // variable que administra el tiempo
	float bBloqueado = false; // bloquea la aparicion de intrumentos por cierto tiempo
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CrearInstrumento();
	void Desbloquear(); // desbloquea el tiempo para que vuelva a aparecer otro instrumento
};
