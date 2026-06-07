#pragma once
#include "DrawDebugHelpers.h" // 디버그 도우미 헤더 파일 포함

// 디버그 그리기 매크로 정의
#define DRAW_SPHERE(Location, Color) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 30, Color, true, 30.f);
#define DRAW_SPHERE_SINGLE_FRAME(Location, Color) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 30, Color, false, -1.f);
#define DRAW_LINE(Start, End, Color) if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, Color, true, -1.f, 0, 1.f);
#define DRAW_LINE_SINGLE_FRAME(Start, End, Color) if(GetWorld()) DrawDebugLine(GetWorld(), Start, End, Color, false, -1.f, 0, 1.f);
#define DRAW_POINT(Location, Color) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, Color, true);
#define DRAW_POINT_SINGLE_FRAME(Location, Color) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, Color, false, -1.f);
#define DRAW_ARROW(Start, End, Color) if(GetWorld()) DrawDebugDirectionalArrow(GetWorld(), Start, End, 50.f, Color, true, -1.f, 0, 4.f);
#define DRAW_VECTOR(Start, End, Color) if(GetWorld()) \
{ \
    DrawDebugLine(GetWorld(), Start, End, Color, true, -1.f, 0, 1.f); \
    DrawDebugPoint(GetWorld(), End, 15.f, Color, true); \
}
#define DRAW_VECTOR_SINGLE_FRAME(Start, End, Color) if(GetWorld()) \
{ \
    DrawDebugLine(GetWorld(), Start, End, Color, false, -1.f, 0, 1.f); \
    DrawDebugPoint(GetWorld(), End, 15.f, Color, false, -1.f); \
}

