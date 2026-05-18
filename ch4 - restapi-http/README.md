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