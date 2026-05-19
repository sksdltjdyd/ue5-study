# CH4 공부노트

> 💡필수 개념
> 
1. REST API (Representational State Transfer API):
- 클라이언트(언리얼 엔진)와 서버가 인터넷을 통해 데이터를 주고받기 위한 일종의 메뉴판이자 규칙
2. GET vs POST (통신 방식):
- GET (읽기): 서버에서 데이터를 가져올 때 사용 (예: 서버에서 플레이어의 랭킹 정보나 글로벌 날씨 데이터 불러오기)
- POST (쓰기/생성): 서버로 데이터를 보낼 때 사용 (예: 유저의 로그인 정보나 스테이지 클리어 기록을 서버로 전송하기)
- JSON (JavaScript Object Notation): 클라이언트와 서버가 데이터를 주고받을 때 사용하는 세계 공통어 { "Level": 5, "UserName": "Player1" } 처럼 키(Key)와 값(Value)으로 이루어져 있어 사람이 읽기 쉽고 언리얼 C++에서 파싱하기도 좋다
---

> 💡언리얼 세팅
> 
1. 프로젝트 통신 허가증 발급: Build.cs 세팅. 언리얼은 기본적으로 게임 엔진이라, 외부 인터넷과 통신하거나 JSON이라는 데이터를 읽는 기능이 기본 상태에서는 꺼져 있다. 이걸 켜주는 작업이 가장 먼저 필요
- 어떻게 하나요?: 프로젝트 폴더 내의 (프로젝트명).Build.cs 파일을 연다
- PublicDependencyModuleNames 목록에 "Http", "Json", "JsonUtilities" 이 세 가지 단어를 추가
- 선생님의 비유: "우리 게임이 외부 우체국(Http)을 이용할 거고, 외계어(Json)를 번역할 수 있는 사전(JsonUtilities)을 프로젝트에 챙길게!" 라고 엔진에게 허락을 받는 과정
2. C++로 편지(Request) 써서 보내기. 우리가 어제 Postman에서 URL을 적고 'Send' 버튼을 눌렀던 행동을 C++ 코드로 똑같이 작성
- 요청 객체 만들기: FHttpModule::Get().CreateRequest()를 통해 빈 편지 봉투를 하나 만든다
- 주소 적기: Request->SetURL("API 주소")로 우리가 원하는 REST API 주소를 적어줌
- 요청 방식 정하기: 데이터를 달라고 하는 것이니 Request->SetVerb("GET")을 설정
- 발송!: Request->ProcessRequest()를 호출하면 우체부(언리얼)가 서버로 편지를 배달
3. 답장(Response)이 오면 포장지(JSON) 뜯기. 서버에서 데이터를 보내주면, 우리는 그걸 언리얼이 이해할 수 있게 해독(Parsing)해야 한다. 이 튜토리얼에서는 엄청나게 긴 위성 데이터가 JSON 형태로 날아온다
- 비동기 콜백(Callback): 편지가 언제 도착할지 모르기 때문에, "답장이 오면 이 함수(람다 혹은 바인딩된 함수)를 실행해 줘!" 라고 미리 지정
- 해독기 켜기: 서버가 준 JSON 텍스트를 TJsonReader라는 돋보기로 읽고, FJsonSerializer::Deserialize를 통해 C++ 객체(FJsonObject)로 변환
- 데이터 쏙쏙 뽑기: 데이터가 배열(Array)이라면 루프를 돌면서 GetStringField("이름")이나 GetNumberField("위치") 함수를 써서 알맹이 데이터만 가져와 내 게임 액터의 위치나 UI에 반영
---

> 💡Http 모듈 추가 핵심 개념
> 
1. HTTP 헤더(Header): "우리의 정체를 밝히고 요구사항 전달하기"
- 서버는 하루에도 수만 건의 요청을 받습니다. 이때 헤더 없이 무작정 "데이터 줘!"라고 하면 무시당하기 십상입니다.
- SetHeader("Content-Type", "application/json"): 서버에게 "우리가 주고받을 데이터 포맷은 JSON이야"라고 명확히 합의하는 과정입니다.
- SetHeader("User-Agent", "X-UnrealEngine-Agent"): "나는 크롬 브라우저가 아니라 언리얼 엔진이야"라고 신분을 밝히는 것입니다. 공개 API 중에서는 User-Agent가 없으면 악성 봇으로 간주하고 차단하는 곳이 많으므로 습관화하는 것이 좋습니다.
2. FJsonObject vs FJsonValue: "JSON의 껍데기와 알맹이"
- 언리얼 C++에서 JSON을 다룰 때 가장 헷갈리는 두 가지 타입입니다.
- FJsonObject (객체): 중괄호 { } 로 묶인 덩어리입니다. 열쇠(Key)를 주면 자물쇠를 열어 값(Value)을 꺼낼 수 있는 '사물함'이라고 생각하시면 됩니다. (예: GetStringField("name"))
- FJsonValue (값): 그 사물함 안에 들어있는 '알맹이 하나'입니다. 이 알맹이는 숫자일 수도, 글자일 수도, 심지어 또 다른 사물함(FJsonObject)일 수도 있습니다. 배열(Array) 안에는 항상 이 FJsonValue들이 일렬로 들어있습니다.
3. 배열(Array) 파싱의 함정 주의 (★가장 중요)
- 영상에 나오는 강사님의 개인 서버 API와 우리가 테스트할 무료 API(jsonplaceholder)는 구조가 살짝 다릅니다! 이 차이를 아는 것이 진짜 실력입니다.
- 영상 속 서버 응답: { "users": [ {..}, {..} ] }
- 제일 바깥이 중괄호 {} 이므로 먼저 FJsonObject로 해독한 뒤, GetArrayField("users")를 써서 안쪽에 있는 배열을 꺼냅니다.
- 우리가 테스트할 API 응답 (.../users): [ {..}, {..}, {..} ]
- 제일 바깥이 대괄호 [] 로 시작하는 순수 배열입니다. 이럴 때는 FJsonObject 그릇이 아니라, 처음부터 TArray<TSharedPtr<FJsonValue>> 라는 배열 그릇에 담아 해독해야 합니다.
---

> 💡Http 모듈 핵심 내장 함수
> 
- 편지 봉투를 꾸미고 발송할 때 (IHttpRequest 객체)
- 우리가 서버에 무언가를 요구할 때(Request) 사용하는 함수들입니다.

1. SetURL(const FString& URL)
- 역할: 편지가 도착할 목적지 주소를 적습니다.
- 사용 예: Request->SetURL("https://api.weather.com/...");
2. SetVerb(const FString& Verb)
- 역할: 통신의 목적(방식)을 정합니다. 데이터를 가져올 거면 "GET", 데이터를 보낼 거면 "POST"를 씁니다.
- 사용 예: Request->SetVerb("GET");
3. SetHeader(const FString& HeaderName, const FString& HeaderValue)
- 역할: 봉투 겉면에 추가 정보(규칙, 신분증 등)를 적습니다.
- 사용 예: Request->SetHeader("Content-Type", "application/json"); (우린 JSON으로 대화할 거야!)
4. SetContentAsString(const FString& ContentString) 🔥 (금요일 핵심 스포일러)
- 역할: GET(읽기)이 아니라 POST(쓰기) 방식을 쓸 때, 서버에 보낼 내 데이터(예: 로그인 ID/PW)를 편지 본문에 꽉꽉 채워 넣는 함수입니다.
5. OnProcessRequestComplete().BindUObject(...)
- 역할: 답장이 도착했을 때 어떤 함수를 실행해서 알림을 받을지(콜백) 연결해 줍니다.
6. ProcessRequest()
- 역할: 다 쓴 편지를 우체통에 쏙 넣고 실제로 발송합니다. 이 함수를 안 부르면 통신이 아예 시작되지 않습니다!

2. 서버에서 온 답장을 뜯어볼 때 (IHttpResponse 객체)
- 서버가 통신을 마치고 우리에게 결과물(Response)을 돌려주었을 때 꺼내 쓰는 함수들입니다.
1. GetResponseCode()
- 역할: 서버가 돌려준 상태 번호(HTTP Status Code)를 확인합니다.
- 사용 예: 200이 나오면 성공, 404가 나오면 주소 틀림(Not Found), 500이 나오면 서버 터짐(서버 에러)을 의미합니다.
2. GetContentAsString()
- 역할: 서버가 보내준 데이터의 알맹이(주로 JSON 문자열)를 꺼냅니다. 이걸 꺼내서 우리가 오늘 했던 것처럼 FJsonSerializer로 해독하게 됩니다.
3. GetHeader(const FString& HeaderName)
- 역할: 우리가 보낼 때 헤더를 썼던 것처럼, 서버도 우리에게 여러 가지 정보(데이터 용량, 서버 시간 등)를 헤더에 담아 보냅니다. 그중 특정 정보만 쏙 뽑아 읽을 때 씁니다.
---