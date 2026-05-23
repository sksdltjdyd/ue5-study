#include "MyHttpActor.h"
#include "HttpModule.h" // Http 모듈 사용
#include "Serialization/JsonReader.h" // Json 읽기
#include "Serialization/JsonSerializer.h" // Json 해독

AMyHttpActor::AMyHttpActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMyHttpActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 게임이 시작되자마자 서버에 요청을 보냅니다!
	// RequestUserData();
	// 공개환율 API 요청
	RequestExchangeRate();
	// 날씨정보 API 요청
	RequestWeatherInfo();
	// 점수를 서버로 보내는 함수 실행
	SendPlayerScore();
}

/*임의API 응답 처리 예시
// ----------------------------------------------------
// [편지 보내기] API 요청 함수
// ----------------------------------------------------
void AMyHttpActor::RequestUserData()
{
	// 1. 우체국(Http 모듈) 객체를 가져옵니다.
	FHttpModule* Http = &FHttpModule::Get();

	// 2. 빈 편지 봉투(Request)를 하나 만듭니다.
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	// 3. 편지가 도착하면(Complete) 'OnResponseReceived' 함수를 실행하라고 알려줍니다.
	Request->OnProcessRequestComplete().BindUObject(this, &AMyHttpActor::OnResponseReceived);

	// 4. 주소와 목적을 적습니다.
	// Request->SetURL("https://jsonplaceholder.typicode.com/users/1"); // 무료 더미 API 주소
	Request->SetURL("https://jsonplaceholder.typicode.com/users"); // users 전체 목록 요청
	Request->SetVerb("GET"); // "데이터를 가져오겠다"는 뜻

	// 4.5 헤더 추가
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");

	// 5. 발송!
	Request->ProcessRequest();
}
*/

/*데이터 수신 및 해독 예시
// ----------------------------------------------------
// [답장 받기] 데이터 수신 및 해독 함수
// ----------------------------------------------------
void AMyHttpActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// 서버가 잘 응답했는지(200번대 성공 코드) 확인합니다.
	if (bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		// 1. 서버가 보낸 편지의 본문(JSON 형태의 문자열)을 꺼냅니다.
		FString ResponseBody = Response->GetContentAsString();
	
		단일 유저 파싱 코드
		// 2. JSON 객체를 담을 빈 그릇을 준비합니다.
		TSharedPtr<FJsonObject> JsonObject;
		
		// 3. 문자열을 읽을 수 있는 돋보기(Reader)를 만듭니다.
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

		// 4. Deserialize: 문자열을 언리얼이 이해하는 FJsonObject로 번역(해독)합니다.
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
			{
			// 5. 빙고! JSON 안에서 "name"이라는 키(Key)를 가진 글자(String) 값을 뽑아냅니다.
			FString UserName = JsonObject->GetStringField("name");

			// 6. 언리얼 출력 로그에 결과 띄우기 (초록색 글씨)
			UE_LOG(LogTemp, Warning, TEXT("API에서 받아온 유저 이름: %s"), *UserName);
	
		
		// 유저 목록 파싱
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

		// 해독 및 반복문 처리
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			UE_LOG(LogTemp, Warning, TEXT("API에서 받아온 유저 수: %d"), JsonArray.Num());

			// 배열 안을 하나씩 들여다본다
			for (int32 i = 0; i < JsonArray.Num(); i++)
			{
				// 1. 배열의 각 칸을 사물함 형태로 연다
				TSharedPtr<FJsonObject> UserObject = JsonArray[i]->AsObject();

				if(UserObject.IsValid())
				{
					// 2. 사물함 안에서 "name"이라는 키를 가진 글자 값을 꺼낸다
					FString UserName = UserObject->GetStringField("name");
					FString UserEmail = UserObject->GetStringField("email");
					FString UserCity = UserObject->GetObjectField("address")->GetStringField("city");
					FString UserPhone = UserObject->GetStringField("phone");

					// 3. 결과 출력
					UE_LOG(LogTemp, Warning, TEXT("유저 %d 이름: %s, 이메일: %s, 도시: %s, 전화번호: %s"), i + 1, *UserName, *UserEmail, *UserCity, *UserPhone);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("유저 %d 데이터 파싱 실패!"), i + 1);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("API 요청 실패!"));
	}
}
*/

// 공개환율 API 호출
void AMyHttpActor::RequestExchangeRate()
{
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	// 콜백 함수 연결 (응답이 오면 실행될 함수)
	Request->OnProcessRequestComplete().BindUObject(this, &AMyHttpActor::OnExchangeRateReceived);

	// API 주소 설정 (KRW 기준 환율 정보 요청)
	Request->SetURL("https://open.er-api.com/v6/latest/KRW"); // 공개환율 API 주소
	Request->SetVerb("GET");

	// 헤더 세팅
	Request->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", "application/json");

	Request->ProcessRequest();
}

// JSON 파싱 및 데이터 출력
void AMyHttpActor::OnExchangeRateReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		FString ResponseBody = Response->GetContentAsString();

		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			// 언리얼 최신 버전에 맞춰 TEXT("문자열") 형태로 모두 감싸주기
			if (JsonObject->GetStringField(TEXT("result")) == TEXT("success"))
			{
				const TSharedPtr<FJsonObject>* RatesObject;
				if (JsonObject->TryGetObjectField(TEXT("rates"), RatesObject))
				{
					double UsdRate = (*RatesObject)->GetNumberField(TEXT("USD"));
					double JpyRate = (*RatesObject)->GetNumberField(TEXT("JPY"));

					double KrwPerUsd = 1.0 / UsdRate;
					double KrwPerJpy = 100.0 / JpyRate; 

					UE_LOG(LogTemp, Warning, TEXT("💸 오늘의 실시간 환율 정보 💸"));
					UE_LOG(LogTemp, Warning, TEXT("1 달러(USD) = %.2f 원"), KrwPerUsd);
					UE_LOG(LogTemp, Warning, TEXT("100 엔(JPY) = %.2f 원"), KrwPerJpy);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("환율 정보 가져오기 실패!"));
	}
}

// 날씨정보 API 요청 함수
void AMyHttpActor::RequestWeatherInfo(){
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	
	// 콜백 함수 연결 (응답이 오면 실행될 함수)
	Request->OnProcessRequestComplete().BindUObject(this, &AMyHttpActor::OnWeatherInfoReceived);

	// 1. 서울의 날씨를 요청하는 Open-Meteo API 주소 (? 뒤에 조건이 붙습니다)
	Request->SetURL(TEXT("https://api.open-meteo.com/v1/forecast?latitude=37.566&longitude=126.978&current_weather=true"));
	Request->SetVerb(TEXT("GET"));
	
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->ProcessRequest();
}

// 날씨정보 API 응답 처리 함수
void AMyHttpActor::OnWeatherInfoReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		FString ResponseBody = Response->GetContentAsString();

		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			// "current_weather"라는 이름의 내부 사물함(객체)을 통째로 꺼냅니다.
			const TSharedPtr<FJsonObject>* CurrentWeatherObj;
			if (JsonObject->TryGetObjectField(TEXT("current_weather"), CurrentWeatherObj))
			{
				// 내부 사물함에서 기온과 풍속 숫자를 꺼냅니다.
				double Temperature = (*CurrentWeatherObj)->GetNumberField(TEXT("temperature"));
				double WindSpeed = (*CurrentWeatherObj)->GetNumberField(TEXT("windspeed"));

				// 1. 데이터를 문자열로 조립
				FString ResultMsg = FString::Printf(TEXT("현재 서울 날씨 정보\n기온: %.1f 도 (섭씨)\n풍속: %.1f km/h"), Temperature, WindSpeed);

				//2. 블루프린트로 데이터 토스(언리얼 에디터에서 알림 받기)
				OnWeatherDataReady(ResultMsg);

				UE_LOG(LogTemp, Warning, TEXT("현재 서울 날씨 정보"));
				UE_LOG(LogTemp, Warning, TEXT("기온: %.1f 도 (섭씨)"), Temperature);
				UE_LOG(LogTemp, Warning, TEXT("풍속: %.1f km/h"), WindSpeed);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("날씨 정보 가져오기 실패!"));
	}
}

// HTTP POST 요청과 응답 처리 예시
void AMyHttpActor::SendPlayerScore()
{
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	// 콜백 함수 연결 (응답이 오면 실행될 함수)
	Request->OnProcessRequestComplete().BindUObject(this, &AMyHttpActor::OnPostResponseReceived);

	// API 주소 설정 (점수를 받을 수 있는 서버 주소로 변경)
	Request->SetURL(TEXT("https://webhook.site/9abcaad7-8537-4250-a122-21ff3e179af7")); // 점수 제출 API 주소
	Request->SetVerb(TEXT("POST")); //Get이 아니라 Post로 설정 (데이터를 보내겠다는 뜻)

	// 헤더 세팅
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json")); // JSON 형태로 보낼 거라고 알려주기

	// 보낼 데이터(JSON 형태로 작성)
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("player_name"), TEXT("PlayerOne")); // 닉네임 추가
	JsonObject->SetNumberField(TEXT("score"), 12345); // 점수 추가

	// 직렬화 (사물함 -> 문자열)
	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

// 서버가 잘 받았는지 확인
void AMyHttpActor::OnPostResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// POST 요청의 성공 응답 코드는 통상 200(OK) 또는 201(Created)입니다.
	if (bWasSuccessful && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		// 서버가 "네 데이터 잘 받았어! 이렇게 저장됐단다" 하고 돌려준 응답을 확인합니다.
		FString ResponseBody = Response->GetContentAsString();
		
		UE_LOG(LogTemp, Warning, TEXT("서버 전송 성공! 서버의 응답:"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ResponseBody);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("서버 전송 실패! 응답 코드: %d"), Response.IsValid() ? Response->GetResponseCode() : 0);
	}
}
