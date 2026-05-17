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