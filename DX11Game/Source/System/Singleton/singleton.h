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
class SingletonFinalizer
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
class Singleton
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
        SingletonFinalizer::addFinalizer(&Singleton<T>::Destroy);
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
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

// �ÓI�����o
template <typename T> T* Singleton<T>::Instance = nullptr;