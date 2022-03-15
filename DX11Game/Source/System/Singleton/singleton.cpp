//=============================================================================
// singleton.cpp
//=============================================================================
// Author  ���� ���V
//=============================================================================

#include "singleton.h"

//=============================================================================
// 
// �������O���
// 
//=============================================================================
namespace 
{  
    // �ő�C���X�^���X����ݒ�
    constexpr int k_MaxInstanceSize = 256;
    // �r���I����p
    std::mutex g_Mutex;
    // �C���X�^���X���J�E���g�p�ϐ�
    int g_NumInstanceCnt = 0;
    // �C���X�^���X���i�[����z��
    CSingletonFinalizer::FinalizerFunc g_Instances[k_MaxInstanceSize]; 
}

//=============================================================================
// 
// �C���X�^���X���ݒ�
// 
//=============================================================================
void CSingletonFinalizer::addFinalizer(FinalizerFunc func)
{
    std::lock_guard<std::mutex> lock(g_Mutex);

    // �ő�ۗL���𒴂������O����
    assert(g_NumInstanceCnt < k_MaxInstanceSize);

     // �C���X�^���X��������
    g_Instances[g_NumInstanceCnt] = func;

    g_NumInstanceCnt++;
}

//=============================================================================
// 
// �C���X�^���X�j��
// 
//=============================================================================
void CSingletonFinalizer::finalize() 
{
    std::lock_guard<std::mutex> lock(g_Mutex);

    // �C���X�^���X��1���j�����Ă���
    for (int i = g_NumInstanceCnt - 1; i >= 0; --i) 
    {
        // �C���X�^���X�폜
        (*g_Instances[i])();     
        g_Instances[i] = nullptr;
    }
    // �C���X�^���X�������Z�b�g
    g_NumInstanceCnt = 0;
}