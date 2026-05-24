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

> 💡외부 API 가져오기
> 
1. 중첩된 객체(Nested Object) 파싱 기법:
- JSON 안에 또 다른 { } 객체가 들어있을 때는 바로 값을 꺼낼 수 없습니다.
- TryGetObjectField("이름", 담을포인터)를 사용해서 내부 사물함을 먼저 통째로 꺼낸 다음, 그 안에서 값을 뽑아야 합니다. (실무 API는 대부분 이렇게 계층 구조로 되어 있습니다.)
2. 데이터 타입에 맞는 추출 함수 사용 (GetNumberField):
- 어제는 글자였기 때문에 GetStringField를 썼지만, 환율처럼 따옴표 없는 숫자 데이터는 GetNumberField()를 써야 합니다. 반환형은 double 입니다. 이외에도 GetBoolField(), GetArrayField() 등이 있습니다.
3. 안전한 파싱을 위한 방어적 프로그래밍 (Try 계열 함수):
- 만약 서버가 갑자기 양식을 바꿔서 "rates"라는 데이터가 안 오면 어떻게 될까요? 무작정 GetObjectField를 부르면 언리얼 엔진이 크래시(Crash)가 나며 꺼집니다.
- 이를 방지하기 위해 TryGetObjectField나 HasField("키이름")을 사용하여 "이 데이터가 진짜로 있는지" 먼저 검사하는 습관을 들여야 합니다.
---

> 💡외부 API 출처
> 
1. 전 세계 API 종합 마켓플레이스
- 가장 쉽고 빠르게 다양한 API를 검색해 볼 수 있는 일종의 'API 쇼핑몰'입니다.
- RapidAPI (Rapid): 세계 최대의 API 허브입니다. 날씨, 스포츠 데이터, 번역, 주식 등 온갖 카테고리의 API가 모여 있습니다. 가입 한 번으로 여러 회사의 API를 쉽게 테스트하고 결제까지 관리할 수 있어 개발자들이 가장 많이 찾는 곳입니다.
- GitHub 'Public APIs' 저장소: 구글이나 깃허브에 public-apis/public-apis라고 검색하면 나오는 아주 유명한 리포지토리입니다. 전 세계 개발자들이 무료로 쓸 수 있는 공개 API들을 주제별(동물 사진, 암호화폐, 애니메이션, 음악 등)로 꼼꼼하게 정리해 둔 거대한 리스트입니다.
2. 국내 공공 데이터 및 포털 서비스
- 한국의 현실 데이터를 게임이나 프로젝트에 연동하고 싶을 때 주로 찾습니다.
- 공공데이터포털 (data.go.kr): 정부가 제공하는 공식 데이터 허브입니다. 기상청의 날씨 특보, 실시간 버스/지하철 도착 정보, 전국 미세먼지 농도 등을 무료로 가져올 수 있습니다. (가입 후 활용 신청을 하면 API Key를 줍니다.)
- 네이버 / 카카오 개발자 센터: 네이버 Papago(AI 번역), 카카오맵, 네이버/카카오 로그인 연동 같은 대형 포털의 강력한 기능을 빌려 쓰고 싶을 때 사용합니다.
3. 게임 및 AI 특화 API (엔지니어 추천)
- 현재 진행 중이신 8주 AI 로드맵과 가장 밀접한 분야입니다.
- Hugging Face / OpenAI / Anthropic: 우리의 궁극적 목표는 언리얼 NNE로 AI 모델을 직접 돌리는 것이지만, 너무 무거운 연산(예: 초거대 LLM 챗봇, 실시간 이미지 생성)은 클라우드에 맡기고 결과만 가져와야 할 때가 있습니다. 이때 이 회사들이 제공하는 REST API를 호출해서 사용합니다.
- IGDB / RAWG: 전 세계 비디오 게임에 대한 방대한 정보(타이틀, 메타스코어, 표지 이미지, 장르 등)를 제공하는 가장 유명한 게임 DB API입니다.
---

> 💡외부 API 사용시 주의할점
> 
- 예시 주소: https://api.weather.com/v1/current?city=Seoul&units=metric
1. 베이스 URL (Base URL): https://api.weather.com
- 의미: "어느 회사의 서버로 갈 것인가?" (기상청 본사 주소)
- 변하지 않는 고정된 주소입니다.
2. 경로 (Path): /v1/current
- 의미: "그 회사에서 어떤 종류의 데이터를 원하는가?" (현재 날씨 부서)
- 폴더 경로처럼 /로 구분하며, 목적에 따라 /forecast(예보), /history(과거 기록) 등으로 바뀝니다. 앞서 환율 API에서 /KRW를 쓴 것도 경로를 통해 한국 원화 데이터를 요청한 것입니다.
3. 쿼리 파라미터 (Query Parameter): ?city=Seoul&units=metric
- 의미: "어떤 옵션을 걸어서 검색할 것인가?" (상세 조건)
- 물음표(?) 뒤에 붙으며, 키=값 형태로 적습니다. 여러 조건이 붙을 때는 & 기호로 연결합니다. (예: 도시는 서울이고, 단위는 미터법으로 줘!)

- 지금 4주차(W4)에서 배우는 HTTP 방식은 서버에 한 번 물어보고(Request->SetURL(...)) 한 번 답장을 받는 단발성 통신이기 때문에 http://나 https://로 시작하는 URL을 씁니다.
- 그런데 다음 주 5주차(W5)에 배울 'WebSocket(웹소켓)'은 게임처럼 서버와 계속 연결을 유지한 채 데이터를 실시간으로 주고받는 통신입니다. 재미있게도 웹소켓 역시 URL 형태를 가지지만, 앞부분이 http://가 아니라 ws:// 또는 wss:// 로 시작한다는 차이가 있습니다! (예: wss://game-server.com/room1)
---

> 💡HTTP POST 요청 구현(서버에 JSON 데이터 보내기)
> 
- GET 방식이 서버의 데이터를 "읽어오는(Read)" 것이라면, POST 방식은 내 데이터를 서버에 "쓰는(Write/Create)" 것입니다.
1. SetVerb("POST")로 통신 목적 바꾸기
- 우체국장에게 "이건 데이터를 달라는 편지가 아니라, 내 데이터를 등록해달라는 택배야!"라고 알려주는 역할입니다.
2. 직렬화 (Serialization)의 마법
- 어제는 서버가 준 '문자열(String)'을 언리얼이 이해하는 '사물함(FJsonObject)'으로 해독(Deserialize)했죠?
- 오늘은 반대입니다! 언리얼에서 만든 '사물함(FJsonObject)'을 인터넷 선을 타고 넘어갈 수 있게 '문자열(String)'로 압축(Serialize)해야 합니다.
3. SetContentAsString(...)로 본문 꽉 채우기
- 압축이 끝난 문자열을 편지 봉투의 본문(Body) 영역에 쑤셔 넣는 POST 통신의 핵심 함수입니다.
---

> 💡언리얼에서 외부 API 가져오기
> 
1. 역할 분담 (MVC 패턴 기초):
- C++ (Model/Controller): 무거운 통신, 복잡한 JSON 해독, 예외 처리를 담당.
- 블루프린트 (View): 넘겨받은 깔끔한 완성본 데이터를 화면에 예쁘게 배치하고 애니메이션을 넣는 것만 담당.
2. BlueprintImplementableEvent:
- C++에서는 함수 이름(명함)만 선언하고 구현부({ })는 작성하지 않습니다. 대신 블루프린트에서 빨간색 이벤트 노드로 나타나 구현을 대신하게 해주는 가장 중요한 통신 매크로입니다.
3. FString::Printf:
- 여러 가지 숫자(%d, %f)와 글자를 조합해서 하나의 예쁜 문장으로 조립할 때 쓰는 아주 유용한 C++ 문자열 포맷팅 함수입니다.
---

> 💡로딩 켜고 끄기
> 
1. 비동기 통신의 라이프사이클 (Lifecycle) 이해하기:
- 통신은 즉시 완료되는 것이 아니라 요청(Request) ➡️ 대기(Wait) ➡️ 응답(Response)의 시간을 거칩니다.
- 유저가 멈춘 화면을 보고 "게임이 뻗었나?" 오해하지 않도록, '대기'하는 동안 시각적 피드백(로딩 UI)을 주는 것이 클라이언트 프로그래머의 필수 소양입니다.
2. UI 상태 관리의 분리:
- C++은 로직의 흐름(지금 통신 중이다/아니다)만 bool 값으로 던져줍니다.
- 로딩 중일 때 기존 텍스트를 흐리게 할지, 빙글빙글 도는 이미지를 띄울지, 화면 전체를 어둡게 할지는 블루프린트(위젯)에서 시각적으로 결정하도록 역할을 명확히 나눕니다.
---