//=============================================================================
// singleton.h
//=============================================================================
// Author  ���� ���V
//=============================================================================
#pragma once

#include <cassert>
#include <mutex>

//=============================================================================
// 
// �N���X��`
// 
//=============================================================================
// �C���X�^���X�j���N���X
class CSingletonFinalizer
{
public:
    // �f���[�g�p�ėp�|�C���^
    using FinalizerFunc = void(*)();
    // �C���X�^���X���J�E���g�p
    static void addFinalizer(FinalizerFunc func); 
    // �C���X�^���X�j��
    static void finalize();
};

// �V���O���g���N���X
template <typename T>

class CSingleton
{
public:
    //�I�u�W�F�N�g�̃C���X�^���X�͂����ɂɂ������݂��Ȃ�
    static T& GetInstance()
    {
        // �C���X�^���X�����͂P�x����
        if (!Instance)  Create();
        return *Instance;
    }

private:
    // �C���X�^���X����
    static void Create()
    {
        Instance = new T;

        // �C���X�^���X�����J�E���g
        CSingletonFinalizer::addFinalizer(&CSingleton<T>::Destroy);
    }

    // �C���X�^���X�폜
    static void Destroy() 
    {
        delete Instance;
        Instance = nullptr;
    }

private:
    static T* Instance;

protected:
    // �R���X�g���N�^�̎g�p���O������֎~����
    CSingleton() = default;
    CSingleton(const CSingleton&) = delete;
    CSingleton& operator=(const CSingleton&) = delete;
    CSingleton(CSingleton&&) = delete;
    CSingleton& operator=(CSingleton&&) = delete;
};

// �ÓI�����o
template <typename T> T* CSingleton<T>::Instance = nullptr;