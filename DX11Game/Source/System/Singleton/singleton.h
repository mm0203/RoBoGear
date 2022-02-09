//=============================================================================
// singleton.h
//=============================================================================
// Author  松野 将之
//=============================================================================
#pragma once

#include <cassert>
#include <mutex>

//=============================================================================
// 
// クラス定義
// 
//=============================================================================
// インスタンス破棄クラス
class SingletonFinalizer
{
public:
    // デリート用汎用ポインタ
    using FinalizerFunc = void(*)();
    // インスタンス数カウント用
    static void addFinalizer(FinalizerFunc func); 
    // インスタンス破棄
    static void finalize();
};

// シングルトンクラス
template <typename T>
class Singleton
{
public:
    //オブジェクトのインスタンスはここににしか存在しない
    static T& GetInstance()
    {
        // インスタンス生成は１度だけ
        if (!Instance)  Create();
        return *Instance;
    }

private:
    // インスタンス生成
    static void Create()
    {
        Instance = new T;

        // インスタンス数をカウント
        SingletonFinalizer::addFinalizer(&Singleton<T>::Destroy);
    }

    // インスタンス削除
    static void Destroy() 
    {
        delete Instance;
        Instance = nullptr;
    }

private:
    static T* Instance;

protected:
    // コンストラクタの使用を外部から禁止する
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

// 静的メンバ
template <typename T> T* Singleton<T>::Instance = nullptr;