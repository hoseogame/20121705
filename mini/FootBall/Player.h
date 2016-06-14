#ifndef PLAYER_H_
#define PLAYER_H_

/*
	- Player.h -
		* Player Class
		* ĳ������ �̵� �� �浹 �˻�
*/

class Player
{
public :
	void PlayerUpdate(int nKey );	// �Է� ���� Ű�� ĳ���� ������
	void PlayerDraw();
	int GetMoveX();
	int GetMoveY();

private :
	int m_nCenterX, m_nCenterY;	// ĳ������ �߰� ��ǥ
	int m_nMoveX, m_nMoveY;		// ĳ������ ���� ��ǥ
	int m_nX, m_nY;				// ���� ��� ���۵Ǵ� ��ǥ


	char* m_pStrPlayer;			// �����ܦ���
	const int PLAYER_LEN = 11;	// ĳ���� ����

	void Init();				// ĳ���� �ʱ�ȭ
	void Release();				// ��ü ��� ����� �޸� ����
	void DrawPositionSet();		// �׸� ����� ��ǥ ����

public:
	Player();
	~Player();
};

#endif /* PLAYER_H_ */