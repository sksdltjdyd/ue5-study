import asyncio
import websockets
import json
import random

async def send_random_data(websocket): # 최신 websockets 라이브러리 문법 적용
    print("✅ 언리얼 엔진 클라이언트 접속 완료!")
    try:
        while True:
            # 1. 랜덤한 X, Y, Z, R, G, B 값을 딕셔너리로 생성
            data_dict = {
                "X": random.uniform(-300.0, 300.0), # X 좌표 (앞뒤)
                "Y": random.uniform(-300.0, 300.0), # Y 좌표 (좌우)
                "Z": random.uniform(50.0, 300.0),   # Z 좌표 (높이)
                "R": random.uniform(0.0, 1.0),      # 빨강 (0~1)
                "G": random.uniform(0.0, 1.0),      # 초록 (0~1)
                "B": random.uniform(0.0, 1.0)       # 파랑 (0~1)
            }
            
            # 2. 딕셔너리를 JSON 문자열(Text)로 직렬화
            json_message = json.dumps(data_dict)
            
            # 3. 언리얼 엔진으로 데이터 발사!
            await websocket.send(json_message)
            print(f"전송한 데이터: {json_message}")
            
            # 2초 대기 후 다시 전송 (무한 반복)
            await asyncio.sleep(2)
            
    except websockets.exceptions.ConnectionClosed:
        print("❌ 언리얼 엔진과 연결이 끊어졌습니다.")

async def main():
    print("🚀 웹소켓 서버를 시작합니다... (ws://127.0.0.1:8080)")
    # 포트 8080번을 열고 언리얼 엔진의 접속을 기다림
    async with websockets.serve(send_random_data, "127.0.0.1", 8080):
        await asyncio.Future()  # 영원히 실행

if __name__ == "__main__":
    asyncio.run(main())