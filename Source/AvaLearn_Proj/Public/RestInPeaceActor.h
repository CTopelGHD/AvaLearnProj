// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"
#include "RestInPeaceActor.generated.h"

UCLASS()
class AVALEARN_PROJ_API ARestInPeaceActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARestInPeaceActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio2Face")
		FString Audio2FacePlayer = "/World/audio2face/Player";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio2Face")
		FString Audio2FaceFile = "E://restinpeace.usd";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio2Face")
		FString TrackName = "F://output-audio.wav";

	UFUNCTION(BlueprintCallable, Category = "RestInPeaceActor")
		void GetStatus();

	void OnStatusResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);



	UFUNCTION(BlueprintCallable, Category = "RestInPeaceActor")
		void GetAudio2FacePlayer();

	UFUNCTION(BlueprintCallable, Category = "RestInPeaceActor")
		void LoadFile();

	void OnLoadFileReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);


	void OnAudio2FacePlayerReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable, Category = "RestInPeaceActor")
		void SetTrack();

	void OnSetTrackReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable, Category = "RestInPeaceActor")
		void PlayTrack();

	void OnPlayTrackReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);



	UFUNCTION(BlueprintCallable, Category = "RestInPeaceActor")
		void PauseTrack();

	void OnPauseTrackReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

	UFUNCTION(BlueprintCallable, Category = "RestInPeaceActor")
		void RewindTrack();

	void OnRewindTrackReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};
