//=============================================================================
//
// �����_���[
// Author : �l�c����
//
//=============================================================================


#ifndef _MANEAGER_H_			// ���̃}�N����`������ĂȂ�������
#define _MANEAGER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"

class CRenderer;
class CInput;
class CTexture;
class CMagicBox;
class CObject;
class CResult;
class CTitle;


class CManager
{
public:

	//���(���[�h)�̎��
	enum MODE
	{
		MODE_TITLE = 0,		//�^�C�g�����
		MODE_GAME,			//�Q�[�����
		MODE_RESULT,		//���U���g���
		MODE_FADE,			//�t�F�[�h���
		MODE_RANKING,		//�����L���O���
		MODE_GAMEOVER,
		MODE_TUTORIAL,
		MODE_MAX
	};

	CManager();
	~CManager();
	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	static CRenderer *GetRenderer();
	static CTexture* GetTexture();	// �e�N�X�`���̏��̎擾
	static CMagicBox*GetMagicBox();
	static void SetMode(CManager::MODE mode);


private:
	static CTexture *m_pTexture;
	static CRenderer * m_cRenderer;
	CInput *m_Input;
	static CMagicBox* m_MagicBox;

	static CObject*m_Game;
	
	MODE m_mode;

};



#endif
