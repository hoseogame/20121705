#ifndef PLAYER_H_
#define PLAYER_H_

/*
	- Player.h -
		* Player Class
		* 캐릭터의 이동 및 충돌 검사
*/

class Player
{
public :
	void PlayerUpdate(int nKey );	// 입력 받은 키로 캐릭터 움직임
	void PlayerDraw();
	int GetMoveX();
	int GetMoveY();

private :
	int m_nCenterX, m_nCenterY;	// 캐릭터의 중간 좌표
	int m_nMoveX, m_nMoveY;		// 캐릭터의 실제 좌표
	int m_nX, m_nY;				// 실제 출력 시작되는 좌표


	char* m_pStrPlayer;			// ┗━●━┛
	const int PLAYER_LEN = 11;	// 캐릭터 길이

	void Init();				// 캐릭터 초기화
	void Release();				// 객체 사용 종료시 메모리 정리
	void DrawPositionSet();		// 그림 출력할 좌표 세팅

public:
	Player();
	~Player();
};

#endif /* PLAYER_H_ */