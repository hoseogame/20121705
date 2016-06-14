#ifndef EFFECT_H_
#define EFFECT_H_

/*
	- Effect.h -
		* Effect Class
		* 이펙트를 관리함
*/
#include <time.h>

class Effect
{
public:
	bool EffectUpdate( clock_t curTime );
	void EffectDraw( int x, int y );

	clock_t GetStartTime() { return m_startTime; };
	clock_t GetStayTime() { return m_stayTime; };

	void SetStartTime( clock_t time ) { m_startTime = time; };
	//void SetStayTime( clock_t time ) { m_stayTime = time; };


private :
	bool m_bEffectOn;

	clock_t m_startTime;	// 효과 발생 시간
	clock_t m_stayTime;		// 효과 지속 시간

public :
	Effect() : m_bEffectOn( false ),m_stayTime( 2000 ) {};
};

#endif /* EFFECT_H_ */