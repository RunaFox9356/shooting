//============================
//
// �Q�[����ʂ̃w�b�_�[
// Author:hamada ryuuga
//
//============================
#ifndef _GAME_H_		//���̃}�N������`����ĂȂ�������
#define _GAME_H_		//2�d�C���N���[�h�h�~�̃}�N����`

#include "object.h"


class CMagicBox;
class CParticleManager;
class CPlayer;

class CGame :public CObject
{
public:
	CGame();
	~CGame();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CMagicBox*GetMagicBox() { return m_MagicBox; };
	static CParticleManager* GetParticleManager() { return paticleManager; }
	static CPlayer * GetPlayer() { return m_Player; };
private:

	static CMagicBox* m_MagicBox;
	static CPlayer* m_Player;
	static CParticleManager* paticleManager;	// �p�[�e�B�N���}�l�W���[
	int m_GameCount;
	int m_SpeedUp;
};
#endif