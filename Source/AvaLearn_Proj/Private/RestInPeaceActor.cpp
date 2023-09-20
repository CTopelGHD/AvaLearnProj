// Fill out your copyright notice in the Description page of Project Settings.

#include "RestInPeaceActor.h"
#include "Json.h"

// Sets default values
ARestInPeaceActor::ARestInPeaceActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARestInPeaceActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARestInPeaceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARestInPeaceActor::GetStatus()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &ARestInPeaceActor::OnStatusResponseReceived);
	Request->SetURL("http://localhost:8011/status");
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}

void ARestInPeaceActor::OnStatusResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	//TSharedPtr<FJsonObject> ResponseObj;
	//TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	//FJsonSerializer::Deserialize(Reader, ResponseObj);

	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *ResponseObj->GetStringField("title"));
	// UE_LOG(LogTemp, Display, TEXT("Title %s"), *ResponseObj->GetStringField("title"));

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *Response->GetContentAsString());
}


void ARestInPeaceActor::GetAudio2FacePlayer()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &ARestInPeaceActor::OnAudio2FacePlayerReceived);
	Request->SetURL("http://localhost:8011/A2F/Player/GetInstances");
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", "application/json");
	Request->ProcessRequest();
}

void ARestInPeaceActor::OnAudio2FacePlayerReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (FJsonSerializer::Deserialize(Reader, ResponseObj)) {

		TSharedPtr<FJsonObject> ResultObject;
		if (ResultObject = ResponseObj->GetObjectField("result"))
		{
			TArray<FString> RegularArray;

			if (ResultObject->TryGetStringArrayField("regular", RegularArray))
			{
				if (RegularArray.Num() > 0)
				{
					Audio2FacePlayer = RegularArray[0];
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Audio2FacePlayer);
				}
			}
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *ResponseObj->GetStringField("regular"));
}

void ARestInPeaceActor::LoadFile()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("file_name", Audio2FaceFile);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &ARestInPeaceActor::OnLoadFileReceived);
	Request->SetURL("http://localhost:8011/A2F/USD/Load");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void ARestInPeaceActor::OnLoadFileReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	//TSharedPtr<FJsonObject> ResponseObj;
	//TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	//FJsonSerializer::Deserialize(Reader, ResponseObj);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *ResponseObj->GetStringField("message"));

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, *Response->GetContentAsString());
}


void ARestInPeaceActor::SetTrack()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("a2f_player", Audio2FacePlayer);
	RequestObj->SetStringField("file_name", TrackName);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &ARestInPeaceActor::OnSetTrackReceived);
	Request->SetURL("http://localhost:8011/A2F/Player/SetTrack");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void ARestInPeaceActor::OnSetTrackReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	//TSharedPtr<FJsonObject> ResponseObj;
	//TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	//FJsonSerializer::Deserialize(Reader, ResponseObj);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *ResponseObj->GetStringField("message"));

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, *Response->GetContentAsString());
}

void ARestInPeaceActor::PlayTrack()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("a2f_player", Audio2FacePlayer);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &ARestInPeaceActor::OnPlayTrackReceived);
	Request->SetURL("http://localhost:8011/A2F/Player/Play");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void ARestInPeaceActor::OnPlayTrackReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	//TSharedPtr<FJsonObject> ResponseObj;
	//TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	//FJsonSerializer::Deserialize(Reader, ResponseObj);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *ResponseObj->GetStringField("message"));

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, *Response->GetContentAsString());
}

void ARestInPeaceActor::PauseTrack()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("a2f_player", Audio2FacePlayer);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &ARestInPeaceActor::OnPauseTrackReceived);
	Request->SetURL("http://localhost:8011/A2F/Player/Pause");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void ARestInPeaceActor::OnPauseTrackReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	//TSharedPtr<FJsonObject> ResponseObj;
	//TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	//FJsonSerializer::Deserialize(Reader, ResponseObj);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *ResponseObj->GetStringField("message"));
	// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *Response->GetContentAsString());
}

void ARestInPeaceActor::RewindTrack()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("a2f_player", Audio2FacePlayer);

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &ARestInPeaceActor::OnRewindTrackReceived);
	Request->SetURL("http://localhost:8011/A2F/Player/Rewind");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void ARestInPeaceActor::OnRewindTrackReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	//TSharedPtr<FJsonObject> ResponseObj;
	//TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	//FJsonSerializer::Deserialize(Reader, ResponseObj);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *ResponseObj->GetStringField("message"));

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *Response->GetContentAsString());
}